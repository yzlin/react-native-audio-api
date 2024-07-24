/* eslint-disable react/react-in-jsx-scope */
import { Button, StyleSheet, Text, View } from 'react-native';
import { useRef, useState, useEffect } from 'react';
import { Slider } from '@miblanchard/react-native-slider';

import {
  AudioContext,
  type Oscillator,
  type Gain,
} from 'react-native-audio-context';

const App = () => {
  const [isPlaying, setIsPlaying] = useState<boolean>(false);
  const [gain, setGain] = useState<number>(1.0);
  const [frequency, setFrequency] = useState<number>(440);
  const [detune, setDetune] = useState<number>(0);

  const audioContextRef = useRef<AudioContext | null>(null);
  const oscillatorRef = useRef<Oscillator | null>(null);
  const gainRef = useRef<Gain | null>(null);

  const setUp = () => {
    audioContextRef.current = new AudioContext();

    oscillatorRef.current = audioContextRef.current.createOscillator();
    oscillatorRef.current.frequency = frequency;
    oscillatorRef.current.detune = detune;
    oscillatorRef.current.type = 'sine';

    gainRef.current = audioContextRef.current.createGain();
    gainRef.current.gain = gain;

    const destination = audioContextRef.current.destination;
    oscillatorRef.current.connect(gainRef.current);
    gainRef.current.connect(destination);
  };

  const handleSliderChange = (
    value: number[],
    defaultValue: number,
    setValue: (value: number) => void,
    ref: React.MutableRefObject<{ [key: string]: any } | null>,
    propName: string
  ) => {
    const newValue = value[0] || defaultValue;
    setValue(newValue);
    if (ref.current) {
      ref.current[propName] = newValue;
    }
  };

  useEffect(() => {
    return () => {
      oscillatorRef.current?.stop(0);
    };
  }, []);

  const handlePlayPause = () => {
    if (!audioContextRef.current) {
      setUp();
    }

    if (isPlaying) {
      oscillatorRef.current?.stop(0);
    } else {
      oscillatorRef.current?.start(0);
    }

    setIsPlaying(!isPlaying);
  };

  return (
    <View style={styles.mainContainer}>
      <Text style={styles.title}>React Native Oscillator</Text>
      <View style={styles.button}>
        <Button
          title={isPlaying ? 'Pause' : 'Play'}
          onPress={handlePlayPause}
        />
      </View>
      <View style={styles.container}>
        <Text>Gain: {gain.toFixed(1)}</Text>
        <Slider
          containerStyle={styles.slider}
          value={gain}
          onValueChange={(value) =>
            handleSliderChange(value, 0.0, setGain, gainRef, 'gain')
          }
          minimumValue={0.0}
          maximumValue={1.0}
          step={0.1}
        />
      </View>
      <View style={styles.container}>
        <Text>Frequency: {frequency.toFixed(0)}</Text>
        <Slider
          containerStyle={styles.slider}
          value={frequency}
          onValueChange={(value) =>
            handleSliderChange(
              value,
              440,
              setFrequency,
              oscillatorRef,
              'frequency'
            )
          }
          minimumValue={120}
          maximumValue={1200}
          step={10}
        />
      </View>
      <View style={styles.container}>
        <Text>Detune: {detune.toFixed(0)}</Text>
        <Slider
          containerStyle={styles.slider}
          value={detune}
          onValueChange={(value) =>
            handleSliderChange(value, 0, setDetune, oscillatorRef, 'detune')
          }
          minimumValue={0}
          maximumValue={100}
          step={1}
        />
      </View>
    </View>
  );
};

const styles = StyleSheet.create({
  mainContainer: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#F5FCFF',
  },
  container: {
    justifyContent: 'center',
    alignItems: 'center',
    margin: 10,
  },
  title: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  },
  button: {
    width: 100,
  },
  slider: {
    width: 300,
    padding: 10,
  },
});

export default App;

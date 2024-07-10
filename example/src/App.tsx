/* eslint-disable react/react-in-jsx-scope */
import { useState, useRef } from 'react';
import { StyleSheet, View, Text } from 'react-native';
import { Button } from 'react-native';
import Slider from '@react-native-community/slider';

import { AudioContext, Oscillator, GainNode } from 'react-native-audio-context';

export default function App() {
  const [isPlaying, setIsPlaying] = useState(false);
  const [gain, setGain] = useState<number>(1.0);
  const audioContextRef = useRef<AudioContext | null>(null);
  const oscillatorRef = useRef<Oscillator | null>(null);
  const gainRef = useRef<GainNode | null>(null);

  const createAudioContext = () => {
    if (!audioContextRef.current) {
      audioContextRef.current = new AudioContext();
    }

    gainRef.current = audioContextRef.current.createGain();
    oscillatorRef.current = audioContextRef.current.createOscillator();
    oscillatorRef.current.connect();
  };

  const handlePress = () => {
    if (!audioContextRef.current) {
      createAudioContext();
    }

    if (!isPlaying) {
      oscillatorRef.current?.start();
    } else {
      oscillatorRef.current?.stop();
    }

    setIsPlaying(!isPlaying);
  };

  const handleGainChange = (value: number) => {
    setGain(value);
    gainRef.current?.setGain(value);
  };

  return (
    <View style={styles.container}>
      <Button title={!isPlaying ? 'Play' : 'Pause'} onPress={handlePress} />
      <Text>Gain: {gain.toFixed(2)}</Text>
      <Slider
        style={styles.slider}
        minimumValue={0.0}
        maximumValue={1.0}
        step={0.01}
        value={gain}
        onValueChange={handleGainChange}
        minimumTrackTintColor="#1FB28A"
        maximumTrackTintColor="#d3d3d3"
        thumbTintColor="#1FB28A"
      />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
  slider: {
    width: 200,
    height: 40,
  },
});

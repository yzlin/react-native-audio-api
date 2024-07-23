/* eslint-disable react/react-in-jsx-scope */
import { Button, StyleSheet, Text, View } from 'react-native';
import { useRef, useState, useEffect } from 'react';

import {
  AudioContext,
  type Oscillator,
  type Gain,
} from 'react-native-audio-context';

const App = () => {
  const [isPlaying, setIsPlaying] = useState(false);

  const audioContextRef = useRef<AudioContext | null>(null);
  const oscillatorRef = useRef<Oscillator | null>(null);
  const gainRef = useRef<Gain | null>(null);

  const setUp = () => {
    audioContextRef.current = new AudioContext();

    oscillatorRef.current = audioContextRef.current.createOscillator();
    oscillatorRef.current.frequency = 800;
    oscillatorRef.current.type = 'sine';

    gainRef.current = audioContextRef.current.createGain();
    gainRef.current.gain = 1.0;

    const destination = audioContextRef.current.destination;
    oscillatorRef.current.connect(gainRef.current);
    gainRef.current.connect(destination);
  };

  useEffect(() => {
    return () => {
      //TODO
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
    <View style={styles.container}>
      <Text style={styles.title}>React Native Oscillator</Text>
      <Button title={isPlaying ? 'Pause' : 'Play'} onPress={handlePlayPause} />
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#F5FCFF',
  },
  title: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  },
});

export default App;

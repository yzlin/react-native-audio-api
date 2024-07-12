/* eslint-disable react/react-in-jsx-scope */
import { Button, StyleSheet, Text, View } from 'react-native';
import { AudioContext } from 'react-native-audio-context';
import type { OscillatorWrapper } from 'react-native-audio-context';

const App = () => {
  AudioContext.createOscillator();
  const oscillator = global.__OscillatorNodeProxy as OscillatorWrapper;

  const startOscillator = () => {
    oscillator.start();
  };

  const stopOscillator = () => {
    oscillator.stop();
  };

  return (
    <View style={styles.container}>
      <Text style={styles.title}>React Native Oscillator</Text>
      <Button title="Start Oscillator" onPress={startOscillator} />
      <Button title="Stop Oscillator" onPress={stopOscillator} />
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

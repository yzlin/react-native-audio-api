/* eslint-disable react/react-in-jsx-scope */
import { Button, StyleSheet, Text, View } from 'react-native';
import { AudioContext } from 'react-native-audio-context';

const App = () => {
  const audioContext = new AudioContext();

  const oscillator = audioContext.createOscillator();
  const oscillator2 = audioContext.createOscillator();

  oscillator.frequency = 200;

  const startOscillator = () => {
    oscillator.start();
    oscillator2.start();
  };

  const stopOscillator = () => {
    oscillator.stop();
    oscillator2.stop();
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

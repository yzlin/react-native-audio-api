import React from 'react';
import { StyleSheet, View, Text } from 'react-native';
import JSIExample from '../../src/JSIExample/JSIExample';

const App: React.FC = () => {
  const multiply = () => {
    return JSIExample.multiply(2, 3);
  };

  return (
    <View style={styles.container}>
      <Text>{multiply()}</Text>
    </View>
  );
};

export default App;

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
    paddingHorizontal: 20,
  },
  keys: {
    fontSize: 14,
    color: 'grey',
  },
  title: {
    fontSize: 16,
    color: 'black',
    marginRight: 10,
  },
  row: {
    flexDirection: 'row',
    alignItems: 'center',
  },
  textInput: {
    flex: 1,
    marginVertical: 20,
    borderWidth: StyleSheet.hairlineWidth,
    borderColor: 'black',
    borderRadius: 5,
    padding: 10,
  },
});

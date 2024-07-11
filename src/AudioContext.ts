import { NativeModules } from 'react-native';
const { AudioContextModule } = NativeModules;

interface AudioContextInterface {
  createOscillator(): void;
}

export const AudioContext = AudioContextModule as AudioContextInterface;

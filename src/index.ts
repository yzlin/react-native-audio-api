import { NativeModules } from 'react-native';
import type { Float } from 'react-native/Libraries/Types/CodegenTypes';
const { AudioContextModule } = NativeModules;

interface Oscillator {
  frequency: Float;
  wave: 'sine' | 'square' | 'sawtooth' | 'triangle';
  detune: Float;
  start: () => void;
  stop: () => void;
}

export class AudioContext {
  constructor() {
    AudioContextModule.initAudioContext();
  }

  createOscillator(): Oscillator {
    return global.__AudioContextProxy.createOscillator();
  }
}

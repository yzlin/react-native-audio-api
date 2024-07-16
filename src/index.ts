import { NativeModules } from 'react-native';
const { AudioContextModule } = NativeModules;

interface Oscillator {
  frequency: number;
  wave: 'sine' | 'square' | 'sawtooth' | 'triangle';
  detune: number;
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

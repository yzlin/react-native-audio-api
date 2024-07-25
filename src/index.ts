import { NativeModules } from 'react-native';
const { AudioContextModule } = NativeModules;
import type {
  Oscillator,
  BaseAudioContext,
  AudioDestinationNode,
  Gain,
} from './types';
import { installACModule } from './utils/install';

installACModule();

export class AudioContext implements BaseAudioContext {
  destination: AudioDestinationNode;

  constructor() {
    AudioContextModule.installAudioContext();
    this.destination = global.__AudioContext.destination;
  }

  createOscillator(): Oscillator {
    return global.__AudioContext.createOscillator();
  }

  createGain(): Gain {
    return global.__AudioContext.createGain();
  }
}

export type { Oscillator, Gain };

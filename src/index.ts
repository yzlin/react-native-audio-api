import { NativeModules } from 'react-native';
const { AudioContextModule } = NativeModules;
import type {
  Oscillator,
  BaseAudioContext,
  AudioDestinationNode,
  Gain,
  StereoPanner,
} from './types';

declare global {
  function nativeCallSyncHook(): unknown;
  var __AudioContext: BaseAudioContext;
}

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

  createStereoPanner() {
    return global.__AudioContext.createStereoPanner();
  }
}

export type { Oscillator, Gain, StereoPanner };

import { NativeModules } from 'react-native';
const { AudioContextModule } = NativeModules;
import type {
  Oscillator,
  BaseAudioContext,
  AudioDestinationNode,
} from './types';

declare global {
  function nativeCallSyncHook(): unknown;
  var __AudioContextProxy: BaseAudioContext;
}

export class AudioContext implements BaseAudioContext {
  destination: AudioDestinationNode;

  constructor() {
    AudioContextModule.installAudioContext();
    this.destination = global.__AudioContextProxy.destination;
  }

  createOscillator(): Oscillator {
    return global.__AudioContextProxy.createOscillator();
  }
}

export type { Oscillator };

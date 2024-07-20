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
  constructor() {
    AudioContextModule.installAudioContext();
  }

  createOscillator(): Oscillator {
    return global.__AudioContextProxy.createOscillator();
  }

  destination(): AudioDestinationNode {
    return global.__AudioContextProxy.destination();
  }
}

export type { Oscillator };

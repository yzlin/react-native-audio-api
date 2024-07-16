import { NativeModules } from 'react-native';
const { AudioContextModule } = NativeModules;
import type { Oscillator, BaseAudioContext } from './types';

declare global {
  function nativeCallSyncHook(): unknown;
  var __AudioContextProxy: BaseAudioContext;
}

export class AudioContext implements BaseAudioContext {
  constructor() {
    AudioContextModule.initAudioContext();
  }

  createOscillator(): Oscillator {
    return global.__AudioContextProxy.createOscillator();
  }
}

export type { Oscillator };

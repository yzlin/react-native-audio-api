export interface AudioContextWrapper {
  createOscillator(): Oscillator;
}

declare global {
  function nativeCallSyncHook(): unknown;
  var __AudioContextProxy: AudioContextWrapper;
}

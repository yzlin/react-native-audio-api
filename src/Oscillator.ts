export interface OscillatorWrapper {
  start(): undefined;
  stop(): undefined;
}

declare global {
  function nativeCallSyncHook(): unknown;
  var __OscillatorNodeProxy: OscillatorWrapper | undefined;
}

export const Oscillator = global.__OscillatorNodeProxy as OscillatorWrapper;

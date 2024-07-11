export interface OscillatorWrapper {
  start(): undefined;
  stop(): undefined;
}

declare global {
  function nativeCallSyncHook(): unknown;
  var __OscillatorProxy: OscillatorWrapper | undefined;
}

export const Oscillator = global.__OscillatorProxy as OscillatorWrapper;

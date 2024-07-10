const AudioContext = require('./NativeAudioContext').default;

export function multiply(a: number, b: number): number {
  return AudioContext.multiply(a, b);
}

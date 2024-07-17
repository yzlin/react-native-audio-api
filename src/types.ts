export interface BaseAudioContext {
  createOscillator(): Oscillator;
}

export interface AudioNode {
  context: BaseAudioContext;
  connect: (destination: AudioNode) => void;
  disconnect: () => void;
}

export interface AudioScheduledSourceNode extends AudioNode {
  start: () => void;
  stop: () => void;
}

type WaveType = 'sine' | 'square' | 'sawtooth' | 'triangle';

export interface Oscillator extends AudioScheduledSourceNode {
  frequency: number;
  wave: WaveType;
  detune: number;
}

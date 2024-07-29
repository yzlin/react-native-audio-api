export interface BaseAudioContext {
  readonly destination: AudioDestinationNode | null;
  createOscillator(): Oscillator;
  createGain(): Gain;
  createStereoPanner(): StereoPanner;
}

export interface AudioNode {
  readonly context: BaseAudioContext;
  readonly numberOfInputs: number;
  readonly numberOfOutputs: number;
  connect: (destination: AudioDestinationNode) => void;
  disconnect: () => void;
}

export interface AudioParam {
  value: number;
}

export interface AudioDestinationNode extends AudioNode {}

export interface AudioScheduledSourceNode extends AudioNode {
  start: (time: number) => void;
  stop: (time: number) => void;
}

type WaveType = 'sine' | 'square' | 'sawtooth' | 'triangle';

export interface Oscillator extends AudioScheduledSourceNode {
  frequency: AudioParam;
  type: WaveType;
  detune: AudioParam;
}

export interface Gain extends AudioNode {
  gain: AudioParam;
}

export interface StereoPanner extends AudioNode {
  pan: AudioParam;
}

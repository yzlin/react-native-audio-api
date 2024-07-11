import { NativeModules } from 'react-native';
const { AudioContextModule } = NativeModules;

interface AudioScheduleSourceNode extends AudioNode {
  context: AudioContext;
  start(): void;
  stop(): void;
}

interface AudioNode {
  connect(): void;
  disconnect(): void;
}

export class AudioContext {
  private source: AudioScheduleSourceNode | null = null;
  private gain: GainNode | null = null;

  constructor() {}

  public createOscillator() {
    AudioContextModule.createOscillatorNode();
    this.source = new Oscillator(this);
    return this.source;
  }

  public createGain() {
    AudioContextModule.createGainNode();
    this.gain = new GainNode();
    return this.gain;
  }
}

export class Oscillator implements AudioScheduleSourceNode {
  context: AudioContext;

  constructor(context: AudioContext) {
    this.context = context;
  }

  public start() {
    AudioContextModule.start();
  }

  public stop() {
    AudioContextModule.stop();
  }

  public connect() {
    AudioContextModule.connect();
  }

  public disconnect() {
    AudioContextModule.disconnect();
  }
}

export class GainNode implements AudioNode {
  gain: number = AudioContextModule.getVolume();

  public connect() {
    AudioContextModule.connect();
  }

  public disconnect() {
    AudioContextModule.disconnect();
  }

  public getGain() {
    return AudioContextModule.getVolume();
  }

  public setGain(gain: number) {
    AudioContextModule.setVolume(gain);
  }
}

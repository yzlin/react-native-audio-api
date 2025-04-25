import { useEffect, useState } from 'react';
import AudioManager from './AudioManager';

export default function useSystemVolume() {
  const [volume, setVolume] = useState(0);

  useEffect(() => {
    AudioManager.enableRemoteCommand('volumeChange', true, (e) => {
      setVolume(e.value);
    });
    return () => {
      AudioManager.enableRemoteCommand('volumeChange', false);
    };
  }, []);

  return volume;
}

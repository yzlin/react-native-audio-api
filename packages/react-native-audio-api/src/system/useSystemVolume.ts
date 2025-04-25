import { useEffect, useState } from 'react';
import AudioManager from './AudioManager';

export default function useSystemVolume() {
  const [volume, setVolume] = useState(0);

  useEffect(() => {
    AudioManager.enableRemoteCommand('volumeChange', true, (e) => {
      setVolume(parseFloat(e.value.toFixed(2)));
    });
    return () => {
      AudioManager.enableRemoteCommand('volumeChange', false);
    };
  }, []);

  return volume;
}

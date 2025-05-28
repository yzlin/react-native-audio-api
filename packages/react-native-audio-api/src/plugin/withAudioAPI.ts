import {
  AndroidConfig,
  createRunOncePlugin,
  ConfigPlugin,
  withInfoPlist,
  withAndroidManifest,
} from '@expo/config-plugins';
const pkg = require('react-native-audio-api/package.json');

interface Options {
  iosBackgroundMode: boolean;
  androidForegroundService: boolean;
  androidFSPermissions: string[];
  androidFSTypes: string[];
}

const withDefaultOptions = (options: Partial<Options>): Options => {
  return {
    iosBackgroundMode: true,
    androidForegroundService: true,
    androidFSPermissions: [
      'android.permission.FOREGROUND_SERVICE',
      'android.permission.WAKE_LOCK',
    ],
    androidFSTypes: ['mediaPlayback'],
    ...options,
  };
};

const withBackgroundAudio: ConfigPlugin = (config) => {
  return withInfoPlist(config, (iosConfig) => {
    iosConfig.modResults.UIBackgroundModes = [
      ...Array.from(
        new Set([...(iosConfig.modResults.UIBackgroundModes ?? []), 'audio'])
      ),
    ];

    return iosConfig;
  });
};

const withAndroidPermissions: ConfigPlugin<Options> = (
  config,
  { androidFSPermissions }: Options
) => {
  return AndroidConfig.Permissions.withPermissions(
    config,
    androidFSPermissions
  );
};

const withForegroundService: ConfigPlugin<Options> = (
  config,
  { androidFSTypes }: Options
) => {
  return withAndroidManifest(config, (mod) => {
    const manifest = mod.modResults;
    const mainApplication =
      AndroidConfig.Manifest.getMainApplicationOrThrow(manifest);

    const SFTypes = androidFSTypes.join('|');

    const serviceElement = {
      $: {
        'android:name':
          'com.swmansion.audioapi.system.MediaNotificationManager$NotificationService',
        'android:stopWithTask': 'true',
        'android:foregroundServiceType': SFTypes,
      },
      intentFilter: [],
    };

    if (!mainApplication.service) {
      mainApplication.service = [];
    }

    mainApplication.service.push(serviceElement);

    return mod;
  });
};

const withAudioAPI: ConfigPlugin<Options> = (config, optionsIn) => {
  const options = withDefaultOptions(optionsIn ?? {});

  if (options.iosBackgroundMode) {
    config = withBackgroundAudio(config);
  }

  if (options.androidForegroundService) {
    config = withAndroidPermissions(config, options);
    config = withForegroundService(config, options);
  }

  return config;
};

export default createRunOncePlugin(withAudioAPI, pkg.name, pkg.version);

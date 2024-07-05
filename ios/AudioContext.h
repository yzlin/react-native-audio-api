#ifdef __cplusplus
#import "react-native-audio-context.h"
#endif

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNAudioContextSpec.h"

@interface AudioContext : NSObject <NativeAudioContextSpec>
#else
#import <React/RCTBridgeModule.h>

@interface AudioContext : NSObject <RCTBridgeModule>
#endif

@end

#import "ABI45_0_0RNGestureHandlerState.h"
#import "ABI45_0_0RNGestureHandlerDirection.h"
#import "ABI45_0_0RNGestureHandlerEvents.h"
#import "ABI45_0_0RNGestureHandlerPointerTracker.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <ABI45_0_0React/ABI45_0_0RCTConvert.h>

#define VEC_LEN_SQ(pt) (pt.x * pt.x + pt.y * pt.y)
#define TEST_MIN_IF_NOT_NAN(value, limit) \
(!isnan(limit) && ((limit < 0 && value <= limit) || (limit >= 0 && value >= limit)))

#define TEST_MAX_IF_NOT_NAN(value, max) \
(!isnan(max) && ((max < 0 && value < max) || (max >= 0 && value > max)))

#define APPLY_PROP(recognizer, config, type, prop, propName) do { \
id value = config[propName]; \
if (value != nil) { recognizer.prop = [ABI45_0_0RCTConvert type:value]; }\
} while(0)

#define APPLY_FLOAT_PROP(prop) do { APPLY_PROP(recognizer, config, CGFloat, prop, @#prop); } while(0)
#define APPLY_INT_PROP(prop) do { APPLY_PROP(recognizer, config, NSInteger, prop, @#prop); } while(0)
#define APPLY_NAMED_INT_PROP(prop, propName) do { APPLY_PROP(recognizer, config, NSInteger, prop, propName); } while(0)

@protocol ABI45_0_0RNGestureHandlerEventEmitter

- (void)sendTouchEvent:(nonnull ABI45_0_0RNGestureHandlerEvent *)event;

- (void)sendStateChangeEvent:(nonnull ABI45_0_0RNGestureHandlerStateChange *)event;

- (void)sendTouchDeviceEvent:(nonnull ABI45_0_0RNGestureHandlerEvent *)event;

- (void)sendStateChangeDeviceEvent:(nonnull ABI45_0_0RNGestureHandlerStateChange *)event;

@end


@protocol ABI45_0_0RNRootViewGestureRecognizerDelegate <UIGestureRecognizerDelegate>

- (void)gestureRecognizer:(nullable UIGestureRecognizer *)gestureRecognizer
    didActivateInViewWithTouchHandler:(nullable UIView *)viewWithTouchHandler;

@end


@interface ABI45_0_0RNGestureHandler : NSObject <UIGestureRecognizerDelegate> {

@protected UIGestureRecognizer *_recognizer;
@protected ABI45_0_0RNGestureHandlerState _lastState;

}

+ (nullable ABI45_0_0RNGestureHandler *)findGestureHandlerByRecognizer:(nonnull UIGestureRecognizer *)recognizer;

- (nonnull instancetype)initWithTag:(nonnull NSNumber *)tag;

@property (nonatomic, readonly, nonnull) NSNumber *tag;
@property (nonatomic, weak, nullable) id<ABI45_0_0RNGestureHandlerEventEmitter> emitter;
@property (nonatomic, readonly, nullable) UIGestureRecognizer *recognizer;
@property (nonatomic, readonly, nullable) ABI45_0_0RNGestureHandlerPointerTracker *pointerTracker;
@property (nonatomic) BOOL enabled;
@property (nonatomic) BOOL usesDeviceEvents;
@property (nonatomic) BOOL shouldCancelWhenOutside;
@property (nonatomic) BOOL needsPointerData;
@property (nonatomic) BOOL manualActivation;

- (void)bindToView:(nonnull UIView *)view;
- (void)unbindFromView;
- (void)resetConfig NS_REQUIRES_SUPER;
- (void)configure:(nullable NSDictionary *)config NS_REQUIRES_SUPER;
- (void)handleGesture:(nonnull id)recognizer;
- (BOOL)containsPointInView;
- (ABI45_0_0RNGestureHandlerState)state;
- (nullable ABI45_0_0RNGestureHandlerEventExtraData *)eventExtraData:(nonnull id)recognizer;

- (void)stopActivationBlocker;
- (void)reset;
- (void)sendEventsInState:(ABI45_0_0RNGestureHandlerState)state
           forViewWithTag:(nonnull NSNumber *)ABI45_0_0ReactTag
            withExtraData:(nonnull ABI45_0_0RNGestureHandlerEventExtraData *)extraData;
- (void)sendStateChangeEvent:(nonnull ABI45_0_0RNGestureHandlerStateChange *)event;
- (void)sendTouchEventInState:(ABI45_0_0RNGestureHandlerState)state
                 forViewWithTag:(nonnull NSNumber *)ABI45_0_0ReactTag;

@end


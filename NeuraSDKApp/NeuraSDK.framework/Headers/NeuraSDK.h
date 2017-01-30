/**
 *  NeuraSDK.h
 *  NeuraSDK
 *
 *  Created by Gal Mirkin on 8/20/15.
 *  Copyright (c) 2015 Neura. All rights reserved.
 */

#import <UIKit/UIKit.h>
#import "NeuraSDKPushNotification.h"


extern NSString * const kNeuraSDKErrorDomain;
extern NSString * const kNeuraSDKErrorsArrayKey;
extern NSString * const NeuraSDKErrorDidReceiveNotification;


/*!
 *  @typedef NEUSdkErrors: aggregates all Neura SDK custom error codes used in notification via NeuraSDKErrorDidReceiveNotification.
 */
typedef NS_OPTIONS(NSUInteger, NEUSdkErrors) {
    NEUSDKErrorGeneral                  = 1000,
    NEUSDKErrorBluetoothDisabled        = 1001,
    NEUSDKErrorWiFiDisabled             = 1002,
    NEUSDKErrorCellularDataDisabled     = 1003,
    NEUSDKErrorLocationDataDisabled     = 1004,
    NEUSDKErrorMotionDataDisabled       = 1005
};


/*!
 @typedef NEUFeatures: contains all bit flags for SDK configuration features. These can be used with 'enableFeaturesWithKeys:' method.
 
 @constant NEUSDKCustomErrorNotification:
 Neura SDK will always send notifications to application in case of permissions and/or service error
 via NeuraSDKErrorDidReceiveNotification notification.
 Appropriate NSNotification userInfo dictionary value for kNeuraSDKErrorsArrayKey key
 will contain the NSArray of NSError objects.
 Every NSError will contain as following:
 1. The error domain will be kNeuraSDKErrorDomain.
 2. The possible error code values can be found in NEUSdkErrors enum above.
 3. The 'localizedDescription' will contain Neura error description.
 By default, the SDK handles critical errors (i.e. permissions) using Neura's UI popup notifications.
 To disable this default behavior (i.e. UI popup notifications), a NEUSDKCustomErrorNotification flag should be passed in 'enableFeaturesWithKeys:' method.
 
 @constant NEUSDKDisableSdkLogging:
 Neura SDK sends periodical logs by default in order to monitor and analyze engine performance.
 To disable this default behavior, the NEUSDKDisableSdkLogging flag should be passed in 'enableFeaturesWithKeys:' method together ('|') with other configuration flags.
 */
typedef NS_OPTIONS(NSUInteger, NEUFeatures) {
    
    NEUSDKCustomErrorNotification       =(1 << 0),
    NEUSDKDisableSdkLogging             =(1 << 1)
};




@interface NeuraSDK: NSObject
typedef void (^Handler)(NSString *token, NSString *error);
typedef void (^PermissionsListHandler)(NSArray *permissionsArray, NSString *error);
typedef void (^ResponseDataHandler)(NSDictionary *responseData, NSString *error);

+ (NeuraSDK *)sharedInstance;

/*! Must be placed in the AppDelegate on applicationdidFinishLaunchingWithOptions */

/*! the App UID from the Neura dev site */
@property (atomic, strong) NSString *appUID;

/*! the App Secret from the Neura dev site */
@property (atomic, strong) NSString *appSecret;


/*!
 *  enables sdk configuration features from NEUFeatures enum
 *
 *  @param flags all required bits associated with related features (NEUFeatures).
 *  This method call overrides internal SDK configuration with 'flags' parameter (collection of bitwise values).
 */
- (void)enableFeaturesWithKeys:(NSUInteger)flags;


/*!
 *  use to get the app permissions list
 *
 *  @param handler handler
 */
- (void)getAppPermissionsWithHandler:(PermissionsListHandler)handler;


/*!
 *  use to get the app Subscriptions list
 *
 *  @param handler handler
 */
- (void)getSubscriptions:(ResponseDataHandler)handler;

/*!
 *  use to open neura settings panel
 *  show list of the permissions that the user approved
 */
- (void)openNeuraSettingsPanel;


/*!
 *  use to logout from neura
 */
- (void)logout;


/*!
 *  use to authenticate the app and to show the login view and login to neura
 *
 *  @param permissions  the permissions to request on login
 *  @param controller the view controller that will show the login view
 */
- (void)authenticateWithPermissions:(NSArray *)permissions
                       onController:(UIViewController *)controller
                        withHandler:(Handler)handler;



/*!
 *  use to authenticate the app and to show the login view and login to neura
 *
 *  @param permissions  the permissions to request on login
 *  @param userInfo Use the following keys:
 *                                         phone - use to set the user phone (if exists SignIn confirmation code will be sent without the need for filling the phone number) 
 *                                                 The number must include country code
 *
 *                                         type - Login screen type:  0 - neura's login screen
 *                                                                    1 - minimal login screen
 *
 *  @param controller the view controller that will show the login view
 */
- (void)authenticateWithPermissions:(NSArray *)permissions
                           userInfo:(NSDictionary *)userInfo
                       onController:(UIViewController *)controller
                        withHandler:(Handler)handler;


/*!
 *  use to subscribe to event
 *
 * @param eventName the event name
 * @param identifier to identify the event
 * @param webHookID the webHook identifier that respond to the event can be set nil
 */
- (void)subscribeToEvent:(NSString *)eventName
              identifier:(NSString *)identifier
               webHookID:(NSString *)webHookID
              completion:(ResponseDataHandler)handler;


/*!
 *  use to remove Subscription
 *
 *  @param identifier the Subscription identifier
 */
- (void)removeSubscriptionWithIdentifier:(NSString *)identifier
                                complete:(ResponseDataHandler)handler;


/*!
 *  Use to check if the event has all the required data
 *
 *  @param eventName event to check if all the require fields exists.
 *
 *  @return false if the event has all the require data in it
 */
- (BOOL)isMissingDataForEvent:(NSString *)eventName;


/*!
 *   Use to get the missing data for the required event to subscribe
 *
 *  @param eventName the event with the missing data
 *
 */
- (void)getMissingDataForEvent:(NSString *)eventName
                   withHandler:(ResponseDataHandler)handler;


/*!
 *  get the sdk version
 *
 *  @return version string
 */
- (NSString *)getVersion;


/*!
 *  get all the supported devices Neura has to offer.
 *
 */
- (void)getSupportedDevicesListWithHandler:(ResponseDataHandler)handler;


/*!
 *  get all the supported capabilities for devices.
 *
 */
- (void)getSupportedCapabilitiesListWithHandler:(ResponseDataHandler)handler;


/*!
 *  check if user has a device with the capabilityName
 *
 *  @param capability name as can be fetched from (getSupportedCapabilitiesListWithHandler)
 */
- (void)hasDeviceWithCapability:(NSString *)capability
                    withHandler:(ResponseDataHandler)handler;


/*!
 *   Opening a device picker screen.
 *   Note that authorization WebView required for connecting the device might be shown.
 *
 *  @param capability Opening a device picker screen with devices has at least one capability from the capability provided
 *  @param deviceName show device only by name
 *   If all params left empty We'll present all our available devices for the user to add.
 */
- (void)addDeviceWithCapability:(NSString *)capability
                     deviceName:(NSString *)deviceName
                    withHandler:(ResponseDataHandler)handler;

/*!
 *  get a collection of states for a user at a given timestamp
 *
 *  @param timeStamp  Required. The timestamp for when you want to get the user's situation
 *  @param contextual In order to get more data about the situation, like previous and next situations. Default: false
 */
- (void)getUserSituationForTimeStamp:(NSDate *)timeStamp
                          contextual:(BOOL)contextual
                         withHandler:(ResponseDataHandler)handler;


/*!
 *  Sending Neura a feedback for an event received.
 *
 *  @param neuraID  Required. The timestamp for when you want to get the user's situation
 *  @param approved In order to get more data about the situation, like previous and next situations. Default: false
 */
- (void)sendFeedbackOnEvent:(NSString*)neuraID
                   approved:(BOOL)approved
                   complete:(ResponseDataHandler)handler;

@end

//
//  NeuraSDKPushNotification.h
//  NeuraSDK
//
//  Created by Gal Mirkin on 14/07/2016.
//  Copyright © 2016 Neura. All rights reserved.
//


#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface NeuraSDKPushNotification : NSObject


/*!
  The key used to sign up for pushed notifications event

  [[NSNotificationCenter defaultCenter] addObserver:self
                                           selector:@selector(didReceiveRemoteNotificationFromNeuraSDK:)
                                               name:NeuraSDKDidReceiveRemoteNotification
                                             object:nil];
*/
extern NSString *const NeuraSDKDidReceiveRemoteNotification;



/*!
                                    Automatic Integration
 
 
 NeuraSDKPushNotification is an easy-to-implement push mechanism which automatically integrates with your app
 without the need to implement any UIApplicationDelegate protocol methods or pass notifications to the library.
 Unlike UIApplicationDelegate protocol methods, it delivers push messages and forwards them straight to your app
 using a technique also known as "method swizzling". This method should be compatible with most use cases.
 
 If you encounter problems or prefer to implement your own push mechanism instead,
 just don't use enableAutomaticPushNotification.

 The following steps will get you started:

  1. #import <NeuraSDK/NeuraSDKPushNotification.h>
  2. placed  [NeuraSDKPushNotification enableAutomaticPushNotification]; in the AppDelegate on applicationdidFinishLaunchingWithOptions
*/
+ (void)enableAutomaticPushNotification;



/*!
    use to get the push device token
 
    @return token
 */
+ (NSString *)getDeviceToken;


/*!
    set token in manual Integration
 
   @param deviceToken the token used for register the device
*/
+ (void)applicationDidRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;



/*!
    receive remote notification
 
   @param userInfo the push data
*/
+ (void)didReceiveRemoteNotification:(NSDictionary *)userInfo;


@end

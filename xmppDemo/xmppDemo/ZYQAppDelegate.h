//
//  ZYQAppDelegate.h
//  xmppDemo
//
//  Created by 张毓庆 on 13-11-27.
//  Copyright (c) 2013年 张毓庆. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "XMPPFramework.h"

#define kXMPPUserNameKey    @"xmppUserName"
#define kXMPPPasswordKey    @"xmppPassword"
#define kXMPPHostNameKey    @"xmppHostName"

#define kNotificationUserLogonState @"NotificationUserLogonState"
// 声明请求完成的block
typedef void(^completionBlock)();

@interface ZYQAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

#pragma mark - xmpp相关的属性和方法定义
/**
 *  全局的xmppStream属性
 */
@property (strong,nonatomic,readonly) XMPPStream *xmppStream;

/**
 *  判断是否是新注册用户的标识
 */
@property (nonatomic,assign) BOOL isRegisterUser;
/**
 *  用户是否登录成功标识
 */
@property (nonatomic,assign) BOOL isUserLogon;

/**
 *  连接到服务器
 *  用户的信息保存在偏好设置中去
 *  @param success 连接正确的块代码
 *  @param failed  连接错误出现的块代码
 */
- (void)connectionWithCompletion:(completionBlock)success failed:(completionBlock)failed;

@end

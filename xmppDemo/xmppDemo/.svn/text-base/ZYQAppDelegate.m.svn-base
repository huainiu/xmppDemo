//
//  ZYQAppDelegate.m
//  xmppDemo
//
//  Created by 张毓庆 on 13-11-27.
//  Copyright (c) 2013年 张毓庆. All rights reserved.
//

#import "ZYQAppDelegate.h"
@interface ZYQAppDelegate()<XMPPStreamDelegate>
{
    completionBlock _successBlock;  // 连接成功的块代码
    completionBlock _failedBlock;   // 连接失败的块代码
}
/**
 *  初始化设置xmppstream流
 */
- (void)setupXMPPStream;
/**
 *  通知服务器用户上线了
 */
- (void)gonOnline;
/**
 *  通知服务器用户下线了
 */
- (void)goOffline;
/**
 *  连接到服务器
 */
- (void)connect;
/**
 *  与服务器断开连接
 */
- (void)disconnect;

@end

@implementation ZYQAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    
    
    [self registerNotification];
    
    return YES;
}
							
- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
    
    
    [self disconnect];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    

}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}
#pragma mark - 通知中心
- (void)registerNotification
{
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    
    [center addObserver:self selector:@selector(loginStateChange) name:kNotificationUserLogonState object:nil];
}

- (void)loginStateChange
{
    UIStoryboard *storyboard = nil;
    if (_isUserLogon)
    {
        // 显示main.storyBoard
        storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    }
    else
    {
        storyboard = [UIStoryboard storyboardWithName:@"login" bundle:nil];
    }
    
    [self.window setRootViewController:storyboard.instantiateInitialViewController];
}

#pragma mark - XMPP相关的方法
#pragma mark 初始化设置stream
- (void)setupXMPPStream
{
    if (_xmppStream == nil)
    {
        _xmppStream = [[XMPPStream alloc]init];
        
        [_xmppStream addDelegate:self delegateQueue:dispatch_get_main_queue()];
    }
}

#pragma mark 用户上线
- (void)gonOnline
{
    // 实例化一个用户展现
    XMPPPresence *presence = [XMPPPresence presence];
    // 通知给好友
    [_xmppStream sendElement:presence];
}

#pragma mark 用户下线
- (void)goOffline
{
    XMPPPresence *presence = [XMPPPresence presence];
    // 通知服务器客户端已经下线
    [_xmppStream sendElement:presence];
}

#pragma mark 开始连接服务器
- (void)connect
{
    // 设置xmpp
    [self setupXMPPStream];
    
    // 指定用户名 主机 连接的时候不需要密码
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSString *hostName = [defaults stringForKey:kXMPPHostNameKey];
    NSString *userName = [NSString stringWithFormat:@"%@@%@",[defaults stringForKey:kXMPPUserNameKey],hostName];
    
    // 设置xmppStream的jid和主机
    [_xmppStream setMyJID:[XMPPJID jidWithString:userName]];
    [_xmppStream setHostName:hostName];
    
    // 开始连接
    NSError *error = nil;
    [_xmppStream connectWithTimeout:XMPPStreamTimeoutNone error:&error];
    
    // 检测连接是否发送成功
    if (error)
    {
        NSLog(@"连接请求发送出错");
    }
    else
    {
        NSLog(@"连接请求发送成功");
    }

}

- (void)connectionWithCompletion:(completionBlock)success failed:(completionBlock)failed
{
    // 记录块代码
    _successBlock = success;
    _failedBlock = failed;
    
    // 如果连接的时候检测到已经连接了服务器那么就先断开连接然后在重新连接服务器
    if ([_xmppStream isConnected])
    {
        [_xmppStream disconnect];
    }
    
    // 连接服务器
    [self connect];
}

#pragma mark 断开连接
- (void)disconnect
{
    // 通知服务器用户下线
    [self goOffline];
    // 断开连接
    [_xmppStream disconnect];
}

#pragma mark - 相关的xmpp的代理方法
#pragma mark 连接完成
- (void)xmppStreamDidConnect:(XMPPStream *)sender
{
    NSLog(@"连接已经建立");
    NSString *password  = [[NSUserDefaults standardUserDefaults] stringForKey:kXMPPPasswordKey];
    
    if (_isRegisterUser)
    {
        // 新用户注册
        [_xmppStream registerWithPassword:password error:nil];
    }
    else
    {
        // 老用户登录
        [_xmppStream authenticateWithPassword:password error:nil];
    }
    
}

#pragma mark 注册成功
- (void)xmppStreamDidRegister:(XMPPStream *)sender
{
    // 注册成功后改变注册模式
    _isRegisterUser = NO;
    
    [self xmppStreamDidConnect:_xmppStream];
}

#pragma mark 注册失败
- (void)xmppStream:(XMPPStream *)sender didNotRegister:(DDXMLElement *)error
{
    _isRegisterUser = NO;
    
    if (_failedBlock != nil)
    {
        _failedBlock();
    }
}

#pragma mark  身份验证后的通过
- (void)xmppStreamDidAuthenticate:(XMPPStream *)sender
{
    // 身份验证通过
    _isUserLogon = YES;
    
    if (_successBlock != nil)
    {
        _successBlock();
    }
    
    // 通知服务器用户上线
    [self gonOnline];
}

#pragma mark 身份验证后失败或者密码错误
- (void)xmppStream:(XMPPStream *)sender didNotAuthenticate:(DDXMLElement *)error
{
    if (_failedBlock != nil)
    {
        _failedBlock();
    }
}
@end

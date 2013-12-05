//
//  ZYQMainViewController.m
//  xmppDemo
//
//  Created by 张毓庆 on 13-11-28.
//  Copyright (c) 2013年 张毓庆. All rights reserved.
//

#import "ZYQMainViewController.h"
#import "ZYQAppDelegate.h"

@interface ZYQMainViewController ()
- (IBAction)userLogout:(UIButton *)sender;

@end

@implementation ZYQMainViewController


- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}
#pragma mark - AppDelegate 的助手方法
- (ZYQAppDelegate *)appDelegate
{
    return [[UIApplication sharedApplication] delegate];
}

#pragma mark - 用户注销登录触发的代码
- (IBAction)userLogout:(UIButton *)sender
{
    [self appDelegate].isUserLogon = NO;
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kNotificationUserLogonState object:nil];
}
@end

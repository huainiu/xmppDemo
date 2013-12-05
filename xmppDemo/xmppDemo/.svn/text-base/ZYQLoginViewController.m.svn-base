//
//  ZYQLoginViewController.m
//  xmppDemo
//
//  Created by 张毓庆 on 13-11-28.
//  Copyright (c) 2013年 张毓庆. All rights reserved.
//

#import "ZYQLoginViewController.h"
#import "NSString+Helper.h"
#import "ZYQAppDelegate.h"

@interface ZYQLoginViewController ()<UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UITextField *userNameText;
@property (weak, nonatomic) IBOutlet UITextField *passwordText;
@property (weak, nonatomic) IBOutlet UITextField *hostNameText;
/**
 *  用户的登录
 */
- (IBAction)userLoginAndRegister:(UIButton *)button;
@end

@implementation ZYQLoginViewController

#pragma mark - appDelegate的助手方法
- (ZYQAppDelegate *)appdelegate
{
    return [[UIApplication sharedApplication] delegate];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
//    _hostNameText.text = [[NSUserDefaults standardUserDefaults] objectForKey:kXMPPHostNameKey];
    _hostNameText.text = @"chouyuqingnopasokon.local";
    _userNameText.text = [[NSUserDefaults standardUserDefaults] objectForKey:kXMPPUserNameKey];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - textfield的代理方法
- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    if (textField == _userNameText)
    {
        [_passwordText becomeFirstResponder];
    }
    else if(textField == _passwordText)
    {
        [_hostNameText becomeFirstResponder];
    }
    else if(textField == _hostNameText)
    {
        [_hostNameText resignFirstResponder];
        //  用户登录
        [self userLoginAndRegister:nil];
    }
    
    return YES;
}
#pragma mark - 用户登录操作
- (IBAction)userLoginAndRegister:(UIButton *)button
{
    // 检查用户是否输入完整
    NSString *userName = [_userNameText.text trimString];
    NSString *password = _passwordText.text;
    NSString *hostName = [_hostNameText.text trimString];
    
    if ([userName isEmptyString] || [password isEmptyString] || [hostName isEmptyString])
    {
        UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"提示信息" message:@"用户输入信息不完整" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
        [alert show];
        
        return;
    }
    
    
    // 将用户输入的信息写入偏好设置中
    [userName saveToNSDefaultsWithKey:kXMPPUserNameKey];
    [password saveToNSDefaultsWithKey:kXMPPPasswordKey];
    [hostName saveToNSDefaultsWithKey:kXMPPHostNameKey];
    
    
    // 让appdelegate开始进行连接
    
    NSString *actionName = nil;
    
    if (button.tag == 1)
    {
        [self appdelegate].isRegisterUser = YES;
        actionName = @"新注册用户";
    }
    else
    {
        actionName = @"用户登录";
    }
    
    
    [[self appdelegate] connectionWithCompletion:^{
       
        NSLog(@" %@ 连接成功",actionName);
        
        [[NSNotificationCenter defaultCenter] postNotificationName:kNotificationUserLogonState object:nil];
        
    } failed:^{
        
        NSLog(@" %@连接失败",actionName);
    }];
    
}
@end

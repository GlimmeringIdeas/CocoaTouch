//
//  UITableViewController.h
//  UIKit
//
//  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UITableView.h>
#import <UIKit/UIKitDefines.h>

// 创建一个确定的尺寸，自动调整尺寸的表视图。设置自己为 dataSource 和 delegate 的代表
// 在“-viewWillAppear:”中，如果它是空的，那么他会重新加载表格数据。否则，它清除所有行。
// 在“ -viewDidAppear:”, it flashes the table's scroll indicators.
// Implements -setEditing:animated: to toggle the editing state of the table.

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(2_0) @interface UITableViewController : UIViewController <UITableViewDelegate, UITableViewDataSource>

// 初始化表格样式
- (instancetype)initWithStyle:(UITableViewStyle)style NS_DESIGNATED_INITIALIZER;

// 初始化 storyboard 的形式
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_DESIGNATED_INITIALIZER;

// 初始化加载 storyboard 的形式
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

// 表视图属性
@property (nonatomic, strong, null_resettable) UITableView *tableView;

// 默认是 YES，选中的时候就清除
@property (nonatomic) BOOL clearsSelectionOnViewWillAppear NS_AVAILABLE_IOS(3_2); // defaults to YES. If YES, any selection is cleared in viewWillAppear:

@property (nonatomic, strong, nullable) UIRefreshControl *refreshControl NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END

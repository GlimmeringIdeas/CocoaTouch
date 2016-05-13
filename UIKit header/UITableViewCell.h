//
//  UITableViewCell.h
//  UIKit
//
//  Copyright (c) 2005-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIGestureRecognizer.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage, UIColor, UILabel, UIImageView, UIButton, UITextField, UITableView, UILongPressGestureRecognizer;

// Cell的初始化方法，可以设置一个风格和标识符的枚举
typedef NS_ENUM(NSInteger, UITableViewCellStyle) {
    // 默认风格，自带标题和一个图片视图，图片在左
    UITableViewCellStyleDefault,
    // 只有标题和副标题 副标题在右边
    UITableViewCellStyleValue1,
    // 只有标题和副标题，副标题在左边标题的下边
    UITableViewCellStyleValue2,
    // 自带图片视图和主副标题，主副标题都在左边，副标题在下
    UITableViewCellStyleSubtitle
};

// 分割线的风格的枚举
typedef NS_ENUM(NSInteger, UITableViewCellSeparatorStyle) {
    // 无线
    UITableViewCellSeparatorStyleNone,
    // 有线
    UITableViewCellSeparatorStyleSingleLine,
    // 此分隔符样式仅支持当前分组样式表视图
    UITableViewCellSeparatorStyleSingleLineEtched
} __TVOS_PROHIBITED;

// cell被选中时风格的枚举
typedef NS_ENUM(NSInteger, UITableViewCellSelectionStyle) {
    // 无
    UITableViewCellSelectionStyleNone,
    // 蓝色
    UITableViewCellSelectionStyleBlue,
    // 灰色
    UITableViewCellSelectionStyleGray,
    // 默认为蓝色
    UITableViewCellSelectionStyleDefault NS_ENUM_AVAILABLE_IOS(7_0)
};

typedef NS_ENUM(NSInteger, UITableViewCellFocusStyle) {
    UITableViewCellFocusStyleDefault,
    UITableViewCellFocusStyleCustom
} NS_ENUM_AVAILABLE_IOS(9_0);

// 获取cell的编辑状态的枚举
typedef NS_ENUM(NSInteger, UITableViewCellEditingStyle) {
    // 无编辑
    UITableViewCellEditingStyleNone,
    // 删除编辑
    UITableViewCellEditingStyleDelete,
    // 插入编辑
    UITableViewCellEditingStyleInsert
};

// 设置附件视图的风格(cell最右侧显示的视图) 的枚举
typedef NS_ENUM(NSInteger, UITableViewCellAccessoryType) {
    // 没有视图
    UITableViewCellAccessoryNone,
    // cell右侧显示一个灰色箭头
    UITableViewCellAccessoryDisclosureIndicator,
    // 显示详情符号和灰色箭头
    UITableViewCellAccessoryDetailDisclosureButton __TVOS_PROHIBITED,
    // cell右侧显示蓝色对号
    UITableViewCellAccessoryCheckmark,
    // cell右侧显示一个详情符号
    UITableViewCellAccessoryDetailButton NS_ENUM_AVAILABLE_IOS(7_0)  __TVOS_PROHIBITED // info button. tracks
};

// cell状态已经转换时调用的函数，可以在子类中重写的状态
typedef NS_OPTIONS(NSUInteger, UITableViewCellStateMask) {
    // 默认状态
    UITableViewCellStateDefaultMask = 0,
    // 编辑状态
    UITableViewCellStateShowingEditControlMask = 1 << 0,
    // 确认删除状态
    UITableViewCellStateShowingDeleteConfirmationMask = 1 << 1
};

#define UITableViewCellStateEditingMask UITableViewCellStateShowingEditControlMask

NS_CLASS_AVAILABLE_IOS(2_0) @interface UITableViewCell : UIView <NSCoding, UIGestureRecognizerDelegate>

// Cell的初始化方法，可以设置一个风格和标识符
- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(nullable NSString *)reuseIdentifier NS_AVAILABLE_IOS(3_0) NS_DESIGNATED_INITIALIZER;

//
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

// Content.  These properties provide direct access to the internal label and image views used by the table view cell.  These should be used instead of the content properties below.
// 图片视图，风格允许时才会创建
@property (nonatomic, readonly, strong, nullable) UIImageView *imageView NS_AVAILABLE_IOS(3_0);

// 标题标签
@property (nonatomic, readonly, strong, nullable) UILabel *textLabel NS_AVAILABLE_IOS(3_0);

// 副标题标签
@property (nonatomic, readonly, strong, nullable) UILabel *detailTextLabel NS_AVAILABLE_IOS(3_0);

// If you want to customize cells by simply adding additional views, you should add them to the content view so they will be positioned appropriately as the cell transitions into and out of editing mode.
// 容纳视图，任何cell的子视图都应该添加在这个上面
@property (nonatomic, readonly, strong) UIView *contentView;

// Default is nil for cells in UITableViewStylePlain, and non-nil for UITableViewStyleGrouped. The 'backgroundView' will be added as a subview behind all other views.
// 背景视图
@property (nonatomic, strong, nullable) UIView *backgroundView;

// Default is nil for cells in UITableViewStylePlain, and non-nil for UITableViewStyleGrouped. The 'selectedBackgroundView' will be added as a subview directly above the backgroundView if not nil, or behind all other views. It is added as a subview only when the cell is selected. Calling -setSelected:animated: will cause the 'selectedBackgroundView' to animate in and out with an alpha fade.
// 选中状态下的背景视图
@property (nonatomic, strong, nullable) UIView *selectedBackgroundView;

// If not nil, takes the place of the selectedBackgroundView when using multiple selection.
// 多选选中时的背景视图
@property (nonatomic, strong, nullable) UIView *multipleSelectionBackgroundView NS_AVAILABLE_IOS(5_0);

// cell的标识符。当被重用的cell将要显示时，会调用这个方法，这个方法最大的用武之地是当你自定义的cell上面有图片时，如果产生了重用，图片可能会错乱（当图片来自异步下载时及其明显），这时我们可以重写这个方法把内容抹掉。
@property (nonatomic, readonly, copy, nullable) NSString *reuseIdentifier;
- (void)prepareForReuse;                                                        // if the cell is reusable (has a reuse identifier), this is called just before the cell is returned from the table view method dequeueReusableCellWithIdentifier:.  If you override, you MUST call super.

@property (nonatomic) UITableViewCellSelectionStyle   selectionStyle;             // default is UITableViewCellSelectionStyleBlue.

// 设置cell是否选中状态
@property (nonatomic, getter=isSelected) BOOL selected;

// 设置cell是否高亮状态
@property (nonatomic, getter=isHighlighted) BOOL highlighted;

//  cell选中状态的方法
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;

// cell高亮状态的方法
- (void)setHighlighted:(BOOL)highlighted animated:(BOOL)animated;               // animate between regular and highlighted state

// cell的编辑状态
@property (nonatomic, readonly) UITableViewCellEditingStyle editingStyle;         // default is UITableViewCellEditingStyleNone. This is set by UITableView using the delegate's value for cells who customize their appearance accordingly.

// 设置是否显示cell自带的自动排序控件
@property (nonatomic) BOOL showsReorderControl;        // default is NO
/**
 
 注意：要让cell实现拖动排序的功能，除了上面设置为YES，还需实现代理中的如下方法：
 
 -(BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath{
    return YES;
 }
 
 -(void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath *)destinationIndexPath{
 }
 
 */


// 设置编辑状态下是否显示缩进
@property (nonatomic) BOOL shouldIndentWhileEditing;   // default is YES.  This is unrelated to the indentation level below.

// 设置附件视图的风格(cell最右侧显示的视图)
@property (nonatomic) UITableViewCellAccessoryType accessoryType;

// 附件视图
@property (nonatomic, strong, nullable) UIView *accessoryView;

// cell编辑时的附件视图风格
@property (nonatomic) UITableViewCellAccessoryType editingAccessoryType;

// cell编辑时的附件视图
@property (nonatomic, strong, nullable) UIView *editingAccessoryView;

// 设置内容区域的缩进级别
@property (nonatomic) NSInteger indentationLevel;

// 设置每个级别的缩进宽度
@property (nonatomic) CGFloat indentationWidth;

// 设置分割线的偏移量
@property (nonatomic) UIEdgeInsets separatorInset NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED;

// 属性编辑状态
@property (nonatomic, getter=isEditing) BOOL editing;

// 设置是否编辑状态
- (void)setEditing:(BOOL)editing animated:(BOOL)animated;

// 返回是否目前正在显示删除按钮
@property(nonatomic, readonly) BOOL showingDeleteConfirmation;

//
@property (nonatomic) UITableViewCellFocusStyle focusStyle NS_AVAILABLE_IOS(9_0) UI_APPEARANCE_SELECTOR;

// These methods can be used by subclasses to animate additional changes to the cell when the cell is changing state
// Note that when the cell is swiped, the cell will be transitioned into the UITableViewCellStateShowingDeleteConfirmationMask state,
// but the UITableViewCellStateShowingEditControlMask will not be set.

// cell状态将要转换时调用的函数，可以在子类中重写
- (void)willTransitionToState:(UITableViewCellStateMask)state NS_AVAILABLE_IOS(3_0);

// cell状态已经转换时调用的函数，可以在子类中重写的枚举
- (void)didTransitionToState:(UITableViewCellStateMask)state NS_AVAILABLE_IOS(3_0);

@end

@interface UITableViewCell (UIDeprecated)

// Frame is ignored.  The size will be specified by the table view width and row height.
- (id)initWithFrame:(CGRect)frame reuseIdentifier:(nullable NSString *)reuseIdentifier NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

// Content properties.  These properties were deprecated in iPhone OS 3.0.  The textLabel and imageView properties above should be used instead.
// For selected attributes, set the highlighted attributes on the textLabel and imageView.

// 设置标题
@property (nonatomic, copy, nullable)   NSString *text NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

// 设置字体
@property (nonatomic, strong, nullable) UIFont   *font NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

// 设置对其模式
@property (nonatomic) NSTextAlignment   textAlignment NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

// 设置断行模式
@property (nonatomic) NSLineBreakMode   lineBreakMode NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

// 设置字体颜色
@property (nonatomic, strong, nullable) UIColor  *textColor NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

// 设置选中状态下的字体颜色
@property (nonatomic, strong, nullable) UIColor  *selectedTextColor NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

// 设置图片
@property (nonatomic, strong, nullable) UIImage  *image NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

// 设置选中状态时的图片
@property (nonatomic, strong, nullable) UIImage  *selectedImage NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

// 设置编辑的时候是否隐藏附件视图
@property (nonatomic) BOOL hidesAccessoryWhenEditing NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;   // default is YES

// Use the table view data source method -tableView:commitEditingStyle:forRowAtIndexPath: or the table view delegate method -tableView:accessoryButtonTappedForRowWithIndexPath: instead
@property (nonatomic, assign, nullable) id target NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

@property (nonatomic, nullable) SEL editAction NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                  // action to call on insert/delete call. set by UITableView
@property (nonatomic, nullable) SEL accessoryAction NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;             // action to call on accessory view clicked. set by UITableView

@end

NS_ASSUME_NONNULL_END

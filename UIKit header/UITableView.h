//
//  UITableView.h
//  UIKit
//
//  Copyright (c) 2005-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UISwipeGestureRecognizer.h>
#import <UIKit/UITableViewCell.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN



// 初始化表视图的frame大小并且设置一个风格，UITableViewStyle是一个枚举
typedef NS_ENUM(NSInteger, UITableViewStyle) {
    // 标准的表视图风格
    UITableViewStylePlain,          // regular table view
    // 分组的表视图风格
    UITableViewStyleGrouped         // preferences style table view
};

// 样式展示风格
typedef NS_ENUM(NSInteger, UITableViewScrollPosition) {
    // 同UITableViewScrollPositionTop
    UITableViewScrollPositionNone,
    // 定位完成后，将定位的行显示在tableView的顶部
    UITableViewScrollPositionTop,    
    // 定位完成后，将定位的行显示在tableView的中间
    UITableViewScrollPositionMiddle,
    // 定位完成后，将定位的行显示在tableView最下面
    UITableViewScrollPositionBottom
};                // scroll so row of interest is completely visible at top/center/bottom of view

// UITableViewRowAnimation参数是一个枚举，枚举的动画类型如下
typedef NS_ENUM(NSInteger, UITableViewRowAnimation) {
    //淡入淡出
    UITableViewRowAnimationFade,
    //从右滑入
    UITableViewRowAnimationRight,
    //从左滑入
    UITableViewRowAnimationLeft,
    //从上滑入
    UITableViewRowAnimationTop,
    //从下滑入
    UITableViewRowAnimationBottom,
    //没有动画
    UITableViewRowAnimationNone,
    UITableViewRowAnimationMiddle,
    // 自动选择合适的动画
    UITableViewRowAnimationAutomatic = 100  // available in iOS 5.0.  chooses an appropriate animation style for you
};

// Including this constant string in the array of strings returned by sectionIndexTitlesForTableView: will cause a magnifying glass icon to be displayed at that location in the index.
// This should generally only be used as the first title in the index.
UIKIT_EXTERN NSString *const UITableViewIndexSearch NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;

// Returning this value from tableView:heightForHeaderInSection: or tableView:heightForFooterInSection: results in a height that fits the value returned from
// tableView:titleForHeaderInSection: or tableView:titleForFooterInSection: if the title is not nil.
UIKIT_EXTERN const CGFloat UITableViewAutomaticDimension NS_AVAILABLE_IOS(5_0);

@class UITableView;
@class UINib;
@protocol UITableViewDataSource;
@class UILongPressGestureRecognizer;
@class UITableViewHeaderFooterView;
@class UIRefreshControl;
@class UIVisualEffect;

typedef NS_ENUM(NSInteger, UITableViewRowActionStyle) {
    UITableViewRowActionStyleDefault = 0,
    UITableViewRowActionStyleDestructive = UITableViewRowActionStyleDefault,
    UITableViewRowActionStyleNormal
} NS_ENUM_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED;

NS_CLASS_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED @interface UITableViewRowAction : NSObject <NSCopying>

+ (instancetype)rowActionWithStyle:(UITableViewRowActionStyle)style title:(nullable NSString *)title handler:(void (^)(UITableViewRowAction *action, NSIndexPath *indexPath))handler;

@property (nonatomic, readonly) UITableViewRowActionStyle style;
@property (nonatomic, copy, nullable) NSString *title;
@property (nonatomic, copy, nullable) UIColor *backgroundColor; // default background color is dependent on style
@property (nonatomic, copy, nullable) UIVisualEffect* backgroundEffect;

@end

NS_CLASS_AVAILABLE_IOS(9_0) @interface UITableViewFocusUpdateContext : UIFocusUpdateContext

@property (nonatomic, strong, readonly, nullable) NSIndexPath *previouslyFocusedIndexPath;
@property (nonatomic, strong, readonly, nullable) NSIndexPath *nextFocusedIndexPath;

@end

//_______________________________________________________________________________________________________________
// this represents the display and behaviour of the cells.

@protocol UITableViewDelegate<NSObject, UIScrollViewDelegate>

@optional

// Display customization

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)tableView:(UITableView *)tableView willDisplayHeaderView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
- (void)tableView:(UITableView *)tableView willDisplayFooterView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
- (void)tableView:(UITableView *)tableView didEndDisplayingCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath*)indexPath NS_AVAILABLE_IOS(6_0);
- (void)tableView:(UITableView *)tableView didEndDisplayingHeaderView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
- (void)tableView:(UITableView *)tableView didEndDisplayingFooterView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);

// Variable height support

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section;
- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section;

// Use the estimatedHeight methods to quickly calcuate guessed values which will allow for fast load times of the table.
// If these methods are implemented, the above -tableView:heightForXXX calls will be deferred until views are ready to be displayed, so more expensive logic can be placed there.
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(7_0);
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForHeaderInSection:(NSInteger)section NS_AVAILABLE_IOS(7_0);
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForFooterInSection:(NSInteger)section NS_AVAILABLE_IOS(7_0);

// Section header & footer information. Views are preferred over title should you decide to provide both

- (nullable UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section;   // custom view for header. will be adjusted to default or specified header height
- (nullable UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section;   // custom view for footer. will be adjusted to default or specified footer height

// Accessories (disclosures). 

- (UITableViewCellAccessoryType)tableView:(UITableView *)tableView accessoryTypeForRowWithIndexPath:(NSIndexPath *)indexPath NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;
- (void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath;

// Selection

// -tableView:shouldHighlightRowAtIndexPath: is called when a touch comes down on a row. 
// Returning NO to that message halts the selection process and does not cause the currently selected row to lose its selected look while the touch is down.
- (BOOL)tableView:(UITableView *)tableView shouldHighlightRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(6_0);
- (void)tableView:(UITableView *)tableView didHighlightRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(6_0);
- (void)tableView:(UITableView *)tableView didUnhighlightRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(6_0);

// 当用户将要选中表格中的某行时触发方法
- (nullable NSIndexPath *)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath;

// 当用户将要取消选中表格中某行时触发
- (nullable NSIndexPath *)tableView:(UITableView *)tableView willDeselectRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(3_0);
// Called after the user changes the selection.

// 当用户完成选中表格中的某行时触发方法
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;

// 取消选中时候用的方法   （不常用）
- (void)tableView:(UITableView *)tableView didDeselectRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(3_0);

// Editing

// Allows customization of the editingStyle for a particular cell located at 'indexPath'. If not implemented, all editable cells will have UITableViewCellEditingStyleDelete set for them when the table has editing property set to YES.
// 指定 tableView编辑的样式 (添加、删除) 需要实现<UITableViewDelegate>
- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath;
- (nullable NSString *)tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;
- (nullable NSArray<UITableViewRowAction *> *)tableView:(UITableView *)tableView editActionsForRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED; // supercedes -tableView:titleForDeleteConfirmationButtonForRowAtIndexPath: if return value is non-nil

// Controls whether the background is indented while editing.  If not implemented, the default is YES.  This is unrelated to the indentation level below.  This method only applies to grouped style table views.
- (BOOL)tableView:(UITableView *)tableView shouldIndentWhileEditingRowAtIndexPath:(NSIndexPath *)indexPath;

// The willBegin/didEnd methods are called whenever the 'editing' property is automatically changed by the table (allowing insert/delete/move). This is done by a swipe activating a single row
- (void)tableView:(UITableView*)tableView willBeginEditingRowAtIndexPath:(NSIndexPath *)indexPath __TVOS_PROHIBITED;
- (void)tableView:(UITableView*)tableView didEndEditingRowAtIndexPath:(NSIndexPath *)indexPath __TVOS_PROHIBITED;

// Moving/reordering

// Allows customization of the target row for a particular row as it is being moved/reordered
- (NSIndexPath *)tableView:(UITableView *)tableView targetIndexPathForMoveFromRowAtIndexPath:(NSIndexPath *)sourceIndexPath toProposedIndexPath:(NSIndexPath *)proposedDestinationIndexPath;               

// Indentation

- (NSInteger)tableView:(UITableView *)tableView indentationLevelForRowAtIndexPath:(NSIndexPath *)indexPath; // return 'depth' of row for hierarchies

// Copy/Paste.  All three methods must be implemented by the delegate.

- (BOOL)tableView:(UITableView *)tableView shouldShowMenuForRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(5_0);
- (BOOL)tableView:(UITableView *)tableView canPerformAction:(SEL)action forRowAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender NS_AVAILABLE_IOS(5_0);
- (void)tableView:(UITableView *)tableView performAction:(SEL)action forRowAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender NS_AVAILABLE_IOS(5_0);

// Focus

- (BOOL)tableView:(UITableView *)tableView canFocusRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0);
- (BOOL)tableView:(UITableView *)tableView shouldUpdateFocusInContext:(UITableViewFocusUpdateContext *)context NS_AVAILABLE_IOS(9_0);
- (void)tableView:(UITableView *)tableView didUpdateFocusInContext:(UITableViewFocusUpdateContext *)context withAnimationCoordinator:(UIFocusAnimationCoordinator *)coordinator NS_AVAILABLE_IOS(9_0);
- (nullable NSIndexPath *)indexPathForPreferredFocusedViewInTableView:(UITableView *)tableView NS_AVAILABLE_IOS(9_0);

@end

UIKIT_EXTERN NSString *const UITableViewSelectionDidChangeNotification;


//_______________________________________________________________________________________________________________

NS_CLASS_AVAILABLE_IOS(2_0) @interface UITableView : UIScrollView <NSCoding>

- (instancetype)initWithFrame:(CGRect)frame style:(UITableViewStyle)style NS_DESIGNATED_INITIALIZER; // must specify style at creation. -initWithFrame: calls this with UITableViewStylePlain
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

// 获取表视图的风格(只读属性)
@property (nonatomic, readonly) UITableViewStyle style;

// 设置表示图代理和数据源代理
@property (nonatomic, weak, nullable) id <UITableViewDataSource> dataSource;
@property (nonatomic, weak, nullable) id <UITableViewDelegate> delegate;

// 设置表示图的行高(默认为44)
@property (nonatomic) CGFloat rowHeight;

// 设置分区的头视图高度和尾视图高度(当代理方法没有实现时才有效)，如果没有设置将返回默认值
@property (nonatomic) CGFloat sectionHeaderHeight;
@property (nonatomic) CGFloat sectionFooterHeight;

// 设置一个行高的估计值，默认为0。这个属性官方的解释是如果你的tableView的行高是可变的，那么设计一个估计高度可以加快代码的运行效率。
@property (nonatomic) CGFloat estimatedRowHeight NS_AVAILABLE_IOS(7_0);

// 分别设置分区头视图的估计高度，默认为0
@property (nonatomic) CGFloat estimatedSectionHeaderHeight NS_AVAILABLE_IOS(7_0);

// 设置分区尾视图的估计高度
@property (nonatomic) CGFloat estimatedSectionFooterHeight NS_AVAILABLE_IOS(7_0);

// 设置分割线的位置
@property (nonatomic) UIEdgeInsets separatorInset NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR;
/**

 如果细心，你可能会发现系统默认的tableView的分割线左端并没有顶到边沿。通过这个属性，可以手动设置分割线的位置偏移，比如你向让tableView的分割线只显示右半边，可以如下设置：
 
    UITableView * tab = [[UITableView alloc]initWithFrame:self.view.frame style:UITableViewStylePlain];
    tab.separatorInset=UIEdgeInsetsMake(0, tab.frame.size.width/2, 0,0);
 
 **/

// 设置tableView背景view视图
@property (nonatomic, strong, nullable) UIView *backgroundView NS_AVAILABLE_IOS(3_2);

// 重载tableView。重载一切并重新显示可见行，我们只保留有关可见的信息。如果表内容缩小，将调整偏移量。
- (void)reloadData;

// 重载索引栏，这个方法常用语新加或者删除了索引类别而无需刷新整个表视图的情况下。
- (void)reloadSectionIndexTitles NS_AVAILABLE_IOS(3_0);   // reloads the index bar.

// 获取分区数
@property (nonatomic, readonly) NSInteger numberOfSections;

// 根据分区获取行数
- (NSInteger)numberOfRowsInSection:(NSInteger)section;

// 获取分区的大小(包括头视图，所有行和尾视图)
- (CGRect)rectForSection:(NSInteger)section;
- (CGRect)rectForHeaderInSection:(NSInteger)section;
- (CGRect)rectForFooterInSection:(NSInteger)section;
- (CGRect)rectForRowAtIndexPath:(NSIndexPath *)indexPath;

// 获取某个点在tableView中的位置信息，如果点在表格行的外部将返回空。
- (nullable NSIndexPath *)indexPathForRowAtPoint:(CGPoint)point;

// 获取某个cell在tableView中的位置信息，如果不可见将返回空
- (nullable NSIndexPath *)indexPathForCell:(UITableViewCell *)cell;

// 根据一个矩形范围返回一个信息数组，数组中是每一行row的位置信息
- (nullable NSArray<NSIndexPath *> *)indexPathsForRowsInRect:(CGRect)rect;

// 通过位置路径获取cell，如果单元格不可见或索引路径不在范围内将返回空
- (nullable __kindof UITableViewCell *)cellForRowAtIndexPath:(NSIndexPath *)indexPath;

// 获取所有可见的cell
@property (nonatomic, readonly) NSArray<__kindof UITableViewCell *> *visibleCells;

// 获取所有可见行的位置信息
@property (nonatomic, readonly, nullable) NSArray<NSIndexPath *> *indexPathsForVisibleRows;

// 根据分区获取头视图
- (nullable UITableViewHeaderFooterView *)headerViewForSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);

// 根据分区获取尾视图
- (nullable UITableViewHeaderFooterView *)footerViewForSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);

// 使表示图定位到某一位置(行)
- (void)scrollToRowAtIndexPath:(NSIndexPath *)indexPath atScrollPosition:(UITableViewScrollPosition)scrollPosition animated:(BOOL)animated;

// 使表示图定位到选中行
- (void)scrollToNearestSelectedRowAtScrollPosition:(UITableViewScrollPosition)scrollPosition animated:(BOOL)animated;

// 表格的插入、删除、重载

// 插入分区
- (void)insertSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation;

// 删除分区
- (void)deleteSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation;

// 重载一个分区
- (void)reloadSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation NS_AVAILABLE_IOS(3_0);

// 移动一个分区
- (void)moveSection:(NSInteger)section toSection:(NSInteger)newSection NS_AVAILABLE_IOS(5_0);

// 插入一些行
- (void)insertRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation;

// 删除一些行
- (void)deleteRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation;

// 重载一些行
- (void)reloadRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation NS_AVAILABLE_IOS(3_0);

// 移动某行
- (void)moveRowAtIndexPath:(NSIndexPath *)indexPath toIndexPath:(NSIndexPath *)newIndexPath NS_AVAILABLE_IOS(5_0);

// 了解了上面几个函数，我们来看什么是操作刷新块：当我们调用的上面的函数时，tableView会立刻调用代理方法进行刷新，如果其中我们所做的操作是删除某行，而然数据源数组我们可能并没有刷新，程序就会崩溃掉，原因是代理返回的信息和我们删除后不符。
// IOS为我们提供了下面两个函数解决这个问题：

// 开始块标志
- (void)beginUpdates;   // allow multiple insert/delete of rows and sections to be animated simultaneously. Nestable

// 结束块标志
- (void)endUpdates;     // only call insert/delete/reload calls or change the editing state inside an update block.  otherwise things like row count, etc. may be invalid.

/**
    我们可以将我们要做的操作全部写在这个块中，那么，只有当程序执行到结束快标志后，才会调用代理刷新方法。代码示例如下：
    [tab beginUpdates];
    [tab deleteRowsAtIndexPaths:@[[NSIndexPath indexPathForRow:1 inSection:0]] withRowAnimation:UITableViewRowAnimationLeft];
    [dataArray removeObjectAtIndex:1];
    [tab endUpdates];
 **/
 
// 编辑，当设置时，行显示插入、删除、重新排序去控制基于数据源的请求

// 设置是否是编辑状态(编辑状态下的cell左边会出现一个减号，点击右边会划出删除按钮)
@property (nonatomic, getter=isEditing) BOOL editing;                             // default is NO. setting is not animated.

// 让tableView处于编辑状态
- (void)setEditing:(BOOL)editing animated:(BOOL)animated;

// 设置cell是否可以被选中(默认为YES)，无论行能都被选中当不在编辑模式时控制
@property (nonatomic) BOOL allowsSelection NS_AVAILABLE_IOS(3_0);

// 设置cell编辑模式下是否可以被选中
@property (nonatomic) BOOL allowsSelectionDuringEditing;

// 设置是否支持多选 （default is NO. Controls whether multiple rows can be selected simultaneously）
@property (nonatomic) BOOL allowsMultipleSelection NS_AVAILABLE_IOS(5_0);

// 设置编辑模式下是否支持多选 （default is NO. Controls whether multiple rows can be selected simultaneously in editing mode）
@property (nonatomic) BOOL allowsMultipleSelectionDuringEditing NS_AVAILABLE_IOS(5_0);


// 选中单元格的相关操作

// 获取选中cell的位置信息（returns nil or index path representing section and row of selection.）
@property (nonatomic, readonly, nullable) NSIndexPath *indexPathForSelectedRow;

// 获取多选cell的位置信息（returns nil or a set of index paths representing the sections and rows of the selection.）
@property (nonatomic, readonly, nullable) NSArray<NSIndexPath *> *indexPathsForSelectedRows NS_AVAILABLE_IOS(5_0);

// 代码手动选中
- (void)selectRowAtIndexPath:(nullable NSIndexPath *)indexPath animated:(BOOL)animated scrollPosition:(UITableViewScrollPosition)scrollPosition;

// 取消选中某行
- (void)deselectRowAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;

// Appearance

// 设置索引栏最小显示行数，默认显示为0
@property (nonatomic) NSInteger sectionIndexMinimumDisplayRowCount;

// 设置索引栏字体颜色（color used for text of the section index）
@property (nonatomic, strong, nullable) UIColor *sectionIndexColor NS_AVAILABLE_IOS(6_0) UI_APPEARANCE_SELECTOR;

// 设置索引栏背景颜色（the background color of the section index while not being touched）
@property (nonatomic, strong, nullable) UIColor *sectionIndexBackgroundColor NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR;

// 设置索引栏被选中时的颜色（the background color of the section index while it is being touched）
@property (nonatomic, strong, nullable) UIColor *sectionIndexTrackingBackgroundColor NS_AVAILABLE_IOS(6_0) UI_APPEARANCE_SELECTOR;

// 设置分割线的风格
@property (nonatomic) UITableViewCellSeparatorStyle separatorStyle __TVOS_PROHIBITED; // default is UITableViewCellSeparatorStyleSingleLine

// 设置分割线颜色，默认为灰色
@property (nonatomic, strong, nullable) UIColor *separatorColor UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED;

// 设置分割线毛玻璃效果(IOS8之后可用)
@property (nonatomic, copy, nullable) UIVisualEffect *separatorEffect NS_AVAILABLE_IOS(8_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED; //

// 判断是否需要根据内容留有空白
@property (nonatomic) BOOL cellLayoutMarginsFollowReadableWidth NS_AVAILABLE_IOS(9_0); // if cell margins are derived from the width of the readableContentGuide.

// 设置tableView头视图
@property (nonatomic, strong, nullable) UIView *tableHeaderView;

// 设置footerView头视图
@property (nonatomic, strong, nullable) UIView *tableFooterView;                           // accessory view below content. default is nil. not to be confused with section footer

// 从复用池中取cell
- (nullable __kindof UITableViewCell *)dequeueReusableCellWithIdentifier:(NSString *)identifier;

// 获取一个已注册的cell
- (__kindof UITableViewCell *)dequeueReusableCellWithIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(6_0);

// 从复用池获取头视图或尾视图
- (nullable __kindof UITableViewHeaderFooterView *)dequeueReusableHeaderFooterViewWithIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(6_0);

// 通过xib文件注册cell
- (void)registerNib:(nullable UINib *)nib forCellReuseIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(5_0);

// 通过OC类注册cell
- (void)registerClass:(nullable Class)cellClass forCellReuseIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(6_0);

// 通过xib文件和OC类获取注册头视图和尾视图
- (void)registerNib:(nullable UINib *)nib forHeaderFooterViewReuseIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(6_0);
- (void)registerClass:(nullable Class)aClass forHeaderFooterViewReuseIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(6_0);

// Focus

// 使用Apple TV遥控器控制屏幕上的用户界面
@property (nonatomic) BOOL remembersLastFocusedIndexPath NS_AVAILABLE_IOS(9_0); // defaults to NO. If YES, when focusing on a table view the last focused index path is focused automatically. If the table view has never been focused, then the preferred focused index path is used.

@end

//_______________________________________________________________________________________________________________
// this protocol represents the data model object. as such, it supplies no information about appearance (including the cells)

@protocol UITableViewDataSource<NSObject>

@required

// 控制每组中有多少个单元格
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section;

// Row display. Implementers should *always* try to reuse cells by setting each cell's reuseIdentifier and querying for available reusable cells with dequeueReusableCellWithIdentifier:
// Cell gets various attributes set automatically based on table (separators) and data source (accessory views, editing controls)

// 控制单元格的内容
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;

@optional
//指定有多少个分区(Section)
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView;              // Default is 1 if not implemented

- (nullable NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section;    // fixed font style. use custom view (UILabel) if you want something different
- (nullable NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section;

// Editing

// 指定 tableView 那些行可以编辑，需要实现<UITableView DataSource>
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath;

// Moving/reordering

// 该方法返回值决定指定indexPath对应的cell是否可以移动
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath;

// Index

// 该方法返回值用于在表格右边建立一个浮动的索引
- (nullable NSArray<NSString *> *)sectionIndexTitlesForTableView:(UITableView *)tableView __TVOS_PROHIBITED;                                                    // return list of section titles to display in section index view (e.g. "ABCD...Z#")
- (NSInteger)tableView:(UITableView *)tableView sectionForSectionIndexTitle:(NSString *)title atIndex:(NSInteger)index __TVOS_PROHIBITED;  // tell table which section corresponds to section title/index (e.g. "B",1))

// Data manipulation - insert and delete support

// After a row has the minus or plus button invoked (based on the UITableViewCellEditingStyle for the cell), the dataSource must commit the change
// Not called for edit actions using UITableViewRowAction - the action's handler will be invoked instead

// 当用户对指定表格行编辑(包括插入和删除)时触发该方法
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath;

// 该方法触发移动  通常对数据进行处理(重要)
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath *)destinationIndexPath;

@end


@interface NSIndexPath (UITableView)

// 返回表格中指定点所在的indexPath
+ (instancetype)indexPathForRow:(NSInteger)row inSection:(NSInteger)section;

@property (nonatomic, readonly) NSInteger section;
@property (nonatomic, readonly) NSInteger row;

@end

NS_ASSUME_NONNULL_END

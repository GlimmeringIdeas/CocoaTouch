//
//  UIScrollView.h
//  UIKit
//
//  Copyright (c) 2007-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

// 枚举indicator风格
typedef NS_ENUM(NSInteger, UIScrollViewIndicatorStyle) {
    // 默认风格
    UIScrollViewIndicatorStyleDefault,
    // 黑色风格
    UIScrollViewIndicatorStyleBlack,
    // 白色风格
    UIScrollViewIndicatorStyleWhite
};

// 枚举键盘的消失方式
typedef NS_ENUM(NSInteger, UIScrollViewKeyboardDismissMode) {
    UIScrollViewKeyboardDismissModeNone,
    // 拖拉页面时消失
    UIScrollViewKeyboardDismissModeOnDrag,
    
    UIScrollViewKeyboardDismissModeInteractive,
} NS_ENUM_AVAILABLE_IOS(7_0);

// 手指滑动后抬起，页面的减速速率。可以使用UIScrollViewDecelerationRateNormal和UIScrollViewDecelerationRateFast常量值来设置合理的减速速率。
UIKIT_EXTERN const CGFloat UIScrollViewDecelerationRateNormal NS_AVAILABLE_IOS(3_0);
UIKIT_EXTERN const CGFloat UIScrollViewDecelerationRateFast NS_AVAILABLE_IOS(3_0);

@class UIEvent, UIImageView, UIPanGestureRecognizer, UIPinchGestureRecognizer;
@protocol UIScrollViewDelegate;

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIScrollView : UIView <NSCoding>

//UIScrollView当前滚动的位置
@property(nonatomic) CGPoint  contentOffset; // default CGPointZero

//设置UIScrollView的滚动范围
@property(nonatomic) CGSize  contentSize; // default CGSizeZero

//这个属性可以在四周增加滚动范围
@property(nonatomic) UIEdgeInsets  contentInset; // default UIEdgeInsetsZero. add additional scroll area around content


@property(nullable,nonatomic,weak) id<UIScrollViewDelegate> delegate; // default nil. weak reference

//指定控件是否只能在一个方向上滚动
@property(nonatomic,getter=isDirectionalLockEnabled) BOOL directionalLockEnabled;

//是否有弹簧效果
@property(nonatomic) BOOL  bounces;

//设置垂直方向的反弹是否有效，默认为有效
@property(nonatomic) BOOL  alwaysBounceVertical;

//设置水平方向的反弹是否有效，默认为无效
@property(nonatomic) BOOL  alwaysBounceHorizontal;

//分页效果，默认是不分页。UIScrollView会被分割成多个独立页面，用户的滚动体验则变成了页面翻转
@property(nonatomic,getter=isPagingEnabled) BOOL  pagingEnabled __TVOS_PROHIBITED;
//一般会配合UIPageControl增强分页效果，UIPageControl常用属性
//NSInteger numberOfPages : 总页数
//NSInteger currentPage : 当前的页码


// 是否能滚动
@property(nonatomic,getter=isScrollEnabled) BOOL  scrollEnabled;

//是否显示水平方向的滚动条
@property(nonatomic) BOOL  showsHorizontalScrollIndicator;

//是否显示垂直方向的滚动条
@property(nonatomic) BOOL  showsVerticalScrollIndicator;

//滚动指标点到滚动视图的边缘的距离。
@property(nonatomic) UIEdgeInsets  scrollIndicatorInsets;

//设定滚动条的样式
@property(nonatomic) UIScrollViewIndicatorStyle   indicatorStyle;

//定滚动条在scrollerView中的位置
@property(nonatomic) CGFloat  decelerationRate NS_AVAILABLE_IOS(3_0);

// 跳转到所指定内容的坐标。但是当设置了“scroview.pagingEnabled = YES”的时候。在你执行setContentOffset方法过后,再执行其他操作时,指定内容的坐标将被还原,pagingEnabled属性会对它进行重置.
- (void)setContentOffset:(CGPoint)contentOffset animated:(BOOL)animated;
//contentOffset：从内容视图的原点偏移的一个点


//此方法滚动查看内容，以便由rect定义的区域仅仅是滚动视图内是可见的。如果该地区已是可见的，该方法什么都不做
- (void)scrollRectToVisible:(CGRect)rect animated:(BOOL)animated;
// rect：定义一个矩形面积的内容视图。


//暂时显示滚动指标。
- (void)flashScrollIndicators;


//当touch后还没有拖动的时候值是YES，否则NO
@property(nonatomic,readonly,getter=isTracking) BOOL  tracking;        // returns YES if user has touched. may not yet have started dragging

//是否正在被拖拽
@property(nonatomic,readonly,getter=isDragging) BOOL  dragging;

//是否正在减速
@property(nonatomic,readonly,getter=isDecelerating) BOOL  decelerating;

//控制视图是否延时调用开始滚动的方法
@property(nonatomic) BOOL delaysContentTouches;

//一个布尔值，控制是否涉及到的内容视图中总是导致跟踪。
@property(nonatomic) BOOL canCancelContentTouches;


- (BOOL)touchesShouldBegin:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event inContentView:(UIView *)view;


- (BOOL)touchesShouldCancelInContentView:(UIView *)view;


//缩小的最小比例，默认为1.0
@property(nonatomic) CGFloat minimumZoomScale;

//放大的最大比例，默认为1.0但必须比minimumZoomScale大
@property(nonatomic) CGFloat maximumZoomScale;

//此值确定多少内容目前正在缩放。默认值是1.0
@property(nonatomic) CGFloat zoomScale NS_AVAILABLE_IOS(3_0);

//新的值应该在是minimumZoomScale和maximumZoomScale之间
- (void)setZoomScale:(CGFloat)scale animated:(BOOL)animated NS_AVAILABLE_IOS(3_0);

//缩小到特定区域的内容，所以它是在接收器中可见。
- (void)zoomToRect:(CGRect)rect animated:(BOOL)animated NS_AVAILABLE_IOS(3_0);

//如果这个属性的值是YES并且变焦缩放超过上限或下限,返回他们之前滚动视图暂时缩放内容。如果这属性是NO，立即停止在一个比例限制缩放。默认是YES。
@property(nonatomic) BOOL  bouncesZoom;

//是否正在缩放
@property(nonatomic,readonly,getter=isZooming)       BOOL zooming;

//如果这个属性的值是YES并且变焦缩放超过上限或下限,返回他们之前滚动视图暂时缩放内容。如果这属性是NO，立即停止在一个比例限制缩放。默认是YES。
@property(nonatomic,readonly,getter=isZoomBouncing)  BOOL zoomBouncing;  // returns YES if we are in the middle of zooming back to the min/max value

//当设为YES，发生这种姿态时滚动视图跳转到内容顶端，此属性的默认值是YES 。
@property(nonatomic) BOOL  scrollsToTop __TVOS_PROHIBITED;          // default is YES.


@property(nonatomic, readonly) UIPanGestureRecognizer *panGestureRecognizer NS_AVAILABLE_IOS(5_0);


@property(nullable, nonatomic, readonly) UIPinchGestureRecognizer *pinchGestureRecognizer NS_AVAILABLE_IOS(5_0);


@property(nonatomic, readonly) UIGestureRecognizer *directionalPressGestureRecognizer UIKIT_AVAILABLE_TVOS_ONLY(9_0);

@property(nonatomic) UIScrollViewKeyboardDismissMode keyboardDismissMode NS_AVAILABLE_IOS(7_0); // default is UIScrollViewKeyboardDismissModeNone

@end

@protocol UIScrollViewDelegate<NSObject>

@optional

// 任何偏移变化的时候触发，也就是只要滚动了就会触发
- (void)scrollViewDidScroll:(UIScrollView *)scrollView;

// 缩放过程中的时候调用
- (void)scrollViewDidZoom:(UIScrollView *)scrollView NS_AVAILABLE_IOS(3_2); // any zoom scale changes

// 将要开始拖拽视图的时候触发
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView;

// 将要结束拖拽视图的时候触发
- (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset NS_AVAILABLE_IOS(5_0);


// 停止拖拽的时候执行
- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate;

// 将开始降速时执行
- (void)scrollViewWillBeginDecelerating:(UIScrollView *)scrollView;

//  减速停止的时候执行
- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView;

// 滚动动画停止时执行,代码改变时出发,也就是setContentOffset改变时
- (void)scrollViewDidEndScrollingAnimation:(UIScrollView *)scrollView;

// 设置放大缩小的视图，要是uiscrollview的subview
- (nullable UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView;

// 开始放大或者缩小
- (void)scrollViewWillBeginZooming:(UIScrollView *)scrollView withView:(nullable UIView *)view NS_AVAILABLE_IOS(3_2);

// 缩放完毕的时候调用
- (void)scrollViewDidEndZooming:(UIScrollView *)scrollView withView:(nullable UIView *)view atScale:(CGFloat)scale; // scale between minimum and maximum. called after any 'bounce' animations

// 是否支持滑动至顶部
- (BOOL)scrollViewShouldScrollToTop:(UIScrollView *)scrollView;   // return a yes if you want to scroll to the top. if not defined, assumes YES

// 滑动到顶部时调用该方法
- (void)scrollViewDidScrollToTop:(UIScrollView *)scrollView;      // called when scrolling animation finished. may be called immediately if already at top

@end

NS_ASSUME_NONNULL_END




//关于UIScrollView左右滚动判断

//工作需要，需要实现UIScrollView左右拖动加载，
//首先设置pageEnable=YES；
//然后通过Delegate实现相关方法。

//将要开始拖拽，手指已经放在view上并准备拖动的那一刻
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView{
    //拖动前的起始坐标
    startContentOffsetX = scrollView.contentOffset.x;
}

//将要结束拖拽，手指已经离开在view上并准备拖动的那一刻
- (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset{
    //将要停止前的坐标
    willEndContentOffsetX = scrollView.contentOffset.x;
    
}

//  减速停止的时候执行
- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView{
    // 最终停止的坐标
    endContentOffsetX = scrollView.contentOffset.x;
    
    if (endContentOffsetX < willEndContentOffsetX && willEndContentOffsetX < startContentOffsetX) {
        //画面从右往左移动，前一页的时候执行
        <#code#>
    } else if (endContentOffsetX > willEndContentOffsetX && willEndContentOffsetX > startContentOffsetX) {
        //画面从左往右移动，后一页的时候执行
        <#code#>
    }
}



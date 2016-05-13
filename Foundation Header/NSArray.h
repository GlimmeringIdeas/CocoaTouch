/*	NSArray.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSObjCRuntime.h>

@class NSData, NSIndexSet, NSString, NSURL;

/****************	Immutable Array		****************/

NS_ASSUME_NONNULL_BEGIN

@interface NSArray<__covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

@property (readonly) NSUInteger count;
#import<Foundation / Foundation.h>

// 获取当前索引的字符串
- (ObjectType)objectAtIndex:(NSUInteger)index;

- (instancetype)init NS_DESIGNATED_INITIALIZER;

// 创建数组并初始化内容
- (instancetype)initWithObjects:(const ObjectType [])objects count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
// NSArray *arrayInit = [[NSArray alloc] initWithObjects:@"one" , @"two" , @"three" , nil];

- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSArray<ObjectType> (NSExtendedArray)

// 在当前数据中追加一个新的对象，并且返回一个新的数据对象(新的数组对象和被追加的对象，是两个不同的数组对象)。
- (NSArray<ObjectType> *)arrayByAddingObject:(ObjectType)anObject;

// 在当前的数组中追加一个新的数据，并且返回一个新的数组对象。
- (NSArray<ObjectType> *)arrayByAddingObjectsFromArray:(NSArray<ObjectType> *)otherArray;

// 使用当前的数组生成一个字符串，新生成的字符串使用提供的separator 字符进行分割。
- (NSString *)componentsJoinedByString:(NSString *)separator;

// 检测数据中是否包含指定的对象元素
- (BOOL)containsObject:(ObjectType)anObject;

// 使用当前的数组生成字符串。可以重写description 改变生成的字符串。相当于java 中的toString 方法。
@property (readonly, copy) NSString *description;

// 根据设置的locale 进行连接数组
- (NSString *)descriptionWithLocale:(nullable id)locale;
- (NSString *)descriptionWithLocale:(nullable id)locale indent:(NSUInteger)level;

// 两个数组的第一个元素是否相同，如果相同，则返回 数组中，第一个元素的字符串，反之，返回null 对象
- (nullable ObjectType)firstObjectCommonWithArray:(NSArray<ObjectType> *)otherArray;

// 从数组中获取 NSRange 对象的数据存放到objects 中，NSRange 的数据标示从location,开始后面length 个数据
- (void)getObjects:(ObjectType __unsafe_unretained [])objects range:(NSRange)range;

// 判断制定的anObject 对象是否存在数组中如果存在返回，对象所在的下标
- (NSUInteger)indexOfObject:(ObjectType)anObject;

// 判断制定的元素，是否在数组中，数组查询的位置，是从range.location 的位置开始，到range.length 的长度结束。
- (NSUInteger)indexOfObject:(ObjectType)anObject inRange:(NSRange)range;

//同上面两个方法一项，测试指定的对象是否在数组中不同的是，这里使用指针进行比较
- (NSUInteger)indexOfObjectIdenticalTo:(ObjectType)anObject;

// 如果数据存在，返回指定的下标，如果不存在，则返回NSNotFund 。
- (NSUInteger)indexOfObjectIdenticalTo:(ObjectType)anObject inRange:(NSRange)range;

// 比较两个数组是否相同 ，数组长度相同，并且相同位置上的元素也相同。
- (BOOL)isEqualToArray:(NSArray<ObjectType> *)otherArray;


@property (nullable, nonatomic, readonly) ObjectType firstObject NS_AVAILABLE(10_6, 4_0);

@property (nullable, nonatomic, readonly) ObjectType lastObject;

//使用数组返回一个 NSEnumerator 对象，这个对象类似与一个指针，可以用来遍历 整个数组 指针从前向后遍历
- (NSEnumerator<ObjectType> *)objectEnumerator;

// 返回一个NSEnumerator 对象，这个对象类似一个指针，可以用来遍历真个数据，所不同的是，这个指针，是从后向前遍历。
- (NSEnumerator<ObjectType> *)reverseObjectEnumerator;

// 生成一个NSData 的对象，主要是用来进行数组的排序。 在下面的方法中使用这个对象
@property (readonly, copy) NSData *sortedArrayHint;

// 进行数组的排序
- (NSArray<ObjectType> *)sortedArrayUsingFunction:(NSInteger (*)(ObjectType, ObjectType, void * __nullable))comparator context:(nullable void *)context;

// 和上面的方法类似，也是苹果用来进行排序的。所不同的是，需要传入一个NSData 的数据。
- (NSArray<ObjectType> *)sortedArrayUsingFunction:(NSInteger (*)(ObjectType, ObjectType, void * __nullable))comparator context:(nullable void *)context hint:(nullable NSData *)hint;

// 这是用来排序的函数，comparator 这个参数，需要传入一个返回结果是NSComparisonResult 的函数，
- (NSArray<ObjectType> *)sortedArrayUsingSelector:(SEL)comparator;

// 用来获取数组中range.location 开始，数据各数 为range.length 的数据，并放置到一个新的数组中
- (NSArray<ObjectType> *)subarrayWithRange:(NSRange)range;

//写入数组中的数据，到指定path 的目录中：参数:atomically 是否把文件保存到辅助文件中
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;

//如同上面的方法一样，所不同的是写入数组中的内容到 网上指定的路径
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically;

//这个方法的实现类似于，数组中的元素，都是类对象，aselector 是这些类中的无参方法。
- (void)makeObjectsPerformSelector:(SEL)aSelector NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");

//这个方法的调用和上面一个方法类似，所不同的是这个对象调用的方法是一个可以带参数的方法。参数的类型是id ,也就是可以是任意的类型。
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(nullable id)argument NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");

//用来根据indexes 获取一个数组， NSIndexSet 是一个用来管理 index 的对象。
- (NSArray<ObjectType> *)objectsAtIndexes:(NSIndexSet *)indexes;

//返回指定下标的一个对象。这个方法类似 objectAtIndex:
- (ObjectType)objectAtIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);

// 相当于 for (...in...)，效率上基本一致，是基于 NSFastEnumeration 实现快速迭代。
- (void)enumerateObjectsUsingBlock:(void (^)(ObjectType obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);


- (void):(NSEnumerationOptions)opts usingBlock:(void (^)(ObjectType obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);


- (void)enumerateObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts usingBlock:(void (^)(ObjectType obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);


- (NSUInteger)indexOfObjectPassingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);


- (NSUInteger)indexOfObjectWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);


- (NSUInteger)indexOfObjectAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);


- (NSIndexSet *)indexesOfObjectsPassingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);


- (NSIndexSet *)indexesOfObjectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);


- (NSIndexSet *)indexesOfObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);


- (NSArray<ObjectType> *)sortedArrayUsingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);


- (NSArray<ObjectType> *)sortedArrayWithOptions:(NSSortOptions)opts usingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);


typedef NS_OPTIONS(NSUInteger, NSBinarySearchingOptions) {
	NSBinarySearchingFirstEqual = (1UL << 8),
	NSBinarySearchingLastEqual = (1UL << 9),
	NSBinarySearchingInsertionIndex = (1UL << 10),
};


- (NSUInteger)indexOfObject:(ObjectType)obj inSortedRange:(NSRange)r options:(NSBinarySearchingOptions)opts usingComparator:(NSComparator)cmp NS_AVAILABLE(10_6, 4_0); // binary search

@end

@interface NSArray<ObjectType> (NSArrayCreation)

+ (instancetype)array;
+ (instancetype)arrayWithObject:(ObjectType)anObject;
+ (instancetype)arrayWithObjects:(const ObjectType [])objects count:(NSUInteger)cnt;
+ (instancetype)arrayWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
NSArray *array = [NSArray arrayWithObjects:,nil];

+ (instancetype)arrayWithArray:(NSArray<ObjectType> *)array;

- (instancetype)initWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
- (instancetype)initWithArray:(NSArray<ObjectType> *)array;
- (instancetype)initWithArray:(NSArray<ObjectType> *)array copyItems:(BOOL)flag;

+ (nullable NSArray<ObjectType> *)arrayWithContentsOfFile:(NSString *)path;
+ (nullable NSArray<ObjectType> *)arrayWithContentsOfURL:(NSURL *)url;
- (nullable NSArray<ObjectType> *)initWithContentsOfFile:(NSString *)path;
- (nullable NSArray<ObjectType> *)initWithContentsOfURL:(NSURL *)url;

@end

@interface NSArray<ObjectType> (NSDeprecated)

/* This method is unsafe because it could potentially cause buffer overruns. You should use -getObjects:range: instead.
*/
- (void)getObjects:(ObjectType __unsafe_unretained [])objects;

@end

/****************	Mutable Array		****************/

@interface NSMutableArray<ObjectType> : NSArray<ObjectType>

- (void)addObject:(ObjectType)anObject;
- (void)insertObject:(ObjectType)anObject atIndex:(NSUInteger)index;
- (void)removeLastObject;
- (void)removeObjectAtIndex:(NSUInteger)index;
- (void)replaceObjectAtIndex:(NSUInteger)index withObject:(ObjectType)anObject;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableArray<ObjectType> (NSExtendedMutableArray)
    
- (void)addObjectsFromArray:(NSArray<ObjectType> *)otherArray;
- (void)exchangeObjectAtIndex:(NSUInteger)idx1 withObjectAtIndex:(NSUInteger)idx2;
- (void)removeAllObjects;
- (void)removeObject:(ObjectType)anObject inRange:(NSRange)range;
- (void)removeObject:(ObjectType)anObject;
- (void)removeObjectIdenticalTo:(ObjectType)anObject inRange:(NSRange)range;
- (void)removeObjectIdenticalTo:(ObjectType)anObject;
- (void)removeObjectsFromIndices:(NSUInteger *)indices numIndices:(NSUInteger)cnt NS_DEPRECATED(10_0, 10_6, 2_0, 4_0);
- (void)removeObjectsInArray:(NSArray<ObjectType> *)otherArray;
- (void)removeObjectsInRange:(NSRange)range;
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(NSArray<ObjectType> *)otherArray range:(NSRange)otherRange;
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(NSArray<ObjectType> *)otherArray;
- (void)setArray:(NSArray<ObjectType> *)otherArray;
- (void)sortUsingFunction:(NSInteger (*)(ObjectType,  ObjectType, void * __nullable))compare context:(nullable void *)context;
- (void)sortUsingSelector:(SEL)comparator;

- (void)insertObjects:(NSArray<ObjectType> *)objects atIndexes:(NSIndexSet *)indexes;
- (void)removeObjectsAtIndexes:(NSIndexSet *)indexes;
- (void)replaceObjectsAtIndexes:(NSIndexSet *)indexes withObjects:(NSArray<ObjectType> *)objects;

- (void)setObject:(ObjectType)obj atIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);

- (void)sortUsingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);
- (void)sortWithOptions:(NSSortOptions)opts usingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);

@end

@interface NSMutableArray<ObjectType> (NSMutableArrayCreation)

+ (instancetype)arrayWithCapacity:(NSUInteger)numItems;

+ (nullable NSMutableArray<ObjectType> *)arrayWithContentsOfFile:(NSString *)path;
+ (nullable NSMutableArray<ObjectType> *)arrayWithContentsOfURL:(NSURL *)url;
- (nullable NSMutableArray<ObjectType> *)initWithContentsOfFile:(NSString *)path;
- (nullable NSMutableArray<ObjectType> *)initWithContentsOfURL:(NSURL *)url;

@end

NS_ASSUME_NONNULL_END

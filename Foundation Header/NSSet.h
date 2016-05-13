/*	
    NSSet.h
 
    NSSet和NSMutableSet是无序的, 但是它保证数据的唯一性。当插入相同的数据时，不会有任何效果。从内部实现来说是hash表，所以可以常数时间内查找一个数据。
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>

@class NSArray, NSDictionary, NSString;

/****************	Immutable Set	****************/

NS_ASSUME_NONNULL_BEGIN

@interface NSSet<__covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

// 得到这个结合对象的长度。
@property (readonly) NSUInteger count;
// [set count] ;

- (nullable ObjectType)member:(ObjectType)object;
- (NSEnumerator<ObjectType> *)objectEnumerator;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithObjects:(const ObjectType [])objects count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSSet<ObjectType> (NSExtendedSet)

// 获取所有set对象
@property (readonly, copy) NSArray<ObjectType> *allObjects;
// NSArray *array = [set allObjects];

- (nullable ObjectType)anyObject;

// 判断这个集合中是否存在传入的对象
- (BOOL)containsObject:(ObjectType)anObject;
// if([set containsObject:@"age"])  return;     判断是否含有age字符串

@property (readonly, copy) NSString *description;
- (NSString *)descriptionWithLocale:(nullable id)locale;
- (BOOL)intersectsSet:(NSSet<ObjectType> *)otherSet;

// 判断两个集合是否完全相等
- (BOOL)isEqualToSet:(NSSet<ObjectType> *)otherSet;
// if ([set isEqualToSet:set1]) return;     判断set 是否等于set1

// 判断集合中的所有数据是否都相等与objeset集合中
- (BOOL)isSubsetOfSet:(NSSet<ObjectType> *)otherSet;
//  if ([set isSubsetOfSet:set1]) return;       判断set是否是set1的子集合

- (void)makeObjectsPerformSelector:(SEL)aSelector NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(nullable id)argument NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");

- (NSSet<ObjectType> *)setByAddingObject:(ObjectType)anObject NS_AVAILABLE(10_5, 2_0);
- (NSSet<ObjectType> *)setByAddingObjectsFromSet:(NSSet<ObjectType> *)other NS_AVAILABLE(10_5, 2_0);
- (NSSet<ObjectType> *)setByAddingObjectsFromArray:(NSArray<ObjectType> *)other NS_AVAILABLE(10_5, 2_0);

- (void)enumerateObjectsUsingBlock:(void (^)(ObjectType obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(ObjectType obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);

- (NSSet<ObjectType> *)objectsPassingTest:(BOOL (^)(ObjectType obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSSet<ObjectType> *)objectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

@end

@interface NSSet<ObjectType> (NSSetCreation)

+ (instancetype)set;
+ (instancetype)setWithObject:(ObjectType)object;

// 创建并初始化
+ (instancetype)setWithObjects:(const ObjectType [])objects count:(NSUInteger)cnt;
// NSSet *set = [NSSet setWithObjects:@"25",@"age",@"张三",@"name",@"男",nil];

+ (instancetype)setWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;

// 用另外一个set对象构造
+ (instancetype)setWithSet:(NSSet<ObjectType> *)set;
// [NSSet setWithSet:(NSSet *)set];

// 用数组构造
+ (instancetype)setWithArray:(NSArray<ObjectType> *)array;
// [NSSet setWithArray:(NSArray *)array];

// 创建集合对象，并且初始化集合中的数值，结尾必需使用nil标志
- (instancetype)initWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
// [NSSet setWithObjects:...];

// NSArray *array = [[NSArray alloc] initWithObjects:@"对象abc",@"rongfzh", @"totogo2010",nil];
// NSSet *set3 = [NSSet setWithArray:array];

- (instancetype)initWithSet:(NSSet<ObjectType> *)set;
- (instancetype)initWithSet:(NSSet<ObjectType> *)set copyItems:(BOOL)flag;
- (instancetype)initWithArray:(NSArray<ObjectType> *)array;

@end

/****************	Mutable Set	****************/

@interface NSMutableSet<ObjectType> : NSSet<ObjectType>

- (void)addObject:(ObjectType)object;
- (void)removeObject:(ObjectType)object;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableSet<ObjectType> (NSExtendedMutableSet)

- (void)addObjectsFromArray:(NSArray<ObjectType> *)array;

// 向集合中删除一个不包含obj集合的所有数据
- (void)intersectSet:(NSSet<ObjectType> *)otherSet;
// [set intersectSet];

// 向集合中删除一个obj集合的所有数据
- (void)minusSet:(NSSet<ObjectType> *)otherSet;
// [set minusSet:obj];

// 删除集合中的所有对象
- (void)removeAllObjects;
// [set removeAllObjects];

// 向集合中添加一个obj集合的所有数据
- (void)unionSet:(NSSet<ObjectType> *)otherSet;
// [set unionSet:obj];

- (void)setSet:(NSSet<ObjectType> *)otherSet;

@end

@interface NSMutableSet<ObjectType> (NSMutableSetCreation)

// 创建可变集合对象，并且初始化长度为6
+ (instancetype)setWithCapacity:(NSUInteger)numItems;
// NSMutableSet *muSet = [NSMutableSet setWithCapacity:6];

@end

/****************	Counted Set	****************/

@interface NSCountedSet<ObjectType> : NSMutableSet<ObjectType> {
    @private
    id _table;
    void *_reserved;
}

- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithArray:(NSArray<ObjectType> *)array;
- (instancetype)initWithSet:(NSSet<ObjectType> *)set;

- (NSUInteger)countForObject:(ObjectType)object;

// 将集合放入迭代器(遍历)
- (NSEnumerator<ObjectType> *)objectEnumerator;
// NSEnumerator *enumerator = [set objectEnumerator];
// for (NSObject *object in enumerator) return;

// 向集合中动态的添加对象。
- (void)addObject:(ObjectType)object;
// NSMutableSet * set = [json.acceptableContentTypes mutableCopy];
// [set addObject:@"text/html"];

// 删除集合中的一个对象
- (void)removeObject:(ObjectType)object;
// [set removeObject:obj];

@end

NS_ASSUME_NONNULL_END

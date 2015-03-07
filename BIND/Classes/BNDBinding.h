//
//  BNDBinding.h
//  BIND
//
//  Created by Marko Hlebar on 27/10/2014.
//  Copyright (c) 2014 Marko Hlebar. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  The valur block which contains the object who's value is being transformed.
 *
 *  @param object object who's value is being transformed.
 *  @param value  a value to transform.
 *
 *  @return a transformed value.
 */
typedef id(^BNDBindingTransformValueBlock)(id object, id value);

@interface BNDBinding : NSObject <NSCoding>

/**
 *  BIND is a special syntax to bind values at keyPath for an object
 *  to another object's value at keyPath.
 *  The syntax is:
 *  leftKeyPath->rightKeyPath|Transformer
 *
 *  where leftKeyPath is the keyPath of bound object, rightKeyPath is the key path of other bound object.
 *  Possible assignment directions are:
 *  -> left object passes values to right object.
 *  <- right object passes values to left object.
 *  <> binding is bidirectional.
 *  !-> left object passes values to right object with no initial value assignment.
 *  <-! right object passes values to left object with no initial value assignment.
 *  <!> binding is bidirectional with no initial value assignment.
 *
 *  Define a transformer with |Transformer,
 *  where Transformer is the optional NSValueTransformer subclass you want to use,
 */
@property (nonatomic, copy) NSString *BIND;

/**
 *  Left bound object following the BIND syntax.
 */
@property (nonatomic, weak, readonly) id leftObject;

/**
 *  Right bound object following the BIND syntax.
 */
@property (nonatomic, weak, readonly) id rightObject;

/**
 *  Builds a binding using BIND syntax.
 *
 *  @param BIND a BIND expression
 *
 *  @return a binding.
 */
+ (instancetype)bindingWithBIND:(NSString *)BIND;

/**
 *  Binds the left object in BIND expression with the right object and sets the initial values.
 *  This removes all previous bindings on previously set objects,
 *  and builds bindings for keyPaths with new objects.
 *  This is useful in situations where you want to reuse the binding,
 *  and just update the objects being bound i.e. on UITableViewCell reuse.
 *
 *
 *  @param leftObject  left object in the bind expression
 *  @param rightObject right object in the bind expression
 */
- (void)bindLeft:(id)leftObject
       withRight:(id)rightObject;

/**
 *  Removes all bindings and references to leftObject and rightObject.
 */
- (void)unbind;

/**

 */

/**
 *  Transforms the bound values with the transform given in the block.
 *  Calling transform: on a binding will cause it to set the values as per binding direction.
 *  If value transformer and transform are assigned,
 *  the value is first passed through the value transformer and then through the block.
 *
 *  @param transformBlock a transform block.
 *
 *  @return a binding that is performing the transform.
 */
- (instancetype)transform:(BNDBindingTransformValueBlock)transformBlock;

@end

//
//  UIView+AutoLayout.h
//  v1.1.0
//  https://github.com/smileyborg/UIView-AutoLayout
//
//  Copyright (c) 2012 Richard Turton
//  Copyright (c) 2013 Tyler Fox
//
//  This code is distributed under the terms and conditions of the MIT license.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to
//  deal in the Software without restriction, including without limitation the
//  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
//  sell copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//  IN THE SOFTWARE.
//

#import <UIKit/UIKit.h>

#pragma mark ALAttributes

typedef NS_ENUM(NSInteger, ALEdge) {
    ALEdgeLeft = NSLayoutAttributeLeft,             // the left edge of the view
    ALEdgeRight = NSLayoutAttributeRight,           // the right edge of the view
    ALEdgeTop = NSLayoutAttributeTop,               // the top edge of the view
    ALEdgeBottom = NSLayoutAttributeBottom,         // the bottom edge of the view
    ALEdgeLeading = NSLayoutAttributeLeading,       // the leading edge of the view (left edge for left-to-right languages like English, right edge for right-to-left languages like Arabic)
    ALEdgeTrailing = NSLayoutAttributeTrailing      // the trailing edge of the view (right edge for left-to-right languages like English, left edge for right-to-left languages like Arabic)
};

typedef NS_ENUM(NSInteger, ALDimension) {
    ALDimensionWidth = NSLayoutAttributeWidth,      // the width of the view
    ALDimensionHeight = NSLayoutAttributeHeight     // the height of the view
};

typedef NS_ENUM(NSInteger, ALAxis) {
    ALAxisVertical = NSLayoutAttributeCenterX,      // a vertical line through the center of the view
    ALAxisHorizontal = NSLayoutAttributeCenterY,    // a horizontal line through the center of the view
    ALAxisBaseline = NSLayoutAttributeBaseline      // a horizontal line at the text baseline (not applicable to all views)
};

typedef void(^ALConstraintsBlock)(void);    // a block of method calls to the UIView+AutoLayout category API


#pragma mark - UIView+AutoLayout

/**
 A category on UIView that provides a simple yet powerful interface for creating Auto Layout constraints.
 */
@interface UIView (AutoLayout)


#pragma mark Factory & Initializer Methods

/**
 Creates and returns a new view that does not convert the autoresizing mask into constraints.
 */
+ (instancetype)newAutoLayoutView;

/**
 Initializes and returns a new view that does not convert the autoresizing mask into constraints.
 */
- (instancetype)initForAutoLayout;


#pragma mark Set Constraint Priority

/**
 Sets the constraint priority to the given value for all constraints created using the UIView+AutoLayout
 category API within the given constraints block.

 NOTE: This method will have no effect (and will NOT set the priority) on constraints created or added
 using the SDK directly within the block!

 @param priority The layout priority to be set on all constraints in the constraints block.
 @param block A block of method calls to the UIView+AutoLayout API that create and add constraints.
 */
+ (void)autoSetPriority:(UILayoutPriority)priority forConstraints:(ALConstraintsBlock)block;


#pragma mark Remove Constraints

/**
 Removes the given constraint from the view it has been added to.

 @param constraint The constraint to remove.
 */
+ (void)autoRemoveConstraint:(NSLayoutConstraint *)constraint;

/**
 Removes the given constraints from the views they have been added to.

 @param constraints The constraints to remove.
 */
+ (void)autoRemoveConstraints:(NSArray *)constraints;

/**
 Removes all explicit constraints that affect the view.
 WARNING: Apple's constraint solver is not optimized for large-scale constraint changes; you may encounter major performance issues after using this method.
 It is not recommended to use this method to "reset" a view for reuse in a different way with new constraints. Create a new view instead.
 NOTE: This method preserves implicit constraints, such as intrinsic content size constraints, which you usually do not want to remove.
 */
- (void)autoRemoveConstraintsAffectingView;

/**
 Removes all constraints that affect the view, optionally including implicit constraints.
 WARNING: Apple's constraint solver is not optimized for large-scale constraint changes; you may encounter major performance issues after using this method.
 It is not recommended to use this method to "reset" a view for reuse in a different way with new constraints. Create a new view instead.
 NOTE: Implicit constraints are auto-generated lower priority constraints (such as those that attempt to keep a view at
 its intrinsic content size by hugging its content & resisting compression), and you usually do not want to remove these.

 @param shouldRemoveImplicitConstraints Whether implicit constraints should be removed or skipped.
 */
- (void)autoRemoveConstraintsAffectingViewIncludingImplicitConstraints:(BOOL)shouldRemoveImplicitConstraints;

/**
 Recursively removes all explicit constraints that affect the view and its subviews.
 WARNING: Apple's constraint solver is not optimized for large-scale constraint changes; you may encounter major performance issues after using this method.
 It is not recommended to use this method to "reset" views for reuse in a different way with new constraints. Create a new view instead.
 NOTE: This method preserves implicit constraints, such as intrinsic content size constraints, which you usually do not want to remove.
 */
- (void)autoRemoveConstraintsAffectingViewAndSubviews;

/**
 Recursively removes all constraints that affect the view and its subviews, optionally including implicit constraints.
 WARNING: Apple's constraint solver is not optimized for large-scale constraint changes; you may encounter major performance issues after using this method.
 It is not recommended to use this method to "reset" views for reuse in a different way with new constraints. Create a new view instead.
 NOTE: Implicit constraints are auto-generated lower priority constraints (such as those that attempt to keep a view at
 its intrinsic content size by hugging its content & resisting compression), and you usually do not want to remove these.

 @param shouldRemoveImplicitConstraints Whether implicit constraints should be removed or skipped.
 */
- (void)autoRemoveConstraintsAffectingViewAndSubviewsIncludingImplicitConstraints:(BOOL)shouldRemoveImplicitConstraints;


#pragma mark Center in Superview

/**
 Centers the view in its superview.

 @return An array of constraints added.
 */
- (NSArray *)autoCenterInSuperview;

/**
 Aligns the view to the same axis of its superview.

 @param axis The axis of this view and of its superview to align.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoAlignAxisToSuperviewAxis:(ALAxis)axis;

#pragma mark Pin Edges to Superview

/**
 Pins the given edge of the view to the same edge of the superview with an inset.

 @param edge The edge of this view and the superview to pin.
 @param inset The amount to inset this view's edge from the superview's edge.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoPinEdgeToSuperviewEdge:(ALEdge)edge withInset:(CGFloat)inset;

/**
 Pins the given edge of the view to the same edge of the superview with an inset as a maximum or minimum.

 @param edge The edge of this view and the superview to pin.
 @param inset The amount to inset this view's edge from the superview's edge.
 @param relation Whether the inset should be at least, at most, or exactly equal to the given value.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoPinEdgeToSuperviewEdge:(ALEdge)edge withInset:(CGFloat)inset relation:(NSLayoutRelation)relation;

/**
 Pins the edges of the view to the edges of its superview with the given edge insets.

 @param insets The insets for this view's edges from the superview's edges.
 @return An array of constraints added.
 */
- (NSArray *)autoPinEdgesToSuperviewEdgesWithInsets:(UIEdgeInsets)insets;


#pragma mark Pin Edges

/**
 Pins an edge of the view to a given edge of another view.

 @param edge The edge of this view to pin.
 @param toEdge The edge of the peer view to pin to.
 @param peerView The peer view to pin to. Must be in the same view hierarchy as this view.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoPinEdge:(ALEdge)edge toEdge:(ALEdge)toEdge ofView:(UIView *)peerView;

/**
 Pins an edge of the view to a given edge of another view with an offset.

 @param edge The edge of this view to pin.
 @param toEdge The edge of the peer view to pin to.
 @param peerView The peer view to pin to. Must be in the same view hierarchy as this view.
 @param offset The offset between the edge of this view and the edge of the peer view.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoPinEdge:(ALEdge)edge toEdge:(ALEdge)toEdge ofView:(UIView *)peerView withOffset:(CGFloat)offset;

/**
 Pins an edge of the view to a given edge of another view with an offset as a maximum or minimum.

 @param edge The edge of this view to pin.
 @param toEdge The edge of the peer view to pin to.
 @param peerView The peer view to pin to. Must be in the same view hierarchy as this view.
 @param offset The offset between the edge of this view and the edge of the peer view.
 @param relation Whether the offset should be at least, at most, or exactly equal to the given value.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoPinEdge:(ALEdge)edge toEdge:(ALEdge)toEdge ofView:(UIView *)peerView withOffset:(CGFloat)offset relation:(NSLayoutRelation)relation;


#pragma mark Align Axes

/**
 Aligns an axis of the view to the same axis of another view.

 @param axis The axis of this view and the peer view to align.
 @param peerView The peer view to align to. Must be in the same view hierarchy as this view.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoAlignAxis:(ALAxis)axis toSameAxisOfView:(UIView *)peerView;

/**
 Aligns an axis of the view to the same axis of another view with an offset.

 @param axis The axis of this view and the peer view to align.
 @param peerView The peer view to align to. Must be in the same view hierarchy as this view.
 @param offset The offset between the axis of this view and the axis of the peer view.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoAlignAxis:(ALAxis)axis toSameAxisOfView:(UIView *)peerView withOffset:(CGFloat)offset;


#pragma mark Match Dimensions

/**
 Matches a dimension of the view to a given dimension of another view.

 @param dimension The dimension of this view to pin.
 @param toDimension The dimension of the peer view to pin to.
 @param peerView The peer view to match to. Must be in the same view hierarchy as this view.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoMatchDimension:(ALDimension)dimension toDimension:(ALDimension)toDimension ofView:(UIView *)peerView;

/**
 Matches a dimension of the view to a given dimension of another view with an offset.

 @param dimension The dimension of this view to pin.
 @param toDimension The dimension of the peer view to pin to.
 @param peerView The peer view to match to. Must be in the same view hierarchy as this view.
 @param offset The offset between the dimension of this view and the dimension of the peer view.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoMatchDimension:(ALDimension)dimension toDimension:(ALDimension)toDimension ofView:(UIView *)peerView withOffset:(CGFloat)offset;

/**
 Matches a dimension of the view to a given dimension of another view with an offset as a maximum or minimum.

 @param dimension The dimension of this view to pin.
 @param toDimension The dimension of the peer view to pin to.
 @param peerView The peer view to match to. Must be in the same view hierarchy as this view.
 @param offset The offset between the dimension of this view and the dimension of the peer view.
 @param relation Whether the offset should be at least, at most, or exactly equal to the given value.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoMatchDimension:(ALDimension)dimension toDimension:(ALDimension)toDimension ofView:(UIView *)peerView withOffset:(CGFloat)offset relation:(NSLayoutRelation)relation;

/**
 Matches a dimension of the view to a multiple of a given dimension of another view.

 @param dimension The dimension of this view to pin.
 @param toDimension The dimension of the peer view to pin to.
 @param peerView The peer view to match to. Must be in the same view hierarchy as this view.
 @param multiplier The multiple of the peer view's given dimension that this view's given dimension should be.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoMatchDimension:(ALDimension)dimension toDimension:(ALDimension)toDimension ofView:(UIView *)peerView withMultiplier:(CGFloat)multiplier;

/**
 Matches a dimension of the view to a multiple of a given dimension of another view as a maximum or minimum.

 @param dimension The dimension of this view to pin.
 @param toDimension The dimension of the peer view to pin to.
 @param peerView The peer view to match to. Must be in the same view hierarchy as this view.
 @param multiplier The multiple of the peer view's given dimension that this view's given dimension should be.
 @param relation Whether the multiple should be at least, at most, or exactly equal to the given value.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoMatchDimension:(ALDimension)dimension toDimension:(ALDimension)toDimension ofView:(UIView *)peerView withMultiplier:(CGFloat)multiplier relation:(NSLayoutRelation)relation;


#pragma mark Set Dimensions

/**
 Sets the view to a specific size.

 @param size The size to set this view's dimensions to.
 @return An array of constraints added.
 */
- (NSArray *)autoSetDimensionsToSize:(CGSize)size;

/**
 Sets the given dimension of the view to a specific size.

 @param dimension The dimension of this view to set.
 @param size The size to set the given dimension to.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoSetDimension:(ALDimension)dimension toSize:(CGFloat)size;

/**
 Sets the given dimension of the view to a specific size as a maximum or minimum.

 @param dimension The dimension of this view to set.
 @param size The size to set the given dimension to.
 @param relation Whether the size should be at least, at most, or exactly equal to the given value.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoSetDimension:(ALDimension)dimension toSize:(CGFloat)size relation:(NSLayoutRelation)relation;


#pragma mark Constrain Any Attributes

/**
 Constrains an attribute (any ALEdge, ALAxis, or ALDimension) of the view to a given attribute of another view.
 This method can be used to constrain different types of attributes across two views.

 @param ALAttribute Any ALEdge, ALAxis, or ALDimension of this view to constrain.
 @param toALAttribute Any ALEdge, ALAxis, or ALDimension of the peer view to constrain to.
 @param peerView The peer view to constrain to. Must be in the same view hierarchy as this view.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoConstrainAttribute:(NSInteger)attribute toAttribute:(NSInteger)toAttribute ofView:(UIView *)peerView;

/**
 Constrains an attribute (any ALEdge, ALAxis, or ALDimension) of the view to a given attribute of another view with an offset.
 This method can be used to constrain different types of attributes across two views.

 @param ALAttribute Any ALEdge, ALAxis, or ALDimension of this view to constrain.
 @param toALAttribute Any ALEdge, ALAxis, or ALDimension of the peer view to constrain to.
 @param peerView The peer view to constrain to. Must be in the same view hierarchy as this view.
 @param offset The offset between the attribute of this view and the attribute of the peer view.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoConstrainAttribute:(NSInteger)attribute toAttribute:(NSInteger)toAttribute ofView:(UIView *)peerView withOffset:(CGFloat)offset;

/**
 Constrains an attribute (any ALEdge, ALAxis, or ALDimension) of the view to a given attribute of another view with an offset as a maximum or minimum.
 This method can be used to constrain different types of attributes across two views.

 @param ALAttribute Any ALEdge, ALAxis, or ALDimension of this view to constrain.
 @param toALAttribute Any ALEdge, ALAxis, or ALDimension of the peer view to constrain to.
 @param peerView The peer view to constrain to. Must be in the same view hierarchy as this view.
 @param offset The offset between the attribute of this view and the attribute of the peer view.
 @param relation Whether the offset should be at least, at most, or exactly equal to the given value.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoConstrainAttribute:(NSInteger)attribute toAttribute:(NSInteger)toAttribute ofView:(UIView *)peerView withOffset:(CGFloat)offset relation:(NSLayoutRelation)relation;

/**
 Constrains an attribute (any ALEdge, ALAxis, or ALDimension) of the view to a given attribute of another view with a multiplier.
 This method can be used to constrain different types of attributes across two views.

 @param ALAttribute Any ALEdge, ALAxis, or ALDimension of this view to constrain.
 @param toALAttribute Any ALEdge, ALAxis, or ALDimension of the peer view to constrain to.
 @param peerView The peer view to constrain to. Must be in the same view hierarchy as this view.
 @param multiplier The multiplier between the attribute of this view and the attribute of the peer view.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoConstrainAttribute:(NSInteger)attribute toAttribute:(NSInteger)toAttribute ofView:(UIView *)peerView withMultiplier:(CGFloat)multiplier;

/**
 Constrains an attribute (any ALEdge, ALAxis, or ALDimension) of the view to a given attribute of another view with a multiplier as a maximum or minimum.
 This method can be used to constrain different types of attributes across two views.

 @param ALAttribute Any ALEdge, ALAxis, or ALDimension of this view to constrain.
 @param toALAttribute Any ALEdge, ALAxis, or ALDimension of the peer view to constrain to.
 @param peerView The peer view to constrain to. Must be in the same view hierarchy as this view.
 @param multiplier The multiplier between the attribute of this view and the attribute of the peer view.
 @param relation Whether the multiplier should be at least, at most, or exactly equal to the given value.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoConstrainAttribute:(NSInteger)attribute toAttribute:(NSInteger)toAttribute ofView:(UIView *)peerView withMultiplier:(CGFloat)multiplier relation:(NSLayoutRelation)relation;


#pragma mark Pin to Layout Guides

/**
 Pins the top edge of the view to the top layout guide of the given view controller with an inset.
 For compatibility with iOS 6 (where layout guides do not exist), this method will simply pin the top edge of
 the view to the top edge of the given view controller's view with an inset.

 @param viewController The view controller whose topLayoutGuide should be used to pin to.
 @param inset The amount to inset this view's top edge from the layout guide.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoPinToTopLayoutGuideOfViewController:(UIViewController *)viewController withInset:(CGFloat)inset;

/**
 Pins the bottom edge of the view to the bottom layout guide of the given view controller with an inset.
 For compatibility with iOS 6 (where layout guides do not exist), this method will simply pin the bottom edge of
 the view to the bottom edge of the given view controller's view with an inset.

 @param viewController The view controller whose bottomLayoutGuide should be used to pin to.
 @param inset The amount to inset this view's bottom edge from the layout guide.
 @return The constraint added.
 */
- (NSLayoutConstraint *)autoPinToBottomLayoutGuideOfViewController:(UIViewController *)viewController withInset:(CGFloat)inset;


#pragma mark Deprecated API Methods


- (NSLayoutConstraint *)autoCenterInSuperviewAlongAxis:(ALAxis)axis __attribute__((deprecated));

- (NSLayoutConstraint *)autoPinCenterAxis:(ALAxis)axis toPositionInSuperview:(CGFloat)value __attribute__((deprecated));

- (NSLayoutConstraint *)autoPinEdge:(ALEdge)edge toPositionInSuperview:(CGFloat)value __attribute__((deprecated));

@end


#pragma mark - NSArray+AutoLayout


@interface NSArray (AutoLayout)


#pragma mark Constrain Multiple Views

/**
 Aligns views in this array to one another along a given edge.
 Note: This array must contain at least 2 views, and all views must share a common superview.

 @param edge The edge to which the subviews will be aligned.
 @return An array of constraints added.
 */
- (NSArray *)autoAlignViewsToEdge:(ALEdge)edge;

/**
 Aligns views in this array to one another along a given axis.
 Note: This array must contain at least 2 views, and all views must share a common superview.

 @param axis The axis to which to subviews will be aligned.
 @return An array of constraints added.
 */
- (NSArray *)autoAlignViewsToAxis:(ALAxis)axis;

/**
 Matches a given dimension of all the views in this array.
 Note: This array must contain at least 2 views, and all views must share a common superview.

 @param dimension The dimension to match for all of the subviews.
 @return An array of constraints added.
 */
- (NSArray *)autoMatchViewsDimension:(ALDimension)dimension;

/**
 Sets the given dimension of all the views in this array to a given size.
 Note: This array must contain at least 1 view.

 @param dimension The dimension of each of the subviews to set.
 @param size The size to set the given dimension of each subview to.
 @return An array of constraints added.
 */
- (NSArray *)autoSetViewsDimension:(ALDimension)dimension toSize:(CGFloat)size;


#pragma mark Distribute Multiple Views

/**
 Distributes the views in this array equally along the selected axis in their superview.
 Views will be the same size (variable) in the dimension along the axis and will have spacing (fixed) between them.

 @param axis The axis along which to distribute the subviews.
 @param spacing The fixed amount of spacing between each subview.
 @param alignment The way in which the subviews will be aligned.
 @return An array of constraints added.
 */
- (NSArray *)autoDistributeViewsAlongAxis:(ALAxis)axis withFixedSpacing:(CGFloat)spacing alignment:(NSLayoutFormatOptions)alignment;

/**
 Distributes the views in this array equally along the selected axis in their superview.
 Views will be the same size (fixed) in the dimension along the axis and will have spacing (variable) between them.

 @param axis The axis along which to distribute the subviews.
 @param size The fixed size of each subview in the dimension along the given axis.
 @param alignment The way in which the subviews will be aligned.
 @return An array of constraints added.
 */
- (NSArray *)autoDistributeViewsAlongAxis:(ALAxis)axis withFixedSize:(CGFloat)size alignment:(NSLayoutFormatOptions)alignment;

@end


#pragma mark - NSLayoutConstraint+AutoLayout


@interface NSLayoutConstraint (AutoLayout)

/**
 Removes the constraint from the view it has been added to.
 */
- (void)autoRemove;

@end

@interface UIViewController (AutoLayoutHelper)

/**
 *	Constraint (set) topLayoutGuide, sets constraints that will make topLayoutGuide a given length, removes any exisiting constraints on the topLayoutGuide
 *
 *	@param	length	length to set (constraint) topLayoutGuide to
 */
- (void) constraintTopLayoutGuideToLength:(CGFloat)length;
@end

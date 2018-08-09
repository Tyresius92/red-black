/**********************************************************************
 * rb_tree.h                                                          *
 *                                                                    *
 * Interface for a polymorphic red black tree                         *
 **********************************************************************/

/***************************
 * PREPROCESSOR DIRECTIVES *
 ***************************/

#ifndef RB_TREE_H
#define RB_TREE_H

/*** INCLUDED FILES ***/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

/*** DEFINITIONS AND TYPEDEFS ***/

typedef struct rb_tree *RedBlack_T;

/**********************
 * FUNCTION CONTRACTS *
 * AND DECLARATIONS   *
 **********************/

/*
 * rb_new
 * 
 * returns a pointer to a new, empty red black tree
 * 
 * CREs         n/a
 * UREs         system out of memory
 *              
 * 
 * @param       void * - pointer to a comparison function. if NULL is passed 
 *                              as argument, strcmp is assumed. 
 *              
 *              comparison_function
 *              @param          item being inserted (val1)
 *              @param          item from tree which we are comparing (val2)
 *              @return         int 
 *                               - zero (0) if val1 == val2
 *                               - positive value (n > 0) if val1 > val2
 *                               - negative value (n < 0) if val1 < val2
 *        
 * @return      pointer to empty rb_tree
 */
RedBlack_T rb_new(void *comparison_func); 

/*
 * rb_tree_free
 * 
 * given a pointer to a red black tree, deallocates the tree and all nodes
 * contained within it, then sets the value of the pointer to NULL
 *
 * CREs         tree == NULL
 * UREs         n/a
 * 
 * @param       RedBlack_T - the tree to be freed
 * @return      n/a
 */
void rb_tree_free(RedBlack_T tree); 

/*
 * rb_tree_is_empty
 * 
 * returns true if the tree is empty, and false otherwise
 * 
 * CREs         tree == NULL
 * UREs         n/a
 * 
 * @param       Redblack_T - tree to be checked if empty
 * @return      bool - true if empty, false otherwise
 */ 
bool rb_tree_is_empty(RedBlack_T tree); 

/*
 * insert_value
 * 
 * given a value (cast to void), inserts the value into the given RB Tree
 * 
 * CREs         tree == NULL
 *              value == NULL
 * 
 * UREs         system out of memory
 *              attempting to pass in a value which cannot be compared with 
 *                      your comparison function
 * 
 * @param       RedBlack_T - tree in which to insert value
 * @param       void * - a pointer to any item to be inserted
 * @return      n/a
 */
int rb_insert_value(RedBlack_T tree, void *value);

/*
 * rb_search
 * 
 * given a tree and a value to search for, returns a pointer to the stored 
 * value, or NULL if the value is not found. If duplicates are in the tree, 
 * returns the first one found
 * 
 * @param       RedBlack_T - tree in which to search
 * @param       void * - value to search for
 * @return      void * - pointer to the value that was found
 */
void *rb_search(RedBlack_T tree, void *value); 

/*
 * rb_delete_value
 * 
 * given a value, deletes the first instance of it that is found in the tree
 * if a value is given that is not in the tree, this function has no effect
 * 
 * CREs         tree == NULL
 * UREs         n/a
 * 
 * @param       RedBlack_T - tree to find the value in
 * @param       void * - pointer to the value to be deleted
 * @return      n/a
 */
void rb_delete_value(RedBlack_T tree, void *value); 

/*
 * rb_tree_minimum
 * 
 * given a tree, returns the minimum value stored in the tree
 * 
 * CREs         tree == NULL
 * UREs         n/a
 * 
 * @param       RedBlack_T - tree to be searched
 * @return      void * - pointer to min value
 */
void *rb_tree_minimum(RedBlack_T tree); 

/*
 * rb_tree_maximum
 * 
 * given a tree, returns the maximum value stored in the tree
 * 
 * CREs         tree == NULL
 * UREs         n/a
 * 
 * @param       RedBlack_T - tree to be searched
 * @return      void * - pointer to max value
 */
void *rb_tree_maximum(RedBlack_T tree); 

/*
 * rb_successor_of_value
 * 
 * given a tree and a value, returns the first successor of that value
 * returned value will always be distinct from value, even if there are 
 * duplicates; returns NULL if no successor
 * 
 * CREs         tree == NULL
 *              value == NULL
 * UREs         n/a
 * 
 * @param       RedBlack_T - tree to be searched
 * @param       void * - value to find the successor of
 * @return      void * - value of the successor
 */
void *rb_successor_of_value(RedBlack_T tree, void *value); 

/*
 * rb_predecessor_of_value
 * 
 * given a tree and a value, returns the first predecessor of that value
 * returned value will always be distinct from value, even if there are 
 * duplicates; returns NULL if no predecessor
 * 
 * CREs         tree == NULL
 *              value == NULL
 * UREs         n/a
 * 
 * @param       RedBlack_T - tree to be searched
 * @param       void * - value to find the predecessor of
 * @return      void * - value of the predecessor
 */
void *rb_predecessor_of_value(RedBlack_T tree, void *value); 

/*
 * rb_map_inorder
 * 
 * given a tree and a pointer to a function, applies the function to every
 * element stored in the tree via an inorder walk
 * example valid operations include: 
 *              - print every value
 *              - increment every stored value by one
 *              - store every element in an array (stored in closure)
 * 
 * CREs         tree == NULL
 *              func_to_apply == NULL
 * UREs         func_to_apply modifies tree structure by performing different
 *                      operations on each node. (for instance, subtracting 1 
 *                      from the first node, 2 from the second, 3 from the 
 *                      third...and n from the nth could result in the BST 
 *                      property being invalidated)
 *                              
 * 
 * @param       Redblack_T - tree to apply function to
 * @param       void * - pointer to a function
 * @param       void * - a closure item; can be anything you would like to 
 *                              make use of when evaluating your function
 * @return      n/a
 */
void rb_map_inorder(RedBlack_T tree, 
                    void func_to_apply(void *value, int depth, void *cl), 
                    void *cl); 

/*
 * rb_map_preorder
 * 
 * given a tree and a pointer to a function, applies the function to every
 * element stored in the tree via a preorder walk
 * example valid operations include: 
 *              - print every value
 *              - increment every stored value by one
 *              - store every element in an array (stored in closure)
 * 
 * CREs         tree == NULL
 *              func_to_apply == NULL
 * UREs         func_to_apply modifies tree structure by performing different
 *                      operations on each node. (for instance, subtracting 1 
 *                      from the first node, 2 from the second, 3 from the 
 *                      third...and n from the nth could result in the BST 
 *                      property being invalidated)
 *                              
 * 
 * @param       Redblack_T - tree to apply function to
 * @param       void * - pointer to a function
 * @param       void * - a closure item; can be anything you would like to 
 *                              make use of when evaluating your function
 * @return      n/a
 */
void rb_map_preorder(RedBlack_T tree, 
                     void func_to_apply(void *value, int depth, void *cl), 
                     void *cl); 

/*
 * rb_map_postorder
 * 
 * given a tree and a pointer to a function, applies the function to every
 * element stored in the tree via a postorder walk
 * example valid operations include: 
 *              - print every value
 *              - increment every stored value by one
 *              - store every element in an array (stored in closure)
 * 
 * CREs         tree == NULL
 *              func_to_apply == NULL
 * UREs         func_to_apply modifies tree structure by performing different
 *                      operations on each node. (for instance, subtracting 1 
 *                      from the first node, 2 from the second, 3 from the 
 *                      third...and n from the nth could result in the BST 
 *                      property being invalidated)
 *                              
 * 
 * @param       Redblack_T - tree to apply function to
 * @param       void * - pointer to a function
 * @param       void * - a closure item; can be anything you would like to 
 *                              make use of when evaluating your function
 * @return      n/a
 */
void rb_map_postorder(RedBlack_T tree, 
                      void func_to_apply(void *value, int depth, void *cl), 
                      void *cl); 

#endif
#include "rb_tree.h"
#include <assert.h>
#include <string.h>
#include <stdint.h>

/*** MACRO DEFINITIONS ***/

#define BLACK 'b'
#define RED 'r'

typedef struct Node {
        void *value;
        struct Node *parent;
        struct Node *left; 
        struct Node *right; 
        char color; 
} Node;

struct rb_tree {
        Node *root; 
        void *comparison_func; 
};

typedef RedBlack_T T; 

/*********************************
 * PRIVATE FUNCTION DECLARATIONS *
 *********************************/ 

/*
 * private_rb_deallocate_all_tree_nodes
 * 
 * helper function for rb_tree_free. Recursively deletes all nodes in 
 * the subtree rooted at n (rb_tree_free passes in tree->root)
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       Node * - the root of a subtree to delete
 * @return      n/a
 */
void private_rb_deallocate_all_tree_nodes(Node *n); 

/* 
 * rotate_left
 * 
 * given a tree and a node n, moves n's right child to be the child of n's 
 * parent, and makes n the child of its right child
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       T - tree in which rotation is occuring
 * @param       Node * - pointer to the node to be rotated
 * @return      n/a
 */
void rb_rotate_left(T tree, Node *n); 

/* 
 * rb_rotate_right
 * 
 * given a tree and a node n, moves n's left child to be the child of n's 
 * parent, and makes n the child of its left child
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       T - tree in which rotation is occuring
 * @param       Node * - pointer to the node to be rotated
 * @return      n/a
 */
void rb_rotate_right(T tree, Node *n); 

/*
 * rb_construct_node
 * 
 * given a value, constructs a node containing that value, with all relational
 * pointers set to NULL, and color set to RED
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       void * - value to go into the node
 * @return      Node * - pointer to the new node
 */ 
Node *rb_construct_node(void *value);


/*
 * private_insert_value
 *
 * helper function for rb_insert_value. does the actual work of inserting
 * the value. 
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       Node * - the root of the current subtree (rb_insert_value 
 *                      passes in tree->root)
 * @param       Node * - a pointer to the node with the value to be deleted
 * @param       void * - a pointer to the comparison function for the current
 *                      root
 * @return      a pointer to the most recently touched node 
 */
Node *private_rb_insert_value(Node *root, Node *new_node, 
                           void *comparison_func(void *val1, void *val2));

/*
 * fix_insertion_violation
 * 
 * given a tree and a pointer to the most recently inserted node,
 * fixes any violations of the red-black properties in tree
 * 
 * CREs         tree == NULL
 * UREs         n/a
 * 
 * @param       T - tree in which we are fixing violations
 * @param       Node * - pointer to the most recently inserted node
 * @return      n/a
 */
void fix_insertion_violation(T tree, Node *inserted);

/*
 * private_find_in_tree
 * 
 * private helper function for rb_search and rb_delete_value. 
 * given a tree, a value, and a comparison function, returns the first 
 * located node with the value we are looking for
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       T - tree in which we are searching
 * @param       void * - pointer to the value we are searching for
 * @param       void * - pointer to the comparison function for that tree
 * @return      Node * - pointer to the node containing value
 */
Node *private_rb_find_in_tree(T tree, void *value, 
                           void *comparison_func(void *val1, void *val2));

/* 
 * rb_transplant
 * 
 * given a tree, a pointer to node u and a pointer to node v, replaces u with v
 * in the tree
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       T - tree in which we are transplanting
 * @param       Node * - pointer to node to be replaced
 * @param       Node * - pointer to node to replace with
 * @return      n/a
 */
void rb_transplant(T tree, Node *u, Node *v); 

/* 
 * rb_delete_fixup
 *
 * given a tree and a pointer to the former subtree of the deleted node, 
 * restores the red black tree properties. all deleted nodes have at most one 
 * child; two child nodes are replaced by their successor, which by definition
 * has at most one child. that child is the second parameter to this function
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       T - tree where a value was deleted
 * @param       Node * - former child of the deleted node
 * @return      n/a
 */
void rb_delete_fixup(T tree, Node *x);

/*
 * private_rb_successor_of_value
 * 
 * private helper function for rb_successor_of_value
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       T - tree in which to search
 * @param       void * - pointer to the value we want the successor of
 * @param       void * - pointer to the comparison function associated with tree
 * @return      void * - pointer to the successor's value (or NULL if no 
 *                      successor exists)
 */
void *private_rb_successor_of_value(T tree, void *value, 
                                 void *comparison_func(void *val1, void *val2));

/*
 * private_rb_predecessor_of_value
 * 
 * private helper function for predcessor_of_value
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       T - tree in which to search
 * @param       void * - pointer to the value we want the predecessor of
 * @param       void * - pointer to the comparison function associated with tree
 * @return      void * - pointer to the predecessor's value (or NULL if no 
 *                      predecessor exists)
 */
void *private_rb_predecessor_of_value(T tree, void *value, 
                                   void *comparison_func(void *val1, void *val2)); 

/*
 * private_rb_find_successor
 * 
 * private general use helper function - given a pointer to node, returns the 
 * node containing the successor
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       Node * - node that we want the successor of
 * @return      Node * - node containing the successor
 */
Node *private_rb_find_successor(Node *n); 

/*
 * private_rb_find_predecessor
 * 
 * private general use helper function - given a pointer to node, returns the 
 * node containing the predecessor
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       Node * - node that we want the predecessor of
 * @return      Node * - node containing the predecessor
 */
Node *private_rb_find_predecessor(Node *n); 

/*
 * private_subrb_tree_minimum
 * 
 * given a node, returns the node containing the minimum value in the subtree 
 * rooted at that node
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       Node * - root of the subtree in question
 * @return      Node * - node containing the minimum
 */ 
Node *private_subrb_tree_minimum(Node *curr_node);

/*
 * private_subrb_tree_minimum
 * 
 * given a node, returns the node containing the minimum value in the subtree 
 * rooted at that node
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       Node * - root of the subtree in question
 * @return      Node * - node containing the minimum
 */ 
Node *private_subrb_tree_maximum(Node *curr_node);

/*
 * rb_private_inorder_map
 * 
 * private helper function for rb_map_inorder
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       Node * - root of the current subtree - rb_map_inorder passes 
 *                      in tree->root
 * @param       int - the current depth in the tree
 * @param       void - function to be applied to every node
 * @param       void * - pointer to closure, contains any data needed for 
 *                      evaluation of func_to_apply
 * @return      n/a
 */
void rb_private_inorder_map(Node *root, 
                            int depth,
                            void func_to_apply(void *value, int depth, void *cl), 
                            void *cl);

/*
 * rb_private_preorder_map
 * 
 * private helper function for rb_map_preorder
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       Node * - root of the current subtree - rb_map_preorder passes 
 *                      in tree->root
 * @param       int - the current depth in the tree
 * @param       void - function to be applied to every node
 * @param       void * - pointer to closure, contains any data needed for 
 *                      evaluation of func_to_apply
 * @return      n/a
 */
void rb_private_preorder_map(Node *root, 
                             int depth, 
                             void func_to_apply(void *value, int depth, void *cl), 
                             void *cl);

/*
 * rb_private_postorder_map
 * 
 * private helper function for rb_map_postorder
 * 
 * CREs         n/a
 * UREs         n/a
 * 
 * @param       Node * - root of the current subtree - rb_map_postorder passes 
 *                      in tree->root
 * @param       int - the current depth in the tree
 * @param       void - function to be applied to every node
 * @param       void * - pointer to closure, contains any data needed for 
 *                      evaluation of func_to_apply
 * @return      n/a
 */
void rb_private_postorder_map(Node *root, 
                              int depth, 
                              void func_to_apply(void *value, int depth, void *cl), 
                              void *cl);




/*****************************
 * PRIVATE WRAPPED FUNCTIONS *
 *****************************/ 

/************************
 * FUNCTION DEFINITIONS *
 ************************/ 

T rb_new(void *comparison_func)
{
        T tree = malloc(sizeof(struct rb_tree)); 

        tree->root = NULL; 

        if (comparison_func == NULL) {
                tree->comparison_func = &strcmp; 
        } else {
                tree->comparison_func = comparison_func; 
        }

        return tree; 
}

void rb_tree_free(T tree)
{
        assert(tree != NULL);

        private_rb_deallocate_all_tree_nodes(tree->root); 
        free(tree); 

        tree = NULL; 
}

bool rb_tree_is_empty(T tree)
{
        assert(tree != NULL); 

        if (tree->root == NULL)
                return true; 
        else 
                return false; 
}

void private_rb_deallocate_all_tree_nodes(Node *n) {
        if (n == NULL)
                return; 

        if (n->left != NULL) 
                private_rb_deallocate_all_tree_nodes(n->left);
        if (n->right != NULL)
                private_rb_deallocate_all_tree_nodes(n->right); 

        free(n); 
}

void rb_rotate_left(T tree, Node *n)
{
        Node *right_child = n->right; 

        n->right = right_child->left; 

        if (n->right != NULL)
                n->right->parent = n; 

        right_child->parent = n->parent; 

        if(n->parent == NULL) {
                tree->root = right_child; 
        } else if (n == n->parent->left) {
                (void) tree; 
                n->parent->left = right_child; 
        } else {
                (void) tree; 
                n->parent->right = right_child; 
        }

        right_child->left = n; 
        n->parent = right_child; 
}

void rb_rotate_right(T tree, Node *n)
{ 
        Node *left_child = n->left; 

        n->left = left_child->right; 

        if (n->left != NULL)
                n->left->parent = n; 

        left_child->parent = n->parent; 

        if(n->parent == NULL) {
                tree->root = left_child; 
        } else if (n == n->parent->left) {
                (void) tree; 
                n->parent->left = left_child; 
        } else {
                (void) tree; 
                n->parent->right = left_child; 
        }

        left_child->right = n; 
        n->parent = left_child; 
}

int rb_insert_value(T tree, void *value)
{
        assert(tree != NULL && value != NULL); 

        Node *new_node = rb_construct_node(value); 
        tree->root = private_rb_insert_value(tree->root, new_node, tree->comparison_func); 

        fix_insertion_violation(tree, new_node);  

        return 0;
}

Node *rb_construct_node(void *value)
{
        Node *new_node = (Node *) malloc(sizeof(Node)); 

        new_node->parent = NULL;
        new_node->left = NULL; 
        new_node->right = NULL; 
        new_node->value = value; 

        new_node->color = RED; 

        return new_node; 
}

Node *private_rb_insert_value(Node *root, Node *new_node, 
                           void *comparison_func(void *val1, void *val2)) 
{
        if (root == NULL) { 
                return new_node; 
        }

        if ((int)(intptr_t) comparison_func(new_node->value, root->value) < 0) {
                root->left = private_rb_insert_value(root->left, new_node, comparison_func); 
                root->left->parent = root; 
        } else {
                root->right = private_rb_insert_value(root->right, new_node, comparison_func); 
                root->right->parent = root; 
        }

        return root; 
}

void fix_insertion_violation(T tree, Node *culprit)
{
        Node *parent_node = NULL; 
        Node *grand_parent_node = NULL; 

        while ((culprit != tree->root) && (culprit->color != BLACK) && (culprit->parent->color == RED)) {
                
                parent_node = culprit->parent; 
                grand_parent_node = culprit->parent->parent; 

                if (parent_node == grand_parent_node->left){

                        Node *uncle = grand_parent_node->right; 

                        if (uncle != NULL && uncle->color == RED) {

                                grand_parent_node->color = RED; 
                                parent_node->color = BLACK; 
                                uncle->color = BLACK; 
                                culprit = grand_parent_node; 

                        } else {

                                if (culprit == parent_node->right) {
                                        rb_rotate_left(tree, parent_node); 
                                        culprit = parent_node; 
                                        parent_node = culprit->parent; 
                                }

                                rb_rotate_right(tree, grand_parent_node); 

                                char temp = parent_node->color; 
                                parent_node->color = grand_parent_node->color; 
                                grand_parent_node->color = temp; 

                                culprit = parent_node; 

                        }
                } else { // parent_node == grand_parent_node->right
                        Node *uncle = grand_parent_node->left; 

                        if ((uncle != NULL) && (uncle->color == RED)) {
                                grand_parent_node->color = RED; 
                                parent_node->color = BLACK; 
                                uncle->color = BLACK; 
                                culprit = grand_parent_node; 
                        } else {
                                if (culprit == parent_node->left) {
                                        rb_rotate_right(tree, parent_node); 
                                        culprit = parent_node; 
                                        parent_node = culprit->parent; 
                                }

                                rb_rotate_left(tree, grand_parent_node);

                                char temp = parent_node->color; 
                                parent_node->color = grand_parent_node->color; 
                                grand_parent_node->color = temp; 

                                culprit = parent_node; 
                        }
                }
        }

        tree->root->color = BLACK; 
}

void *rb_search(T tree, void *value)
{
        Node *result = private_rb_find_in_tree(tree, value, tree->comparison_func); 

        if (result != NULL) 
                return (void *) result->value; 

        return result; //AKA return NULL 
}

Node *private_rb_find_in_tree(T tree, void *value, 
                           void *comparison_func(void *val1, void *val2))
{
        bool found = false; 
        Node *curr = tree->root; 
        int c = 0; 

        while (!found && curr != NULL) {
                c = (int)(intptr_t) comparison_func(value, curr->value); 

                if (c == 0) {
                        found = true; 
                } else if (c < 0) {
                        curr = curr->left; 
                } else if (c > 0) {
                        curr = curr->right; 
                }
        }

        return curr; 
}

void rb_delete_value(T tree, void *value)
{
        assert(tree != NULL && value != NULL); 

        Node *subtree_of_deleted = NULL; 

        Node *delete_me = private_rb_find_in_tree(tree, value, tree->comparison_func); 

        if (delete_me == NULL) 
                return;

        Node *y = delete_me; 
        char y_original_color = y->color; 

        if (delete_me->left == NULL) {
                subtree_of_deleted = delete_me->right; 
                rb_transplant(tree, delete_me, delete_me->right); 
        } else if (delete_me->right == NULL) {
                subtree_of_deleted = delete_me->left; 
                rb_transplant(tree, delete_me, delete_me->left);
        } else {
                y = private_rb_find_successor(delete_me); 
                y_original_color = y->color; 

                subtree_of_deleted = y->right; 

                if (y->parent == delete_me && subtree_of_deleted != NULL) {
                        subtree_of_deleted->parent = y; 
                } else {
                        rb_transplant(tree, y, y->right); 
                        y->right = delete_me->right; 
                        if (y->right != NULL)
                                y->right->parent = y; 
                }

                rb_transplant(tree, delete_me, y); 
                y->left = delete_me->left; 
                y->left->parent = y; 
                y->color = delete_me->color; 
        }

        free(delete_me); 

        if (y_original_color == BLACK) 
                rb_delete_fixup(tree, subtree_of_deleted); 
}

void rb_transplant(T tree, Node *u, Node *v) 
{
        if (u->parent == NULL) {
                tree->root = v; 
        } else if (u == u->parent->left) {
                u->parent->left = v; 
        } else {
                u->parent->right = v;
        }

        if (v != NULL)
                v->parent = u->parent; 
}

void rb_delete_fixup(T tree, Node *culprit)
{
        if (culprit == NULL)
                return; 

        Node *sibling = NULL; 

        while (culprit != tree->root && culprit->color == BLACK) {
                if (culprit == culprit->parent->left) {
                        sibling = culprit->parent->right; 

                        if (sibling->color == RED) {
                                sibling->color = BLACK; 
                                culprit->parent->color = RED; 
                                rb_rotate_left(tree, culprit->parent); 
                                sibling = culprit->parent->right; 
                        }

                        if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                                sibling->color = RED; 
                                culprit = culprit->parent; 
                        } else {
                                if (sibling->right->color == BLACK) {
                                        sibling->left->color = BLACK; 
                                        sibling->color = RED; 
                                        rb_rotate_right(tree, sibling); 
                                        sibling = culprit->parent->right; 
                                }
                                sibling->color = culprit->parent->color; 
                                culprit->parent->color = BLACK; 
                                sibling->right->color = BLACK; 
                                rb_rotate_left(tree, culprit->parent); 
                                culprit = tree->root; 
                        }
                } else { //culprit == culprit->parent->right
                        sibling = culprit->parent->left; 

                        if (sibling->color == RED) {
                                sibling->color = BLACK; 
                                culprit->parent->color = RED; 
                                rb_rotate_left(tree, culprit->parent); 
                                sibling = culprit->parent->left; 
                        }

                        if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                                sibling->color = RED; 
                                culprit = culprit->parent; 
                        } else {
                                if (sibling->left->color == BLACK) {
                                        sibling->right->color = BLACK; 
                                        sibling->color = RED; 
                                        rb_rotate_left(tree, sibling); 
                                        sibling = culprit->parent->left; 
                                }
                                sibling->color = culprit->parent->color; 
                                culprit->parent->color = BLACK; 
                                sibling->left->color = BLACK; 
                                rb_rotate_right(tree, culprit->parent); 
                                culprit = tree->root; 
                        }
                }

        }
        culprit->color = BLACK; 
}

void *rb_tree_maximum(T tree)
{
        Node *result = private_subrb_tree_maximum(tree->root); 
        return result->value; 
}

void *rb_tree_minimum(T tree)
{
        Node *result = private_subrb_tree_minimum(tree->root); 
        return result->value; 
}

void *rb_successor_of_value(T tree, void *value)
{
        return private_rb_successor_of_value(tree, value, tree->comparison_func); 
}

void *rb_predecessor_of_value(T tree, void *value)
{
        return private_rb_predecessor_of_value(tree, value, tree->comparison_func); 
} 

void *private_rb_successor_of_value(T tree, void *value, 
                                 void *comparison_func(void *val1, void *val2))
{
        Node *curr_node = tree->root; 
        Node *successor = NULL; 
        int c; 

        while (curr_node != NULL) {
                c = (int)(intptr_t) comparison_func(value, curr_node->value);

                if (c < 0) {
                        successor = curr_node; 
                        curr_node = curr_node->left; 
                } else {
                        curr_node = curr_node->right; 
                }
        }

        if (successor == NULL) 
                return NULL; 
        else
                return successor->value; 
}

void *private_rb_predecessor_of_value(T tree, void *value, 
                                   void *comparison_func(void *val1, void *val2))
{
        Node *curr_node = tree->root; 
        Node *successor = NULL; 
        int c; 

        while (curr_node != NULL) {
                c = (int)(intptr_t) comparison_func(value, curr_node->value);
                if (c > 0) {
                        successor = curr_node; 
                        curr_node = curr_node->right; 
                } else {
                        curr_node = curr_node->left; 
                }
        }

        if (successor == NULL) 
                return NULL; 
        else
                return successor->value; 
}

Node *private_rb_find_successor(Node *n)
{
        return private_subrb_tree_minimum(n->right);  
}

Node *private_rb_find_predecessor(Node *n)
{
        return private_subrb_tree_maximum(n->left); 
}

Node *private_subrb_tree_maximum(Node *curr_node)
{
        while (curr_node->right != NULL)
                curr_node = curr_node->right; 

        return curr_node;
}

Node *private_subrb_tree_minimum(Node *curr_node)
{
        while (curr_node->left != NULL)
                curr_node = curr_node->left; 

        return curr_node;
}

void rb_map_inorder(T tree,  
                    void func_to_apply(void *value, int depth, void *cl), 
                    void *cl)
{
        int depth = 0; 
        rb_private_inorder_map(tree->root, depth, func_to_apply, cl); 
}

void rb_private_inorder_map(Node *root, 
                            int depth, 
                            void func_to_apply(void *value, int depth, void *cl), 
                            void *cl)
{

        if (root->left != NULL)
                rb_private_inorder_map(root->left, depth + 1, func_to_apply, cl); 

        func_to_apply(root->value, depth, cl); 

        if (root->right != NULL)
                rb_private_inorder_map(root->right, depth + 1, func_to_apply, cl); 
}

void rb_map_preorder(T tree, 
                     void func_to_apply(void *value, int depth, void *cl), 
                     void *cl)
{
        int depth = 0; 
        rb_private_preorder_map(tree->root, depth, func_to_apply, cl); 
}

void rb_private_preorder_map(Node *root, 
                            int depth, 
                            void func_to_apply(void *value, int depth, void *cl), 
                            void *cl)
{
        func_to_apply(root->value, depth, cl); 

        if (root->left != NULL)
                rb_private_preorder_map(root->left, depth + 1, func_to_apply, cl); 

        if (root->right != NULL)
                rb_private_preorder_map(root->right, depth + 1, func_to_apply, cl); 
}

void rb_map_postorder(T tree, 
                      void func_to_apply(void *value, int depth, void *cl), 
                      void *cl)
{
        int depth = 0; 
        rb_private_postorder_map(tree->root, depth, func_to_apply, cl); 
}

void rb_private_postorder_map(Node *root, 
                              int depth, 
                              void func_to_apply(void *value, int depth, void *cl), 
                              void *cl)
{
        if (root->left != NULL)
                rb_private_postorder_map(root->left, depth + 1, func_to_apply, cl); 

        if (root->right != NULL)
                rb_private_postorder_map(root->right, depth + 1, func_to_apply, cl); 

        func_to_apply(root->value, depth, cl); 
}

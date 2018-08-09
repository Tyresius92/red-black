#include "vendor/unity.h"
#include "../src/rb_tree.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_rb_new(void)
{
        RedBlack_T test_tree = rb_new(NULL);
        TEST_ASSERT_NOT_NULL(test_tree);

        free(test_tree); 
}

void test_rb_insert_string(void)
{
        RedBlack_T test_tree = rb_new(NULL);
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "Hello")); 

        rb_tree_free(test_tree); 
}

void test_rb_is_empty_on_empty_tree(void)
{
        RedBlack_T test_tree = rb_new(NULL);
        TEST_ASSERT_TRUE(rb_tree_is_empty(test_tree));

        free(test_tree); 
}

void test_rb_is_empty_one_item_tree(void)
{
        RedBlack_T test_tree = rb_new(NULL);
        rb_insert_value(test_tree, "hello");

        TEST_ASSERT_FALSE(rb_tree_is_empty(test_tree)); 

        rb_tree_free(test_tree); 
}

void test_rb_insert_several_values(void)
{
        RedBlack_T test_tree = rb_new(NULL); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "hello")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "world"));
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "the"));
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "earth"));
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "says"));
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "hello"));

        rb_tree_free(test_tree); 
}

void test_rb_insert_many_times_and_force_rebalancing(void)
{
        RedBlack_T test_tree = rb_new(NULL); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "a")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "b")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "c")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "d")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "e")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "f")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "g")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "h")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "i")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "j")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "k")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "l")); 

        rb_tree_free(test_tree); 
}

void test_rb_insert_reversed_order_and_force_rebalancing(void)
{
        RedBlack_T test_tree = rb_new(NULL); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "l")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "k")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "j")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "i")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "h")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "g")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "f")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "e")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "d")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "c")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "b")); 
        TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, "a")); 

        rb_tree_free(test_tree); 
}

void test_rb_search(void)
{
        RedBlack_T test_tree = rb_new(NULL); 

        rb_insert_value(test_tree, "a"); 
        TEST_ASSERT_NOT_NULL(rb_search(test_tree, "a")); 
        TEST_ASSERT_EQUAL_STRING("a", rb_search(test_tree, "a")); 

        TEST_ASSERT_NULL(rb_search(test_tree, "b")); 
        rb_insert_value(test_tree, "b"); 
        TEST_ASSERT_NOT_NULL(rb_search(test_tree, "b")); 
        TEST_ASSERT_EQUAL_STRING("b", rb_search(test_tree, "b")); 

        TEST_ASSERT_NULL(rb_search(test_tree, "hello")); 
        rb_insert_value(test_tree, "hello"); 
        TEST_ASSERT_NOT_NULL(rb_search(test_tree, "hello")); 
        TEST_ASSERT_EQUAL_STRING("a", rb_search(test_tree, "a")); 


        rb_tree_free(test_tree); 
}

int integer_comparison(void *val_one, void *val_two)
{
        if (*(int *) val_one == *(int *) val_two) {
                return 0; 
        } else if (*(int *) val_one > *(int *) val_two) {
                return 1; 
        } else {
                return -1; 
        }
}

void test_rb_insert_ints(void)
{
        RedBlack_T test_tree = rb_new(&integer_comparison);

        int *test_ptr = NULL; 

        int a[] = { 1, 2, 3, 4, 5, 6, 6, 7, 9, 11};

        for (int i = 0; i < 10; i++) {
                test_ptr = &a[i]; 
                TEST_ASSERT_EQUAL(0, rb_insert_value(test_tree, test_ptr)); 
        }

        rb_tree_free(test_tree); 
}

void test_rb_search_for_ints(void)
{
        RedBlack_T test_tree = rb_new(&integer_comparison);

        int *test_ptr = NULL; 

        int a[] = { 214, 25, 64, 4, 7, 729, 34, 28, 9, 11};

        for (int i = 0; i < 10; i++) {
                test_ptr = &a[i]; 
                rb_insert_value(test_tree, test_ptr); 
        }

        int x = 4; 
        int y = 9; 
        int z = 70000000; 

        TEST_ASSERT_NOT_NULL(rb_search(test_tree, &x)); 
        TEST_ASSERT_EQUAL(x, *(int *) rb_search(test_tree, &x)); 
        
        TEST_ASSERT_NOT_NULL(rb_search(test_tree, &y)); 
        TEST_ASSERT_EQUAL(y, *(int *) rb_search(test_tree, &y)); 

        TEST_ASSERT_NULL(rb_search(test_tree, &z)); 

        rb_tree_free(test_tree); 
}

struct string_closure_size_six {
        int index; 
        int depth_ray[6]; 
        char *word_ray[6]; 
};


void function_to_apply_test_map_string(void *value, int depth, void *cl)
{
        struct string_closure_size_six *closure = (struct string_closure_size_six *) cl; 
        int index = closure->index; 
        
        closure->depth_ray[index] = depth; 
        closure->word_ray[index] = value; 
        closure->index = index + 1; 
}

void test_rb_map_inorder_string(void)
{
        RedBlack_T test_tree = rb_new(NULL); 

        int expected_depth[] = { 2, 1, 3, 2, 0, 1 };
        char *expected_words[] = {"earth", "hello", "hello", "says", "the", "world"};

        char *word_ray[] = {"hello", "world", "the", "earth", "says", "hello"}; 

        for (int i = 0; i < 6; i++) {
                rb_insert_value(test_tree, word_ray[i]); 
        }

        struct string_closure_size_six cl; 
        cl.index = 0; 
        
        rb_map_inorder(test_tree, &function_to_apply_test_map_string, &cl);

        for (int i = 0; i < 6; i++) {
                TEST_ASSERT_EQUAL(expected_depth[i], cl.depth_ray[i]);
                TEST_ASSERT_EQUAL_STRING(expected_words[i], cl.word_ray[i]);  
        }

        rb_tree_free(test_tree); 
}

void test_rb_map_preorder_string(void)
{
        RedBlack_T test_tree = rb_new(NULL); 

        int expected_depth[] = { 0, 1, 2, 2, 3, 1 };
        char *expected_words[] = {"the", "hello", "earth", "says", "hello", "world"};

        char *word_ray[] = {"hello", "world", "the", "earth", "says", "hello"}; 

        for (int i = 0; i < 6; i++) {
                rb_insert_value(test_tree, word_ray[i]); 
        }

        struct string_closure_size_six cl; 
        cl.index = 0; 
        
        rb_map_preorder(test_tree, &function_to_apply_test_map_string, &cl);

        for (int i = 0; i < 6; i++) {
                TEST_ASSERT_EQUAL(expected_depth[i], cl.depth_ray[i]);
                TEST_ASSERT_EQUAL_STRING(expected_words[i], cl.word_ray[i]);  
        }

        rb_tree_free(test_tree); 
}

void test_rb_map_postorder_string(void)
{
        RedBlack_T test_tree = rb_new(NULL); 

        int expected_depth[] = { 2, 3, 2, 1, 1, 0 };
        char *expected_words[] = {"earth", "hello", "says", "hello", "world", "the"};

        char *word_ray[] = {"hello", "world", "the", "earth", "says", "hello"}; 

        for (int i = 0; i < 6; i++) {
                rb_insert_value(test_tree, word_ray[i]); 
        }

        struct string_closure_size_six cl; 
        cl.index = 0; 
        
        rb_map_postorder(test_tree, &function_to_apply_test_map_string, &cl);

        for (int i = 0; i < 6; i++) {
                TEST_ASSERT_EQUAL(expected_depth[i], cl.depth_ray[i]);
                TEST_ASSERT_EQUAL_STRING(expected_words[i], cl.word_ray[i]);  
        }

        rb_tree_free(test_tree); 
}

void test_rb_delete_value(void)
{
        RedBlack_T test_tree = rb_new(NULL); 
        rb_insert_value(test_tree, "hello"); 
        rb_insert_value(test_tree, "world");
        rb_insert_value(test_tree, "the");
        rb_insert_value(test_tree, "earth");
        rb_insert_value(test_tree, "says");

        TEST_ASSERT_EQUAL_STRING("hello", rb_search(test_tree, "hello")); 

        rb_delete_value(test_tree, "hello"); 

        TEST_ASSERT_NULL(rb_search(test_tree, "hello")); 
        TEST_ASSERT_EQUAL_STRING("world", rb_search(test_tree, "world"));
        TEST_ASSERT_EQUAL_STRING("the", rb_search(test_tree, "the"));
        TEST_ASSERT_EQUAL_STRING("earth", rb_search(test_tree, "earth"));
        TEST_ASSERT_EQUAL_STRING("says", rb_search(test_tree, "says"));

        rb_delete_value(test_tree, "the"); 

        TEST_ASSERT_NULL(rb_search(test_tree, "the"));
        TEST_ASSERT_NULL(rb_search(test_tree, "hello")); 
        TEST_ASSERT_EQUAL_STRING("world", rb_search(test_tree, "world"));
        TEST_ASSERT_EQUAL_STRING("earth", rb_search(test_tree, "earth"));
        TEST_ASSERT_EQUAL_STRING("says", rb_search(test_tree, "says"));

        rb_delete_value(test_tree, "earth"); 

        TEST_ASSERT_NULL(rb_search(test_tree, "earth"));
        TEST_ASSERT_NULL(rb_search(test_tree, "the"));
        TEST_ASSERT_NULL(rb_search(test_tree, "hello")); 
        TEST_ASSERT_EQUAL_STRING("world", rb_search(test_tree, "world"));
        TEST_ASSERT_EQUAL_STRING("says", rb_search(test_tree, "says"));

        rb_delete_value(test_tree, "world"); 

        TEST_ASSERT_NULL(rb_search(test_tree, "earth"));
        TEST_ASSERT_NULL(rb_search(test_tree, "the"));
        TEST_ASSERT_NULL(rb_search(test_tree, "hello")); 
        TEST_ASSERT_NULL(rb_search(test_tree, "world"));
        TEST_ASSERT_EQUAL_STRING("says", rb_search(test_tree, "says"));

        rb_delete_value(test_tree, "says"); 

        TEST_ASSERT_NULL(rb_search(test_tree, "earth"));
        TEST_ASSERT_NULL(rb_search(test_tree, "the"));
        TEST_ASSERT_NULL(rb_search(test_tree, "hello")); 
        TEST_ASSERT_NULL(rb_search(test_tree, "world"));
        TEST_ASSERT_NULL(rb_search(test_tree, "says"));

        TEST_ASSERT_TRUE(rb_tree_is_empty(test_tree)); 

        rb_tree_free(test_tree); 
}

void test_rb_delete_value_not_in_tree(void)
{
        RedBlack_T test_tree = rb_new(NULL); 
        rb_insert_value(test_tree, "hello"); 
        rb_insert_value(test_tree, "world");
        rb_insert_value(test_tree, "the");
        rb_insert_value(test_tree, "earth");
        rb_insert_value(test_tree, "says");

        TEST_ASSERT_EQUAL_STRING("hello", rb_search(test_tree, "hello")); 
        TEST_ASSERT_EQUAL_STRING("world", rb_search(test_tree, "world"));
        TEST_ASSERT_EQUAL_STRING("the", rb_search(test_tree, "the"));
        TEST_ASSERT_EQUAL_STRING("earth", rb_search(test_tree, "earth"));
        TEST_ASSERT_EQUAL_STRING("says", rb_search(test_tree, "says"));
        TEST_ASSERT_NULL(rb_search(test_tree, "not_in_tree"));

        rb_delete_value(test_tree, "not_in_tree"); 

        TEST_ASSERT_EQUAL_STRING("hello", rb_search(test_tree, "hello")); 
        TEST_ASSERT_EQUAL_STRING("world", rb_search(test_tree, "world"));
        TEST_ASSERT_EQUAL_STRING("the", rb_search(test_tree, "the"));
        TEST_ASSERT_EQUAL_STRING("earth", rb_search(test_tree, "earth"));
        TEST_ASSERT_EQUAL_STRING("says", rb_search(test_tree, "says"));
        TEST_ASSERT_NULL(rb_search(test_tree, "not_in_tree"));

        rb_tree_free(test_tree); 
}

void test_rb_tree_minimum(void)
{
        RedBlack_T test_tree = rb_new(NULL); 
        rb_insert_value(test_tree, "hello"); 
        rb_insert_value(test_tree, "world");
        rb_insert_value(test_tree, "the");
        rb_insert_value(test_tree, "earth");
        rb_insert_value(test_tree, "says");

        TEST_ASSERT_EQUAL_STRING("earth", rb_tree_minimum(test_tree)); 

        rb_tree_free(test_tree); 
}

void test_rb_tree_maximum(void)
{
        RedBlack_T test_tree = rb_new(NULL); 
        rb_insert_value(test_tree, "hello"); 
        rb_insert_value(test_tree, "world");
        rb_insert_value(test_tree, "the");
        rb_insert_value(test_tree, "earth");
        rb_insert_value(test_tree, "says");

        TEST_ASSERT_EQUAL_STRING("world", rb_tree_maximum(test_tree)); 

        rb_tree_free(test_tree); 
}

void test_rb_successor_of_value(void)
{
        RedBlack_T test_tree = rb_new(NULL); 
        rb_insert_value(test_tree, "hello"); 
        rb_insert_value(test_tree, "world");
        rb_insert_value(test_tree, "the");
        rb_insert_value(test_tree, "earth");
        rb_insert_value(test_tree, "says");

        TEST_ASSERT_EQUAL_STRING("world", rb_successor_of_value(test_tree, "the"));
        TEST_ASSERT_EQUAL_STRING("hello", rb_successor_of_value(test_tree, "earth"));
        TEST_ASSERT_EQUAL_STRING("the", rb_successor_of_value(test_tree, "says")); 
        TEST_ASSERT_EQUAL_STRING("says", rb_successor_of_value(test_tree, "not_in_tree"));
        TEST_ASSERT_NULL(rb_successor_of_value(test_tree, "world"));

        rb_tree_free(test_tree); 
}

void test_rb_predecessor_of_value(void)
{
        RedBlack_T test_tree = rb_new(NULL); 
        rb_insert_value(test_tree, "hello"); 
        rb_insert_value(test_tree, "world");
        rb_insert_value(test_tree, "the");
        rb_insert_value(test_tree, "earth");
        rb_insert_value(test_tree, "says");

        TEST_ASSERT_EQUAL_STRING("says", rb_predecessor_of_value(test_tree, "the"));
        TEST_ASSERT_EQUAL_STRING("hello", rb_predecessor_of_value(test_tree, "says"));
        TEST_ASSERT_EQUAL_STRING("earth", rb_predecessor_of_value(test_tree, "hello"));  
        TEST_ASSERT_EQUAL_STRING("hello", rb_predecessor_of_value(test_tree, "not_in_tree"));
        TEST_ASSERT_NULL(rb_predecessor_of_value(test_tree, "earth"));

        rb_tree_free(test_tree); 
}

int main(void)
{
        UnityBegin("test/test_rb_tree.c");

        RUN_TEST(test_rb_new); 
        RUN_TEST(test_rb_insert_string); 
        RUN_TEST(test_rb_is_empty_on_empty_tree); 
        RUN_TEST(test_rb_is_empty_one_item_tree); 
        RUN_TEST(test_rb_insert_several_values); 
        RUN_TEST(test_rb_insert_many_times_and_force_rebalancing); 
        RUN_TEST(test_rb_insert_reversed_order_and_force_rebalancing); 
        RUN_TEST(test_rb_search); 
        RUN_TEST(test_rb_insert_ints); 
        RUN_TEST(test_rb_search_for_ints); 
        RUN_TEST(test_rb_map_inorder_string); 
        RUN_TEST(test_rb_map_preorder_string); 
        RUN_TEST(test_rb_map_postorder_string); 
        RUN_TEST(test_rb_delete_value); 
        RUN_TEST(test_rb_delete_value_not_in_tree); 
        RUN_TEST(test_rb_tree_minimum); 
        RUN_TEST(test_rb_tree_maximum); 
        RUN_TEST(test_rb_successor_of_value); 
        RUN_TEST(test_rb_predecessor_of_value); 

        UnityEnd();
        return 0;
}

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "stack.h"

void test_new_stack(void **state)
{
    Stack st = stack_new(sizeof(int), 2);
    assert_int_equal(((int *)st.data)[0], 0);
    assert_int_equal(((int *)st.data)[1], 0);
    assert_true(st.element_size == sizeof(int));
    assert_true(st.size == 0);
    assert_true(st.capacity == 2);

    stack_destroy(&st);
}


void test_destroy_stack(void **state)
{
    Stack st = stack_new(sizeof(int), 2);

    stack_destroy(&st);
    assert_true(st.data == NULL);
    assert_true(st.element_size == 0);
    assert_true(st.size == 0);
    assert_true(st.capacity == 0);
}


void test_push_stack(void **state)
{
    Stack st = stack_new(sizeof(int), 2);

    {
        int item = 2;
        stack_push(&st, &item);
        item = 4;
        stack_push(&st, &item);
    }
    assert_int_equal(((int *)st.data)[0], 2);
    assert_int_equal(((int *)st.data)[1], 4);
    assert_true(st.size == 2);
    assert_true(st.capacity == 2);

    {
        int item = 60;
        stack_push(&st, &item);
    }
    assert_int_equal(((int *)st.data)[2], 60);
    assert_true(st.size == 3);
    assert_true(st.capacity == 3);

    {
        int item = 800;
        stack_push(&st, &item);
    }
    assert_int_equal(((int *)st.data)[3], 800);
    assert_true(st.size == 4);
    assert_true(st.capacity == 4);

    {
        int item = 1000;
        stack_push(&st, &item);
    }
    assert_true(st.size == 5);
    assert_true(st.capacity == 6);

    stack_destroy(&st);
    assert_true(st.data == NULL);
}


int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_new_stack),
        cmocka_unit_test(test_destroy_stack),
        cmocka_unit_test(test_push_stack),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

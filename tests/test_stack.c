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
    assert_true(st.data == NULL);
    assert_true(st.element_size == 0);
    assert_true(st.size == 0);
    assert_true(st.capacity == 0);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_new_stack),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "slotmap.h"


void test_new_sm(void **state)
{
    Slotmap sm = sm_new();

    assert_int_equal(((int)sm.free_stack.size), 0);

    sm_destroy(&sm);
}

void test_destroy_sm(void **state)
{
    Slotmap sm = sm_new();
    sm_destroy(&sm);

    assert_int_equal((sm.free_stack.capacity), 0);
    assert_true(sm.item_table == NULL);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_new_sm),
        cmocka_unit_test(test_destroy_sm)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

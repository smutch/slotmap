#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "slotmap.h"


void test_new_sm(void **state)
{
    Slotmap sm = sm_new();

    assert_int_equal(((int)sm.free_stack.size), 0);
    assert_int_equal(((int)sm.chunk_stack.size), 0);

    sm_destroy(&sm);
}

void test_destroy_sm(void **state)
{
    Slotmap sm = sm_new();
    sm_destroy(&sm);

    assert_int_equal((sm.free_stack.capacity), 0);
    assert_true(sm.chunk_stack.data == NULL);
}

void test_create_item(void **state)
{
    Slotmap sm = sm_new();
    sm_item_id id = sm_create_item(&sm);

    assert_int_equal(id, 0);

    // TODO(test): Finish test...

    sm_destroy(&sm);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_new_sm),
        cmocka_unit_test(test_create_item),
        cmocka_unit_test(test_destroy_sm)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

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

    id = sm_create_item(&sm);
    assert_int_equal(id, 1);

    sm_create_item(&sm);
    id = sm_create_item(&sm);
    assert_int_equal(id, 3);

    sm_destroy(&sm);
}

void test_get_item(void **state)
{
    Slotmap sm = sm_new();

    sm_item_id id = sm_create_item(&sm);
    SMItem* item = sm_get_item(&sm, id);
    assert_int_equal(item->id, id);

    item->value = 50;
    item = sm_get_item(&sm, id);
    assert_float_equal(item->value, 50, 1e-8);

    sm_destroy(&sm);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_new_sm),
        cmocka_unit_test(test_create_item),
        cmocka_unit_test(test_get_item),
        cmocka_unit_test(test_destroy_sm)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

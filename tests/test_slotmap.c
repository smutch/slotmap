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

    SMItem* item = sm_create_item(&sm);
    assert_int_equal(item->id, 0);

    item = sm_create_item(&sm);
    assert_int_equal(item->id, 1);

    sm_create_item(&sm);
    item = sm_create_item(&sm);
    assert_int_equal(item->id, 3);

    sm_destroy(&sm);
}

void test_get_item(void **state)
{
    Slotmap sm = sm_new();

    SMItem* item = sm_create_item(&sm);
    SMItem* retrieved = sm_get_item(&sm, item->id);
    assert_int_equal(retrieved->id, item->id);

    item->value = 50;
    retrieved = sm_get_item(&sm, retrieved->id);
    assert_float_equal(retrieved->value, 50, 1e-8);

    sm_destroy(&sm);
}

void test_remove_item(void **state)
{
    Slotmap sm = sm_new();

    SMItem* item0 = sm_create_item(&sm);
    sm_item_id id0 = item0->id;
    SMItem* item1 = sm_create_item(&sm);
    sm_item_id id1 = item1->id;

    sm_remove_item(&sm, id0);
    assert_null(sm_get_item(&sm, id0));

    sm_remove_item(&sm, id1);
    assert_null(sm_get_item(&sm, id1));

    item0 = sm_create_item(&sm);
    id0 = item0->id;
    item1 = sm_create_item(&sm);
    id1 = item1->id;

    sm_remove_item(&sm, id1);
    assert_null(sm_get_item(&sm, id1));
    assert_int_equal(sm_get_item(&sm, id0)->id, id0);

    sm_remove_item(&sm, id0);
    assert_null(sm_get_item(&sm, id0));

    sm_destroy(&sm);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_new_sm),
        cmocka_unit_test(test_create_item),
        cmocka_unit_test(test_get_item),
        cmocka_unit_test(test_remove_item),
        cmocka_unit_test(test_destroy_sm)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

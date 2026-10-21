#include "common.h"

extern s32 scene_object_payload_alias;
extern void get_linked_carry_item_data(void *record, s32 first_value, s32 second_value);

/* Run plt_carry_on_chk_ext using the global record and its context values. */
void plt_carry_on_chk_ext(void) {
    s32 *record = &scene_object_payload_alias;
    s32 *context = record - 8;


    get_linked_carry_item_data(record, context[2], context[3]);
}

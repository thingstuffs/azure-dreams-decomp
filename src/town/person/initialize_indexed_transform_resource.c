#include "common.h"

extern void initialize_the_store_two_values_set_state_flags(void *record, s32 value_08, void *value_0c);
extern void *D_800D4F88[];
extern s32 D_800C283C[];

/* Initialize the object with its indexed resource and set its flag and data pointer. */
void initialize_indexed_transform_resource(void *object, s32 setup_value, s32 unused) {
    u8 *obj = (u8 *)object;

    initialize_the_store_two_values_set_state_flags(object, setup_value, D_800D4F88[obj[0x94]]);
    obj[0x14] = 1;
    *(void **)(obj + 0x50) = D_800C283C;
}

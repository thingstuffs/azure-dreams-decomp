/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

extern void handle_insert_initialize_two_values_status_flags(void *, s32, void *);
extern void initialize_optional_object_state(void *, s32, void *, void *);

extern s32 town_object_resource_table[];
extern s32 D_800D0690[];
extern s32 D_800D0710[];
extern s32 D_800F8C80[];

/*
 * Sets state data D_800F8C80 and object data D_800D0710, initializes the town resource table
 * entries, and binds optional state D_800D0690.
 */
void initialize_object_resources_and_state(void *object, s32 init_arg, void *state) {
    *(void **)((u8 *)state + 8) = D_800F8C80;
    *(void **)((u8 *)object + 0x7C) = D_800D0710;
    handle_insert_initialize_two_values_status_flags(object, init_arg, town_object_resource_table);
    initialize_optional_object_state(object, init_arg, state, D_800D0690);
}

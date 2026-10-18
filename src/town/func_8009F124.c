#include "common.h"

extern void handle_insert_initialize_two_values_status_flags(void *, s32, void *);
extern void initialize_optional_object_state(void *, s32, void *, void *);

extern s32 D_800CFD00[];
extern s32 D_800D06AC[];
extern s32 D_800D0704[];
extern s32 D_800F8C44[];

/* Sets up an object's resource tables and associated state. */
void initialize_object_resource_tables(void *object, s32 init_arg, void *state) {
    *(void **)((u8 *)state + 8) = D_800F8C44;
    *(void **)((u8 *)object + 0x80) = D_800D0704;
    handle_insert_initialize_two_values_status_flags(object, init_arg, D_800CFD00);
    initialize_optional_object_state(object, init_arg, state, D_800D06AC);
}

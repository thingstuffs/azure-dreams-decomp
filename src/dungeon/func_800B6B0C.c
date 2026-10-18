#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800BC26C_0 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800BC26C_0;   /* result in create_tracked_effect */

typedef struct S_800BC26C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    s16 unk_0C;
    s16 unk_0E;
} S_800BC26C_1;   /* fields in create_tracked_effect */


extern void * func_8003FD64();
extern s32 func_8004491C();
extern void retire_effect_when_owner_or_value_ends(void *context);
extern s32 traverse_nodes_and_render_unflagged();

/* Creates an object and initializes its owner, parameter, and mode-dependent fields. */
void *create_tracked_effect(s32 owner, s16 mode, s32 param)
{
    void *object;
    u8 *fields;
    s16 saved_mode;

    object = func_8003FD64(0x110, (void *)owner);
    saved_mode = mode;
    if (object != NULL) {
        ((S_800BC26C_0 *)object)->unk_10 = retire_effect_when_owner_or_value_ends;
        func_8004491C(object, traverse_nodes_and_render_unflagged);
        fields = (u8 *)object + 0x20;
        ((S_800BC26C_0 *)object)->unk_20 = owner;
        ((S_800BC26C_1 *)fields)->unk_04 = param;
        if (mode != 0) {
            ((S_800BC26C_1 *)fields)->unk_0C = 0x7F80;
        } else {
            ((S_800BC26C_1 *)fields)->unk_0C = 0x7FC0;
        }
        ((S_800BC26C_1 *)fields)->unk_0E = saved_mode;
    }
    return object;
}

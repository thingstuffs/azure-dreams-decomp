#include "common.h"

extern void *allocate_and_initialize_display_object(s32, s32, s32, s32, s32, s32);
extern s32 D_800A2338;
extern s32 D_800A23D0;

/* Forward four inputs to allocate_and_initialize_display_object with two fixed data pointers. */
void *create_object_with_shared_data(s32 input_first, s32 input_second, s32 input_third, s32 input_fourth) {
    return allocate_and_initialize_display_object(input_first, input_second, input_third, input_fourth, &D_800A2338, &D_800A23D0);
}

/* MECHANISM: sp+0x10 and sp+0x14 are outgoing ABI slots for arguments 5 and 6,
   not volatile locals; forwarding incoming a0-a3 exposes the real six-argument call.
   The true-space rowbase name lets the second outgoing store occupy the jal delay slot. */

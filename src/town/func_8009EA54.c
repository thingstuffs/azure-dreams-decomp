#include "common.h"

extern s32 check_object_type_and_data_tag(void *record);
extern void func_8004437C(s32 a0, s32 a1);
extern short SD_Call(int a0);
extern u8 D_8009B9BC[];

/* Clear object state, assign the context handler, and trigger effects if the check succeeds. */
void initialize_object_and_maybe_play_sound(u8 *context, s8 *object, s32 *state)
{
    object[0x15] = 0;
    state[3] = 0;
    state[4] = 0;
    state[5] = 0;
    *(void **)(context + 0x50) = D_8009B9BC;
    if (check_object_type_and_data_tag(context + 0x4C) != 0) {
        func_8004437C(0x26, 0);
        SD_Call(0x200);
    }
}

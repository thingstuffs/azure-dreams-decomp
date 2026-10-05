#include "common.h"

extern void func_80099754(void *record);
extern void func_80098928(void *record, void *setup_value, s32 init_value);

/* Move the position toward its target until the countdown expires, then finish the move. */
void func_80098690(u8 *motion, u8 *position, s32 callback_arg) {
    s16 steps_left;
    s16 y_steps_left;

    steps_left = (*(u16 *)(motion + 0xA) -= 1);
    if (steps_left > 0) {
        *(s32 *)(position + 0) += (((s32) *(s16 *)(motion + 0x30) << 16) - *(s32 *)(position + 0)) / steps_left;
        *(s32 *)(position + 4) += (((s32) *(s16 *)(motion + 0x32) << 16)
            - *(s32 *)(position + 4)) / (y_steps_left = *(s16 *)(motion + 0xA));
        return;
    }
    *(u16 *)(position + 2) = *(u16 *)(motion + 0x30);
    *(u16 *)(position + 6) = *(u16 *)(motion + 0x32);
    func_80099754(position);
    func_80098928(motion, position, callback_arg);
}

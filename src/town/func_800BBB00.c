#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

M2C_UNK func_800B9204(); /* extern */
extern u8 D_800D185C;
extern u8 D_800D185D;

/* Updates two wrapping indices from input flags and calls func_800B9204 on a button combination. */
void func_800B9260(void) {
    GameWork *input_state = &gameWork;
    s32 input_flags = ((s32)input_state->unk_010);
    u32 buttons;
    s32 masked_buttons;

    if (input_flags < 0) {
        D_800D185C += 0x20;
    }
    if (input_flags & 0x20000000) {
        D_800D185C++;
    }
    D_800D185C %= 33;
    if (input_flags & 0x40000000) {
        D_800D185D += 0x42;
    }
    if (input_flags & 0x10000000) {
        D_800D185D++;
    }
    buttons = D_800D185D;
    buttons -= buttons / 67 * 67;
    *(volatile u8 *) &D_800D185D = buttons;
    buttons = *(volatile s32 *) &input_state->buttons;
    masked_buttons = buttons & 0x500000;
    if (masked_buttons == 0x500000) {
        func_800B9204(D_800D185D);
    }
}

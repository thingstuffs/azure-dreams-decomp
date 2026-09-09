#include "common.h"

typedef s32 M2C_UNK;


extern s32 func_8002553C();
extern M2C_UNK func_80025598();
extern M2C_UNK func_800255AC();
extern M2C_UNK func_8002661C();
extern M2C_UNK func_80026CD8();
extern M2C_UNK func_80026D0C();
extern M2C_UNK func_80027454();
extern M2C_UNK func_800274A8();
extern M2C_UNK func_80028620();
extern M2C_UNK SD_Call();

extern M2C_UNK D_80027E10;
extern M2C_UNK D_80027E84;
extern u8 D_80083160[];


typedef struct S_800277A8_0 {
    u8 pad_00[0x8];
    union { s32 n; volatile s32 v; } unk_08;   /* accessed as both */
    u8 pad_0C[0x4];
    volatile s32 unk_10;
} S_800277A8_0;   /* input in func_800277A8 */

typedef struct S_800277A8_1_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800277A8_1_pre;   /* the 0x10 bytes before arg0 in func_800277A8, addressed as arg0[-1] */

typedef struct S_800277A8_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    u8 pad_18[0x10];
    s32 unk_28;
    u8 pad_2C[0x10];
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    u8 pad_48[0x40];
    s32 unk_88;
} S_800277A8_1;   /* arg0 in func_800277A8 */

/* Handle menu buttons and move the selection, refreshing the page when needed. */
void func_800277A8(void *menu) {
    u8 *input = D_80083160;
    s32 held_buttons;
    s32 buttons;
    s32 cursor_step = 0;
    s32 repeat_count;
    s32 new_offset;
    s32 old_offset;
    s32 row_count;
    s32 rows_left;

    held_buttons = ((S_800277A8_0 *)input)->unk_08.n;
    if (held_buttons == 0) {
        return;
    }

    buttons = ((S_800277A8_0 *)input)->unk_10;
    if (buttons & 0x20) {
        SD_Call(0x515);
        ((S_800277A8_1_pre *)menu)[-1].unk_00 = &D_80027E10;
        ((S_800277A8_1 *)menu)->unk_00 = ((S_800277A8_1 *)menu)->unk_04;
        func_80028620((u8 *)menu - 0x20);
        func_80025598(((S_800277A8_1 *)menu)->unk_44);
        return;
    }

    if (buttons & 0x10) {
        SD_Call(0x503);
        func_800274A8(menu);
        func_800255AC(((S_800277A8_1 *)menu)->unk_44);
        return;
    }

    if (buttons & 0x40) {
        SD_Call(0x503);
        func_80027454((u8 *)menu + 0x38, ((S_800277A8_1 *)menu)->unk_14,
                     (((S_800277A8_1 *)menu)->unk_08 / 72) * 72,
                     ((S_800277A8_1 *)menu)->unk_28);
        func_8002661C(func_8002553C(((S_800277A8_1 *)menu)->unk_44),
                     ((S_800277A8_1 *)menu)->unk_40 +
                         (((S_800277A8_1 *)menu)->unk_08 % 72) * 2);
        return;
    }

    if (!(held_buttons & 0x5000)) {
        goto check_delta;
    }

    if (buttons & 0x5000) {
        ((S_800277A8_1 *)menu)->unk_0C = 0;
        buttons = ((S_800277A8_0 *)input)->unk_10;
        if (buttons & 0x1000) {
            goto dispatch_negative;
        }
        goto test_positive;
    }

    repeat_count = ((S_800277A8_1 *)menu)->unk_0C;
    if (repeat_count < 9) {
        goto increment_count;
    }

    ((S_800277A8_1 *)menu)->unk_0C = repeat_count - 1;
    buttons = ((S_800277A8_0 *)input)->unk_08.v;
    if (!(buttons & 0x1000)) {
        goto test_positive;
    }

dispatch_negative:
    cursor_step = -9;
    goto check_delta;

test_positive:
    if (!(buttons & 0x4000)) {
        goto check_delta;
    }

dispatch_positive:
    cursor_step = 9;
    goto check_delta;

increment_count:
    ((S_800277A8_1 *)menu)->unk_0C = repeat_count + 1;

check_delta:
    if (cursor_step == 0) {
        return;
    }

    SD_Call(0x502);
    new_offset = ((S_800277A8_1 *)menu)->unk_08 + cursor_step;
    row_count = ((S_800277A8_1 *)menu)->unk_3C;
    rows_left = row_count - new_offset / 9;
    if (rows_left <= 0 || row_count < rows_left) {
        return;
    }

    old_offset = new_offset - cursor_step;
    ((S_800277A8_1 *)menu)->unk_08 = new_offset;
    if (new_offset / 72 != old_offset / 72) {
        func_80026CD8(((S_800277A8_1 *)menu)->unk_88);
        ((S_800277A8_1_pre *)menu)[-1].unk_00 = &D_80027E84;
        ((S_800277A8_1 *)menu)->unk_00 = ((S_800277A8_1 *)menu)->unk_04;
        return;
    }

    func_80026D0C(((S_800277A8_1 *)menu)->unk_88);
}

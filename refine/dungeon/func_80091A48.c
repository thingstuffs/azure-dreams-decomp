#include "common.h"

typedef struct S_800971A8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x64];
    s16 unk_100;
} S_800971A8_0;   /* arg0 in func_800971A8 */

typedef struct S_800971A8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800971A8_1;   /* arg1 in func_800971A8 */

typedef struct S_800971A8_2 {
    u8 pad_00[0x5C];
    s32 unk_5C;
} S_800971A8_2;   /* arg3 in func_800971A8 */

typedef struct S_800971A8_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800971A8_3;   /* arg2 in func_800971A8 */


typedef struct { u8 pad0[2]; u16 field2; s16 field4; u8 pad6[6]; } D_80083460_t;
extern D_80083460_t D_80083460;
extern u8 D_80096384[];
extern void *D_80088B18[];
extern void func_80095DD0(void *, void *, void *, void *);
extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);

/* Advances timed movement toward a destination and handles completion. */
void func_800971A8(S_800971A8_0 *action, S_800971A8_1 *motion, S_800971A8_3 *destination, S_800971A8_2 *actor) {
    u16 delay;
    u8 state;
    s32 vertical_speed;
    void *fallback_data;
    D_80083460_t *move_control;
    static void *const state_labels[] = {
        &&case_a, &&case_b, &&done, &&done, &&done, &&done, &&done,
        &&done, &&case_a, &&case_b, &&case_a, &&case_b, &&case_c
    };
    (void)state_labels;
    state = action->unk_9B;
    if (state >= 13) goto done;
    goto *D_80088B18[state];
case_a:
    delay = action->unk_96 - 1;
    action->unk_96 = delay;
    if ((s16)delay > 0) goto done;
    state = action->unk_9B;
    vertical_speed = 8;
    if (state == 0) {
        vertical_speed = 0xFFF00000;
        goto store_selected;
    }
    if (state == vertical_speed) vertical_speed = 0xFFF80000;
    else vertical_speed = 0xFFEC0000;
store_selected:
    motion->unk_14 = vertical_speed;
    func_80099F70(actor->unk_5C);
    func_80099F04(actor->unk_5C);
    D_80083460.field2 |= 0x812;
    action->unk_98 &= 0xFFF3;
    action->unk_9B++;
    func_800A56E0(0x50A);
    return;
case_b:
    move_control = &D_80083460;
    if (move_control->field4 == 0) goto after_div;
    {
        s32 target_x, current_x, current_y;
        target_x = destination->unk_24 << 6;
        current_x = motion->unk_02 - 0x20;
        motion->unk_0C = ((target_x - current_x) << 16) / move_control->field4;
        current_y = motion->unk_06 - 0x20;
        motion->unk_10 = (((destination->unk_25 << 6) - current_y) << 16) / move_control->field4;
    }
after_div:
    move_control->field4--;
    if (move_control->field4 > 0) goto done;
    move_control->field4 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, destination->unk_24, destination->unk_25);
    if (action->unk_9B >= 10) {
        move_control->field4 = 1;
        action->unk_9B++;
        return;
    }
    if (action->unk_100 >= 0) {
        func_80095DD0(action, motion, destination, actor);
        return;
    }
    fallback_data = D_80096384;
    goto store_tail;
case_c:
    if (destination->unk_14 & 0x6000) {
        D_80083460.field4 = 0;
        if (action->unk_100 >= 0) {
            func_80095DD0(action, motion, destination, actor);
            return;
        }
        fallback_data = D_80096384;
        goto store_tail;
    }
    goto done;
store_tail:
    action->unk_8C = fallback_data;
done:
    return;
}

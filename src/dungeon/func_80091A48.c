#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"






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
void func_800971A8(Rec_func_8008ACDC_arg0 *action, Rec_D_800E3D7C *motion, Rec_D_80082E80 *destination, Rec_D_800E3D7C *actor) {
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
    state = action->unk_9B.as_u8;
    if (state >= 13) goto done;
    goto *D_80088B18[state];
case_a:
    delay = action->unk_96.as_u16 - 1;
    action->unk_96.as_u16 = delay;
    if ((s16)delay > 0) goto done;
    state = action->unk_9B.as_u8;
    vertical_speed = 8;
    if (state == 0) {
        vertical_speed = 0xFFF00000;
        goto store_selected;
    }
    if (state == vertical_speed) vertical_speed = 0xFFF80000;
    else vertical_speed = 0xFFEC0000;
store_selected:
    motion->unk_14.as_s32 = vertical_speed;
    func_80099F70(actor->unk_5C);
    func_80099F04(actor->unk_5C);
    D_80083460.field2 |= 0x812;
    action->unk_98 &= 0xFFF3;
    action->unk_9B.as_u8++;
    func_800A56E0(0x50A);
    return;
case_b:
    move_control = &D_80083460;
    if (move_control->field4 == 0) goto after_div;
    {
        s32 target_x, current_x, current_y;
        target_x = destination->unk_24 << 6;
        current_x = motion->unk_00.at02_s16.v - 0x20;
        motion->unk_0C.as_s32 = ((target_x - current_x) << 16) / move_control->field4;
        current_y = motion->unk_04.at02_s16.v - 0x20;
        motion->unk_10.at00_s32.v = (((destination->unk_25 << 6) - current_y) << 16) / move_control->field4;
    }
after_div:
    move_control->field4--;
    if (move_control->field4 > 0) goto done;
    move_control->field4 = 0;
    motion->unk_10.at00_s32.v = 0;
    motion->unk_0C.as_s32 = 0;
    func_800A2B04(motion, destination->unk_24, destination->unk_25);
    if (action->unk_9B.as_u8 >= 10) {
        move_control->field4 = 1;
        action->unk_9B.as_u8++;
        return;
    }
    if (action->unk_100 >= 0) {
        func_80095DD0(action, motion, destination, actor);
        return;
    }
    fallback_data = D_80096384;
    goto store_tail;
case_c:
    if (destination->unk_14.at00_u16.v & 0x6000) {
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
    action->unk_8C.as_pv = fallback_data;
done:
    return;
}

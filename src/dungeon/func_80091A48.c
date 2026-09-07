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

void func_800971A8(Rec_func_8008ACDC_arg0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3) {
    u16 timer; u8 state; s32 selected; void *tail_ptr; D_80083460_t *global;
    static void *const jt_keep[] = {
        &&case_a, &&case_b, &&done, &&done, &&done, &&done, &&done,
        &&done, &&case_a, &&case_b, &&case_a, &&case_b, &&case_c
    };
    (void)jt_keep;
    state = arg0->unk_9B.as_u8;
    if (state >= 13) goto done;
    goto *D_80088B18[state];
case_a:
    timer = arg0->unk_96.as_u16 - 1;
    arg0->unk_96.as_u16 = timer;
    if ((s16)timer > 0) goto done;
    state = arg0->unk_9B.as_u8;
    selected = 8;
    if (state == 0) {
        selected = 0xFFF00000;
        goto store_selected;
    }
    if (state == selected) selected = 0xFFF80000;
    else selected = 0xFFEC0000;
store_selected:
    arg1->unk_14.as_s32 = selected;
    func_80099F70(arg3->unk_5C);
    func_80099F04(arg3->unk_5C);
    D_80083460.field2 |= 0x812;
    arg0->unk_98 &= 0xFFF3;
    arg0->unk_9B.as_u8++;
    func_800A56E0(0x50A); return;
case_b:
    global = &D_80083460;
    if (global->field4 == 0) goto after_div;
    {
        s32 scaled, coord_x, coord_y;
        scaled = arg2->unk_24 << 6;
        coord_x = arg1->unk_00.at02_s16.v - 0x20;
        arg1->unk_0C.as_s32 = ((scaled - coord_x) << 16) / global->field4;
        coord_y = arg1->unk_04.at02_s16.v - 0x20;
        arg1->unk_10.at00_s32.v = (((arg2->unk_25 << 6) - coord_y) << 16) / global->field4;
    }
after_div:
    global->field4--;
    if (global->field4 > 0) goto done;
    global->field4 = 0;
    arg1->unk_10.at00_s32.v = 0; arg1->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
    if (arg0->unk_9B.as_u8 >= 10) {
        global->field4 = 1; arg0->unk_9B.as_u8++; return;
    }
    if (arg0->unk_100 >= 0) {
        func_80095DD0(arg0, arg1, arg2, arg3);
        return;
    }
    tail_ptr = D_80096384;
    goto store_tail;
case_c:
    if (arg2->unk_14.at00_u16.v & 0x6000) {
        D_80083460.field4 = 0;
        if (arg0->unk_100 >= 0) {
            func_80095DD0(arg0, arg1, arg2, arg3); return;
        }
        tail_ptr = D_80096384;
        goto store_tail;
    }
    goto done;
store_tail:
    arg0->unk_8C.as_pv = tail_ptr;
done: return;
}

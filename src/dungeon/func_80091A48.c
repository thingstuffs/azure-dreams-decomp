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

void func_800971A8(S_800971A8_0 *arg0, S_800971A8_1 *arg1, S_800971A8_3 *arg2, S_800971A8_2 *arg3) {
    u16 timer; u8 state; s32 selected; void *tail_ptr; D_80083460_t *global;
    static void *const jt_keep[] = {
        &&case_a, &&case_b, &&done, &&done, &&done, &&done, &&done,
        &&done, &&case_a, &&case_b, &&case_a, &&case_b, &&case_c
    };
    (void)jt_keep;
    state = arg0->unk_9B;
    if (state >= 13) goto done;
    goto *D_80088B18[state];
case_a:
    timer = arg0->unk_96 - 1;
    arg0->unk_96 = timer;
    if ((s16)timer > 0) goto done;
    state = arg0->unk_9B;
    selected = 8;
    if (state == 0) {
        selected = 0xFFF00000;
        goto store_selected;
    }
    if (state == selected) selected = 0xFFF80000;
    else selected = 0xFFEC0000;
store_selected:
    arg1->unk_14 = selected;
    func_80099F70(arg3->unk_5C);
    func_80099F04(arg3->unk_5C);
    D_80083460.field2 |= 0x812;
    arg0->unk_98 &= 0xFFF3;
    arg0->unk_9B++;
    func_800A56E0(0x50A); return;
case_b:
    global = &D_80083460;
    if (global->field4 == 0) goto after_div;
    {
        s32 scaled, coord_x, coord_y;
        scaled = arg2->unk_24 << 6;
        coord_x = arg1->unk_02 - 0x20;
        arg1->unk_0C = ((scaled - coord_x) << 16) / global->field4;
        coord_y = arg1->unk_06 - 0x20;
        arg1->unk_10 = (((arg2->unk_25 << 6) - coord_y) << 16) / global->field4;
    }
after_div:
    global->field4--;
    if (global->field4 > 0) goto done;
    global->field4 = 0;
    arg1->unk_10 = 0; arg1->unk_0C = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
    if (arg0->unk_9B >= 10) {
        global->field4 = 1; arg0->unk_9B++; return;
    }
    if (arg0->unk_100 >= 0) {
        func_80095DD0(arg0, arg1, arg2, arg3);
        return;
    }
    tail_ptr = D_80096384;
    goto store_tail;
case_c:
    if (arg2->unk_14 & 0x6000) {
        D_80083460.field4 = 0;
        if (arg0->unk_100 >= 0) {
            func_80095DD0(arg0, arg1, arg2, arg3); return;
        }
        tail_ptr = D_80096384;
        goto store_tail;
    }
    goto done;
store_tail:
    arg0->unk_8C = tail_ptr;
done: return;
}

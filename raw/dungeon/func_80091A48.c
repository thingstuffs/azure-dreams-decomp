#include "common.h"

typedef struct { u8 pad0[2]; u16 field2; s16 field4; u8 pad6[6]; } D_80083460_t;
extern D_80083460_t D_80083460;
extern u8 D_80096384[];
extern void *D_80088B18[];
extern void func_80095DD0(void *, void *, void *, void *);
extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

void func_800971A8(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 timer; u8 state; s32 selected; void *tail_ptr; D_80083460_t *global;
    static void *const jt_keep[] = {
        &&case_a, &&case_b, &&done, &&done, &&done, &&done, &&done,
        &&done, &&case_a, &&case_b, &&case_a, &&case_b, &&case_c
    };
    (void)jt_keep;
    state = FIELD(arg0, u8, 0x9B);
    if (state >= 13) goto done;
    goto *D_80088B18[state];
case_a:
    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((s16)timer > 0) goto done;
    state = FIELD(arg0, u8, 0x9B);
    selected = 8;
    if (state == 0) {
        selected = 0xFFF00000;
        goto store_selected;
    }
    if (state == selected) selected = 0xFFF80000;
    else selected = 0xFFEC0000;
store_selected:
    FIELD(arg1, s32, 0x14) = selected;
    func_80099F70(FIELD(arg3, s32, 0x5C));
    func_80099F04(FIELD(arg3, s32, 0x5C));
    D_80083460.field2 |= 0x812;
    FIELD(arg0, u16, 0x98) &= 0xFFF3;
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x50A); return;
case_b:
    global = &D_80083460;
    if (global->field4 == 0) goto after_div;
    {
        s32 scaled, coord_x, coord_y;
        scaled = FIELD(arg2, u8, 0x24) << 6;
        coord_x = FIELD(arg1, s16, 2) - 0x20;
        FIELD(arg1, s32, 0xC) = ((scaled - coord_x) << 16) / global->field4;
        coord_y = FIELD(arg1, s16, 6) - 0x20;
        FIELD(arg1, s32, 0x10) = (((FIELD(arg2, u8, 0x25) << 6) - coord_y) << 16) / global->field4;
    }
after_div:
    global->field4--;
    if (global->field4 > 0) goto done;
    global->field4 = 0;
    FIELD(arg1, s32, 0x10) = 0; FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    if (FIELD(arg0, u8, 0x9B) >= 10) {
        global->field4 = 1; FIELD(arg0, u8, 0x9B)++; return;
    }
    if (FIELD(arg0, s16, 0x100) >= 0) {
        func_80095DD0(arg0, arg1, arg2, arg3);
        return;
    }
    tail_ptr = D_80096384;
    goto store_tail;
case_c:
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        D_80083460.field4 = 0;
        if (FIELD(arg0, s16, 0x100) >= 0) {
            func_80095DD0(arg0, arg1, arg2, arg3); return;
        }
        tail_ptr = D_80096384;
        goto store_tail;
    }
    goto done;
store_tail:
    FIELD(arg0, void *, 0x8C) = tail_ptr;
done: return;
}

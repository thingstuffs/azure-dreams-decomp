#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80171094[];
extern s32 D_8008346C[];
extern u8 D_80176460[8];
extern s16 D_80083228[5];
typedef struct Obj0 {
    u8 pad04[4];
    s8 field04;
    u8 pad14[0x14 - 5];
    u16 field14;
    u8 pad8c[0x8c - 0x16];
    u8 *field8c;
    u8 pad96[0x96 - 0x90];
    u16 field96;
    u16 field98;
    u8 pad9b[1];
    u8 state9b;
} Obj0;

typedef struct Obj2 {
    u8 pad04[4];
    s8 field04;
    u8 pad14[0x14 - 5];
    u16 field14;
    u8 pad24[0x24 - 0x16];
    u8 field24;
    u8 field25;
    u8 pad2c[0x2c - 0x26];
    u8 *field2c;
} Obj2;

typedef struct Obj3 {
    u8 pad14[0x14];
    u32 field14;
    u8 pad2a[0x2a - 0x18];
    s16 field2a;
    u8 pad46[0x46 - 0x2c];
    u16 field46;
    u8 pad60[0x60 - 0x48];
    struct Obj3 *field60;
} Obj3;

extern void func_800AD594(Obj3 *, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_80047784(Obj2 *, u8, s32);
extern void func_80174CB0(s32);
extern void func_80174D0C(s32);
extern void func_80175D04(Obj0 *, void *, Obj2 *);
extern void func_801762A4(s32, Obj3 *);

void func_80174AF4(Obj0 *arg0, void *arg1, Obj2 *arg2, Obj3 *arg3) {
    s32 state;
    s32 temp_state;
    u16 count;
    u16 temp_count;
    u16 temp_flags;
    s32 var_a0;

    state = arg0->state9b;
    var_a0 = 1;
    if (state != var_a0) {
        if ((s32) state < 2) {
            if (state == 0) {
                goto state0;
            }
            goto common;
        }
    } else {
        goto state1;
    }
    if (state != 2) {
        goto common;
    }
    goto state2;

state0:
    temp_flags = arg2->field14;
    if (temp_flags & 0x8000) {
        arg2->field14 = (u16) (temp_flags | 0x6000);
        arg0->state9b = 2;
        goto epilogue;
    }
    if (arg2->field04 != var_a0) {
        if ((temp_flags & 0x6000) == 0) {
            goto common;
        }
    } else if ((temp_flags & 0x1000) == 0) {
        if ((temp_flags & 0x6000) == 0) {
            goto common;
        }
    }
state0_call:
    func_80175D04(arg0, arg1, arg2);
    var_a0 = 1;
    if ((arg3->field14 & 0x4000) || (var_a0 = 0, (arg3->field60->field14 & 0x4000) != 0)) {
        func_801762A4(var_a0, arg3);
    }
    func_800A56E0(0x80D);
    temp_state = arg0->state9b;
    temp_count = 0x20;
    arg0->field96 = temp_count;
    arg0->state9b = temp_state + 1;
    goto common;

state1:
    count = arg0->field96 - 1;
    arg0->field96 = count;
    if ((count << 0x10) != 0) {
        if ((arg2->field14 | 0x8000) == 0) {
            goto common;
        }
    }
    temp_state = arg0->state9b;
    temp_count = 4;
    arg0->field96 = temp_count;
    arg0->state9b = temp_state + 1;
    goto common;

state2:
    count = arg0->field96 - 1;
    arg0->field96 = count;
    if ((count << 0x10) != 0 && (arg2->field14 & 0xE000) == 0) {
        goto epilogue;
    }
    func_800AD594(arg3, 0x400);
    func_800A2B04(arg1, arg2->field24, arg2->field25);
    arg0->field8c = D_80171094;
    *D_8008346C = 0;
    arg3->field46 &= 0x7FFF;
    goto common;

common:
    if (arg2->field14 & 0xE000) {
        arg2->field2c = D_80176460;
        func_80047784(arg2, D_80176460[((D_80083228[0] + arg3->field2a + 0x100) >> 9) & 7], 0);
        arg0->field98 &= 0xFFF7;
    }

epilogue:
    return;
}

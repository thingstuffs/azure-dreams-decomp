#include "common.h"

typedef struct S_80172D1C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172D1C_0;   /* arg0 in func_80172D1C */

typedef struct S_80172D1C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80172D1C_1;   /* obj in func_80172D1C */

typedef struct S_80172D1C_2 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
    union { s32 s; volatile s32 u; } unk_0C;   /* accessed as both */
    union { s32 s; volatile s32 u; } unk_10;   /* accessed as both */
    s32 unk_14;
} S_80172D1C_2;   /* arg1 in func_80172D1C */

typedef struct S_80172D1C_3 {
    u8 pad_00[0x48];
    s16 unk_48;
} S_80172D1C_3;   /* (u8 *)calc_other in func_80172D1C */

typedef struct S_80172D1C_4 {
    u8 pad_00[0x12];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
} S_80172D1C_4;   /* arg2 in func_80172D1C */

typedef struct S_80172D1C_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80172D1C_5;   /* part in func_80172D1C */

typedef struct S_80172D1C_6 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 pad_29[0x1];
    s16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
} S_80172D1C_6;   /* arg3 in func_80172D1C */

typedef struct S_80172D1C_7 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80172D1C_7;   /* global_base in func_80172D1C */

typedef struct S_80172D1C_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172D1C_8;   /* ((S_80172D1C_1 *)obj)->unk_08 in func_80172D1C */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784();
extern s32 rand(void);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern u8 D_80045340[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u8 D_80083498[];
extern u8 D_801711A4[];
extern u8 D_8017406C[];
extern u8 D_8017418C[];
extern u8 D_80174194[];

void func_80172D1C(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *obj;
    void *part;
    void *effect_cb;
    u8 *obj20;
    u8 *global_base;
    s32 i;
    s32 state;
    s32 value;
    s32 value2;
    s32 flags;
    s32 timer;
    s32 temp;
    s16 state_timer;
    s32 motion_x;
    s32 motion_y;
    s32 calc;
    register s32 calc_other ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    register s32 calc_half ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 call_a1 ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 call_a2 ASM_REG("$6");   /* MATCH pin: retail schedule: same instructions, different order without it */

    if (((S_80172D1C_0 *)arg0)->unk_9B == 1) {
        i = 6;
        effect_cb = D_8017406C;
        do {
            obj = func_8003FD64(0x312, D_80083498);
            if (obj != 0) {
                func_8004491C(obj, D_80045340);
                part = ((S_80172D1C_1 *)obj)->unk_0C;
                ((S_80172D1C_1 *)obj)->unk_10 = effect_cb;

                ((S_80172D1C_8 *)(((S_80172D1C_1 *)obj)->unk_08))->unk_02 =
                    ((S_80172D1C_2 *)arg1)->unk_02.s + (rand() & 0xF) - 8;
                ((S_80172D1C_8 *)(((S_80172D1C_1 *)obj)->unk_08))->unk_06 =
                    ((S_80172D1C_2 *)arg1)->unk_06.s + (rand() & 0xF) - 8;
                ((S_80172D1C_8 *)(((S_80172D1C_1 *)obj)->unk_08))->unk_0A =
                    ((S_80172D1C_2 *)arg1)->unk_0A + (rand() & 0xF) - 8;

                ((S_80172D1C_8 *)(((S_80172D1C_1 *)obj)->unk_08))->unk_0C =
                    ((rand() & 0xFF) - 0x80) << 10;
                ((S_80172D1C_8 *)(((S_80172D1C_1 *)obj)->unk_08))->unk_10 =
                    ((rand() & 0xFF) - 0x80) << 10;
                calc = rand();
                calc_half = (s32)part;
                call_a1 = 0x2D;
                call_a2 = 0;
                calc &= 3;
                calc_other = -4;
                calc_other -= calc;
                calc_other <<= 16;
                ((S_80172D1C_8 *)(((S_80172D1C_1 *)obj)->unk_08))->unk_14 = calc_other;

                calc_other = (s32)obj + 0x20;
                ASM_KEEP(calc_other);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                ((S_80172D1C_3 *)((u8 *)calc_other))->unk_48 = 10;
                flags = ((S_80172D1C_4 *)arg2)->unk_28;
                ASM_KEEP(flags);   /* MATCH pin: retail schedule: same instructions, different order without it */
                calc_other = ((S_80172D1C_5 *)part)->unk_14;
                ((S_80172D1C_5 *)part)->unk_1E = 0x1800;
                ((S_80172D1C_5 *)part)->unk_1C = 0x1800;
                calc_other |= 0xC;
                ASM_KEEP(calc_other);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                ((S_80172D1C_5 *)part)->unk_28 = flags;
                ((S_80172D1C_5 *)part)->unk_14 = calc_other;
                calc_other = ((S_80172D1C_4 *)arg2)->unk_12;
                ((S_80172D1C_5 *)part)->unk_10 = 0x20;
                ((S_80172D1C_5 *)part)->unk_12 = calc_other - 0x80;
                func_80047784((void *)calc_half, call_a1, call_a2, flags);
                ((S_80172D1C_5 *)part)->unk_0C = 0x808080;
            }
            i--;
        } while (i >= 0);
    }

    i = (((S_80172D1C_6 *)arg3)->unk_6A >> 9) & 7;
    state = ((S_80172D1C_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if (state >= 2) {
        goto check_state_2;
    }
    if (state == 0) {
        goto state_0;
    }
    goto end;

check_state_2:
    if (state == 2) {
        goto state_2;
    }
    goto end;

state_0:
    func_800AD4D0(arg3);
    if (((S_80172D1C_6 *)arg3)->unk_28 == 0) {
        ((S_80172D1C_2 *)arg1)->unk_14 = 0;
        ((S_80172D1C_2 *)arg1)->unk_10.s = 0;
        ((S_80172D1C_2 *)arg1)->unk_0C.s = 0;
        func_800AAA54(arg0, arg1, arg2, D_80174194);
        goto end;
    }
    if (((S_80172D1C_4 *)arg2)->unk_14 & 0x8000) {
        ((S_80172D1C_0 *)arg0)->unk_96.s = 0;
        ((S_80172D1C_0 *)arg0)->unk_9B = 2;
        goto end;
    }

    ((S_80172D1C_2 *)arg1)->unk_0C.s = D_8006CCD8[i] << 18;
    ((S_80172D1C_2 *)arg1)->unk_10.s = D_8006CCE8[i] << 18;
    ((S_80172D1C_0 *)arg0)->unk_9B++;
    state_timer = -1;
    if (((S_80172D1C_6 *)arg3)->unk_1C & 0x228) {
        state_timer = 8;
    }
    ((S_80172D1C_0 *)arg0)->unk_96.s = state_timer;
    motion_x = ((S_80172D1C_2 *)arg1)->unk_0C.s;
    ((S_80172D1C_2 *)arg1)->unk_0C.s = motion_x - motion_x / 4;
    motion_y = ((S_80172D1C_2 *)arg1)->unk_10.s;
    ((S_80172D1C_2 *)arg1)->unk_10.s = motion_y - motion_y / 4;
    goto end;

state_1:
    ((S_80172D1C_2 *)arg1)->unk_0C.s -= D_8006CCD8[i] << 14;
    ((S_80172D1C_2 *)arg1)->unk_10.s -= D_8006CCE8[i] << 14;
    timer = ((S_80172D1C_0 *)arg0)->unk_96.s;
    if (timer > 0) {
        ((S_80172D1C_0 *)arg0)->unk_96.s = ((S_80172D1C_0 *)arg0)->unk_96.u - 1;
        goto timer_join;
    }
    if (((S_80172D1C_4 *)arg2)->unk_14 & 0x6000) {
        ((S_80172D1C_0 *)arg0)->unk_96.s = 0;
    }

timer_join:
    if (((S_80172D1C_0 *)arg0)->unk_96.s != 0) {
        goto end;
    }
    if (((S_80172D1C_6 *)arg3)->unk_28 == 0) {
        ((S_80172D1C_0 *)arg0)->unk_9B = 0;
        ((S_80172D1C_2 *)arg1)->unk_14 = 0;
        ((S_80172D1C_2 *)arg1)->unk_10.s = 0;
        ((S_80172D1C_2 *)arg1)->unk_0C.s = 0;
        func_800AAA54(arg0, arg1, arg2, D_80174194);
        goto end;
    }
    ((S_80172D1C_0 *)arg0)->unk_96.s = 8;
    ((S_80172D1C_0 *)arg0)->unk_9B++;
    goto end;

state_2:
    if (((S_80172D1C_0 *)arg0)->unk_96.s != 0) {
        calc = ((S_80172D1C_4 *)arg2)->unk_24;
        calc_other = ((S_80172D1C_2 *)arg1)->unk_02.u;
        calc <<= 6;
        calc_other -= 0x20;
        calc -= calc_other;
        calc <<= 15;
        calc >>= 1;
        ((S_80172D1C_2 *)arg1)->unk_0C.u = calc;

        calc = ((S_80172D1C_4 *)arg2)->unk_25;
        calc_other = ((S_80172D1C_2 *)arg1)->unk_06.u;
        calc <<= 6;
        calc_other -= 0x20;
        calc -= calc_other;
        calc <<= 15;
        calc_other = ((S_80172D1C_2 *)arg1)->unk_0C.u;
        calc >>= 1;
        ((S_80172D1C_2 *)arg1)->unk_10.u = calc;
        calc_half = calc_other >> 1;
        calc_other = calc_other + calc_half;
        ((S_80172D1C_2 *)arg1)->unk_0C.s = calc_other;
        calc_other = calc >> 1;
        calc += calc_other;
        ((S_80172D1C_2 *)arg1)->unk_10.s = calc;
    }
    temp = ((S_80172D1C_0 *)arg0)->unk_96.u - 1;
    ((S_80172D1C_0 *)arg0)->unk_96.s = temp;
    if ((temp << 16) > 0) {
        goto end;
    }
    ((S_80172D1C_2 *)arg1)->unk_14 = 0;
    ((S_80172D1C_2 *)arg1)->unk_10.s = 0;
    ((S_80172D1C_2 *)arg1)->unk_0C.s = 0;
    func_800A2B04(arg1, ((S_80172D1C_4 *)arg2)->unk_24, ((S_80172D1C_4 *)arg2)->unk_25);
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_8017418C;
    func_80047784(arg2,
                  D_8017418C[((D_80083228 + ((S_80172D1C_6 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                  0);
    global_base = D_80083460;
    if (((S_80172D1C_7 *)global_base)->unk_10 == (s32)((u8 *)arg3 - 0x20)) {
        ((S_80172D1C_7 *)global_base)->unk_10 &= 0x7FFFFFFF;
    }
    ((S_80172D1C_0 *)arg0)->unk_8C = D_801711A4;

end:
    return;
}

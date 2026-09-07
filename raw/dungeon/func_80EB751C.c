#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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
    register s32 calc ASM_REG("$2");
    register s32 calc_other ASM_REG("$3");
    register s32 calc_half ASM_REG("$4");
    register s32 call_a1 ASM_REG("$5");
    register s32 call_a2 ASM_REG("$6");

    if (FIELD(arg0, u8, 0x9B) == 1) {
        i = 6;
        effect_cb = D_8017406C;
        do {
            obj = func_8003FD64(0x312, D_80083498);
            if (obj != 0) {
                func_8004491C(obj, D_80045340);
                part = FIELD(obj, void *, 0xC);
                FIELD(obj, void *, 0x10) = effect_cb;

                FIELD(FIELD(obj, void *, 8), s16, 2) =
                    FIELD(arg1, u16, 2) + (rand() & 0xF) - 8;
                FIELD(FIELD(obj, void *, 8), s16, 6) =
                    FIELD(arg1, u16, 6) + (rand() & 0xF) - 8;
                FIELD(FIELD(obj, void *, 8), s16, 0xA) =
                    FIELD(arg1, u16, 0xA) + (rand() & 0xF) - 8;

                FIELD(FIELD(obj, void *, 8), s32, 0xC) =
                    ((rand() & 0xFF) - 0x80) << 10;
                FIELD(FIELD(obj, void *, 8), s32, 0x10) =
                    ((rand() & 0xFF) - 0x80) << 10;
                calc = rand();
                calc_half = (s32)part;
                call_a1 = 0x2D;
                call_a2 = 0;
                calc &= 3;
                calc_other = -4;
                calc_other -= calc;
                calc_other <<= 16;
                FIELD(FIELD(obj, void *, 8), s32, 0x14) = calc_other;

                calc_other = (s32)obj + 0x20;
                ASM_KEEP(calc_other);
                FIELD((u8 *)calc_other, s16, 0x48) = 10;
                flags = FIELD(arg2, s32, 0x28);
                ASM_KEEP(flags);
                calc_other = FIELD(part, u16, 0x14);
                FIELD(part, s16, 0x1E) = 0x1800;
                FIELD(part, s16, 0x1C) = 0x1800;
                calc_other |= 0xC;
                ASM_KEEP(calc_other);
                FIELD(part, s32, 0x28) = flags;
                FIELD(part, u16, 0x14) = calc_other;
                calc_other = FIELD(arg2, u16, 0x12);
                FIELD(part, s16, 0x10) = 0x20;
                FIELD(part, s16, 0x12) = calc_other - 0x80;
                func_80047784((void *)calc_half, call_a1, call_a2, flags);
                FIELD(part, s32, 0xC) = 0x808080;
            }
            i--;
        } while (i >= 0);
    }

    i = (FIELD(arg3, u16, 0x6A) >> 9) & 7;
    state = FIELD(arg0, u8, 0x9B);
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
    if (FIELD(arg3, u8, 0x28) == 0) {
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800AAA54(arg0, arg1, arg2, D_80174194);
        goto end;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, s16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B) = 2;
        goto end;
    }

    FIELD(arg1, s32, 0xC) = D_8006CCD8[i] << 18;
    FIELD(arg1, s32, 0x10) = D_8006CCE8[i] << 18;
    FIELD(arg0, u8, 0x9B)++;
    state_timer = -1;
    if (FIELD(arg3, s32, 0x1C) & 0x228) {
        state_timer = 8;
    }
    FIELD(arg0, s16, 0x96) = state_timer;
    motion_x = FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 0xC) = motion_x - motion_x / 4;
    motion_y = FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 0x10) = motion_y - motion_y / 4;
    goto end;

state_1:
    FIELD(arg1, s32, 0xC) -= D_8006CCD8[i] << 14;
    FIELD(arg1, s32, 0x10) -= D_8006CCE8[i] << 14;
    timer = FIELD(arg0, s16, 0x96);
    if (timer > 0) {
        FIELD(arg0, s16, 0x96) = FIELD(arg0, u16, 0x96) - 1;
        goto timer_join;
    }
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg0, s16, 0x96) = 0;
    }

timer_join:
    if (FIELD(arg0, s16, 0x96) != 0) {
        goto end;
    }
    if (FIELD(arg3, u8, 0x28) == 0) {
        FIELD(arg0, u8, 0x9B) = 0;
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800AAA54(arg0, arg1, arg2, D_80174194);
        goto end;
    }
    FIELD(arg0, s16, 0x96) = 8;
    FIELD(arg0, u8, 0x9B)++;
    goto end;

state_2:
    if (FIELD(arg0, s16, 0x96) != 0) {
        calc = FIELD(arg2, u8, 0x24);
        calc_other = FIELD(arg1, s16, 2);
        calc <<= 6;
        calc_other -= 0x20;
        calc -= calc_other;
        calc <<= 15;
        ASM_KEEP(calc);
        calc >>= 1;
        ASM_KEEP(calc);
        FIELD(arg1, volatile s32, 0xC) = calc;

        calc = FIELD(arg2, u8, 0x25);
        calc_other = FIELD(arg1, s16, 6);
        calc <<= 6;
        calc_other -= 0x20;
        calc -= calc_other;
        calc <<= 15;
        ASM_KEEP(calc);
        calc_other = FIELD(arg1, volatile s32, 0xC);
        ASM_KEEP(calc_other);
        calc >>= 1;
        ASM_KEEP(calc);
        FIELD(arg1, volatile s32, 0x10) = calc;
        ASM_SCHED_BARRIER();
        calc_half = calc_other >> 1;
        calc_other = calc_other + calc_half;
        FIELD(arg1, s32, 0xC) = calc_other;
        calc_other = calc >> 1;
        calc += calc_other;
        FIELD(arg1, s32, 0x10) = calc;
    }
    temp = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, s16, 0x96) = temp;
    if ((temp << 16) > 0) {
        goto end;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg2, void *, 0x2C) = D_8017418C;
    func_80047784(arg2,
                  D_8017418C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                  0);
    global_base = D_80083460;
    if (FIELD(global_base, s32, 0x10) == (s32)((u8 *)arg3 - 0x20)) {
        FIELD(global_base, s32, 0x10) &= 0x7FFFFFFF;
    }
    FIELD(arg0, void *, 0x8C) = D_801711A4;

end:
    return;
}

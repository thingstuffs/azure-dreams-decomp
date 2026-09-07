#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern u8 D_8006CCD8[9];
extern u8 D_8006CCE8[9];
extern s16 D_80081468[3];
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u16 D_80083460[6];
extern u8 D_801710F4[];
extern u8 D_80174EF8[];
extern u8 D_80174F00[];
extern u8 D_80174F58[];
extern u16 D_80174FC4[];
extern u16 D_80174FD4[];
extern void *D_801708F0[];

extern void func_80047784(void *, s32, s32);
extern void func_8009A21C(s32, s32, s32);
extern void func_8009A3D0(s32, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern s16 func_800A4E2C(u8 *, u8 *);
extern void func_800A56E0(s32);
extern void func_800AA53C(void *);
extern void func_800AD594(void *, s32);
extern s16 func_800BCB04(s32, s32, s16);

#define state arg0
#define motion arg1
#define actor arg2
#define object arg3

void func_80174428(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4, &&case_5
    };
    s32 ystep;
    s32 xstep;
    register s16 *xstep_ptr ASM_REG("$3");
    u32 direction_offset;
    register u32 raw_direction ASM_REG("$2");
    s16 result;
    register s32 case4_result ASM_REG("$4");
    register s32 case4_valid ASM_REG("$2");
    register s32 counter ASM_REG("$17");
    u8 *world;
    s16 *level;
    register void **jump_base ASM_REG("$2");
    u32 jump_offset;
    u32 state_id;
    register u32 state_valid ASM_REG("$2");
    xstep_ptr = (s16 *)&D_8006CCD8;
    raw_direction = FIELD(object, u16, 0x2A);
    direction_offset = raw_direction >> 8;
    direction_offset &= 0xE;
    state_id = FIELD(state, u8, 0x9B);
    xstep_ptr = (s16 *)((u8 *)xstep_ptr + direction_offset);
    direction_offset += (u32)&D_8006CCE8;
    state_valid = state_id < 6;
    xstep = *xstep_ptr;
    ystep = *(s16 *)direction_offset;
    if (!state_valid) {
        return;
    }
    (void)jt_keep;
    jump_base = D_801708F0;
    jump_offset = state_id << 2;
    jump_offset = jump_offset + (u32)jump_base;
    goto **(void **)jump_offset;

case_0:
        func_8009A3D0(FIELD(actor, u8, 0x24), FIELD(actor, u8, 0x25),
            (FIELD(object, s32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
        FIELD(actor, u8 *, 0x2C) = D_80174EF8;
        func_80047784(actor,
            D_80174EF8[((D_80083228 + FIELD(object, s16, 0x2A) + 0x100) >> 9) & 7], 0);
        FIELD(motion, s32, 0x0C) = (xstep << 19) + (xstep << 18);
        FIELD(motion, s32, 0x10) = (ystep << 19) + (ystep << 18);
        FIELD(state, u16, 0x96) = 4;
        func_800A56E0(0x80E);
        FIELD(state, u8, 0x9B)++;
        if (!(FIELD(actor, u16, 0x14) & 0x8000)) {
            FIELD(state, u16, 0x96)--;
            if (FIELD(state, s16, 0x96) > 0) {
                return;
            }
        }
        FIELD(motion, s32, 0x10) = 0;
        FIELD(motion, s32, 0x0C) = 0;
        FIELD(actor, u8 *, 0x2C) = D_80174F58;
        func_80047784(actor,
            D_80174F58[((*(s16 *)(D_80082E80 + 0x3A8) +
                FIELD(object, s16, 0x2A) + 0x100) >> 9) & 7], 0);
        FIELD(state, u16, 0x96) = 0;
        FIELD(motion, s32, 0x0C) = (-xstep) << 18;
        FIELD(motion, s32, 0x10) = (-ystep) << 18;
        goto advance_state;

case_1:
        if (!(FIELD(actor, u16, 0x14) & 0xE000)) {
            return;
        }
        FIELD(motion, s32, 0x10) = 0;
        FIELD(motion, s32, 0x0C) = 0;
        FIELD(actor, u8 *, 0x2C) = D_80174F00;
        func_80047784(actor,
            D_80174F00[((D_80083228 + FIELD(object, s16, 0x2A) + 0x100) >> 9) & 7], 0);
        if (FIELD(object, s32, 0x1C) & 0x2000) {
            FIELD(state, u16, 0x96) = 7;
            FIELD(state, u8, 0x9B) = 5;
            return;
        }
        FIELD(object, u16, 0x2A) &= 0xFFF;
        goto advance_state;

case_2: {
        u16 angle = FIELD(object, u16, 0x2A);
        if ((FIELD(object, s16, 0x2A) == 0x400) ||
            (FIELD(actor, u16, 0x14) & 0x8000)) {
            func_80047784(actor, 0x37, 0);
            goto advance_state;
        }
        if ((u32)(angle - 0x401) < 0x800) {
            FIELD(object, u16, 0x2A) = angle - 0x80;
            return;
        }
        FIELD(object, u16, 0x2A) = (angle + 0x80) & 0xFFF;
        return;
    }

case_3:
        FIELD(actor, u8, 0x24) = (u8)xstep;
        FIELD(actor, u8, 0x25) = (u8)ystep;
        goto advance_state;

case_4:
        if (!(FIELD(actor, u16, 0x14) & 0xE000)) {
            return;
        }
        func_80047784(actor, 0x38, 0);
        counter = 0x40;
        world = D_80082E80;
        level = D_80081468;
        FIELD(state, u16, 0x96) = 0;
        xstep = FIELD(actor, u8, 0x24);
        ystep = FIELD(actor, u8, 0x25);

        ASM_KEEP(counter);
        counter--;
case_4_check:
        if (counter <= 0) {
            goto case_3;
        }
        {
            case4_result = func_800A4E2C(actor + 0x24, actor + 0x25);
            counter--;
            if (case4_result < 0) {
                goto case_4_check;
            }
            counter++;
            if (case4_result != (s8)world[0x26]) {
                goto case_4_position;
            }
            counter--;
            if (*(s16 *)((u8 *)level + 6) >= 2) {
                goto case_4_check;
            }
            counter++;
case_4_position:
            case4_result = func_800BCB04((FIELD(actor, u8, 0x24) << 6) | 0x20,
                (FIELD(actor, u8, 0x25) << 6) | 0x20,
                (s16)(FIELD(motion, u16, 0x0A) - 0x80));
            case4_valid = case4_result < 0x201;
            counter--;
            if (!case4_valid) {
                goto case_4_check;
            }
            goto advance_state;
        }

advance_state:
        FIELD(state, u8, 0x9B)++;
        return;

case_5:
    {
        FIELD(actor, u16, 0x1C) = D_80174FC4[FIELD(state, s16, 0x96)];
        FIELD(actor, u16, 0x1E) = D_80174FD4[FIELD(state, s16, 0x96)];
        if (FIELD(state, s16, 0x96) == 4) {
            func_800A56E0(0x705);
        }
        if (!(FIELD(actor, u16, 0x14) & 0x8000)) {
            FIELD(state, u16, 0x96)++;
            if (FIELD(state, s16, 0x96) < 8) {
                return;
            }
        }
        D_80083460[5]--;
        func_800AA53C(object);
        result = func_800BCB04((FIELD(actor, u8, 0x24) << 6) | 0x20,
            (FIELD(actor, u8, 0x25) << 6) | 0x20,
            (s16)(FIELD(motion, u16, 0x0A) - 0x80));
        FIELD(object, s16, 0x88) = result;
        FIELD(actor, u8 *, 0x2C) = D_80174F00;
        func_800AD594(object, 0x200);
        func_80047784(actor,
            FIELD(actor, u8 *, 0x2C)[((D_80083228 + FIELD(object, s16, 0x2A) + 0x100) >> 9) & 7], 0);
        func_8009A21C(FIELD(actor, u8, 0x24), FIELD(actor, u8, 0x25),
            (FIELD(object, s32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
        func_800A2B04(motion, FIELD(actor, u8, 0x24), FIELD(actor, u8, 0x25));
        FIELD(actor, u16, 0x1E) = 0x1000;
        FIELD(actor, u16, 0x1C) = 0x1000;
        FIELD(state, u8 *, 0x8C) = D_801710F4;
        func_800A4ACC(object);
        FIELD(object, u8, 0x6D) = 0;
        FIELD(object, u16, 0x46) &= 0x7FFF;
        return;
    }
}

#undef state
#undef motion
#undef actor
#undef object

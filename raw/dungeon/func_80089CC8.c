#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern M2C_UNK func_80048A44();
extern s32 rand();
extern M2C_UNK func_8008F610();
extern M2C_UNK func_8008F684();
extern M2C_UNK func_8008F694();
extern M2C_UNK func_8008F6CC();
extern s32 func_800990FC();
extern s32 func_80099194();
extern M2C_UNK func_80099290();
extern s32 func_80099734();
extern M2C_UNK func_80099844();
extern M2C_UNK func_80099F04();
extern M2C_UNK func_80099F70();
extern M2C_UNK func_800A56E0();
extern M2C_UNK func_800A5720();
extern s16 func_800A6DA4();

extern s32 D_80081484;
extern s16 D_80083228;
extern s32 D_8008ACDC;
extern u8 D_8008EAC8[];
extern u8 D_800DCFB0[8];
extern u8 D_800DD0B8[8];
extern u8 D_800E0523[];
extern u8 D_800E0683[];
extern u8 D_80083460[12];
extern s32 D_800E3540;
extern s16 D_800E3DA8[2];

#line 1 "a"
void func_8008F428(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 value;
    s32 saved;
    u16 half;
    u8 state;

    if (FIELD(arg0, void *, 0x124) != 0) {
        if (!(FIELD(arg2, u16, 0x14) & 0x6000)) {
            return;
        }

        state = FIELD(arg0, u8, 0x9B);
        if (state == 0) {
            register u8 *effect ASM_REG("$2");
            register void *effect_arg ASM_REG("$4");

            D_800E3DA8[0] = 0;
            D_800E3DA8[1] = 0;
            value = FIELD(FIELD(arg0, void *, 0x124), s32, 0x1C);
            effect_arg = arg2;
            if (value & 0x2000) {
                goto use_effect;
            }
            if (value & 0x228) {
                goto use_effect;
            }
            value = func_800A6DA4(0, 0x10);
            effect_arg = arg2;
            if ((s16)value < 6) {
                goto start_wait;
            }
use_effect:
            effect = D_8008EAC8;
            ASM_KEEP(effect);
            func_8008F694(effect_arg, D_800DD0B8);
            return;
        }

        if (state == 1) {
            D_800E3DA8[0] = (rand() & 0xF) - 8;
            D_800E3DA8[1] = (rand() & 0xF) - 8;
            half = FIELD(arg0, u16, 0x96) - 1;
            FIELD(arg0, u16, 0x96) = half;
            if ((s16)half > 0) {
                return;
            }
            func_800A56E0(0x510);
            func_80099844(FIELD(arg0, void *, 0x124), D_800E0523);
            {
                register void *entity ASM_REG("$4");
                register s32 old_value ASM_REG("$5");
                register u32 mask1 ASM_REG("$6");
                register u32 mask2 ASM_REG("$7");
                register u8 *old_value_page ASM_REG("$3");
                register s32 flags ASM_REG("$2");

                mask1 = 0xFFF7FFFF;
                mask2 = 0xFFEF0000;
                ASM_KEEP(mask2);
                old_value_page = (u8 *)0x80080000;
                ASM_KEEP(old_value_page);
                entity = FIELD(arg0, void *, 0x124);
                old_value = FIELD(old_value_page, s32, 0x1484);
                flags = FIELD(entity, s32, 0x1C);
                mask2 |= 0xFFFF;
                FIELD(old_value_page, s32, 0x1484) = 0;
                FIELD(entity, s32, 0x1C) = flags & mask1;
                flags = FIELD(arg3, s32, 0x1C);
                D_800E3540 = old_value;
                FIELD(arg3, s32, 0x1C) = flags & mask2;
                ASM_KEEP(entity);
                ASM_KEEP(old_value);
                ASM_KEEP(mask1);
                ASM_KEEP(mask2);
            }
            {
                register s32 next_state ASM_REG("$2");

                next_state = FIELD(arg0, u8, 0x9B) + 1;
                ASM_TAILSLOT_PIN(next_state);
                func_8008F610();
            }
            return;
        }

        {
            u8 *flags_base = D_80083460;

            FIELD(flags_base, u16, 2) |= 0x412;
        }
        func_80099F70(FIELD(arg3, void *, 0x5C));
        func_80099F04(FIELD(arg3, void *, 0x5C));
        func_8008F684(arg2);
        return;
    }

    state = FIELD(arg0, u8, 0x9B);
    if (state == 0) {
        if (FIELD(arg2, s8, 4) < 2) {
            return;
        }
        FIELD(arg2, u16, 0x14) |= 0x800;
start_wait:
        FIELD(arg0, u16, 0x96) = 0x10;
        FIELD(arg0, u8, 0x9B) = FIELD(arg0, u8, 0x9B) + 1;
        func_8008F6CC();
        return;
    }

    half = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = half;
    if ((s16)half > 0) {
        return;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    func_800A56E0(0x506);
    {
        register void *call_arg ASM_REG("$4");
        register s32 pass_value ASM_REG("$5");
        register s32 saved_value ASM_REG("$16");

        value = func_800990FC();
        call_arg = FIELD(arg0, void *, 0x11C);
        pass_value = value;
        saved_value = pass_value;
        func_80099290(func_80099194(D_800E0683,
            func_80099734(call_arg, pass_value)));
        func_800A5720(saved_value);
        FIELD(arg0, void *, 0x8C) = &D_8008ACDC;
        call_arg = arg2;
        FIELD(call_arg, u8 *, 0x2C) = D_800DCFB0;
        func_80048A44(call_arg,
            D_800DCFB0[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0, 1);
        ASM_KEEP(call_arg);
        ASM_KEEP(pass_value);
        ASM_KEEP(saved_value);
    }
}

/* MECHANISM: The retail 0x28 frame follows from held s1/s2/s3 arguments and the
   late s0 return value; edge-live a0 and LEAD28 preserve both tail-call slots.
   A pinned 0x80080000 page, v0 flag local, held D_80083460 base, and loading the
   arg3 flags before the D_800E3540 store reproduce the exact remat order. */

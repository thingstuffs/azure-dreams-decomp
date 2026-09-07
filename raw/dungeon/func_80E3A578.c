#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

extern void *D_801708A0[];
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern M2C_UNK D_800C6AEC;
extern M2C_UNK D_8017086C;
extern M2C_UNK D_80170898;
extern M2C_UNK D_80170EE4;
extern M2C_UNK D_8017398C;

void func_8004491C();
void func_80044A50();
s32 func_800990FC();
s32 func_80099194();
void func_80099290();
s32 func_8009929C();
s32 func_80099734();
void func_8009A028();
void func_8009A21C();
void func_8009A3D0();
void *func_8009B25C();
void func_800A56E0();
void func_800A5720();
s16 func_800A70E4();
void func_800A9A0C();
void func_800BC318();
void func_801741E8() __attribute__((noreturn));
void func_8017424C() __attribute__((noreturn));
void func_80175DD0();
void *func_8017618C();

void func_80173D78(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    register void *found ASM_REG("$18");
    void *created;
    void *base;
    s32 x;
    s32 y;
    s32 index;
    s32 temp_s0;
    register s32 call_ret ASM_REG("$2");
    register void *call_obj ASM_REG("$4");
    register s32 call_arg ASM_REG("$5");
    s32 chain;
    s32 mode;
    s32 map_flags;
    u32 sound_x;
    u32 sound_y;
    s16 step;
    u16 flags16;
    u16 counter;
    u8 state;

    state = M2C_FIELD(arg0, u8 *, 0x9B);
    if (state >= 5U) {
        return;
    }
    (void)jt_keep;
    goto *D_801708A0[(u32)state];

jt_c0:
    flags16 = M2C_FIELD(arg2, u16 *, 0x14);
    if (!(flags16 & 0xE000)) {
        return;
    }
    if (!(flags16 & 0x8000)) {
        func_800A56E0(0x80D);
    }
    M2C_FIELD(arg0, u8 *, 0x9B) = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        M2C_FIELD(arg0, u16 *, 0x96) = 0;
        func_8017424C();
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0x10;
    func_8017424C();

jt_c1:
    if (!(M2C_FIELD(arg0, u16 *, 0x96) & 3)) {
        if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            func_80175DD0(arg0, arg1, arg2, 0);
            func_80175DD0(arg0, arg1, arg2, 1);
        }
    }
    counter = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = counter;
    if ((s16)counter > 0) {
        return;
    }

    index = ((u16)M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
    x = M2C_FIELD(arg2, u8 *, 0x24) + *(u16 *)((s8 *)&D_8006CCD8 + index);
    y = M2C_FIELD(arg2, u8 *, 0x25) + *(u16 *)((s8 *)&D_8006CCE8 + index);
    M2C_FIELD(arg3, s32 *, 0x60) = 0;

    if (M2C_FIELD(arg0, u8 *, 0xAC) == 0) {
        found = func_8009B25C(arg3, x & 0xFFFF, y & 0xFFFF,
                             M2C_FIELD(arg3, s16 *, 0x88));
        M2C_FIELD(arg3, void **, 0x60) = found;
        if (found != 0) {
            state = M2C_FIELD(found, u8 *, 0x13);
            if (((u32)(state - 1) >= 0x2DU) || (state == 0x1E)) {
                call_ret = func_800990FC();
                ASM_KEEP(call_ret);
                call_obj = arg3;
                ASM_KEEP(call_obj);
                call_arg = call_ret;
                ASM_KEEP(call_arg);
                chain = func_80099734(call_obj, temp_s0 = call_arg);
                func_80099290(
                    func_80099194(&D_80170898,
                        func_80099734(found,
                            func_8009929C(0xA,
                                func_80099194(&D_8017086C, chain)))));
                ASM_KEEP(found);
                func_800A5720(temp_s0);
                ASM_KEEP(temp_s0);
                func_800A56E0(0x506);
                M2C_FIELD(arg3, s32 *, 0x60) = 0;
            }
        }
    }

    if (M2C_FIELD(arg0, u8 *, 0xAC) < 2U) {
        if (M2C_FIELD(arg3, s32 *, 0x60) == 0) {
            step = func_800A70E4((s16)x, (s16)y,
                                 M2C_FIELD(arg3, s16 *, 0x88));
            if (step >= 0) {
                M2C_FIELD(arg3, s32 *, 0x60) = step + 1;
            }
        }
    }

    if (M2C_FIELD(arg3, s32 *, 0x60) == 0) {
        void *counter_base;

        func_800A9A0C(arg3);
        M2C_FIELD(arg0, void **, 0x8C) = &D_80170EE4;
        counter_base = &D_80083460;
        M2C_FIELD(counter_base, u16 *, 0xA) =
            M2C_FIELD(counter_base, u16 *, 0xA) - 1;
        M2C_FIELD(arg3, u32 *, 0x1C) &= 0xEFFFFFFF;
        func_8017424C();
    }

    M2C_FIELD(arg0, u8 *, 0x9B) = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
    map_flags = M2C_FIELD(arg3, s32 *, 0x14);
    sound_x = M2C_FIELD(arg2, u8 *, 0x24);
    sound_y = M2C_FIELD(arg2, u8 *, 0x25);
    mode = 0x3000;
    if (map_flags & 0x2000) {
        mode = 0x300;
    }
    func_8009A3D0(sound_x, sound_y, mode);

    M2C_FIELD(arg3, u32 *, 0x1C) |= 0x10000;
    created = func_8017618C(arg0, arg1, arg2, arg3);
    M2C_FIELD(arg0, void **, 0xA4) = created;
    if (created != 0) {
        base = (s8 *)arg0 - 0x20;
        func_80044A50(base);
        func_8004491C(base, &D_800C6AEC);
        M2C_FIELD(arg2, u8 *, 0xF) = 0;
        M2C_FIELD(arg2, u16 *, 0x12) = M2C_FIELD(arg2, u16 *, 0x12) - 0x80;
        M2C_FIELD(arg2, u16 *, 0x14) |= 0xC;
        func_8009A028(arg3);
        M2C_FIELD(base, u32 *, 0x10) |= 0x80000000;
        func_801741E8();
    }

    map_flags = M2C_FIELD(arg3, s32 *, 0x14);
    sound_x = M2C_FIELD(arg2, u8 *, 0x24);
    sound_y = M2C_FIELD(arg2, u8 *, 0x25);
    mode = 0x3000;
    if (map_flags & 0x2000) {
        mode = 0x300;
    }
    func_8009A21C(sound_x, sound_y, mode);
    M2C_FIELD(arg3, u32 *, 0x1C) &= 0xFFFEFFFF;
    func_8017424C();

jt_c2:
    state = M2C_FIELD(arg2, u8 *, 0xF);
    if (state < 7U) {
        M2C_FIELD(arg2, u8 *, 0xF) = state + 1;
        M2C_FIELD(arg2, u8 *, 0xC) =
            M2C_FIELD(arg2, u8 *, 0xC) +
            (-(s32)M2C_FIELD(arg2, u8 *, 0xC) /
             (8 - M2C_FIELD(arg2, volatile u8 *, 0xF)));
        M2C_FIELD(arg2, u8 *, 0xD) =
            M2C_FIELD(arg2, u8 *, 0xD) +
            (-(s32)M2C_FIELD(arg2, u8 *, 0xD) /
             (8 - M2C_FIELD(arg2, u8 *, 0xF)));
        M2C_FIELD(arg2, u8 *, 0xE) =
            M2C_FIELD(arg2, u8 *, 0xE) +
            (-(s32)M2C_FIELD(arg2, u8 *, 0xE) /
             (8 - M2C_FIELD(arg2, u8 *, 0xF)));
        func_8017424C();
    }

    ASM_SCHED_BARRIER();
    base = (s8 *)arg0 - 0x20;
    func_80044A50(base);
    func_800BC318(base);
    M2C_FIELD(arg2, u8 *, 0xF) = 0;
    M2C_FIELD(arg2, u32 *, 0xC) = 0x00808080;
    M2C_FIELD(arg2, u16 *, 0x14) |= 0x800;
    M2C_FIELD(arg2, u16 *, 0x12) = M2C_FIELD(arg2, u16 *, 0x12) + 0x80;
    M2C_FIELD(arg2, u16 *, 0x14) &= 0xFFF3;
    M2C_FIELD(arg0, u8 *, 0x9B) = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
    func_8017424C();

jt_c3:
{
    void *counter_base;

    M2C_FIELD(arg0, u8 *, 0x9A) = 0x18;
    M2C_FIELD(arg0, u8 *, 0x9B) = 0;
    M2C_FIELD(arg0, void **, 0x8C) = &D_8017398C;
    counter_base = &D_80083460;
    M2C_FIELD(counter_base, u16 *, 0xA) =
        M2C_FIELD(counter_base, u16 *, 0xA) - 1;
    M2C_FIELD(arg3, u8 *, 0x6D) = 0;
    M2C_FIELD(arg3, u32 *, 0x1C) &= 0xEFFFFFFF;
    M2C_FIELD(arg3, u16 *, 0x46) &= 0x7FFF;
}
jt_c4:
    return;
}

/* MECHANISM: The true-rowbase function keeps the four arguments in s4/s7/s1/s3 and preserves the retail 0x38 frame.
   Guarded ABI staging reproduces the RNG-result a1-to-s0 call slot; sibling block-local counter bases select v1.
   A volatile byte reread restores the first color-step load, and named map_flags fixes both load schedules.
   ASM_SCHED_BARRIER keeps arg0-0x20 in the taken block instead of gcc stealing it into the branch delay. */

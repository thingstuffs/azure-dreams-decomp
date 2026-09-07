#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_8004E994();
extern void func_800B0EF4(void);
extern void func_800B0EF8(void);
extern void func_800B0F3C(void);

extern s32 D_800814A0;
extern u8 D_800DDC40[];
extern u8 *D_800E3D7C[];

void func_800B0D34(void *arg0, void *arg1, void *arg2) {
    u16 packed;
    register s32 base_phase ASM_REG("$3");
    s32 phase;
    register s32 reflected ASM_REG("$2");
    void *out;
    void *info;
    s32 mode;

    packed = FIELD(arg0, u16, 0x12);
    out = FIELD(arg0, void *, 4);
    info = FIELD(arg0, void *, 0x14);
    base_phase = packed & 0x1F;
    ASM_KEEP(base_phase);
    phase = base_phase;
    if (packed & 0x10) {
        reflected = -base_phase & 0x1F;
        ASM_KEEP(reflected);
        phase = reflected;
        if (reflected == 0) {
            phase = 0x10;
        }
    }

    out = (u8 *)out + 4;
    if ((s32)FIELD(info, u8, 0x29) /
            (s32)((FIELD(info, u8, 0x11) >> 1) + 2) >=
        (s32)FIELD(info, u8, 0x28)) {
        FIELD(out, s8, 0) = -0x80 - phase * 8;
        FIELD(out, s8, 2) = 0x10;
        FIELD(out, s8, 1) = 0x10;
    }

    out = (u8 *)out + 4;
    if (FIELD(info, u8, 0x25) < 10) {
        FIELD(out, s8, 0) = -0x80 - phase * 8;
        FIELD(out, s8, 2) = 0x10;
        FIELD(out, s8, 1) = 0x10;
    }

    mode = FIELD(arg0, s16, 0x10);
    FIELD(arg0, u16, 0x12)++;
    if (mode == 0) {
        goto mode_zero;
    }
    if (mode == 1) {
        goto mode_one;
    }
    FIELD(arg2, u8, 4) = 0;
    func_800B0EF8();
    return;

mode_zero:
    {
        u16 value = FIELD(arg2, u16, 0x18);
        if (value != 0) {
            FIELD(arg2, u16, 0x18) = value + 0x80;
        }
    }
    if (FIELD(D_800E3D7C[0], void *, 0x104) !=
        FIELD(arg0, void *, 0x14)) {
        FIELD(arg0, u16, 0x10)++;
        func_800B0EF4();
        return;
    }
    goto finish;

mode_one:
    {
        s16 signed_value = FIELD(arg2, s16, 0x18);
        u16 value = FIELD(arg2, u16, 0x18);
        if (signed_value >= -0x3FF) {
            FIELD(arg2, u16, 0x18) = value - 0x100;
            func_800B0EF4();
            return;
        }
    }
    func_8004E994(FIELD(arg0, s32, 0x5C));
    {
        s32 i = 0;
        s32 *global_base = (s32 *)0x80080000;
        void *object = arg0;
        do {
            void *entry = FIELD(object, void *, 0x28);
            if (entry != 0) {
                FIELD(entry, u16, -2) |= 0x8000;
                global_base[0x14A0 / 4] |= 0x8000;
            }
            i++;
            object = (u8 *)object + 4;
        } while (i < 4);
    }
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
    func_800B0F3C();
    return;

finish:
    FIELD(arg2, u8, 4) = 0;
    {
        void *source = FIELD(info, void *, -0x18);
        s32 adjustment;
        u16 source_value;
        FIELD(arg1, u16, 2) = FIELD(source, u16, 2);
        FIELD(arg1, u16, 6) = FIELD(source, u16, 6);
        adjustment = D_800DDC40[FIELD(info, u8, 0x13)] + 0x50;
        source_value = FIELD(source, u16, 0xA);
        FIELD(arg1, u16, 0xA) = source_value - adjustment;
    }
}

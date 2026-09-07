#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_8006CCD8[16];
extern u8 D_8006CCE8[16];
extern volatile u16 D_80013714[];
extern u8 D_80083160[];
extern s16 D_80083228[];
extern u16 D_80083460[];
extern s16 D_80083464[];
extern u8 D_800DCFB0[];
extern u8 D_800DCFB8[];
extern u8 D_800DCFC0[];
extern u8 D_800DCFE8[];
extern u8 D_800DD030[];
extern u8 D_800DD0D0[];
extern u8 D_800E3544[];

extern void D_8008ACDC(void);
extern void func_80048A44();
extern void func_8008BCB4();
extern void func_8008BD50();
extern void func_8008BD80();
extern void func_8008BE64() __attribute__((noreturn));
extern void func_8008C048() __attribute__((noreturn));
extern void func_8008C10C();
extern void func_8008CD4C();
extern void func_8008E264();
extern void func_80094ED4();
extern void func_80099F04();
extern void func_80099F70();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s16 func_8009ABA0();
extern void func_8009F644();
extern s32 func_800A5C70();
extern void func_800A67F4();

void func_8008B9FC(void *arg0, s32 arg1, void *arg2, void *arg3) {
    static void *const keepalive[] = { &&block_80086620, &&block_80086704 };
    u8 *state = D_80083160;
    u8 *alt_callback;
    u16 *flags;
    u16 *check_flags;
    s16 temp_v0;
    u16 index;
    register s32 mask ASM_REG("$3");
    s32 flag_word;
    u16 temp_v0_2;

    temp_v0 = func_8009ABA0(FIELD(arg3, s16, 0x2A), arg1, arg2,
                            FIELD(arg3, s16, 0x88), 0x20);
    if (temp_v0 > 0) {
        FIELD(arg0, u8, 0x9B) = 0;
        func_8009A3D0(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), 0x300);
        index = ((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE;
        {
            u8 x = FIELD(arg2, u8, 0x24);
            u8 *movement_x = D_8006CCD8;
            x = (u8)(x + movement_x[index]);
            FIELD(arg2, u8, 0x24) = x;
        }
        FIELD(arg2, u8, 0x25) =
            (u8)(FIELD(arg2, u8, 0x25) + D_8006CCE8[index]);
        func_8009A21C(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), 0x300);
        flags = D_80083460;
        flags[1] |= 8;
        FIELD(arg0, s32, 0x8C) = 0;

        if (temp_v0 != 4) {
            if ((D_80013714[0] & 2) ||
                (((FIELD(state, s32, 8) & 0x20) != 0) &&
                 ((FIELD(arg0, u16, 0xA2) & 0x100) == 0) &&
                 func_800A5C70())) {
                flags[1] |= 0x80;
                if (FIELD(arg2, u8 *, 0x2C) != D_800DCFC0) {
                    FIELD(arg2, u8 *, 0x2C) = D_800DCFC0;
                    func_80048A44(
                        arg2,
                        D_800DCFC0[((s32)(FIELD(state, s16, 0xC8) +
                                         FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                        0, 1);
                }
            }
        }

        check_flags = D_80083460;
        if ((check_flags[1] & 0x80) || (temp_v0 == 1)) {
            func_80099F70(FIELD(arg3, s32, 0x5C));
            func_80099F04(FIELD(arg3, s32, 0x5C));
            if (!(check_flags[1] & 0x80) &&
                ((D_800E3544[0] == 8) || (D_800E3544[0] == 0))) {
                if (FIELD(arg2, u8 *, 0x2C) != D_800DCFB8) {
                    register void *callback_call ASM_REG("$4");
                    callback_call = arg2;
                    ASM_KEEP(callback_call);
                    FIELD(arg2, u8 *, 0x2C) = D_800DCFB8;
                    func_80048A44(
                        callback_call,
                        D_800DCFB8[((s32)(D_80083228[0] +
                                         FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                        0, 1);
                }
            }
            FIELD(arg0, s8, 0x9A) = 0xF;
            D_80083464[0] = 8;
            func_8008BD80();
            return;
        }

        FIELD(arg0, u16, 0x98) |= 0xC;
        if (temp_v0 < 4) {
            FIELD(arg0, u16, 0xA2) |= 1;
            func_8008BCB4();
            return;
        }
        if ((temp_v0 == 2) || (temp_v0 == 4)) {
            FIELD(arg0, u8, 0x9B) = 8;
        }
        func_80094ED4(arg0, arg1, arg2, arg3);
        D_80083464[0] = 8;
        if (FIELD(arg2, u8 *, 0x2C) == D_800DCFB8) {
            FIELD(arg2, u16, 0x14) |= 0x6000;
            func_8008E264(arg0, arg1, arg2, arg3);
            func_8008BD50(arg3);
            return;
        }
        FIELD(arg2, u8 *, 0x2C) = D_800DD030;
        func_80048A44(
            arg2,
            D_800DD030[((s32)(D_80083228[0] + FIELD(arg3, s16, 0x2A) +
                              0x100) >> 9) & 7],
            0, 1);
        FIELD(arg0, s8, 0x9A) = 0x10;
        {
            register void *tail_word_obj ASM_REG("$4");
            tail_word_obj = arg3;
            ASM_USE_NV(tail_word_obj);
            FIELD(tail_word_obj, s32, 0x1C) |= 0x40000000;
        }
        func_8009F644(arg3, 8, 0, 0);
        func_8008C10C();
        return;

block_80086620:
        func_8009F644(arg3, 8, 0, 0);
        mask = 0x40000000;
        ASM_PAGEBASE_PIN(mask);
        func_8008BE64();
        return;
    }

    if (temp_v0 < 0) {
        if ((D_80013714[0] & 1) ||
            (temp_v0_2 = FIELD(arg0, u16, 0x96) + 1,
             FIELD(arg0, u16, 0x96) = temp_v0_2,
             (s16)temp_v0_2 >= 0x15)) {
            func_8008CD4C(arg0, arg1, arg2, arg3, (s32)temp_v0);
            if (FIELD(arg0, u8, 0x9B) >= 0x10) {
                FIELD(arg3, s32, 0x1C) |= 0x40000000;
                func_8008C10C();
                return;
            }
        }
        return;
    }

    {
        register void *callback_obj ASM_REG("$4");
        callback_obj = arg2;
        ASM_USE(callback_obj);
        FIELD(callback_obj, u8 *, 0x2C) = D_800DCFB0;
        func_80048A44(
            callback_obj,
            D_800DCFB0[((s32)(FIELD(state, s16, 0xC8) +
                              FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0, 1);
    }
    FIELD(arg0, void *, 0x8C) = D_8008ACDC;
    func_8008C10C();
    return;

block_80086704:
    flag_word = FIELD(arg3, s32, 0x1C) | mask;
    FIELD(arg3, s32, 0x1C) = flag_word;
    ASM_KEEP(flag_word);
    flags = D_80083460;
    flags[1] |= 0x812;
    func_800A67F4();
    func_80094ED4(arg0, arg1, arg2, arg3);
    if (!(D_80013714[0] & 8)) {
        return;
    }

    if (D_800E3544[0] == 0xF0) {
        if (FIELD(arg2, u8 *, 0x2C) == D_800DCFC0) {
            goto halve_flags;
        }
        {
            register void *callback_obj_f0 ASM_REG("$4");
            callback_obj_f0 = arg2;
            ASM_USE(callback_obj_f0);
            FIELD(callback_obj_f0, u8 *, 0x2C) = D_800DCFC0;
            func_80048A44(
                callback_obj_f0,
                *(volatile u8 *)(D_800DCFC0 +
                    (((s32)(FIELD(D_80083464, s16, -0x23C) +
                              FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7)),
                0, 1);
        }
        func_8008C048();
        ASM_USE(arg2);
        return;
    }

    if (D_800E3544[0] == 0xF8) {
        alt_callback = D_800DCFB8 + 8;
        FIELD(arg0, u16, 0xA2) |= 0x100;
        flags[5]++;
        if (FIELD(arg2, u8 *, 0x2C) == alt_callback) {
            goto halve_flags;
        }
        FIELD(arg2, u8 *, 0x2C) = alt_callback;
        func_80048A44(
            arg2,
            alt_callback[((s32)(D_80083228[0] + FIELD(arg3, s16, 0x2A) +
                                 0x100) >> 9) & 7],
            0, 1);
        func_8008C048();
        return;
    }

    if (D_800E3544[0] == 0xE8) {
        FIELD(arg2, u8 *, 0x2C) = D_800DCFE8;
        func_80048A44(
            arg2,
            D_800DCFE8[((s32)(D_80083228[0] + FIELD(arg3, s16, 0x2A) +
                               0x100) >> 9) & 7],
            1, 1);
        func_8009A3D0(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), 0x300);
        index = ((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE;
        FIELD(arg2, u8, 0x24) -= ((s16 *)(void *)D_8006CCD8)[index / 2] * 2;
        FIELD(arg2, u8, 0x25) -= ((s16 *)(void *)D_8006CCE8)[index / 2] * 2;
        func_8009A21C(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), 0x300);
halve_flags:
        flags[2] = (s16)flags[2] >> 1;
        func_8008C10C();
        return;
    }

    if (D_800E3544[0] == 0xE0) {
        FIELD(arg2, u8 *, 0x2C) = D_800DD0D0;
        func_80048A44(
            arg2,
            D_800DD0D0[((s32)(D_80083228[0] + FIELD(arg3, s16, 0x2A) +
                               0x100) >> 9) & 7],
            1, 1);
        func_8009A3D0(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), 0x300);
        index = ((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE;
        {
            u8 x = FIELD(arg2, u8, 0x24);
            u8 *movement_x = D_8006CCD8;
            x = (u8)(x - movement_x[index]);
            FIELD(arg2, u8, 0x24) = x;
        }
        FIELD(arg2, u8, 0x25) -= D_8006CCE8[index];
        func_8009A21C(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), 0x300);
    }
}

#include "common.h"

/* S_80058B70: view of the D_80085FA8[] element struct touched here (base passed
 * to func_80058ABC/func_80058B2C/func_800589B8; direct fields f00,f1c,f20,f24). */
typedef struct {
    s32 f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24, f28, f2c;
    s32 f30, f34, f38, f3c, f40, f44;
    s8 f48; u8 f49; s8 f4a, f4b, f4c, f4d[3];
} S_80058B70;

extern S_80058B70 D_80085FA8[32];
extern s32 D_80085FA4[4];   /* [0] = base pointer to another struct */
extern s32 D_80085FA0[4];
extern s32 D_800737C4[4];
extern s32 D_800737C8[4];
extern s32 D_800737D4[4];
extern s32 D_800869A8[4];
extern s32 D_800869B0[4];
extern s32 D_800869B4[4];
extern s32 D_800869B8[4];

extern s32 func_80058850(s32);
extern s32 func_80058940(s32);
extern u32 func_80058ABC(S_80058B70 *);
extern s32 func_80058B2C(S_80058B70 *);
extern void func_800589B8(S_80058B70 *);

/* Configures the first playback slot and playback parameters for the current mode. */
s32 func_80058B70(void)
{
    S_80058B70 *slot = &D_80085FA8[0];
    s32 playback_value = 0;
    s32 entry_index;
    u32 timing_divisor;
    u32 playback_rate;
    u32 scaled_rate;

    D_800737D4[0] = 0;
    switch (D_800737C8[0]) {
    case 1:
        {
            s32 slot_id = func_80058850(0);
            slot->f00 = slot_id;
            if (slot_id == -1) {
                return 0;
            }
        }
        D_80085FA0[0] = func_80058ABC(slot);
        D_800869B8[0] = func_80058B2C(slot) & 0xFFFF;
        D_800869B4[0] = func_80058B2C(slot) & 0xFFFF;
        D_800869A8[0] = func_80058B2C(slot) & 0xFFFF;
        if (D_800869B8[0] == 0) {
            s32 initial_value;
            D_800869B0[0] = 0x10000;
            initial_value = func_80058940(0);
            D_800869B0[0] = initial_value;
            slot->f1c = initial_value;
        } else {
            entry_index = 0;
            D_800869B0[0] = 0x10000;
            if ((u32)playback_value < (u32)D_800869B4[0]) {
                do {
                    playback_value = func_80058940(playback_value);
                    entry_index++;
                    slot->f1c = playback_value;
                } while ((u32)entry_index < (u32)D_800869B4[0]);
            }
            D_800869B0[0] = playback_value;
        }
        break;
    case 0:
        slot->f00 = 8;
        D_800869A8[0] = func_80058B2C(slot) & 0xFFFF;
        D_800869B8[0] = 0;
        D_800869B4[0] = 1;
        D_800869B0[0] = 0x10000;
        D_800869B0[0] = func_80058940(0);
        timing_divisor = func_80058ABC(slot) >> 8;
        playback_rate = 0x3938700 / timing_divisor;
        slot->f20 = timing_divisor;
        slot->f24 = playback_rate;
        slot->f20 = playback_rate;
        scaled_rate = (playback_rate * 100) / 115;
        slot->f24 = scaled_rate;
        if (scaled_rate >= 0x100) {
            slot->f24 = 0xFF;
        }
        switch ((u32)D_800869A8[0]) {
        case 0x18:
        case 0x3C:
            slot->f24 = (u32)slot->f24 >> 1;
            break;
        case 0x1E:
            slot->f24 = (u32)slot->f24 >> 2;
            break;
        }
        func_800589B8(slot);
        break;
    case 2:
        D_800869B8[0] = 1;
        {
            s8 *mode_data = (s8 *)D_80085FA4[0];
            D_800869A8[0] = *(s32 *)(mode_data + 8);
            D_800869B4[0] = *(s32 *)(mode_data + 0xC);
            D_800869B0[0] = *(s32 *)(mode_data + 4);
        }
        break;
    }
    if ((u32)D_800869A8[0] >= 0x60) {
        D_800737C4[0] = D_800869A8[0];
    } else {
        D_800737C4[0] = 0;
    }
    D_800737C4[0] = D_800869A8[0];
    return 1;
}

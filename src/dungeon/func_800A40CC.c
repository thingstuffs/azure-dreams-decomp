#include "common.h"

extern void func_8003E4FC(s32, void *, void *);
extern void func_8003F540(s32, s32, s32, s32);
extern void func_8003F6D4(s32, void *, void *, s32);
extern s32 func_800445E0(void);
extern s32 func_800A9390(s16);
extern s32 func_800A9400(s16);

extern s32 D_80024000[];
extern s32 D_8003E140[];
extern s32 D_8006CD58[];
extern s8 D_800DCF4D;
extern u8 D_800DCF59;
extern s32 D_800DD918[];
extern s32 D_800DDAB8[];
extern s32 D_800E58B0[];

s32 func_800A982C(s16 arg0, s16 arg1) {
    register s32 changed;
    s32 result;
    u32 raw;
    register u32 scaled ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 *entry;
    s32 *table;
    s32 *root;
    s32 *message;
    s32 sound_pos;
    register s32 offset ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 state_value;

    root = (s32 *)0x80024000;
    if (D_800DCF59 == 0) {
        changed = 0;
        if ((arg0 != (D_800DCF4D & 0x3F)) ||
            ((((u8)D_800DCF4D >> 6) & 1) != arg1)) {
            changed = 1;
        }
        result = changed;
        if (result != 0) {
            if (arg1 != 0) {
                sound_pos = ((s16)func_800A9390(arg0) * 0xC) + 0x607F;
            } else {
                sound_pos = ((arg0 - 1) * 0xC) + 0x607F;
            }
            message = D_800E58B0;
            func_8003F6D4(0xC, root, message, sound_pos);
            func_8003E4FC(6, message, 0);
            func_8003E4FC(0xFF, D_8003E140, &D_800DCF59);
            D_800DCF4D = arg0 | (arg1 << 6);
        }

        if (arg1 != 0) {
            table = D_800DDAB8;
            raw = func_800A9400(arg0) << 16;
        } else {
            table = D_800DD918;
            raw = arg0 << 16;
        }
        scaled = raw >> 15;
        state_value = D_8006CD58[0];
        ASM_KEEP(state_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        offset = (s32)(scaled << 16) >> 14;
        entry = (s32 *)(offset + (u32)table);
        func_8003F540(0, state_value, entry[0], entry[1]);
        func_8003E4FC(0x15, (void *)func_800445E0(), 0);

        result = changed;
        if (result != 0) {
            D_800DCF59 = 2;
            return 0;
        }
    } else {
        if (D_800DCF59 != 1) {
            return 0;
        }
        D_800DCF59 = 0;
    }
    return root[0];
}

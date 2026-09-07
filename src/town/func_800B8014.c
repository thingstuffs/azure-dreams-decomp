#include "common.h"

extern void func_8004E5A0(u32 value, s32 width, u8 *dst);
extern u8 *func_8004E69C(u8 *text);
extern u8 *strcat(u8 *dst, const u8 *src);
extern void func_800B53BC(s32 arg0, const u8 *arg1, s32 arg2, s32 arg3,
                         s32 arg4);
extern u8 *func_800B544C(u8 *text, void *arg1);

extern s32 D_80089308[2];
extern u8 D_80089310[];
extern u8 D_80089318[];
extern u8 D_8008931C[];
extern u8 D_80089324[];

void func_800B5774(void *arg0, void *arg1) {
    u8 digits[64];
    u8 text[64];

    memcpy(text, D_80089308, 5);

    func_8004E5A0(((u8 *)arg0)[0x11], 2, digits);
    func_8004E69C(digits);
    strcat(text, digits);
    strcat(text, D_80089310);
    strcat(text, D_80089318);

    func_8004E5A0(((u8 *)arg0)[0x28], 3, digits);
    strcat(text, digits);
    strcat(text, D_8008931C);

    func_8004E5A0(((u8 *)arg0)[0x29], 3, digits);
    strcat(text, digits);

    func_800B53BC(*(s32 *)((u8 *)arg1 + 0x10), text, 0, 0x6C, 0x98);
    func_800B53BC(*(s32 *)((u8 *)arg1 + 0x4C), D_80089324, 0, 0x48,
                    0xB8);
    func_800B53BC(*(s32 *)((u8 *)arg1 + 0x14),
                    func_800B544C(text, arg0), 0, 0x48, 0xC0);
}

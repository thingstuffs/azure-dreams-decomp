#include "common.h"

extern void func_800478B8();
extern void func_80044A50();

extern u8 D_80083160[];
extern u8 D_800814A0[];
extern u16 D_8017591C[];
extern s32 D_80175928[];

void func_80175114(void *arg0, void *arg1, void *arg2)
{
    u8 *entity = arg0;
    u8 *other = arg2;
    u8 *colors = D_80083160;
    u16 value;
    u16 value2;

    if (entity[0x9A] == 0) {
        D_80175928[0] = *(s32 *)(other + 8);
        func_800478B8(other);

        if (*(u16 *)(other + 0x14) & 0xE000) {
            func_80044A50(entity - 0x20);
            *(u16 *)(entity + 0x96) = 0x10;
            entity[0x9A]++;
        }

        value = *(u16 *)(entity + 0x96);
        *(u16 *)(entity + 0x96) = value + 1;
        if ((value & 3) == 1) {
            D_8017591C[0]++;
            return;
        }
    } else {
        colors[0xA8] += (0x80 - colors[0xA8]) / *(s16 *)(entity + 0x96);
        colors[0xA9] += (0x80 - colors[0xA9]) / *(s16 *)(entity + 0x96);
        colors[0xAA] += (0x80 - colors[0xAA]) / *(s16 *)(entity + 0x96);

        value2 = *(u16 *)(entity + 0x96) - 1;
        *(u16 *)(entity + 0x96) = value2;
        if ((value2 << 16) <= 0) {
            *(u16 *)(entity - 2) |= 0x8000;
            *(s32 *)D_800814A0 |= 0x8000;
        }
    }
}

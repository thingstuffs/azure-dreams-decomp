#include "common.h"

extern void func_80044A50(void *arg0);
extern void func_800478B8(void *arg0);

extern s32 D_800814A0[3];
extern u8 D_80083160[0xAB];
extern u16 D_801742E0;
extern s32 D_801742E8;

/* Update the entity timer, then fade colors to neutral and flag completion. */
void func_80173B94(void *entity_data, void *unused, void *source_data)
{
    u8 *entity = entity_data;
    u8 *source = source_data;
    u8 *colors = D_80083160;
    u16 ticks;
    u16 fade_left;

    if (entity[0x9A] == 0) {
        D_801742E8 = *(s32 *)(source + 8);
        func_800478B8(source);

        if (*(u16 *)(source + 0x14) & 0xE000) {
            func_80044A50(entity - 0x20);
            *(u16 *)(entity + 0x96) = 0x10;
            entity[0x9A]++;
        }

        ticks = *(u16 *)(entity + 0x96);
        *(u16 *)(entity + 0x96) = ticks + 1;
        if ((ticks & 3) == 0) {
            D_801742E0--;
            return;
        }
    } else {
        colors[0xA8] += (0x80 - colors[0xA8]) / *(s16 *)(entity + 0x96);
        colors[0xA9] += (0x80 - colors[0xA9]) / *(s16 *)(entity + 0x96);
        colors[0xAA] += (0x80 - colors[0xAA]) / *(s16 *)(entity + 0x96);

        fade_left = *(u16 *)(entity + 0x96) - 1;
        *(u16 *)(entity + 0x96) = fade_left;
        if ((fade_left << 16) <= 0) {
            *(u16 *)(entity - 2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
    }
}

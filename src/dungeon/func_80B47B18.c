#include "common.h"

extern void func_800478B8();
extern void func_80044A50();

extern u8 D_80083160[];
extern u8 D_800814A0[];
extern u16 D_80175B20[];
extern s32 D_80175B28[];

/* Advances the effect timer, then fades colors to neutral and marks completion. */
void func_80175318(void *entity_data, void *unused, void *source_data)
{
    u8 *entity = entity_data;
    u8 *source = source_data;
    u8 *colors = D_80083160;
    u16 elapsed_ticks;
    u16 fade_ticks;

    if (entity[0x9A] == 0) {
        D_80175B28[0] = *(s32 *)(source + 8);
        func_800478B8(source);

        if (*(u16 *)(source + 0x14) & 0xE000) {
            func_80044A50(entity - 0x20);
            *(u16 *)(entity + 0x96) = 0x10;
            entity[0x9A]++;
        }

        elapsed_ticks = *(u16 *)(entity + 0x96);
        *(u16 *)(entity + 0x96) = elapsed_ticks + 1;
        if ((elapsed_ticks & 7) == 0) {
            D_80175B20[0]++;
            return;
        }
    } else {
        colors[0xA8] += (0x80 - colors[0xA8]) / *(s16 *)(entity + 0x96);
        colors[0xA9] += (0x80 - colors[0xA9]) / *(s16 *)(entity + 0x96);
        colors[0xAA] += (0x80 - colors[0xAA]) / *(s16 *)(entity + 0x96);

        fade_ticks = *(u16 *)(entity + 0x96) - 1;
        *(u16 *)(entity + 0x96) = fade_ticks;
        if ((fade_ticks << 16) <= 0) {
            *(u16 *)(entity - 2) |= 0x8000;
            *(s32 *)D_800814A0 |= 0x8000;
        }
    }
}

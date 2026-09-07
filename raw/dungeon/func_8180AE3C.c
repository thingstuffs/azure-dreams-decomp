#include "common.h"

#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))

extern s32 D_80026F68;
extern s32 D_800814A0;

void func_8004491C(void *, void *);

void func_8002663C(void *arg0, void *arg1)
{
    s16 state;
    s16 dark_count;
    s16 light_count;
    s16 dark_next_count;
    s16 light_next_count;
    u8 dark_color;
    u8 dark_next_color;
    u8 light_color;
    u8 light_next_color;

    state = S16_AT(arg0, 0xE);
    if (state == 1) {
        goto light;
    }
    if (state >= 2) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto initialize;
    }
    goto done;

state_ge_2:
    if (state == 3) {
        goto state_3;
    }
    if (state == 4) {
        goto dark;
    }
    goto done;

initialize:
    func_8004491C((u8 *)arg0 - 0x20, &D_80026F68);
    S16_AT(arg0, 0) = 0x50;
    S16_AT(arg0, 4) = 0xA0;
    S16_AT(arg0, 2) = 0x58;
    S16_AT(arg0, 6) = 0xB0;
    S16_AT(arg1, 0xA) = 0x40;
    S16_AT(arg0, 0xC) = 8;
    S16_AT(arg0, 0xE) = (s16)(U16_AT(arg0, 0xE) + 1);

light:
    light_count = S16_AT(arg0, 0xC);
    if (light_count != 0) {
        light_color = U8_AT(arg0, 0xA);
        light_next_color =
            light_color + ((0x60 - light_color) / light_count);
        U8_AT(arg0, 0xA) = light_next_color;
        U8_AT(arg0, 9) = light_next_color;
        U8_AT(arg0, 8) = light_next_color;
    }
    light_next_count = U16_AT(arg0, 0xC) - 1;
    S16_AT(arg0, 0xC) = light_next_count;
    if ((light_next_count << 0x10) > 0) {
        goto done;
    }
    U8_AT(arg0, 0xA) = 0x60;
    U8_AT(arg0, 9) = 0x60;
    U8_AT(arg0, 8) = 0x60;
    S16_AT(arg0, 0xE) = (s16)(U16_AT(arg0, 0xE) + 1);
    goto done;

state_3:
    S16_AT(arg0, 0xC) = 8;
    S16_AT(arg0, 0xE) = (s16)(U16_AT(arg0, 0xE) + 1);

dark:
    dark_count = S16_AT(arg0, 0xC);
    if (dark_count != 0) {
        dark_color = U8_AT(arg0, 0xA);
        dark_next_color = dark_color + ((0 - dark_color) / dark_count);
        U8_AT(arg0, 0xA) = dark_next_color;
        U8_AT(arg0, 9) = dark_next_color;
        U8_AT(arg0, 8) = dark_next_color;
    }
    dark_next_count = U16_AT(arg0, 0xC) - 1;
    S16_AT(arg0, 0xC) = dark_next_count;
    if ((dark_next_count << 0x10) > 0) {
        goto done;
    }
    U16_AT(arg0, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}

/* MECHANISM: The true-space CFG uses local gotos to one epilogue, never calls
   to func_800267D8; retail lexical block order keeps the light path before dark.
   Two long-lived arguments naturally reproduce the 0x20 s0/s1/ra frame. */

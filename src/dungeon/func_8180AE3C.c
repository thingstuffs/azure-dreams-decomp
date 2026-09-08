#include "common.h"

#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))

extern s32 D_80026F68;
extern s32 D_800814A0;

void func_8004491C(void *, void *);

/* Initializes an effect, fades its color in and out, and flags completion. */
void func_8002663C(void *effect, void *control)
{
    s16 state;
    s16 dark_frames;
    s16 light_frames;
    s16 dark_frames_left;
    s16 light_frames_left;
    u8 dark_color;
    u8 dark_next_color;
    u8 light_color;
    u8 light_next_color;

    state = S16_AT(effect, 0xE);
    if (state == 1) {
        goto light;
    }
    if (state >= 2) {
        goto check_dark;
    }
    if (state == 0) {
        goto initialize;
    }
    goto done;

check_dark:
    if (state == 3) {
        goto start_dark;
    }
    if (state == 4) {
        goto dark;
    }
    goto done;

initialize:
    func_8004491C((u8 *)effect - 0x20, &D_80026F68);
    S16_AT(effect, 0) = 0x50;
    S16_AT(effect, 4) = 0xA0;
    S16_AT(effect, 2) = 0x58;
    S16_AT(effect, 6) = 0xB0;
    S16_AT(control, 0xA) = 0x40;
    S16_AT(effect, 0xC) = 8;
    S16_AT(effect, 0xE) = (s16)(U16_AT(effect, 0xE) + 1);

light:
    light_frames = S16_AT(effect, 0xC);
    if (light_frames != 0) {
        light_color = U8_AT(effect, 0xA);
        light_next_color =
            light_color + ((0x60 - light_color) / light_frames);
        U8_AT(effect, 0xA) = light_next_color;
        U8_AT(effect, 9) = light_next_color;
        U8_AT(effect, 8) = light_next_color;
    }
    light_frames_left = U16_AT(effect, 0xC) - 1;
    S16_AT(effect, 0xC) = light_frames_left;
    if ((light_frames_left << 0x10) > 0) {
        goto done;
    }
    U8_AT(effect, 0xA) = 0x60;
    U8_AT(effect, 9) = 0x60;
    U8_AT(effect, 8) = 0x60;
    S16_AT(effect, 0xE) = (s16)(U16_AT(effect, 0xE) + 1);
    goto done;

start_dark:
    S16_AT(effect, 0xC) = 8;
    S16_AT(effect, 0xE) = (s16)(U16_AT(effect, 0xE) + 1);

dark:
    dark_frames = S16_AT(effect, 0xC);
    if (dark_frames != 0) {
        dark_color = U8_AT(effect, 0xA);
        dark_next_color = dark_color + ((0 - dark_color) / dark_frames);
        U8_AT(effect, 0xA) = dark_next_color;
        U8_AT(effect, 9) = dark_next_color;
        U8_AT(effect, 8) = dark_next_color;
    }
    dark_frames_left = U16_AT(effect, 0xC) - 1;
    S16_AT(effect, 0xC) = dark_frames_left;
    if ((dark_frames_left << 0x10) > 0) {
        goto done;
    }
    U16_AT(effect, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}

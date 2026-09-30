#include "common.h"
#include "shared/object_flags.h"

#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

typedef struct { u16 x; u16 y; u16 z; u16 pad_a; } HistEntry;   /* 8-byte trail entry at +0x20 */
typedef struct { u8 pad[0x24]; HistEntry hist[7]; } TrailEffect;

extern s32 func_800644B8(s32);
extern s32 rand(void);
extern u8 D_80028868[];

/* Update a trailing effect's position, brightness, and animation frame. */
void func_80026680(void *effect, void *transform, void *render_data)
{
    s32 history_index;
    s16 brightness;
    s32 brightness_delta;
    u8 source_brightness;
    u16 brightness_offset;
    s16 phase;
    s16 frames_left;
    u16 fade_brightness;
    u32 next_frame;
    u8 fade_in_brightness;
    u8 fade_out_brightness;
    void *history_src;
    void *history_dst;
    void *related;
    void *parent;

    for (history_index = 6; history_index > 0; history_index--) {
        ((TrailEffect *)effect)->hist[history_index].x = ((TrailEffect *)effect)->hist[history_index - 1].x;
        ((TrailEffect *)effect)->hist[history_index].y = ((TrailEffect *)effect)->hist[history_index - 1].y;
        ((TrailEffect *)effect)->hist[history_index].z = ((TrailEffect *)effect)->hist[history_index - 1].z;
    }

    U16_AT(effect, 0x24) = U16_AT(transform, 2);
    U16_AT(effect, 0x26) = U16_AT(transform, 6);
    U16_AT(effect, 0x28) = U16_AT(transform, 0xA);

    related = PTR_AT(effect, 8);
    if (related == 0) {
        phase = S16_AT(effect, 0x64);
        switch (phase) {
        case 0:
            U16_AT(transform, 2) += ((S16_AT(PTR_AT(effect, 0), 2) - S16_AT(transform, 2)) * 4) /
                               S16_AT(effect, 0x66);
            U16_AT(transform, 6) += ((S16_AT(PTR_AT(effect, 0), 6) - S16_AT(transform, 6)) * 4) /
                               S16_AT(effect, 0x66);
            S32_AT(transform, 8) +=
                (S32_AT(PTR_AT(effect, 0), 8) -
                 (func_800644B8(S16_AT(effect, 0x66) * 42) << 12) -
                 S32_AT(transform, 8)) /
                S16_AT(effect, 0x66);

            if (S16_AT(effect, 0x6A) < 0xC0) {
                U16_AT(effect, 0x6A) = U16_AT(effect, 0x6A) + 0x10;
            }
            fade_in_brightness = U8_AT(effect, 0x6A);
            U8_AT(render_data, 0xD) = fade_in_brightness;
            U8_AT(render_data, 0xE) = fade_in_brightness;
            U8_AT(render_data, 0xC) = fade_in_brightness;

            frames_left = U16_AT(effect, 0x66) - 1;
            S16_AT(effect, 0x66) = frames_left;
            if (frames_left <= 0) {
                U16_AT(transform, 2) = U16_AT(PTR_AT(effect, 0), 2);
                U16_AT(transform, 6) = U16_AT(PTR_AT(effect, 0), 6);
                U16_AT(transform, 0xA) = U16_AT(PTR_AT(effect, 0), 0xA);
                U16_AT(effect, 0x64)++;
            }
            break;
        case 1:
            related = PTR_AT(effect, 4);
            if (related != 0) {
                related = PTR_AT(related, -0x14);
                U8_AT(related, 0xC) = ((U16_AT(effect, 0x68) & 3) * 0x10) + 0x40;
                U8_AT(related, 0xD) = ((U16_AT(effect, 0x68) & 3) * 0x10) + 0x40;
                U8_AT(related, 0xE) = ((U16_AT(effect, 0x68) & 3) * 0x10) + 0x40;
            }

            fade_brightness = U16_AT(effect, 0x6A);
            fade_brightness = fade_brightness - ((s32)(fade_brightness << 16) >> 19);
            U16_AT(effect, 0x6A) = fade_brightness;
            fade_out_brightness = U8_AT(effect, 0x6A);
            U8_AT(render_data, 0xD) = fade_out_brightness;
            U8_AT(render_data, 0xE) = fade_out_brightness;
            U8_AT(render_data, 0xC) = fade_out_brightness;

            if (S16_AT(effect, 0x6A) < 0x11) {
                U16_AT(effect, -2) |= 0x8000;
                objectFlagBlock.flags |= 0x8000;
            }
        }
    } else {
        related = (u8 *)related + 0x20;
        U16_AT(transform, 2) = U16_AT(related, 0x34);
        U16_AT(transform, 6) = U16_AT(related, 0x36);
        U16_AT(transform, 0xA) = U16_AT(related, 0x38);

        parent = PTR_AT(effect, 8);
        related = PTR_AT(parent, 0xC);
        source_brightness = U8_AT(related, 0xC);
        brightness_offset = U16_AT(effect, 0x6E);
        brightness_delta = source_brightness - brightness_offset;
        brightness = brightness_delta;
        if ((s16)brightness_delta < 0x20) {
            brightness = 0;
        }

        frames_left = U16_AT(effect, 0x66) - 1;
        S16_AT(effect, 0x66) = frames_left;
        if ((frames_left <= 0) && ((s16)brightness == 0)) {
            U16_AT(effect, -2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
        U8_AT(render_data, 0xE) = brightness;
        U8_AT(render_data, 0xD) = brightness;
        U8_AT(render_data, 0xC) = brightness;
    }

    S16_AT(transform, 0xE) = U16_AT(effect, 0x44) + (rand() & 0xF) - 8;
    S16_AT(transform, 0x12) = U16_AT(effect, 0x46) + (rand() & 0xF) - 8;
    S16_AT(transform, 0x16) = U16_AT(effect, 0x48) + (rand() & 0xF) - 8;

    next_frame = U32_AT(render_data, 8) + 0xC;
    U32_AT(render_data, 8) = next_frame;
    if ((u32)D_80028868 < next_frame) {
        U32_AT(render_data, 8) = (u32)(D_80028868 - 0x48);
    }
    U16_AT(effect, 0x68)++;
}

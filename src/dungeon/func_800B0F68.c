#include "common.h"

typedef struct DungeonEffect {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    u16 field_A;
    s32 field_C;
    s32 field_10;
    u8 pad14[2];
    s16 field_16;
    u16 flags;
} DungeonEffect;

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand(void);
extern void func_8009A350(s32, s32, s32, u16 *);
extern void func_800B653C(DungeonEffect *, s16);
extern void func_800B6814(void *);

/* Emits scattered effects at evenly spaced angles unless the tile to the left blocks them. */
void func_800B66C8(void *source)
{
    DungeonEffect effect;
    s32 tile_x;
    s32 tile_y;
    s32 angle;
    s32 effect_count;
    s32 angle_step;
    s32 emitted;
    u16 source_field_a;

    tile_x = *(s16 *)((u8 *)source + 2) / 64 - 1;
    tile_y = *(s16 *)((u8 *)source + 6) / 64;
    func_8009A350(tile_x, tile_y, 0, &effect.flags);
    if (effect.flags & 0x400) {
        func_800B6814(source);
        return;
    }

    effect_count = (rand() & 7) | 4;
    angle_step = 0x1000 / effect_count;
    angle = rand();
    source_field_a = *(u16 *)((u8 *)source + 0xA);
    effect.field_16 = -4;
    effect.field_A = source_field_a;
    for (emitted = 0; emitted < effect_count; emitted++) {
        effect.x = *(u16 *)((u8 *)source + 2) +
                   (rand() & 0x1F) - 0x10;
        effect.y = *(u16 *)((u8 *)source + 6) +
                   (rand() & 0x1F) - 0x10;
        effect.field_C = func_80064584(angle) << 5;
        effect.field_10 = func_800644B8(angle) << 5;
        func_800B653C(&effect, angle);
        angle += angle_step;
    }
}

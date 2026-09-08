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
    void *object;
    register s32 tile_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 tile_y;
    s32 angle;
    s32 effect_count;
    s32 angle_step;
    register s32 emitted ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 object_field_a;

    object = source;
    tile_x = *(s16 *)((u8 *)object + 2);
    if (tile_x < 0) {
        tile_x += 0x3F;
    }
    tile_y = *(s16 *)((u8 *)object + 6);
    tile_x >>= 6;
    ASM_KEEP(tile_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (tile_y < 0) {
        tile_y += 0x3F;
    }
    func_8009A350(tile_x - 1, tile_y >> 6, 0, &effect.flags);
    if (effect.flags & 0x400) {
        func_800B6814(object);
        return;
    }

    emitted = 0;
    effect_count = (rand() & 7) | 4;
    ASM_KEEP(effect_count);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    angle_step = 0x1000 / effect_count;
    angle = rand();
    object_field_a = *(u16 *)((u8 *)object + 0xA);
    effect.field_16 = -4;
    effect.field_A = object_field_a;
    if (effect_count != 0) {
        do {
            emitted++;
            effect.x = *(u16 *)((u8 *)object + 2) +
                       (rand() & 0x1F) - 0x10;
            effect.y = *(u16 *)((u8 *)object + 6) +
                       (rand() & 0x1F) - 0x10;
            effect.field_C = func_80064584(angle) << 5;
            effect.field_10 = func_800644B8(angle) << 5;
            func_800B653C(&effect, angle);
            angle += angle_step;
        } while (emitted < effect_count);
    }
}

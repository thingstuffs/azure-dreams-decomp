#include "common.h"

#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern s32 D_800814A0;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_8017588C[];

extern void func_80047784(void *, u8, s32);
extern void func_8009A028(void *);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A2FE0(void *);
extern void func_800A32A4(void *);
extern void func_800A56E0(s32);
extern void func_800ACF88(void *);

/* Fade the entity's sprites, then remove the entity and trigger its final effect. */
void func_80173108(void *actor, s32 unused, void *sprite, void *entity)
{
    u8 state;
    u8 *sprite_group;
    s32 sprite_index;
    s32 group_index;

    state = U8(actor, 0x9B);
    sprite_group = 0;
    switch (state) {
    case 0:
        if (S16(&D_80083460, 0xA) != 0) {
            break;
        }
        U8(actor, 0x9B) = 1;
        /* fallthrough */
    case 1: {
        s32 entity_flags;
        s32 sprite_offset;
        u8 *group_cursor;
        u32 white_rgb;
        u8 *group_sprite;

        entity_flags = S32(entity, 0x14);
        if (entity_flags & 0x4000) {
            if (!(entity_flags & 0x20000000)) {
                func_800ACF88(entity);
            }
        }
        func_800A56E0(0x805);

        group_index = 0;
        S16(sprite, 0x10) = 0x60;
        U16(sprite, 0x14) |= 0xC;
        U16(actor, 0x98) &= 0xDFFF;
        if (S16(actor, 0x9E) > 0) {
            white_rgb = 0xFFFFFF;
            group_cursor = actor;
            do {
                sprite_group = (u8 *)PTR(group_cursor, 0xA4) + 0x20;
                sprite_index = 0;
                if (S16(sprite_group, 2) > 0) {
                    sprite_offset = 8;
                    do {
                        group_sprite = sprite_group + sprite_offset;
                        U32(group_sprite, 0xC) = white_rgb;
                        func_80047784(group_sprite, 0x23, 0);
                        sprite_offset += 0x30;
                        sprite_index++;
                    } while (sprite_index < S16(sprite_group, 2));
                }
                group_cursor += 4;
                group_index++;
            } while (group_index < S16(actor, 0x9E));
        }
        U8(actor, 0x9B) = U8(actor, 0x9B) + 1;
        break;
    }

    case 2: {
        u8 *group_cursor;
        u8 *sprite_entry;
        s32 fade_delta;

        if ((s32)sprite_group < S16(actor, 0x9E)) {
            group_index = 0;
            fade_delta = 0xFFEFEFF0;
            group_cursor = actor;
            do {
                sprite_group = (u8 *)PTR(group_cursor, 0xA4) + 0x20;
                sprite_index = 0;
                if (S16(sprite_group, 2) > 0) {
                    sprite_entry = sprite_group;
                    do {
                        (*(volatile u32 *)((u8 *)sprite_entry + 0x14)) += fade_delta;
                        sprite_index++;
                        sprite_entry += 0x30;
                    } while (sprite_index < S16(sprite_group, 2));
                }
                group_cursor += 4;
                group_index++;
            } while (group_index < S16(actor, 0x9E));
        }
        if (U16(sprite_group, 0x1C) & 0x6000) {
            PTR(sprite, 0x2C) = D_8017588C;
            func_80047784(sprite,
                D_8017588C[((D_80083228 + S16(entity, 0x2A) + 0x100) >> 9) & 7],
                0);
            U16(actor, 0x96) = 0x80;
            U8(actor, 0x9B) = U8(actor, 0x9B) + 1;
        }
        break;
    }

    case 3: {
        u8 brightness;
        u8 tile_x;
        u8 tile_y;
        s32 effect_id;
        u8 *dungeon_state;

        U32(entity, 0x1C) |= 0x10000000;
        brightness = U8(actor, 0x96);
        U8(sprite, 0xE) = brightness;
        U8(sprite, 0xD) = brightness;
        U8(sprite, 0xC) = brightness;
        U16(actor, 0x96) -= 0x10;
        if (U8(sprite, 0xC) != 0) {
            break;
        }
        dungeon_state = (u8 *)&D_80083460;
        if (U32(dungeon_state, 0x10) == (u32)((u8 *)entity - 0x20)) {
            U32(dungeon_state, 0x10) &= 0x7FFFFFFF;
        }
        func_800A2FE0(entity);
        func_800A32A4(entity);
        tile_x = U8(sprite, 0x24);
        tile_y = U8(sprite, 0x25);
        effect_id = 0x3000;
        if (U32(entity, 0x1C) & 0x2000) {
            effect_id = 0x300;
        }
        func_8009A3D0(tile_x, tile_y, effect_id);
        func_8009A028(entity);
        U16(entity, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    }
    }
}

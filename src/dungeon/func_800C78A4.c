#include "modules/trap_effects_candidate.h"
#include "shared/object_node.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800CD004_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD004_0_pre;   /* the 0x14 bytes before arg0 in spawn_source_sprite_effect, addressed as arg0[-1] */

typedef struct S_800CD004_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0xF];
    u8 unk_13;
    u8 pad_14[0x74];
    u16 unk_88;
} S_800CD004_0;   /* arg0 in spawn_source_sprite_effect */

typedef struct S_800CD004_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_800CD004_1;   /* object in spawn_source_sprite_effect */

typedef struct S_800CD004_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CD004_2;   /* map in spawn_source_sprite_effect */

typedef struct S_800CD004_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CD004_3;   /* quad in spawn_source_sprite_effect */

typedef struct S_800CD004_4 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0xA];
    s16 unk_1C;
    s16 unk_1E;
} S_800CD004_4;   /* sprite in spawn_source_sprite_effect */

typedef struct S_800CD004_5 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CD004_5;   /* tail in spawn_source_sprite_effect */

typedef struct S_800CD004_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CD004_6;   /* counter in spawn_source_sprite_effect */


extern s32 func_8004491C();
extern s32 func_80069EF8(void);
extern s32 play_sound_if_enabled();
extern void display_fixed_item_action_message();
extern s32 generate_random_value(void);

extern u8 D_800CCDA0;
extern u8 D_800DFD0C[];
extern u8 D_800DFD30[];


/* Spawn a sprite effect for the source or invoke its fallback action. */
s32 spawn_source_sprite_effect(void *source, s32 rng_arg_1, s32 rng_arg_2, s32 rng_arg_3)
{
    s32 random;
    s16 roll;
    s32 tile_x;
    void *effect;
    S_800CD004_3 *quad;
    S_800CD004_5 *effect_state;
    S_800CD004_4 *sprite;
    S_800CD004_2 *map;
    void *texture;
    s32 color;
    s32 variant;
    u32 height_offset;
    s32 height_delta;
    void *init_effect;

    if (D_800E3D40 == 0) {
        random = generate_random_value() & 0xFFFF;
        if (((S_800CD004_0 *)source)->unk_03 != 0) {
            roll = random % ((S_800CD004_0 *)source)->unk_03;
        } else {
            roll = 0;
        }
    } else {
        roll = 0;
    }

    if (roll < 0x30) {
        effect = func_8003FC64(2);
        if (effect != NULL) {
            init_effect = effect;
            ((S_800CD004_1 *)effect)->unk_10 = &D_800CCDA0;
            func_8004491C(init_effect, func_80045340);

            map = ((S_800CD004_0_pre *)source)[-1].unk_00;
            tile_x = map->unk_24;
            quad = ((S_800CD004_1 *)effect)->unk_08;
            quad->unk_02 = (tile_x << 6) + 0x20;
            quad->unk_06 = (map->unk_25 << 6) + 0x20;
            quad->unk_0A = ((S_800CD004_0 *)source)->unk_88 - 0x200;

            sprite = ((S_800CD004_1 *)effect)->unk_0C;
            sprite->unk_1E = 0x1000;
            sprite->unk_1C = 0x1000;
            color = 0x808080;
            sprite->unk_0C = color;

            variant = func_80069EF8();
            if (variant & 3) {
                texture = D_800DFD0C;
            } else {
                texture = D_800DFD30;
            }
            sprite->unk_08 = texture;
            sprite->unk_10 = 0x20;

            height_offset = D_800DDC40[((S_800CD004_0 *)source)->unk_13];
            effect_state = (u8 *)effect + 0x20;
            height_delta = ((S_800CD004_0 *)source)->unk_88 - height_offset;
            effect_state->unk_0A = height_delta;
            ((S_800CD004_1 *)effect)->unk_20 = source;
            effect_state->unk_06 = 0xC;

            g_dungeon_status.unk_0A = ((u16)g_dungeon_status.unk_0A) + 1;
            play_sound_if_enabled(0x50D);
        }
    } else {
        if (((S_800CD004_0 *)source)->unk_13 == 0) {
            display_fixed_item_action_message();
        }
        return 1;
    }
    return effect != NULL;
}

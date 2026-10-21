#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


typedef struct OffsetPair {
    s16 x;
    s16 y;
} OffsetPair;

typedef struct OffsetTable {
    OffsetPair entries[8];
} OffsetTable;

extern OffsetTable D_80170884;
extern s32 D_80171728;
extern u8 D_80174DEC[];

extern void select_sprite_entry(void *, s32, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void process_nodes_at_target_tile(void *, s32, s32, s32);
extern void create_randomly_rotated_offset_effect(void *, s32, s32, s32);


typedef struct S_80174A28_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174A28_0;   /* arg0 in advance_directional_effect_action */

typedef struct S_80174A28_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174A28_1;   /* arg1 in advance_directional_effect_action */

typedef struct S_80174A28_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80174A28_2;   /* arg2 in advance_directional_effect_action */

typedef struct S_80174A28_3 {
    u8 pad_00[0x2A];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
} S_80174A28_3;   /* arg3 in advance_directional_effect_action */

/* Advances a timed directional action, triggers its effects, and resets the actor state. */
void advance_directional_effect_action(void *action, void *motion, void *sprite, void *actor)
{
    OffsetTable offsets = D_80170884;
    s32 coord_value;

    switch (((S_80174A28_0 *)action)->unk_9B) {
    case 0:
        ((S_80174A28_1 *)motion)->unk_14 = 0;
        ((S_80174A28_1 *)motion)->unk_10 = 0;
        ((S_80174A28_1 *)motion)->unk_0C = 0;
        ((S_80174A28_0 *)action)->unk_96 = 0x14;
        ((S_80174A28_0 *)action)->unk_9B++;
        break;

    case 1:
        if ((--((S_80174A28_0 *)action)->unk_96 == 0x12) ||
            (((S_80174A28_2 *)sprite)->unk_14 & 0x8000)) {
            OffsetPair *offset;
            u16 flags;
            s32 height;
            s32 x_sum;
            s32 tile_x;
            s32 x_offset;
            s32 y_offset;
            void *effect_actor;

            flags = ((S_80174A28_2 *)sprite)->unk_14;
            effect_actor = actor;
            ((S_80174A28_2 *)sprite)->unk_14 = flags | 0x0800;
            height = ((S_80174A28_1 *)motion)->unk_0A;
            tile_x = ((S_80174A28_2 *)sprite)->unk_24;
            offset = &offsets.entries[(((S_80174A28_3 *)actor)->unk_2A.u >> 9) & 7];
            x_offset = offset->x;
            x_sum = tile_x + x_offset;
            y_offset = offset->y;
            x_sum = x_sum & 0xFFFF;
            coord_value = ((S_80174A28_2 *)sprite)->unk_25 + y_offset;
            create_randomly_rotated_offset_effect(effect_actor, x_sum, coord_value & 0xFFFF, height);
        }
        if ((((S_80174A28_0 *)action)->unk_96 == 0x0A) ||
            (((S_80174A28_2 *)sprite)->unk_14 & 0x8000)) {
            ((S_80174A28_2 *)sprite)->unk_14 &= 0xF7FF;
            play_sound_if_enabled(0x605);
        }
        if ((((S_80174A28_0 *)action)->unk_96 == 9) ||
            (((S_80174A28_2 *)sprite)->unk_14 & 0x8000)) {
            OffsetPair *offset;
            u16 angle;
            s32 height;
            s32 tile_x;
            s32 x;
            s32 x_sum;
            s32 y_offset;

            angle = ((S_80174A28_3 *)actor)->unk_2A.u;
            offset = offsets.entries + ((angle >> 9) & 7);
            height = ((S_80174A28_1 *)motion)->unk_0A;
            tile_x = ((S_80174A28_2 *)sprite)->unk_24;
            coord_value = offset->x;
            x_sum = tile_x + coord_value;
            y_offset = offset->y;
            coord_value = ((S_80174A28_2 *)sprite)->unk_25 + y_offset;
            x = x_sum & 0xFFFF;
            process_nodes_at_target_tile(actor, x, coord_value & 0xFFFF, height);
        }
        if ((((S_80174A28_0 *)action)->unk_96 <= 0) ||
            (((S_80174A28_2 *)sprite)->unk_14 & 0x8000)) {
            ((S_80174A28_0 *)action)->unk_96 = 0;
            ((S_80174A28_0 *)action)->unk_9B++;
        }
        break;

    case 2:
        if (((S_80174A28_2 *)sprite)->unk_14 & 0xE000) {
            ((S_80174A28_1 *)motion)->unk_14 = 0;
            ((S_80174A28_1 *)motion)->unk_10 = 0;
            ((S_80174A28_1 *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion,
                ((S_80174A28_2 *)sprite)->unk_24, ((S_80174A28_2 *)sprite)->unk_25);
            if (((S_80174A28_2 *)sprite)->unk_2C != D_80174DEC) {
                ((S_80174A28_2 *)sprite)->unk_2C = D_80174DEC;
                ((S_80174A28_2 *)sprite)->unk_14 &= 0xF7FF;
                select_sprite_entry(sprite,
                    ((S_80174A28_2 *)sprite)->unk_2C[((g_game_work.view.camera_rotation.parts.viewAngle +
                        ((S_80174A28_3 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
                    0);
                ((S_80174A28_0 *)action)->unk_9B++;
            }
        }
        break;

    case 3:
        spend_actor_mp(actor, 0x400);
        ((S_80174A28_0 *)action)->unk_8C = &D_80171728;
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)actor + (0x46))) &= 0x7FFF;
        break;
    }
}

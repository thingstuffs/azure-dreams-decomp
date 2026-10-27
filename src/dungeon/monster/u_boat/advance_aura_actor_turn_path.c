#include "shared/entity.h"
#include "shared/actor_status_ids.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/monster/barong.h"
#include "engine/graphics.h"
#include "dungeon/level.h"

extern s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s16 check_movement_clearance_and_height();
extern s16 get_rounded_facing_and_rounding_flag();
void create_owner_linked_directional_object(ActorRecord *owner_data, ObjectPosition *source_position, SpriteFrameState *source_sprite);
extern u8 uboat_default_frames[];

typedef struct S_80172144_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    s16 unk_8A;
} S_80172144_0;   /* state in advance_aura_actor_turn_path */

typedef struct S_80172144_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    u8 pad_9B[0x15];
    u8 unk_B0;
    u8 pad_B1[0x4];
    u8 unk_B5;
} S_80172144_1;   /* arg0 in advance_aura_actor_turn_path */

typedef struct S_80172144_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80172144_3;   /* temp_v0_2 in advance_aura_actor_turn_path */

typedef struct S_80172144_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80172144_4;   /* (u8 *)state + ((S_80172144_0 *)state)->unk_8A in advance_aura_actor_turn_path */

/* Advance the entity along its path and update its movement state. */
void advance_aura_actor_turn_path(ActorRecord *actor, ObjectPosition *actor_slot, SpriteFrameState *entity_arg, ActorRecord *state_arg) {
    register void *state = state_arg;
    register SpriteFrameState *entity= entity_arg;
    s32 tile_flags;
    s16 direction;
    s16 move_result;
    s32 effect_status;
    s16 old_x_early;
    s16 old_x;
    s16 old_y;
    s32 step_count;
    S_80172144_3 *path_step;

    if ((((S_80172144_0 *)state)->unk_71.s > 0) &&
        ((s32)((S_80172144_0 *)state)->unk_71.u > ((S_80172144_0 *)state)->unk_8A)) {
        if ((((S_80172144_1 *)actor)->unk_B5 == 0) &&
            (*(u8 ***)&entity->frameTable != uboat_default_frames)) {
            entity->frameTable = uboat_default_frames;
            select_sprite_entry(entity,
                uboat_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80172144_0 *)state)->unk_2A + 0x100) >> 9) & 7],
                0);
            if (((S_80172144_1 *)actor)->unk_B0 == 0) {
                create_owner_linked_directional_object(actor, actor_slot, entity);
            }
        }
        old_x_early = entity->tile_x;
        old_y = entity->tile_y;
        effect_status = get_entity_effect_value(state, STATUS_NO_TILE_OCCUPANCY);
        old_x = old_x_early;
        if ((effect_status << 0x10) == 0) {
            s32 tile_x;
            s32 tile_y;
            s32 flags;
            s32 mode;

            tile_x = old_x;
            mode = 0x3000;
            flags = ((S_80172144_0 *)state)->unk_1C;
            tile_y = old_y;
            if (flags & 0x2000) {
                mode = 0x300;
            }
            update_map_cell_flags_with_item_limit(tile_x, tile_y, mode);
        }
        path_step = (u8 *)state + ((S_80172144_0 *)state)->unk_8A;
        direction = get_rounded_facing_and_rounding_flag(old_x, old_y,
            path_step->unk_74, path_step->unk_7C,
            (u8 *)actor + 0x98);
        move_result = check_movement_clearance_and_height(direction, entity, state, 0x20);
        entity->tile_x = ((S_80172144_4 *)((u8 *)state + ((S_80172144_0 *)state)->unk_8A))->unk_74;
        entity->tile_y = ((S_80172144_4 *)((u8 *)state + ((S_80172144_0 *)state)->unk_8A))->unk_7C;
        ((S_80172144_0 *)state)->unk_8A = (u16)((S_80172144_0 *)state)->unk_8A + 1;
        if ((effect_status << 0x10) == 0) {
            s32 new_x;
            s32 new_y;

            tile_flags = 0x3000;
            new_x = entity->tile_x;
            new_y = entity->tile_y;
            if (((S_80172144_0 *)state)->unk_1C & ACTOR_PLAYER_SIDE) {
                tile_flags = 0x300;
            }
            cycle_map_cell_flags(new_x, new_y, tile_flags);
        }
        ((S_80172144_0 *)state)->unk_2A = direction;
        if (move_result == 3 && (((S_80172144_1 *)actor)->unk_B5 == 0) && !(g_dungeon_status.flags & 0x80) &&
            !(entity->flags & 0x8000)) {
            advance_arcing_actor_move(actor, actor_slot, entity, state);
            ((S_80172144_1 *)actor)->unk_8C = 0;
            ((S_80172144_0 *)state)->unk_1C |= ACTOR_REFRESH_GROUND;
        } else {
            ((S_80172144_1 *)actor)->unk_9A = 0xF;
            ((S_80172144_1 *)actor)->unk_8C = 0;
            ((S_80172144_0 *)state)->unk_1C |= ACTOR_REFRESH_GROUND;
        }
        if (g_dungeon_status.flags & 0x80) {
            ((S_80172144_1 *)actor)->unk_96 = 0;
            return;
        }
        ((S_80172144_1 *)actor)->unk_96 = 8;
        step_count = ((S_80172144_0 *)state)->unk_71.u;
        if ((s32)step_count > 0) {
            ((S_80172144_1 *)actor)->unk_96 = 8 / (s32)step_count;
        }
    }
}

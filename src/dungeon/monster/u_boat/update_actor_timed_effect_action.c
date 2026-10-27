#include "engine/graphics.h"
#include "engine/texture.h"
#include "dungeon/level/floor_flags.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/effect/screen.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"
#include "engine/node/allocation.h"
#include "dungeon/level.h"
#include "engine/node.h"

typedef struct S_8017558C_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    s16 unk_94;
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    s16 unk_A8;
    u8 pad_AA[0x2];
    void * unk_AC;
    u8 unk_B0;
    u8 unk_B1;
    s8 unk_B2;
    s8 unk_B3;
    s8 unk_B4;
    u8 pad_B5[0x1];
    u16 unk_B6;
    u16 unk_B8;
    u16 unk_BA;
} S_8017558C_0;   /* arg0 in update_actor_timed_effect_action */

typedef struct S_8017558C_5 {
    u8 pad_00[0x38];
    s16 unk_38;
    u8 pad_3A[0x6];
    void * unk_40;
    void * unk_44;
} S_8017558C_5;

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 uboat_aura_start_frames[];
extern u8 u_boat_timed_effect_update_address[];
extern s32 clipped_sprite_renderer_address[3];
extern u8 uboat_aura_later_frames[];
extern u8 u_boat_aura_frames[];
extern u8 uboat_default_frames[];
extern u8 uboat_aura_sprite_data[];
#include "dungeon/monster/u_boat.h"
struct S_80174C64_0;
void create_owner_linked_directional_object(ActorRecord *owner_data, ObjectPosition *source_position, SpriteFrameState *source_sprite);      /* extern */
void update_actor_movement_history(struct S_80174C64_0 *motion, ObjectPosition *position, SpriteFrameState *record, void *object); /* extern */

/* Update the actor action sequence, including its effect, animations, and position restoration. */
/* Starts U-Boat's terrain effect, runs its obstacle-following movement, restores its saved position, and
 * spends MP. */
void update_actor_timed_effect_action(void *action, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    s16 height_delta;
    s16 height;
    s16 view_dir;
    SpriteFrameState *effect_sprite;
    u16 timer;
    u16 finish_timer;
    u16 effect_timer;
    u16 start_timer;
    u16 windup_timer;
    u16 restore_timer;
    u16 saved_angle;
    u16 pause_timer;
    u8 phase;
    s32 restore_phase;
    s32 next_phase;
    ObjectNodeHeader *effect;
    S_8017558C_5 *effect_state;
    ObjectPosition *effect_position;

    s32 global_flags;

    phase = ((S_8017558C_0 *)action)->unk_9B;
    switch (phase) {
    case 0:
        if (sprite->flags & 0x8000) {
            {
                s32 finish_phase;
                pack_and_submit_cell_height_levels();
                finish_phase = 5;
                global_flags = dungeon_floor_flags;
                ((S_8017558C_0 *)action)->unk_96 = finish_phase;
                dungeon_floor_flags = global_flags | FLOOR_MAP_VIEW_HOLD;
                ((S_8017558C_0 *)action)->unk_9B = finish_phase;
            }
            sprite->flags = (u16) (sprite->flags | 0x6000);
            return;
        }
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        height_delta = sample_terrain_surface_height(((u16)position->x.w.i), ((u16)position->y.w.i), (s16) (((u16)actor->ground_height)
            - 0x20));
        height = ((u16)actor->ground_height);
        height_delta -= height;
        if (((S_8017558C_0 *)action)->unk_92.s >= height_delta) {
            ((S_8017558C_0 *)action)->unk_92.u = (u16) height_delta;
        } else {
            ((S_8017558C_0 *)action)->unk_92.u = ((S_8017558C_0 *)action)->unk_92.u + 0xC;
            if (height_delta < (s16) ((S_8017558C_0 *)action)->unk_92.u) {
                ((S_8017558C_0 *)action)->unk_92.u = (u16) height_delta;
            }
        }
        if (((S_8017558C_0 *)action)->unk_92.s == 0) {
            sprite->frameTable = uboat_aura_start_frames;
            select_sprite_entry(sprite, uboat_aura_start_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            play_sound_if_enabled(0x800);
            ((S_8017558C_0 *)action)->unk_96 = 2U;
            ((S_8017558C_0 *)action)->unk_9B = (u8) (((S_8017558C_0 *)action)->unk_9B + 1);
            sprite->depth_bias = 6;
            ((S_8017558C_0 *)action)->unk_A6 = (u16) actor->facing;
        }
        effect_timer = ((S_8017558C_0 *)action)->unk_96 + 1;
        ((S_8017558C_0 *)action)->unk_96 = effect_timer;
        if ((s16) effect_timer != 1) {
            return;
        }
        effect = allocate_list_node(0x12, action - 0x20);
        if (effect == NULL) {
            return;
        }
        ((S_8017558C_0 *)action)->unk_AC = effect;
        effect->update_callback = u_boat_timed_effect_update_address;
        register_node(effect, clipped_sprite_renderer_address);
        effect_state = ((void *)effect) + 0x20;
        effect_state->unk_38 = 5;
        effect_state->unk_40 = action;
        effect_state->unk_44 = position;
        effect_sprite = effect->sprite;
        effect_sprite->tpage_abr = 0x40;
        effect_sprite->flags = (u16) (effect_sprite->flags | 0xC);
        effect_position = effect->position;
        effect_position->x.w.i = (u16) ((u16)position->x.w.i);
        effect_position->y.w.i = (u16) ((u16)position->y.w.i);
        effect_position->z.w.i = (u16) ((u16)actor->ground_height);
        effect_sprite = effect->sprite;
        effect_sprite->scale_y = 0xA00;
        effect_sprite->scale_x = 0xA00;
        effect_sprite->color.c.b = 0;
        effect_sprite->color.c.g = 0;
        effect_sprite->color.c.r = 0;
        effect_sprite->source = uboat_aura_sprite_data;
        return;
    case 1:
        start_timer = ((S_8017558C_0 *)action)->unk_96 - 1;
        ((S_8017558C_0 *)action)->unk_96 = start_timer;
        if ((start_timer << 0x10) > 0) {
            if (!(sprite->flags & 0xE000)) {
                return;
            }
        }
        sprite->frameTable = uboat_aura_later_frames;
        select_sprite_entry(sprite, uboat_aura_later_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        ((S_8017558C_0 *)action)->unk_96 = 3U;
        ((S_8017558C_0 *)action)->unk_9B = (u8) (((S_8017558C_0 *)action)->unk_9B + 1);
        ((S_8017558C_0 *)action)->unk_B6 = (u16) ((u16)position->x.w.i);
        ((S_8017558C_0 *)action)->unk_B8 = (u16) ((u16)position->y.w.i);
        ((S_8017558C_0 *)action)->unk_BA = (u16) ((u16)actor->ground_height);
        return;
    case 2:
        windup_timer = ((S_8017558C_0 *)action)->unk_96 - 1;
        ((S_8017558C_0 *)action)->unk_96 = windup_timer;
        if ((windup_timer << 0x10) > 0) {
            return;
        }
        next_phase = ((S_8017558C_0 *)action)->unk_9B;
        ((S_8017558C_0 *)action)->unk_96 = 0x1EU;
        ((S_8017558C_0 *)action)->unk_A8 = 0;
        ((S_8017558C_0 *)action)->unk_B1 = 0U;
        ((S_8017558C_0 *)action)->unk_B2 = 0;
        ((S_8017558C_0 *)action)->unk_B4 = 0;
        ((S_8017558C_0 *)action)->unk_B3 = 0;
        next_phase += 1;
        ((S_8017558C_0 *)action)->unk_9B = next_phase;
        return;
    case 3:
        update_actor_movement_history(action, position, sprite, actor);
        return;
    case 4:
        restore_phase = ((S_8017558C_0 *)action)->unk_B1;
        switch (restore_phase) {
        case 0:
            restore_timer = ((S_8017558C_0 *)action)->unk_96 + 1;
            ((S_8017558C_0 *)action)->unk_96 = restore_timer;
            if ((s16) restore_timer == 1) {
                position->x.w.i = (u16) ((S_8017558C_0 *)action)->unk_B6;
                position->y.w.i = (u16) ((S_8017558C_0 *)action)->unk_B8;
                actor->ground_height = (u16) ((S_8017558C_0 *)action)->unk_BA;
                saved_angle = ((S_8017558C_0 *)action)->unk_A6;
                actor->facing = (s16) saved_angle;
                view_dir = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (s16) saved_angle + 0x100) >> 9) & 7;
                select_indirect_table_entry(sprite, (*(u8 * *)&sprite->frameTable)[view_dir], sprite->unk_04);
                ((S_8017558C_0 *)action)->unk_94 = view_dir;
            }
            if ((s16) ((S_8017558C_0 *)action)->unk_96 < 0x10) {
                return;
            }
            ((S_8017558C_0 *)action)->unk_96 = 0U;
            ((S_8017558C_0 *)action)->unk_B1 = (u8) (((S_8017558C_0 *)action)->unk_B1 + 1);
            sprite->flags = (u16) (sprite->flags & 0x9F7F);
            return;
        case 1:
            pause_timer = ((S_8017558C_0 *)action)->unk_96;
            ((S_8017558C_0 *)action)->unk_96 = (u16) (pause_timer + 1);
            if ((s16) pause_timer < 4) {
                return;
            }
            ((S_8017558C_0 *)action)->unk_96 = 0U;
            ((S_8017558C_0 *)action)->unk_B1 = (u8) (((S_8017558C_0 *)action)->unk_B1 + 1);
            sprite->frameTable = u_boat_aura_frames;
            select_sprite_entry(sprite, u_boat_aura_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            sprite->flags = (u16) (sprite->flags & 0x9F7F);
            play_sound_if_enabled(0x801);
            return;
        case 2:
            if (!(sprite->flags & 0xE000)) {
                return;
            }
            position->velocity_z = 0;
            position->velocity_y = 0;
            position->velocity_x = 0;
            set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
            actor->flags1C = (s32) (actor->flags1C | 0x40000);
            ((S_8017558C_0 *)action)->unk_98 = (u16) (((S_8017558C_0 *)action)->unk_98 | 8);
            if (*(u8 * *)&sprite->frameTable == uboat_default_frames) {
                return;
            }
            sprite->frameTable = uboat_default_frames;
            select_sprite_entry(sprite, uboat_default_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            ((S_8017558C_0 *)action)->unk_96 = 5U;
            ((S_8017558C_0 *)action)->unk_9B = (u8) (((S_8017558C_0 *)action)->unk_9B + 1);
            if (((S_8017558C_0 *)action)->unk_B0 != 0) {
                return;
            }
            create_owner_linked_directional_object(action, position, sprite);
            return;
        }
        return;
    case 5:
        finish_timer = ((S_8017558C_0 *)action)->unk_96;
        ((S_8017558C_0 *)action)->unk_96 = (u16) (finish_timer - 1);
        if ((finish_timer << 0x10) > 0) {
            return;
        }
        sprite->depth_bias = 0;
        spend_actor_mp(actor, 0x1000);
        ((S_8017558C_0 *)action)->unk_8C = uboat_behavior_entry;
        g_dungeon_status.active_actor = 0;
        actor->action_flags = (u16) (actor->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
        return;
    }
}

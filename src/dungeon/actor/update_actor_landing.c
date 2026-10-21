#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800D991C_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
} S_800D991C_0;   /* arg0 in update_actor_landing */

void func_8003DB94();        /* extern */
s16 get_rounded_facing_and_rounding_flag();       /* extern */
void set_record_integer_tile_center();              /* extern */
s32 advance_status_timers();                      /* extern */
void on_actor_status_updated(void *actor);                      /* extern */
void spend_actor_mp();             /* extern */
s32 check_actor_floor_trap();                  /* extern */
void update_actor_facing_animation(void *actor, EntityRec *motion, void *sprite, ActorRecord *status);
extern void *actor_action_frames[];

/* Update airborne movement toward a map tile and finish the landing transition. */
void update_actor_landing(void *motion_state, ObjectPosition *transform, void *map_entity, ActorRecord *actor) {
    s32 direction_aux;
    void **animation_table;
    s32 frames_left;
    s16 next_timer;
    s32 target_x;
    s32 velocity_x;
    s32 target_y;
    s32 actor_flags;
    s32 current_x;
    s32 current_y;
    s32 phase;

    phase = ((S_800D991C_0 *)motion_state)->unk_9B;
    switch (phase) {
    case 0:
        ((S_800D991C_0 *)motion_state)->unk_98 = (u16) (((S_800D991C_0 *)motion_state)->unk_98 | 8);
        transform->velocity_z = 0xFFF00000;
        actor->flags1C = (s32) (actor->flags1C & 0xF7FFFFFF);
        ((S_800D991C_0 *)motion_state)->unk_A4 = 0;
        ((S_800D991C_0 *)motion_state)->unk_9B = (u8) (((S_800D991C_0 *)motion_state)->unk_9B + 1);
    case 1:
        frames_left = ((S_800D991C_0 *)motion_state)->unk_96;
        ((S_800D991C_0 *)motion_state)->unk_90 = (s32) (((S_800D991C_0 *)motion_state)->unk_90
            - ((S_800D991C_0 *)motion_state)->unk_A4);
        if (frames_left != 0) {
            target_x = ((SpriteFrameState *)map_entity)->unk_24 << 6;
            current_x = transform->x.w.i - 0x20;
            velocity_x = (s32) ((target_x - current_x) << 0x10) / frames_left;
            current_y = transform->y.w.i - 0x20;
            transform->velocity_x = velocity_x;
            target_y = ((SpriteFrameState *)map_entity)->unk_25 << 6;
            transform->velocity_y = (s32) ((s32) ((target_y - current_y)
                << 0x10) / (s16) ((S_800D991C_0 *)motion_state)->unk_96);
            ((S_800D991C_0 *)motion_state)->unk_A4 = (s32) (((S_800D991C_0 *)motion_state)->unk_A4
                + transform->velocity_z);
            transform->velocity_z = (s32) (transform->velocity_z + 0x48000);
        }
        ((S_800D991C_0 *)motion_state)->unk_90 = (s32) (((S_800D991C_0 *)motion_state)->unk_90
            + ((S_800D991C_0 *)motion_state)->unk_A4);
        if (((S_800D991C_0 *)motion_state)->unk_96 < 2) {
            ((S_800D991C_0 *)motion_state)->unk_90 = 0;
            ((S_800D991C_0 *)motion_state)->unk_98 = (u16) (((S_800D991C_0 *)motion_state)->unk_98 & 0xFFF7);
            actor->flags1C = (s32) (actor->flags1C | 0x08000000);
            ((S_800D991C_0 *)motion_state)->unk_9B = (u8) (((S_800D991C_0 *)motion_state)->unk_9B + 1);
        }
    case 2:
        if (actor->flags1C & 0x08000000) {
            ((S_800D991C_0 *)motion_state)->unk_98 = (u16) (((S_800D991C_0 *)motion_state)->unk_98 & 0xFFF7);
            transform->velocity_z = 0;
            transform->velocity_y = 0;
            transform->velocity_x = 0;
            set_record_integer_tile_center(transform, ((SpriteFrameState *)map_entity)->unk_24, ((SpriteFrameState *)map_entity)->unk_25);
            animation_table = actor_action_frames;
            ((SpriteFrameState *)map_entity)->frameTable = animation_table;
            func_8003DB94(map_entity, *(void **)((u8 *)animation_table + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                + actor->facing + 0x100) >> 7) & 0x1C)), 0);
            ((S_800D991C_0 *)motion_state)->unk_9B = (u8) (((S_800D991C_0 *)motion_state)->unk_9B + 1);
        }
    default:
        next_timer = (u16) ((S_800D991C_0 *)motion_state)->unk_96 - 1;
        ((S_800D991C_0 *)motion_state)->unk_96 = next_timer;
        if ((next_timer << 0x10) <= 0) {
            transform->velocity_z = 0;
            transform->velocity_y = 0;
            transform->velocity_x = 0;
            set_record_integer_tile_center(transform, ((SpriteFrameState *)map_entity)->unk_24, ((SpriteFrameState *)map_entity)->unk_25);
            spend_actor_mp(actor, 4);
            advance_status_timers(actor);
            if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
                g_dungeon_status.activity_counts.parts.pending_movement_count = (s16) ((u16) g_dungeon_status.activity_counts.parts.pending_movement_count - 1);
            }
            actor_flags = actor->flags1C;
            if (!(actor_flags & 0x2000)) {
                if (!(actor_flags & 0x410)) {
                    if (actor_flags & 0x20000) {
                        actor->facing = get_rounded_facing_and_rounding_flag(((SpriteFrameState *)map_entity)->unk_24,
                            ((SpriteFrameState *)map_entity)->unk_25, reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
                    }
                }
            }
            if ((check_actor_floor_trap(map_entity, actor) << 0x10) > 0) {
                ((S_800D991C_0 *)motion_state)->unk_8C = &update_actor_facing_animation;
                on_actor_status_updated(actor);
            }
        }
    }
}


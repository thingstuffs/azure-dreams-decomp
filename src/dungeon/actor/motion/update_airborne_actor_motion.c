
struct ObjectPosition;
#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/level.h"
#include "dungeon/effect.h"
#include "dungeon/effect/screen.h"

typedef struct S_800974DC_0 {
    u8 pad_00[0x8C];
    void (*unk_8C)(void *, ObjectPosition *, SpriteFrameState *, ActorRecord *);
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x5E];
    u8 unk_102;
} S_800974DC_0;   /* arg0 in update_airborne_actor_motion */

typedef struct S_800974DC_4_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800974DC_4_pre;   /* 0x14-byte header immediately before the payload. */

typedef struct S_800974DC_6 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800974DC_6;

void select_record_entry_and_value(void *state, void *entries, short index);
void set_record_integer_tile_center(ObjectPosition *record, s32 tile_x, s32 tile_y); /* extern */
void handle_actor_commands_and_facing(void *actor, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor_data);
extern void *actor_default_frames[];
extern u8 actor_alternate_frames[8];

/* Updates airborne movement, landing animation, and alignment to the actor's tile. */
void update_airborne_actor_motion(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 dir_offset;
    u16 ticks_left;
    s32 dir_y;
    u8 phase;
    EntityRec *linked_object;

    phase = body->action_phase.u;
    switch (phase) {
    case 0:
        select_nearby_target_and_initialize_slot((u8 *)actor - 0x20, motion, 8, 0x300);
        sprite->frameTable = actor_alternate_frames;
        select_record_entry_and_value(sprite, *(void **)(actor_alternate_frames + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
            >> 7) & 0x1C)), 0);
        dir_offset = ((u16) actor->facing >> 8) & 0xE;
        motion->velocity_x = (s32) (*(s16 *)((u8 *)dir_step_x + dir_offset) << 0x11);
        dir_y = *(s16 *)((u8 *)dir_step_y + dir_offset);
        motion->velocity_z = 0xFFEBC000;
        motion->velocity_y = (s32) (dir_y << 0x11);
        body->action_timer.u = 3U;
        body->action_state_flags = (u16) (body->action_state_flags & 0xFFF7);
        body->action_phase.u = (u8) (body->action_phase.u + 1);
        return;
    case 1:
        if (sprite->flags & 0x8000) {
            body->action_timer.u = 0U;
        } else {
            body->action_timer.u = (u16) (body->action_timer.u - 1);
        }
        if (body->action_timer.s == 0) {
            if (((PlayerRecord *)body)->unk_102 == 0) {
                actor->unk_20 = 1;
                if (resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1) == 0) {
                    linked_object = actor->target;
                    if (linked_object != 0) {
                        actor->target = 0;
                        linked_object->flags1C = (s32) (linked_object->flags1C & 0xEFFFFFFF);
                        ((S_800974DC_6 *)(((S_800974DC_4_pre *)linked_object)[-1].unk_00))->unk_0C = 0x808080;
                    }
                }
            }
        }
        if ((s16) body->action_timer.u <= 0) {
            if (sprite->flags & 0xE000) {
                sprite->frameTable = actor_default_frames;
                select_record_entry_and_value(sprite, *(void **)((u8 *)actor_default_frames + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing
                    + 0x100) >> 7) & 0x1C)), 0);
                body->action_phase.u = (u8) (body->action_phase.u + 1);
            }
        }
    case 2:
        if (!(body->unk_A0.parts.high & 0x10)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        if ((s16) body->action_timer.u > 0) {
            return;
        }
        sprite->frameTable = actor_default_frames;
        select_record_entry_and_value(sprite, *(void **)((u8 *)actor_default_frames + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
            >> 7) & 0x1C)), 0);
        body->action_phase.u = 3U;
        return;
    case 3:
    {
        s32 coord;
        u32 delta;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        body->action_timer.u = 2U;
        delta = (u32)sprite->tile_x << 6;
        coord = motion->x.w.i - 0x20;
        delta -= (u32)coord;
        motion->velocity_x = (s32)(delta * 0x10000U) / (s16) body->action_timer.u;
        coord = motion->y.w.i - 0x20;
        delta = ((u32)sprite->tile_y << 6) - (u32)coord;
        motion->velocity_y = (s32)(delta * 0x10000U) / (s16) body->action_timer.u;
        body->action_phase.u = (u8) (body->action_phase.u + 1);
        return;
    }
    case 4:
        ticks_left = body->action_timer.u - 1;
        body->action_timer.u = ticks_left;
        if ((ticks_left << 0x10) > 0 && !(sprite->flags & 0x8000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        process_unflagged_linked_entries(actor->next_actor_header);
        g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 0x412);
        ((S_800974DC_0 *)body)->unk_8C = &handle_actor_commands_and_facing;
        g_dungeon_status.active_actor = 0;
        body->action_timer.u = 0U;
        return;
    }
}

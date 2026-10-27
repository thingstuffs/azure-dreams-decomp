#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/kid.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
#include "dungeon/player/object/action_state.h"
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void func_80174218(void *, void *, void *, void *);

extern u8 kid_action_resume_address[];
extern u8 kid_frame_set_3[];
extern u8 kid_alt_spawn_direction_frames[];

typedef struct S_80173ED8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
} S_80173ED8_0;   /* arg0 in advance_entity_animation_actions */

typedef struct S_80173ED8_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173ED8_2;   /* counter in advance_entity_animation_actions */

typedef struct S_80173ED8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80173ED8_4;   /* global in advance_entity_animation_actions */

typedef struct S_80173ED8_5 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80173ED8_5;   /* owner in advance_entity_animation_actions */

/* Advances entity animation states and handles pending actions. */
void advance_entity_animation_actions(void *action, void *context, SpriteFrameState *sprite, void *entity)
{
    void *saved_context;
    register DungeonGlobalStatus *dungeon_state;
    void *saved_entity;
    u8 state;
    s32 direction;

    saved_context = context;
#define action action
#define context saved_context
#define sprite sprite

    state = ((S_80173ED8_0 *)action)->unk_9B;
    saved_entity = entity;
#define entity saved_entity
    switch (state) {
    case 0:
    {
        u8 *counter_state;

        if ((sprite->flags & 0xE000) == 0) {
            return;
        }

        counter_state = (u8 *)&g_dungeon_status.turn_scale;
        ((S_80173ED8_2 *)counter_state)->unk_0A--;
        sprite->frameTable = kid_alt_spawn_direction_frames;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        select_sprite_entry(sprite, kid_alt_spawn_direction_frames[direction & 7], 0);
        ((S_80173ED8_0 *)action)->unk_9B++;
        return;
    }

    case 1:
        if (((EntityRec *)entity)->tileY != 0) {
            register u8 *counter_state;

            sprite->frameTable = kid_frame_set_3;
            direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
            select_sprite_entry(sprite, kid_frame_set_3[direction & 7], 0);
            (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
            counter_state = (u8 *)&g_dungeon_status.turn_scale;
            ((S_80173ED8_2 *)counter_state)->unk_0A++;
            ((S_80173ED8_0 *)action)->unk_9B++;
            return;
        }

        dungeon_state = &g_dungeon_status.turn_scale;
        if (dungeon_state->flags & 0x1000) {
            return;
        }

        if ((((EntityRec *)entity)->unk_64 != 0) &&
            begin_ready_actor_directional_action(action, context, sprite, 0)) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(action, context, sprite, entity);
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(action, context, sprite, entity);
            ((S_80173ED8_0 *)action)->unk_A8 = 0;
            func_80174218(action, context, sprite, entity);
            return;
        }

        if (((EntityRec *)entity)->unk_6D == 0) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            void *owner = primary_actor_record;

            if ((check_entity_relation(entity,
                    (u8 *)((S_80173ED8_5 *)owner)->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_mp(entity);
        on_actor_status_updated(entity);
        if (((EntityRec *)entity)->tileY == 0) {
            return;
        }

        sprite->frameTable = kid_frame_set_3;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        select_sprite_entry(sprite, kid_frame_set_3[direction & 7], 0);
        ((EntityRec *)entity)->flags1C |= 0x40000;
        ((S_80173ED8_4 *)dungeon_state)->unk_0A++;

        ((S_80173ED8_0 *)action)->unk_9B++;
        return;

    case 2:
    {
        u8 *counter_state;

        if ((sprite->flags & 0xE000) == 0) {
            return;
        }

        counter_state = (u8 *)&g_dungeon_status.turn_scale;
        ((S_80173ED8_2 *)counter_state)->unk_0A--;
        ((EntityRec *)entity)->flags1C &= ~(ACTOR_MP_EMPTY | ACTOR_ASLEEP);
        ((S_80173ED8_0 *)action)->unk_8C = kid_action_resume_address;
        return;
    }

    default:
        return;
    }
}

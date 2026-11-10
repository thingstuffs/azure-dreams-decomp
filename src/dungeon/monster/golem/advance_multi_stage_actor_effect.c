#include "engine/graphics/select_sprite_entry_api.h"
#include "common.h"
#include "dungeon/monster/golem.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/effect/screen.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"
#include "dungeon/data.h"

extern void spend_actor_mp(void *, s32);
extern void *create_randomized_offset_object(ActorRecord *, void *, SpriteFrameState *);

extern u8 golem_direction_frames[8];

void advance_multi_stage_actor_effect(ActorRecord *body, void *incoming_entity, SpriteFrameState *sprite, ActorRecord *incoming_actor)
{
        /* MATCH: the local state join must retain state_work in retail's s2. */
    ActorRecord *state_work = body;
    EntityRec *entity = incoming_entity;
    SpriteFrameState *object = sprite;
    ActorRecord *actor = incoming_actor;
    u8 state;
    u16 flags;
    u16 flags3;
    u16 timer;

    state = state_work->action_phase;
    switch (state) {

    case 0:
        timer = state_work->action_timer - 1;
        state_work->action_timer = timer;
        if ((s16)timer > 0) {
            return;
        }
        object->frameTable = golem_frame_set_4;
        select_sprite_entry(object,
            golem_frame_set_4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        entity->flags14 = 0;
        entity->unk_10 = 0;
        entity->unk_0C = 0;
        state_work->action_phase++;
        return;

    case 1:
        flags = object->flags;
        if (flags & 0x8000) {
            state_work->action_phase = 4;
            object->flags |= 0x6000;
            if (state_work->unk_AC.bytes[2] != 2) {
                return;
            }
            resolve_attack_damage_and_effects(actor, object, actor->facing, 1);
            return;
        }
        if (object->unk_04 != 2) {
            return;
        }
        if (!(flags & 0x1000)) {
            return;
        }
        play_sound_if_enabled(0x808);
        state_work->unk_B0.address = create_randomized_offset_object(state_work, entity, object);
        state_work->action_phase++;
        return;

    case 2:
        if (!(object->flags & 0xE000)) {
            return;
        }
        object->frameTable = golem_frame_set_1;
        select_sprite_entry(object,
            golem_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        object->flags |= 0x0800;
        state_work->action_phase++;
        return;

    case 3:
        flags3 = object->flags;
        if (flags3 & 0x8000) {
            object->frameTable = golem_frame_set_1;
            select_sprite_entry(object,
                golem_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            object->flags |= 0x0800;
            return;
        }
        if (!(flags3 & 0x6000)) {
            return;
        }
        object->frameTable = golem_direction_frames;
        select_sprite_entry(object,
            golem_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        state_work->unk_AC.bytes[2] = 0;
        actor->flags14 &= ~0x40000000;
        entity->flags14 = 0;
        entity->unk_10 = 0;
        entity->unk_0C = 0;
        set_record_integer_tile_center(entity, object->tile_x, object->tile_y);
        spend_actor_mp(actor, 0x800);
        actor->action_flags &= 0x7FFF;
        state_work->unk_8C.address = update_dungeon_actor_actions;
        g_dungeon_status.active_actor = 0;
        break;

    case 4:
        if (!(object->flags & 0xE000)) {
            return;
        }
        object->frameTable = golem_direction_frames;
        select_sprite_entry(object,
            golem_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        state_work->unk_AC.bytes[2] = 0;
        actor->flags14 &= ~0x40000000;
        entity->flags14 = 0;
        entity->unk_10 = 0;
        entity->unk_0C = 0;
        set_record_integer_tile_center(entity, object->tile_x, object->tile_y);
        spend_actor_mp(actor, 0x800);
        actor->action_flags &= 0x7FFF;
        state_work->unk_8C.address = update_dungeon_actor_actions;
        g_dungeon_status.active_actor = 0;
        break;
    default:
        return;
    }
}

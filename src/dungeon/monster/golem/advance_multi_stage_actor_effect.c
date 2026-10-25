#include "common.h"
#include "dungeon/monster/golem.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x8C];
    void *field_8C;
} StateWorkFieldView_81085DBC;

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern s32 create_randomized_offset_object(void *, void *, void *);

extern u8 golem_direction_frames[8];
extern u8 golem_frame_set_4[8];
extern u8 golem_frame_set_1[8];

typedef struct S_801735BC_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x12];
    u8 unk_AE;
    u8 pad_AF[0x1];
    s32 unk_B0;
} S_801735BC_0;   /* state_work in advance_multi_stage_actor_effect */

typedef struct S_801735BC_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801735BC_1;   /* actor in advance_multi_stage_actor_effect */

void advance_multi_stage_actor_effect(void *incoming_state_work, void *incoming_entity, void *incoming_object, void *incoming_actor)
{
        /* MATCH: the local state join must retain state_work in retail's s2. */
    void *state_work = incoming_state_work;
    EntityRec *entity = incoming_entity;
    SpriteFrameState *object = incoming_object;
    void *actor = incoming_actor;
    u8 state;
    u16 flags;
    u16 flags3;
    u16 timer;

    state = ((S_801735BC_0 *)state_work)->unk_9B;
    switch (state) {

    case 0:
        timer = ((S_801735BC_0 *)state_work)->unk_96 - 1;
        ((S_801735BC_0 *)state_work)->unk_96 = timer;
        if ((s16)timer > 0) {
            return;
        }
        object->frameTable = golem_frame_set_4;
        select_sprite_entry(object,
            golem_frame_set_4[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801735BC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        entity->flags14 = 0;
        entity->unk_10 = 0;
        entity->unk_0C = 0;
        ((S_801735BC_0 *)state_work)->unk_9B++;
        return;

    case 1:
        flags = object->flags;
        if (flags & 0x8000) {
            ((S_801735BC_0 *)state_work)->unk_9B = 4;
            object->flags |= 0x6000;
            if (((S_801735BC_0 *)state_work)->unk_AE != 2) {
                return;
            }
            resolve_attack_damage_and_effects(actor, object, ((S_801735BC_1 *)actor)->unk_2A, 1);
            return;
        }
        if (object->unk_04 != 2) {
            return;
        }
        if (!(flags & 0x1000)) {
            return;
        }
        play_sound_if_enabled(0x808);
        ((S_801735BC_0 *)state_work)->unk_B0 = create_randomized_offset_object(state_work, entity, object);
        ((S_801735BC_0 *)state_work)->unk_9B++;
        return;

    case 2:
        if (!(object->flags & 0xE000)) {
            return;
        }
        object->frameTable = golem_frame_set_1;
        select_sprite_entry(object,
            golem_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801735BC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        object->flags |= 0x0800;
        ((S_801735BC_0 *)state_work)->unk_9B++;
        return;

    case 3:
        flags3 = object->flags;
        if (flags3 & 0x8000) {
            object->frameTable = golem_frame_set_1;
            select_sprite_entry(object,
                golem_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801735BC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            object->flags |= 0x0800;
            return;
        }
        if (!(flags3 & 0x6000)) {
            return;
        }
        object->frameTable = golem_direction_frames;
        select_sprite_entry(object,
            golem_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801735BC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801735BC_0 *)state_work)->unk_AE = 0;
        ((S_801735BC_1 *)actor)->unk_14 &= ~0x40000000;
        entity->flags14 = 0;
        entity->unk_10 = 0;
        entity->unk_0C = 0;
        set_record_integer_tile_center(entity, object->tile_x, object->tile_y);
        spend_actor_mp(actor, 0x800);
        ((S_801735BC_1 *)actor)->unk_46 &= 0x7FFF;
        (((StateWorkFieldView_81085DBC *)state_work)->field_8C) = update_dungeon_actor_actions;
        g_dungeon_status.active_actor = 0;
        break;

    case 4:
        if (!(object->flags & 0xE000)) {
            return;
        }
        object->frameTable = golem_direction_frames;
        select_sprite_entry(object,
            golem_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801735BC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801735BC_0 *)state_work)->unk_AE = 0;
        ((S_801735BC_1 *)actor)->unk_14 &= ~0x40000000;
        entity->flags14 = 0;
        entity->unk_10 = 0;
        entity->unk_0C = 0;
        set_record_integer_tile_center(entity, object->tile_x, object->tile_y);
        spend_actor_mp(actor, 0x800);
        ((S_801735BC_1 *)actor)->unk_46 &= 0x7FFF;
        (((StateWorkFieldView_81085DBC *)state_work)->field_8C) = update_dungeon_actor_actions;
        g_dungeon_status.active_actor = 0;
        break;
    default:
        return;
    }
}

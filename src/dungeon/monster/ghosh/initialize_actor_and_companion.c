#include "engine/node/allocation.h"
#include "shared/actor_status_flags.h"
#include "engine/node/registration.h"
#include "dungeon/monster/ghosh.h"
#include "shared/actor_property_flags.h"
#include "common.h"
#include "dungeon/system/random_range.h"
#include "shared/monster_ids.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor/animation.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "engine/entity.h"
#include "dungeon/monster/ghosh_frames.h"


typedef struct S_8016AEDC_4 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x11];
    s16 unk_AE;
    s8 unk_B0;
    u8 pad_B1[0x3];
    s8 unk_B4;
} S_8016AEDC_4;   /* a0_copy in initialize_actor_and_companion */




struct ObjectNodeHeader;

extern s32 ghosh_action_resume_address;

/*
 * Creates Ghosh and its companion one tile to the right, stores both nodes, and retains the
 * companion's resources.
 */
void *initialize_actor_and_companion(s16 mode_flags, s32 config_24, s32 config_25, s32 config_0a)
{
    S_8016AEDC_4 *work_copy;
    u16 spawn_config_0a;
    s32 saved_config_24;
    s16 saved_config_25;
    ObjectNodeHeader *object;
    ActorRecord *work;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    u8 *callback;
    ActorRecord *spawned;
    s32 mode_kind;
    u16 saved_config_0a;

    work = 0;
    saved_config_24 = config_24;
    saved_config_25 = config_25;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    saved_config_0a = config_0a;
    if (object != 0) {
        work = NODE_BODY(object);
        ghosh_actor_node = object;
        object->update_callback = update_ghosh_actor;
        work->species = MONSTER_GHOSH;
        register_node(object, project_sprite_chain);

        callback = ghosh_frame_set_3;
        part_a = object->position;
        work_copy = work;
        part_a->z.w.i = config_0a;
        part_b = object->sprite;
        mode_kind = mode_flags & 3;
        part_b->frameTable = callback;
        part_b->tile_x = saved_config_24;

        part_b->tile_y = saved_config_25;
        if (mode_kind == 1) {
            work->flags14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            work->flags1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (mode_kind >= 2) {
            work->flags14 |= ACTOR_CLASS_ENABLED;
            work->flags1C |= ACTOR_PLAYER_SIDE;
        }

        initialize_actor_sprite_and_animation(object, part_a, part_b, (s16)mode_flags);
        {

            work_copy->unk_9A = 0xFF;
            work_copy->unk_9C = -1;
            work_copy->unk_8C = &ghosh_action_resume_address;
            work_copy->unk_AE = 0;
            work_copy->unk_B4 = 0;
            work_copy->unk_B0 = 0;
            part_b->flags |= 0x80;
            try_move_actor_to_valid_position(work_copy, part_a, part_b, work);
        }
        work->unk_49 = 0xE;
        work->unk_48 = 3;
        work->unk_4A = random_dungeon_range_16(0x10, 0x18);
        work->unk_4B = 1;
    }

    {
        s32 spawn_mode;
        s32 spawn_config_24;
        s32 spawn_config_25;

        spawn_mode = (s16)mode_flags;
        spawn_config_24 = (s16)(saved_config_24 + 1);
        config_25 = (s32)((u32)saved_config_25 << 16);
        spawn_config_0a = saved_config_0a;
        spawn_config_25 = config_25 >> 16;
        spawned = allocate_boss_actor(spawn_mode, spawn_config_24, spawn_config_25, (s16)spawn_config_0a);
    }
    retain_spawn_resource(spawned->species, 1);
    func_80042640(spawned, spawned->species);
    spawned->unk_43 = 0xFF;
    spawned->unk_12 = 0;
    return work;
}

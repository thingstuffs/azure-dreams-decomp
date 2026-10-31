#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"
#include "dungeon/actor.h"
#include "dungeon/item.h"
#include "engine/object.h"

typedef void (*Callback)(void *, void *, void *, void *);

#include "engine/texture/select_indirect_table_entry_api.h"
#include "slus.h"
#include "engine/texture.h"

struct ActorRecord; struct Rec_func_800A9E70_arg0; struct S_800A9E70_2; s32 refresh_actor_facing_and_lifecycle(struct Rec_func_800A9E70_arg0 *, s32, struct S_800A9E70_2 *, struct ActorRecord *);

extern u8 D_800F8BBC[9];
extern void ghosh_motion_resume_address(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
extern Callback ghosh_action_handlers[];

typedef struct S_8016F2E0_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8016F2E0_0;   /* slot in update_boss_actor_movement */

typedef struct S_8016F2E0_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8016F2E0_1_pre;   /* the 0x14 bytes before node in update_boss_actor_movement, addressed as node[-1] */

typedef struct S_8016F2E0_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8016F2E0_2;   /* record in update_boss_actor_movement */

typedef struct S_8016F2E0_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    s8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_8016F2E0_3;   /* actor in update_boss_actor_movement */


/* Updates actor callbacks, facing, movement, and floor contact. */
void update_boss_actor_movement(void *entity, ObjectPosition *motion, SpriteFrameState *sprite)
{
    void *actor = entity;
    s16 old_direction;
    s16 direction_copy;
    Callback paused_callback;
    s32 floor_height;
    s16 actor_height;
    s16 direction_value;
    u8 *tile_slot;
    u16 sprite_flags;
    u16 updated_flags;
    s32 previous_direction;
    s32 direction_tiles;
    s32 slot_index;
    u8 *actor_slot;
    S_8016F2E0_1_pre *actor_node;
    S_8016F2E0_2 *actor_record;

    if ((*(s32 *)((u8 *)entity + (0x14))) & 0x00800000) {
        (*(s32 *)((u8 *)entity + (0x14))) &= 0xFF7FFFFF;
        enqueue_runtime_pool_script(&D_800F8BBC);
        (*((u8 *)entity + (0x6D))) = 0;
        (*((u8 *)entity + (0x9B))) = 0;
        (*((u8 *)entity + (0x71))) &= 0x7F;
    }

    if (system_update_flags & 8) {
        slot_index = 1;
        actor_slot = ((u8 *)dungeon_actor_ring_anchor) + 4;
        do {
            actor_node = ((S_8016F2E0_0 *)actor_slot)->unk_AC;
            if (actor_node != 0) {
                actor_record = actor_node[-1].unk_00;
                actor_record->unk_14 &= 0xFFBF;
            }
            slot_index--;
            actor_slot -= 4;
        } while (slot_index >= 0);
    }

    if (g_dungeon_status.flags & 0x2000) {
        paused_callback = (*(Callback *)((u8 *)entity + (0x8C)));
        if (paused_callback == (Callback)&ghosh_motion_resume_address) {
            paused_callback(entity, motion, sprite, actor);
            return;
        }
        ((S_8016F2E0_3 *)actor)->unk_71 &= 0x7F;
        return;
    }

    old_direction = ((S_8016F2E0_3 *)actor)->unk_6D;
    if (refresh_actor_facing_and_lifecycle(entity, (s32)(motion), sprite, actor) != 0) {
        return;
    }

    {
        Callback update_callback = (*(Callback *)((u8 *)entity + (0x8C)));
        if (update_callback != 0) {
            update_callback(entity, motion, sprite, actor);
        }
    }
    ghosh_action_handlers[(*((u8 *)entity + (0x9A)))](entity, motion, sprite, actor);

    if (old_direction != ((S_8016F2E0_3 *)actor)->unk_6D) {
        try_move_actor_to_valid_position(entity, motion, sprite, actor);
    }

    sprite_flags = sprite->flags;
    updated_flags = sprite_flags & 0x8000;
    if (updated_flags == 0) {
        old_direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016F2E0_3 *)actor)->unk_2A + 0x100) >> 9) & 7;
        previous_direction = (*(s16 *)((u8 *)entity + (0x94)));
        direction_value = old_direction;
        direction_copy = old_direction;
        if (previous_direction != direction_value) {
            direction_tiles = *(s32 *)&sprite->frameTable;
            if (direction_tiles != 0) {
                tile_slot = (u8 *)direction_tiles + direction_value;
                select_indirect_table_entry(sprite,
                    *tile_slot,
                    sprite->unk_04);
            }
            (*(s16 *)((u8 *)entity + (0x94))) = old_direction;
        }

        tile_slot = dir_sprite_flag + direction_copy;
        if (*tile_slot != 0) {
            sprite->flags |= 1;
        } else {
            sprite->flags &= 0xFFFE;
        }
        if (!(((S_8016F2E0_3 *)actor)->unk_1C & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
        }

        apply_monster_koyaw_data(((S_8016F2E0_3 *)actor)->unk_1C, (u8 *)sprite + 0xC);
    } else {
        updated_flags = sprite_flags & 0x0800;
        if (updated_flags != 0) {
            updated_flags = sprite_flags & 0x8FFF;
        } else {
            updated_flags = sprite_flags | 0x7000;
        }
        sprite->flags = updated_flags;
    }

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;

    if ((*(u16 *)((u8 *)entity + (0x98))) & 8) {
        (*((u8 *)entity + (0x9D))) = 0;
    } else {
        motion->velocity_z += (*(s8 *)((u8 *)entity + (0x9D))) * 0x14000;
        (*((u8 *)entity + (0x9D)))++;
    }
    (*(s32 *)((u8 *)entity + (0x90))) += motion->velocity_z;

    if (!((*(u16 *)((u8 *)entity + (0x98))) & 4)) {
        floor_height = sample_terrain_surface_height(((u16) motion->x.w.i),
                              ((u16) motion->y.w.i),
                              (s16)(((S_8016F2E0_3 *)actor)->unk_88.u - 0x20));
        if ((s16)floor_height < 0x200) {
            actor_height = ((S_8016F2E0_3 *)actor)->unk_88.s;
            if ((*(s16 *)((u8 *)entity + (0x92))) + actor_height < (s16)floor_height) {
                ((S_8016F2E0_3 *)actor)->unk_1C &= 0xF7FFFFFF;
            } else {
                if ((s16)floor_height >= actor_height) {
                    (*(s32 *)((u8 *)entity + (0x90))) = 0;
                } else {
                    (*(s16 *)((u8 *)entity + (0x92))) = floor_height - actor_height;
                }
                motion->velocity_z = 0;
                ((S_8016F2E0_3 *)actor)->unk_1C |= 0x08000000;
                (*((u8 *)entity + (0x9D))) = 0;
            }

            if (((S_8016F2E0_3 *)actor)->unk_1C & 0x40000000) {
                ((S_8016F2E0_3 *)actor)->unk_1C &= 0xBFFFFFFF;
                floor_height = sample_terrain_surface_height((sprite->tile_x << 6) | 0x20,
                                      (sprite->tile_y << 6) | 0x20,
                                      (s16)(((S_8016F2E0_3 *)actor)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity + (0x92))) += ((S_8016F2E0_3 *)actor)->unk_88.u - floor_height;
                ((S_8016F2E0_3 *)actor)->unk_88.u = floor_height;
            }
        } else {
            ((S_8016F2E0_3 *)actor)->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        ((S_8016F2E0_3 *)actor)->unk_1C &= 0xF7FFFFFF;
    }
    motion->z.w.i = ((S_8016F2E0_3 *)actor)->unk_88.u + (*(u16 *)((u8 *)entity + (0x92)));
    sprite->flags |= 0x40;
}

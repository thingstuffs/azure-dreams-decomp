#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/monster/beldo_large.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/object_links.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor/status.h"
#include "dungeon/level.h"
#include "dungeon/actor.h"
#include "dungeon/item.h"
#include "engine/entity.h"
#include "engine/object.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef void (*Callback)(void *, void *, void *, void *);

#include "engine/texture/select_indirect_table_entry_api.h"
#include "slus.h"
#include "engine/texture.h"

struct Owner_800A48F0; 
struct ActorRecord; struct Rec_func_800A9E70_arg0; struct S_800A9E70_2; s32 refresh_actor_facing_and_lifecycle(struct Rec_func_800A9E70_arg0 *, s32, struct S_800A9E70_2 *, struct ActorRecord *);
void beldo_large_action_resume_address(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);

extern Callback beldo_large_callbacks[];
extern u8 D_80173DDC[];

typedef struct S_80169EC0_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80169EC0_0;   /* scan in update_actor_callbacks_and_motion */

   /* the 0x14 bytes before entry in update_actor_callbacks_and_motion, addressed as entry[-1] */

typedef struct S_80169EC0_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80169EC0_2;   /* record in update_actor_callbacks_and_motion */

typedef struct S_80169EC0_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80169EC0_3;   /* actor in update_actor_callbacks_and_motion */

   /* data in update_actor_callbacks_and_motion */


/* Updates actor callbacks, facing, movement, and terrain height. */
void update_actor_callbacks_and_motion(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite)
{
    void *actor = body;
    s16 initial_state;
    s16 direction;
    u32 state_bits;
    ActorActionHandler special_callback;
    ActorActionHandler update_callback;
    s32 terrain_height;
    s32 actor_flags;
    s32 slot_index;
    u8 *slot_ptr;
    SpriteLinkPrefixView *slot_entry;
    S_80169EC0_2 *slot_record;
    u16 status;
    u16 height;
    s32 signed_height;
    s32 height_offset;

    if (body->unk_B0.bytes[1] == 0 &&
        !(system_update_flags & 1) && g_dungeon_status.activity_counts.parts.pending_action_count == 0) {
        body->unk_B0.bytes[1] = 1;
        enqueue_runtime_pool_script(D_80173DDC);
        body->pending_turn_updates = 0;
        body->action_phase.u = 0;
    }

    if ((*(u16 *)0x80013714) & 8) {
        slot_index = 1;
        slot_ptr = ((u8 *)dungeon_actor_ring_anchor) + 4;
        do {
            slot_entry = ((S_80169EC0_0 *)slot_ptr)->unk_AC;
            if (slot_entry != NULL) {
                slot_record = slot_entry[-1].sprite;
                slot_record->unk_14 &= 0xFFBF;
            }
            slot_index--;
            slot_ptr -= 4;
        } while (slot_index >= 0);
    }

    if (body->unk_B0.bytes[0] == 1) {
        set_or_clear_actor_status_slot(actor, STATUS_SPEED, 1);
    } else {
        clear_slots_of_type(actor, STATUS_SPEED);
    }
    if (g_dungeon_status.flags & 0x2000) {
        special_callback = body->unk_8C.handler;
        if (special_callback == (Callback)beldo_large_action_resume_address) {
            special_callback(body, motion, sprite, actor);
            return;
        } else {
            ((S_80169EC0_3 *)actor)->unk_71 &= 0x7F;
            return;
        }
    }

    {
        void *call_owner = body;
        void *call_motion = motion;
        void *call_data = sprite;

        initial_state = (s8)((S_80169EC0_3 *)actor)->unk_6D.u;
        if (refresh_actor_facing_and_lifecycle(call_owner, (s32)(call_motion), call_data, actor) != 0) {
            return;
        }
    }

    update_callback = body->unk_8C.handler;
    if (update_callback != NULL) {
        update_callback(body, motion, sprite, actor);
    }
    beldo_large_callbacks[body->action_id.u](body, motion, sprite, actor);
    if ((s16)initial_state != ((S_80169EC0_3 *)actor)->unk_6D.s) {
        try_move_actor_to_valid_position(body, motion, sprite, actor);
    }

    status = sprite->flags;
    if (!(status & 0x8000)) {
        u16 frame_status;
        u16 cleared_status;
        state_bits = (u32)(g_game_work.view.camera_rotation.parts.viewAngle + ((S_80169EC0_3 *)actor)->unk_2A + 0x100);
        state_bits = (s32)state_bits >> 9;
        direction = state_bits & 7;
        if (body->unk_94 != direction) {
            u8 *facing_steps = sprite->frameTable;
            if (facing_steps != NULL) {
                select_indirect_table_entry(sprite, facing_steps[direction], sprite->unk_04);
            }
            body->unk_94 = direction;
        }

        frame_status = sprite->flags;
        cleared_status = frame_status & 0xFFFE;
        sprite->flags = cleared_status;
        if (!(((S_80169EC0_3 *)actor)->unk_1C & ACTOR_PARALYZED)) {
            if (!(frame_status & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags = cleared_status | 0x7000;
        }
        apply_monster_koyaw_data(((S_80169EC0_3 *)actor)->unk_1C, (u8 *)sprite + 0xC);
    } else {
        sprite->flags = (status & 0x800) ?
                                (status & 0x8FFF) : (status | 0x7000);
    }

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    if (body->action_state_flags & 8) {
        body->unk_9D.u = 0;
    } else {
        motion->velocity_z += body->unk_9D.s * 0x14000;
        body->unk_9D.u++;
    }
    body->unk_90.value += motion->velocity_z;

    if (!(body->action_state_flags & 4) &&
        ((terrain_height = sample_terrain_surface_height(((u16) motion->x.w.i),
            ((u16) motion->y.w.i),
                           (s16)(((S_80169EC0_3 *)actor)->unk_88.u - 0x20))),
         (s16)terrain_height < 0x200)) {
        height_offset = body->unk_90.parts.high.s;
        signed_height = ((S_80169EC0_3 *)actor)->unk_88.s;
        height = ((S_80169EC0_3 *)actor)->unk_88.u;
        if (height_offset + signed_height < (s16)terrain_height) {
            ((S_80169EC0_3 *)actor)->unk_1C &= ACTOR_GROUNDED_CLEAR_MASK;
        } else {
            if ((s16)terrain_height >= signed_height) {
                body->unk_90.value = 0;
            } else {
                body->unk_90.parts.high.s = terrain_height - height;
            }
            motion->velocity_z = 0;
            ((S_80169EC0_3 *)actor)->unk_1C |= ACTOR_GROUNDED;
            body->unk_9D.u = 0;
        }
        actor_flags = ((S_80169EC0_3 *)actor)->unk_1C;
        if (actor_flags & 0x40000000) {
            ((S_80169EC0_3 *)actor)->unk_1C = actor_flags & 0xBFFFFFFF;
            terrain_height = sample_terrain_surface_height((sprite->tile_x << 6) | 0x20,
                                   (sprite->tile_y << 6) | 0x20,
                                   (s16)(((S_80169EC0_3 *)actor)->unk_88.u - 0x20));
            body->unk_90.parts.high.s += ((S_80169EC0_3 *)actor)->unk_88.u - terrain_height;
            ((S_80169EC0_3 *)actor)->unk_88.u = terrain_height;
        }
    } else {
        ((S_80169EC0_3 *)actor)->unk_1C &= ACTOR_GROUNDED_CLEAR_MASK;
    }

    motion->z.w.i = (*(s8 *)((u8 *)body + (0xAA))) +
                              (((S_80169EC0_3 *)actor)->unk_88.u +
                               body->unk_90.parts.high.u);
    sprite->flags |= 0x40;
}

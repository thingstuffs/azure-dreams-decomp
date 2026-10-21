#include "common.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/object_links.h"
#include "shared/sprite_frame_state.h"

#ifndef NULL
#define NULL ((void *)0)
#endif


typedef void (*Callback)(void *, void *, void *, void *);

s32 func_800353F4(void *);
extern void clear_slots_of_type();
#include "engine/texture/select_indirect_table_entry_api.h"
extern void func_800478B8();
void apply_monster_koyaw_data(s32, s8 *);
struct Owner_800A48F0; s16 set_or_clear_actor_status_slot(struct Owner_800A48F0 *, s8, s8);
struct ActorRecord; struct Rec_func_800A9E70_arg0; struct S_800A9E70_2; s32 refresh_actor_facing_and_lifecycle(struct Rec_func_800A9E70_arg0 *, s32, struct S_800A9E70_2 *, struct ActorRecord *);
s32 try_move_actor_to_valid_position(void *, void *, void *, void *);
extern s32 sample_terrain_surface_height();
extern void D_8016A36C();

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

typedef struct S_80169EC0_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80169EC0_5;   /* motion in update_actor_callbacks_and_motion */

/* Updates actor callbacks, facing, movement, and terrain height. */
void update_actor_callbacks_and_motion(void *owner_arg, void *motion, void *data)
{
    void *actor = owner_arg;
    s16 initial_state;
    s16 direction;
    u32 state_bits;
    Callback special_callback;
    Callback update_callback;
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

    if ((*(u8 *)((u8 *)owner_arg + (0xB1))) == 0 &&
        !(system_update_flags & 1) && g_dungeon_status.activity_counts.parts.pending_action_count == 0) {
        (*(u8 *)((u8 *)owner_arg + (0xB1))) = 1;
        func_800353F4(D_80173DDC);
        (*(u8 *)((u8 *)owner_arg + (0x6D))) = 0;
        (*(u8 *)((u8 *)owner_arg + (0x9B))) = 0;
    }


    if ((*(u16 *)0x80013714) & 8) {
        slot_index = 1;
        slot_ptr = ((u8 *)dungeon_actor_ring_anchor) + 4;
        do {
            slot_entry = ((S_80169EC0_0 *)slot_ptr)->unk_AC;
            if (slot_entry != NULL) {
                slot_record = slot_entry[-1].unk_00;
                slot_record->unk_14 &= 0xFFBF;
            }
            slot_index--;
            slot_ptr -= 4;
        } while (slot_index >= 0);
    }

    if ((*(u8 *)((u8 *)owner_arg + (0xB0))) == 1) {
        set_or_clear_actor_status_slot(actor, 7, 1);
    } else {
        clear_slots_of_type(actor, 7);
    }
    if (g_dungeon_status.flags & 0x2000) {
        special_callback = (*(Callback *)((u8 *)owner_arg + (0x8C)));
        if (special_callback == (Callback)D_8016A36C) {
            special_callback(owner_arg, motion, data, actor);
            return;
        } else {
            ((S_80169EC0_3 *)actor)->unk_71 &= 0x7F;
            return;
        }
    }

    {
        void *call_owner = owner_arg;
        void *call_motion = motion;
        void *call_data = data;

        initial_state = (s8)((S_80169EC0_3 *)actor)->unk_6D.u;
        if (refresh_actor_facing_and_lifecycle(call_owner, (s32)(call_motion), call_data, actor) != 0) {
            return;
        }
    }

    update_callback = (*(Callback *)((u8 *)owner_arg + (0x8C)));
    if (update_callback != NULL) {
        update_callback(owner_arg, motion, data, actor);
    }
    beldo_large_callbacks[(*(u8 *)((u8 *)owner_arg + (0x9A)))](owner_arg, motion, data, actor);
    if ((s16)initial_state != ((S_80169EC0_3 *)actor)->unk_6D.s) {
        try_move_actor_to_valid_position(owner_arg, motion, data, actor);
    }

    status = ((SpriteAnimationTableView *)data)->unk_14;
    if (!(status & 0x8000)) {
        u16 frame_status;
        u16 cleared_status;
        state_bits = (u32)(g_game_work.view.camera_rotation.parts.viewAngle + ((S_80169EC0_3 *)actor)->unk_2A + 0x100);
        state_bits = (s32)state_bits >> 9;
        direction = state_bits & 7;
        if ((*(s16 *)((u8 *)owner_arg + (0x94))) != direction) {
            u8 *facing_steps = ((SpriteAnimationTableView *)data)->unk_2C;
            if (facing_steps != NULL) {
                select_indirect_table_entry(data, facing_steps[direction], ((SpriteAnimationTableView *)data)->unk_04);
            }
            (*(s16 *)((u8 *)owner_arg + (0x94))) = direction;
        }

        frame_status = ((SpriteAnimationTableView *)data)->unk_14;
        cleared_status = frame_status & 0xFFFE;
        ((SpriteAnimationTableView *)data)->unk_14 = cleared_status;
        if (!(((S_80169EC0_3 *)actor)->unk_1C & 0x20)) {
            if (!(frame_status & 0x40)) {
                func_800478B8(data);
            }
        } else {
            ((SpriteAnimationTableView *)data)->unk_14 = cleared_status | 0x7000;
        }
        apply_monster_koyaw_data(((S_80169EC0_3 *)actor)->unk_1C, (u8 *)data + 0xC);
    } else {
        ((SpriteAnimationTableView *)data)->unk_14 = (status & 0x800) ?
                                (status & 0x8FFF) : (status | 0x7000);
    }

    ((S_80169EC0_5 *)motion)->unk_00.at00.v += ((S_80169EC0_5 *)motion)->unk_0C;
    ((S_80169EC0_5 *)motion)->unk_04.at00.v += ((S_80169EC0_5 *)motion)->unk_10;
    if ((*(u16 *)((u8 *)owner_arg + (0x98))) & 8) {
        (*(u8 *)((u8 *)owner_arg + (0x9D))) = 0;
    } else {
        ((S_80169EC0_5 *)motion)->unk_14 += (*(s8 *)((u8 *)owner_arg + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)owner_arg + (0x9D)))++;
    }
    (*(s32 *)((u8 *)owner_arg + (0x90))) += ((S_80169EC0_5 *)motion)->unk_14;

    if (!((*(u16 *)((u8 *)owner_arg + (0x98))) & 4) &&
        ((terrain_height = sample_terrain_surface_height(((S_80169EC0_5 *)motion)->unk_00.at02.v,
            ((S_80169EC0_5 *)motion)->unk_04.at02.v,
                           (s16)(((S_80169EC0_3 *)actor)->unk_88.u - 0x20))),
         (s16)terrain_height < 0x200)) {
        height_offset = (*(s16 *)((u8 *)owner_arg + (0x92)));
        signed_height = ((S_80169EC0_3 *)actor)->unk_88.s;
        height = ((S_80169EC0_3 *)actor)->unk_88.u;
        if (height_offset + signed_height < (s16)terrain_height) {
            ((S_80169EC0_3 *)actor)->unk_1C &= 0xF7FFFFFF;
        } else {
            if ((s16)terrain_height >= signed_height) {
                (*(s32 *)((u8 *)owner_arg + (0x90))) = 0;
            } else {
                (*(s16 *)((u8 *)owner_arg + (0x92))) = terrain_height - height;
            }
            ((S_80169EC0_5 *)motion)->unk_14 = 0;
            ((S_80169EC0_3 *)actor)->unk_1C |= 0x08000000;
            (*(u8 *)((u8 *)owner_arg + (0x9D))) = 0;
        }
        actor_flags = ((S_80169EC0_3 *)actor)->unk_1C;
        if (actor_flags & 0x40000000) {
            ((S_80169EC0_3 *)actor)->unk_1C = actor_flags & 0xBFFFFFFF;
            terrain_height = sample_terrain_surface_height((((SpriteAnimationTableView *)data)->unk_24 << 6) | 0x20,
                                   (((SpriteAnimationTableView *)data)->unk_25 << 6) | 0x20,
                                   (s16)(((S_80169EC0_3 *)actor)->unk_88.u - 0x20));
            (*(s16 *)((u8 *)owner_arg + (0x92))) += ((S_80169EC0_3 *)actor)->unk_88.u - terrain_height;
            ((S_80169EC0_3 *)actor)->unk_88.u = terrain_height;
        }
    } else {
        ((S_80169EC0_3 *)actor)->unk_1C &= 0xF7FFFFFF;
    }

    ((S_80169EC0_5 *)motion)->unk_0A = (*(s8 *)((u8 *)owner_arg + (0xAA))) +
                              (((S_80169EC0_3 *)actor)->unk_88.u +
                               (*(u16 *)((u8 *)owner_arg + (0x92))));
    ((SpriteAnimationTableView *)data)->unk_14 |= 0x40;
}

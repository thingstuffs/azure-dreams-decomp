#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801722BC_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    union { s16 s; u16 u; } unk_A4;   /* accessed as both */
} S_801722BC_0;   /* arg0 in complete_airborne_actor_recovery */

typedef struct S_801722BC_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801722BC_2;   /* arg3 in complete_airborne_actor_recovery */

extern void select_sprite_entry(void *, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);
extern s32 check_actor_floor_trap(void *, void *);

extern u8 D_80170E68[];
extern u8 D_80173884[];
extern u8 D_8017388C[];

/* Updates airborne movement, landing animation, and actor recovery when the timer expires. */
void complete_airborne_actor_recovery(void *anim, void *motion, void *entity, void *actor)
{
    s32 direction_aux;
    s32 move_ticks;
    s32 origin_x;
    s32 origin_y;
    s32 height_offset;
    s32 height;
    s32 arc_ticks;
    s32 target_x;
    s16 next_tick;
    s32 actor_flags;
    u16 remaining_ticks;
    s32 phase;
    DungeonGlobalStatus *counter_base;

    phase = ((S_801722BC_0 *)anim)->unk_9B;
    switch (phase) {
    case 0:
        if (!(((SpriteFrameState *)entity)->flags & 0x6000)) {
            break;
        }
        ((SpriteFrameState *)entity)->frameTable = D_80173884;
        select_sprite_entry(
            entity,
            D_80173884[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801722BC_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801722BC_0 *)anim)->unk_98 |= 8;
        ((S_801722BC_2 *)actor)->unk_1C.s &= 0xF7FFFFFF;
        ((ObjectPosition *)motion)->velocity_z = 0xFFF00000;
        ((S_801722BC_0 *)anim)->unk_A0 = 0;
        ((S_801722BC_0 *)anim)->unk_9B++;
    case 1:
        move_ticks = ((S_801722BC_0 *)anim)->unk_A4.s;
        ((S_801722BC_0 *)anim)->unk_90 =
            ((S_801722BC_0 *)anim)->unk_90 - ((S_801722BC_0 *)anim)->unk_A0;
        if (move_ticks != 0) {
            target_x = ((SpriteFrameState *)entity)->unk_24 << 6;
            origin_x = ((ObjectPosition *)motion)->x.w.i - 0x20;
            origin_y = ((ObjectPosition *)motion)->y.w.i - 0x20;
            ((ObjectPosition *)motion)->velocity_x =
                ((target_x - origin_x) << 16) /
                move_ticks;
            ((ObjectPosition *)motion)->velocity_y =
                (((((SpriteFrameState *)entity)->unk_25 << 6) - origin_y) << 16) /
                (s16)((S_801722BC_0 *)anim)->unk_A4.s;
            arc_ticks = ((S_801722BC_0 *)anim)->unk_A4.s;
            ((ObjectPosition *)motion)->velocity_z += (arc_ticks << 15) + (arc_ticks << 13);
            ((S_801722BC_0 *)anim)->unk_A0 += ((ObjectPosition *)motion)->velocity_z;
        }
        height = ((S_801722BC_0 *)anim)->unk_90;
        height_offset = ((S_801722BC_0 *)anim)->unk_A0;
        next_tick = ((S_801722BC_0 *)anim)->unk_A4.u - 1;
        height += height_offset;
        ((S_801722BC_0 *)anim)->unk_A4.s = next_tick;
        ((S_801722BC_0 *)anim)->unk_90 = height;
        if (next_tick < 0) {
            ((S_801722BC_0 *)anim)->unk_90 = 0;
            ((S_801722BC_0 *)anim)->unk_98 &= 0xFFF7;
            ((S_801722BC_2 *)actor)->unk_1C.s |= 0x08000000;
            ((S_801722BC_0 *)anim)->unk_9B++;
        }
    case 2:
        if (((S_801722BC_2 *)actor)->unk_1C.s & 0x08000000) {
            ((S_801722BC_0 *)anim)->unk_98 &= 0xFFF7;
            ((ObjectPosition *)motion)->velocity_z = 0;
            ((ObjectPosition *)motion)->velocity_y = 0;
            ((ObjectPosition *)motion)->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)entity)->unk_24, ((SpriteFrameState *)entity)->unk_25);
            ((SpriteFrameState *)entity)->frameTable = D_8017388C;
            select_sprite_entry(
                entity,
                D_8017388C[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801722BC_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801722BC_0 *)anim)->unk_9B++;
        }
    }

    remaining_ticks = ((S_801722BC_0 *)anim)->unk_96 - 1;
    ((S_801722BC_0 *)anim)->unk_96 = remaining_ticks;
    if ((remaining_ticks << 16) <= 0) {
        ((ObjectPosition *)motion)->velocity_z = 0;
        ((ObjectPosition *)motion)->velocity_y = 0;
        ((ObjectPosition *)motion)->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)entity)->unk_24, ((SpriteFrameState *)entity)->unk_25);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);

        counter_base = &g_dungeon_status;
        if (counter_base->activity_counts.parts.pending_movement_count != 0) {
            (*(u16 *)&counter_base->activity_counts.parts.pending_movement_count)--;
        }

        actor_flags = ((S_801722BC_2 *)actor)->unk_1C.u;
        if (actor_flags & 0x2000) {
            if (((S_801722BC_2 *)actor)->unk_46 & 0x8000) {
                ((S_801722BC_2 *)actor)->unk_46 &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                ((S_801722BC_2 *)actor)->unk_2A = get_rounded_facing_and_rounding_flag(
                    ((SpriteFrameState *)entity)->unk_24, ((SpriteFrameState *)entity)->unk_25,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
            }
        }

        if ((check_actor_floor_trap(entity, actor) << 16) > 0) {
            ((S_801722BC_0 *)anim)->unk_8C = D_80170E68;
            on_actor_status_updated(actor);
        }
    }
}

/* MECHANISM: Four held arguments naturally give the 0x38 frame and s0/s1/s3/s2 save order. Named
   coordinate/delta and position/offset locals close both load-order residues. */

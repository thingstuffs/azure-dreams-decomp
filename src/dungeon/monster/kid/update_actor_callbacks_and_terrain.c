#include "shared/entity.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/level.h"
#include "dungeon/item.h"
#include "engine/texture.h"

void select_sprite_entry(void *, u8, s32);             /* extern */
void advance_sprite_animation_and_textures(void *);                       /* extern */
s32 rsin(s32);                            /* extern */
s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *); /* extern */
s32 try_move_actor_to_valid_position(void *, void *, void *, void *); /* extern */
void kid_action_resume_address(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite_in, ActorRecord *entity);
extern u8 kid_direction_frames[12];
extern u8 kid_alt_direction_frames[12];
extern u8 kid_frame_set_1[12];
extern u8 kid_frame_set_2[12];
extern void *D_80175198[3];


typedef struct S_80170BF8_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170BF8_1;   /* arg1 in update_actor_callbacks_and_terrain */

   /* arg2 in update_actor_callbacks_and_terrain */

typedef struct S_80170BF8_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80170BF8_3;   /* actor2 in update_actor_callbacks_and_terrain */

/* Updates actor callbacks, movement, animation, and terrain-relative height. */
/* Runs Kid's callbacks and directional animation, alternates idle sprite tables, and adjusts bobbing
 * height to the terrain. */
void update_actor_callbacks_and_terrain(ActorRecord *actor_arg, ObjectPosition *motion_arg, void *object_arg) {
    u16 initial_flags = g_dungeon_status.flags;
    s32 bob_offset = 0;
    S_80170BF8_3 *actor_base = (S_80170BF8_3 *)actor_arg;

    ActorActionHandler update_callback;
    ActorActionHandler paused_callback;
    u8 *anim_table;
    u8 *hidden_anim_table;
    s16 base_height;
    s16 hidden_base_height;
    s16 height_offset;
    s16 hover_ground_offset;
    s16 ground_height;
    s16 hidden_ground_height;
    s16 hidden_hover_offset;
    s16 tile_height;
    s32 ground_offset;
    s32 ground_offset_2;
    s32 ground_offset_3;
    s32 ground_offset_4;
    s32 height_flags;
    s32 actor_flags;
    s32 hidden_actor_flags;
    s32 display_height;
    u32 frame_addr;
    u32 facing_flags;
    u16 motion_flags;
    u16 object_flags;
    u16 anim_flags;
    u16 hidden_anim_flags;
    s32 facing;
    s16 state_or_facing;
    if (initial_flags & 0x2000) {
        paused_callback = actor_arg->unk_8C.handler;
        if (paused_callback == &kid_action_resume_address) {
            paused_callback(actor_arg, motion_arg, object_arg, ({ void *actor_value = (actor_arg);  actor_value; }));
            return;
        }
        actor_arg->movement_queue_state = (u8) (actor_arg->movement_queue_state & 0x7F);
        return;
    }
    state_or_facing = (s8) actor_arg->pending_turn_updates;
    if (refresh_actor_facing_and_lifecycle(actor_arg, ((void *)(motion_arg)), object_arg, actor_arg) == 0) {
        update_callback = actor_arg->unk_8C.handler;
        if (update_callback != NULL) {
            update_callback(actor_arg, ((void *)(motion_arg)), object_arg, actor_arg);
        }
        ((void (*)(void *, void *, void *, void *))D_80175198[actor_arg->action_id.u])(actor_arg,
            ((void *)(motion_arg)), object_arg, actor_arg);
        if ((s16) state_or_facing != (s8) actor_arg->pending_turn_updates) {
            try_move_actor_to_valid_position(actor_arg, ((void *)(motion_arg)), object_arg, actor_arg);
        }
        motion_arg->x.v =
            (s32) (motion_arg->x.v
            + motion_arg->velocity_x);
        motion_arg->y.v =
            (s32) (motion_arg->y.v
            + motion_arg->velocity_y);
        if (!(actor_arg->flags1C & 0x40000) && !(actor_arg->action_state_flags & 8)) {
            motion_arg->velocity_z = (s32) (motion_arg->velocity_z
                + (actor_arg->unk_9D.s * 0x14000));
            actor_arg->unk_9D.u = (u8) (actor_arg->unk_9D.u + 1);
        } else {
            actor_arg->unk_9D.s = 0;
        }
        actor_arg->unk_90.value = (s32) (actor_arg->unk_90.value
            + motion_arg->velocity_z);
        object_flags = ((SpriteAnimationTableView *)object_arg)->flags;
        if (!(object_flags & 0x8000)) {
            facing = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor_base->unk_2A + 0x100) >> 9) & 7;
            state_or_facing = (s16) facing;
            if (actor_arg->unk_94 != state_or_facing) {
                select_indirect_table_entry(object_arg, *(((SpriteAnimationTableView *)object_arg)->frame_table + state_or_facing),
                    ((SpriteAnimationTableView *)object_arg)->frame_index);
                actor_arg->unk_94 = facing;
            }
            if (dir_sprite_flag[state_or_facing] != 0) {
                facing_flags = ((SpriteAnimationTableView *)object_arg)->flags;
                facing_flags |= 1;
            } else {
                facing_flags = ((SpriteAnimationTableView *)object_arg)->flags & 0xFFFE;
            }
            ((SpriteAnimationTableView *)object_arg)->flags = (u16) facing_flags;
            if (actor_arg->action_id.u != 8) {
                apply_monster_koyaw_data(actor_base->unk_1C, object_arg + 0xC);
            }
            if (!(actor_base->unk_1C & 0x20)) {
                if (!(((SpriteAnimationTableView *)object_arg)->flags & 0x40)) {
                    advance_sprite_animation_and_textures(object_arg);
                }
            } else {
                ((SpriteAnimationTableView *)object_arg)->flags = (u16) (((SpriteAnimationTableView *)object_arg)->flags | 0x7000);
                actor_base->unk_1C = (s32) (actor_base->unk_1C & 0xFFFBFFFF);
            }
            actor_flags = actor_base->unk_1C & 0xF7FFFFFF;
            actor_base->unk_1C = actor_flags;
            if (actor_flags & 0x40000) {
                if (!(((SpriteAnimationTableView *)object_arg)->flags & 0x40)) {
                    anim_flags = actor_arg->action_state_flags;
                    if (anim_flags & 0x8000) {
                        actor_arg->action_state_flags = (u16) (anim_flags & 0x7FFF);
                        anim_table = ((SpriteAnimationTableView *)object_arg)->frame_table;
                        if (anim_table == kid_alt_direction_frames) {
                            ((SpriteAnimationTableView *)object_arg)->frame_table = kid_direction_frames;
                            frame_addr = (u32) ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor_base->unk_2A
                                + 0x100) >> 9) & 7));
                            frame_addr += (u32) kid_direction_frames;
                            select_sprite_entry(object_arg, *(u8 *) frame_addr, 0);
                        } else if (anim_table == kid_direction_frames) {
                            ((SpriteAnimationTableView *)object_arg)->frame_table = kid_alt_direction_frames;
                            frame_addr = (u32) ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor_base->unk_2A
                                + 0x100) >> 9) & 7));
                            frame_addr += (u32) kid_alt_direction_frames;
                            select_sprite_entry(object_arg, *(u8 *) frame_addr, 0);
                        } else if (anim_table == kid_frame_set_1) {
                            ((SpriteAnimationTableView *)object_arg)->frame_table = kid_frame_set_2;
                            frame_addr = (u32) ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor_base->unk_2A
                                + 0x100) >> 9) & 7));
                            frame_addr += (u32) kid_frame_set_2;
                            select_sprite_entry(object_arg, *(u8 *) frame_addr, 0);
                        } else if (anim_table == kid_frame_set_2) {
                            ((SpriteAnimationTableView *)object_arg)->frame_table = kid_frame_set_1;
                            frame_addr = (u32) ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor_base->unk_2A
                                + 0x100) >> 9) & 7));
                            frame_addr += (u32) kid_frame_set_1;
                            select_sprite_entry(object_arg, *(u8 *) frame_addr, 0);
                        }
                    }
                    if (((SpriteAnimationTableView *)object_arg)->flags & 0x6000) {
                        actor_arg->action_state_flags = (u16) (actor_arg->action_state_flags | 0x8000);
                        if (((SpriteAnimationTableView *)object_arg)->frame_table == kid_direction_frames) {
                            actor_arg->unk_A8.s = 0;
                        }
                    }
                    bob_offset = rsin((actor_arg->unk_A8.s << 0xC) / 20) >> 0xA;
                    actor_arg->unk_A8.s = (s16) ((u16) actor_arg->unk_A8.s + 1);
                }
                if (!(actor_arg->action_state_flags & 8)) {
                    hover_ground_offset = (s16) (sample_terrain_surface_height(((S_80170BF8_1 *)((void *)(motion_arg)))->unk_00.at02.v,
                        ((S_80170BF8_1 *)((void *)(motion_arg)))->unk_04.at02.v,
                        (s16) (actor_base->unk_88.u - 0x20))
                        - actor_base->unk_88.u);
                    if (actor_arg->unk_90.parts.high.s > (hover_ground_offset - 0x20)) {
                        actor_arg->unk_90.parts.high.s =
                            (s16) (((u16) actor_arg->unk_90.parts.high.s) - 8);
                    } else if (actor_arg->unk_90.parts.high.s < (hover_ground_offset - 0x2A)) {
                        actor_arg->unk_90.parts.high.s =
                            (s16) (((u16) actor_arg->unk_90.parts.high.s) + 8);
                    }
                }
            } else {
                motion_flags = actor_arg->action_state_flags;
                actor_arg->unk_A8.s = 0;
                actor_arg->action_state_flags = (u16) (motion_flags & 0x7FFF);
                if (!(motion_flags & 8)) {
                    ground_offset = sample_terrain_surface_height(((S_80170BF8_1 *)((void *)(motion_arg)))->unk_00.at02.v,
                        ((S_80170BF8_1 *)((void *)(motion_arg)))->unk_04.at02.v,
                        (s16) (actor_base->unk_88.u - 0x20));
                    ground_height = (s16) ground_offset;
                    base_height = actor_base->unk_88.s;
                    ground_offset_2 = (s32) ground_height - base_height;
                    if (ground_offset_2 < actor_arg->unk_90.parts.high.s) {
                        actor_arg->unk_90.parts.high.s = ground_offset_2;
                        actor_arg->unk_9D.s = 0;
                        motion_arg->velocity_z = 0;
                        actor_base->unk_1C = actor_base->unk_1C | 0x08000000;
                    }
                }
            }
        } else {
            ((SpriteAnimationTableView *)object_arg)->flags = (object_flags & 0x800)
                ? (object_flags & 0x8FFF) : (object_flags | 0x7000);
            hidden_actor_flags = actor_base->unk_1C & 0xF7FFFFFF;
            actor_base->unk_1C = hidden_actor_flags;
            if (!(hidden_actor_flags & 0x40000)) {
                actor_arg->unk_A8.s = 0;
                actor_arg->unk_90.parts.high.s = (s16) ((u16) actor_arg->unk_90.parts.high.s
                    - bob_offset);
                bob_offset = 0;
                if (!(actor_arg->action_state_flags & 8)) {
                    ground_offset_3 = sample_terrain_surface_height(((S_80170BF8_1 *)((void *)(motion_arg)))->unk_00.at02.v,
                        ((S_80170BF8_1 *)((void *)(motion_arg)))->unk_04.at02.v,
                        (s16) (actor_base->unk_88.u - 0x20));
                    hidden_ground_height = (s16) ground_offset_3;
                    hidden_base_height = actor_base->unk_88.s;
                    ground_offset_4 = (s32) hidden_ground_height - hidden_base_height;
                    if (ground_offset_4 < actor_arg->unk_90.parts.high.s) {
                        actor_arg->unk_90.parts.high.s = ground_offset_4;
                        actor_arg->unk_9D.s = 0;
                        motion_arg->velocity_z = 0;
                        actor_base->unk_1C = actor_base->unk_1C | 0x08000000;
                    }
                }
            } else {
                if (!(((SpriteAnimationTableView *)object_arg)->flags & 0x40)) {
                    hidden_anim_flags = actor_arg->action_state_flags;
                    if (hidden_anim_flags & 0x8000) {
                        actor_arg->action_state_flags = (u16) (hidden_anim_flags & 0x7FFF);
                        hidden_anim_table = ((SpriteAnimationTableView *)object_arg)->frame_table;
                        if (hidden_anim_table == kid_alt_direction_frames) {
                            ((SpriteAnimationTableView *)object_arg)->frame_table = kid_direction_frames;
                            frame_addr = (u32) ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor_base->unk_2A
                                + 0x100) >> 9) & 7));
                            frame_addr += (u32) kid_direction_frames;
                            select_sprite_entry(object_arg, *(u8 *) frame_addr, 0);
                        } else if (hidden_anim_table == kid_direction_frames) {
                            ((SpriteAnimationTableView *)object_arg)->frame_table = kid_alt_direction_frames;
                            frame_addr = (u32) ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor_base->unk_2A
                                + 0x100) >> 9) & 7));
                            frame_addr += (u32) kid_alt_direction_frames;
                            select_sprite_entry(object_arg, *(u8 *) frame_addr, 0);
                        } else if (hidden_anim_table == kid_frame_set_1) {
                            ((SpriteAnimationTableView *)object_arg)->frame_table = kid_frame_set_2;
                            frame_addr = (u32) ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor_base->unk_2A
                                + 0x100) >> 9) & 7));
                            frame_addr += (u32) kid_frame_set_2;
                            select_sprite_entry(object_arg, *(u8 *) frame_addr, 0);
                        } else if (hidden_anim_table == kid_frame_set_2) {
                            ((SpriteAnimationTableView *)object_arg)->frame_table = kid_frame_set_1;
                            frame_addr = (u32) ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor_base->unk_2A
                                + 0x100) >> 9) & 7));
                            frame_addr += (u32) kid_frame_set_1;
                            select_sprite_entry(object_arg, *(u8 *) frame_addr, 0);
                        }
                    }
                    if (((SpriteAnimationTableView *)object_arg)->flags & 0x6000) {
                        actor_arg->action_state_flags = (u16) (actor_arg->action_state_flags | 0x8000);
                        if (((SpriteAnimationTableView *)object_arg)->frame_table == kid_direction_frames) {
                            actor_arg->unk_A8.s = 0;
                        }
                    }
                    bob_offset = rsin((actor_arg->unk_A8.s << 0xC) / 20) >> 0xA;
                    actor_arg->unk_A8.s = (s16) ((u16) actor_arg->unk_A8.s + 1);
                }
                if (!(actor_arg->action_state_flags & 8)) {
                    hidden_hover_offset = sample_terrain_surface_height(((S_80170BF8_1 *)((void *)(motion_arg)))->unk_00.at02.v,
                        ((S_80170BF8_1 *)((void *)(motion_arg)))->unk_04.at02.v,
                        (s16) (actor_base->unk_88.u - 0x20)) - actor_base->unk_88.u;
                    height_offset = actor_arg->unk_90.parts.high.s;
                    if (height_offset > (hidden_hover_offset - 0x20)) {
                        actor_arg->unk_90.parts.high.s =
                            (s16) (((u16) actor_arg->unk_90.parts.high.s) - 8);
                    } else if (height_offset < (hidden_hover_offset - 0x2A)) {
                        actor_arg->unk_90.parts.high.s =
                            (s16) (((u16) actor_arg->unk_90.parts.high.s) + 8);
                    }
                }
            }
            actor_arg->unk_A8.s = 0;
            actor_arg->action_state_flags = (u16) (actor_arg->action_state_flags & 0x7FFF);
        }
        height_flags = actor_base->unk_1C;
        if (height_flags & 0x40000000) {
            actor_base->unk_1C = (s32) (height_flags & 0xBFFFFFFF);
            tile_height = sample_terrain_surface_height((((SpriteAnimationTableView *)object_arg)->tile_x << 6) | 0x20,
                (((SpriteAnimationTableView *)object_arg)->tile_y << 6) | 0x20,
                (s16) (actor_base->unk_88.u - 0x20));
            if (tile_height < 0x200) {
                actor_arg->unk_90.parts.high.s = (s16) ((u16) actor_arg->unk_90.parts.high.s
                    + (actor_base->unk_88.u - tile_height));
                actor_base->unk_88.u = (u16) tile_height;
            }
        }
        display_height = (s32) (actor_base->unk_88.u
            + (u16) actor_arg->unk_90.parts.high.s + bob_offset);
        motion_arg->z.w.i = (s16) display_height;
        ((SpriteAnimationTableView *)object_arg)->flags = (u16) (((SpriteAnimationTableView *)object_arg)->flags | 0x40);
    }
}

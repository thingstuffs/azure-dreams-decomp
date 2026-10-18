#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "records/Rec_func_800AA258_arg2.h"

extern void func_8003DB94(void *, void *, s32);
extern s32 find_active_rect_containing_point(s32, s32);
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void advance_actor_queued_path(void *, void *, void *, void *);
extern void advance_actor_traversable_heading(void *, void *, void *, void *);
extern void install_actor_action_handler_after_floor_trap_check(void *, void *, void *, void *);

extern void *D_800E262C[];


/* Updates actor state, facing, and directional animation. */
void update_actor_facing_animation(void *actor, EntityRec *motion, void *sprite, EntityRec *status)
{
    void **anim_table;
    s32 cell_record;
    s32 direction_aux;

    if (g_dungeon_status.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        advance_actor_queued_path(actor, motion, sprite, status);
        return;
    }

    if (status->tileY == 0) {
        void *current_anim;

        advance_actor_pending_action(actor, motion, sprite, status);
        current_anim = ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv;
        anim_table = D_800E262C;
        if (current_anim == anim_table) {
            return;
        }
    } else {

        if (((u32)status->flags1C) & 0x200) {
            if (((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv == D_800E262C) {
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xD;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 1;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
                status->flags1C &= ~0x40000;
                return;
            }
            if (reset_actor_action_state(actor, motion, sprite, 0)) {
                return;
            }
        }

        if (!(g_dungeon_status.flags & 0x2000)) {
            if (((u32)status->flags1C) & 0x100) {
                begin_pushed_actor_move(actor, motion, sprite, status);
                return;
            }

            if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
                u8 next_state = 0xE;

                anim_table = D_800E262C;
                if (((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv != anim_table) {
                    (*(void * *)((u8 *)sprite + (0x2C))) = anim_table;
                    func_8003DB94(sprite,
                        *(void **)((u8 *)anim_table +
                            (((g_game_work.view.viewAngle + status->facing + 0x100) >> 7) & 0x1C)),
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = next_state;
            }

            ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF3;
            if (status->unk_64 != 0) {
                if (begin_ready_actor_directional_action(actor, motion, sprite, 0)) {
                    return;
                }
            }

            if (((u32)status->flags1C) & 0x80000) {
                ((Rec_func_800A9E70_arg0 *)actor)->unk_90.at00_s32.v = 0;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFFE;
                motion->flags14 = 0;
                begin_actor_move_to_target_facing(actor, motion, sprite, status);
                install_actor_action_handler_after_floor_trap_check(actor, motion, sprite, status);
                return;
            }

            if ((s16)can_entity_gain_level(status) != 0) {
                process_selected_actor_record(actor, motion, sprite, status);
            }
        }

        cell_record = find_active_rect_containing_point(((Rec_func_800AA258_arg2 *)sprite)->unk_24,
            ((Rec_func_800AA258_arg2 *)sprite)->unk_25);
        ((Rec_func_800AA258_arg2 *)sprite)->unk_26.as_u8 = cell_record;

        if (status->unk_6D > 0) {
            if (((u32)status->flags1C) & 0x20) {
                update_actor_status_and_food(status);
                return;
            }
            advance_actor_traversable_heading(actor, motion, sprite, status);
            return;
        }

        if (!(((u32)status->flags1C) & 0x2000)) {
            s32 record_index = (s8)cell_record;

            if ((record_index < 0) ||
                !(D_800E2970[record_index].flags & 2)) {
                if (!(((u32)status->flags1C) & 0x430)) {

                    if ((s16)compare_monster_neighbor_values(((Rec_func_800AA258_arg2 *)sprite)->unk_24,
                            ((Rec_func_800AA258_arg2 *)sprite)->unk_25, D_80082E80.tileX,
                            D_80082E80.tileY) != 0) {
                        status->facing = get_rounded_facing_and_rounding_flag(
                            ((Rec_func_800AA258_arg2 *)sprite)->unk_24, ((Rec_func_800AA258_arg2 *)sprite)->unk_25,
                            D_80082E80.tileX, D_80082E80.tileY,
                            &direction_aux);
                    }
                }
            }
        }

        if (g_dungeon_status.flags & 0x2000) {
            return;
        }
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0x40) {
            return;
        }
        anim_table = D_800E262C;
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv == anim_table) {
            return;
        }
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_98 & 1) {
            return;
        }
    }
    (*(void * *)((u8 *)sprite + (0x2C))) = anim_table;
    func_8003DB94(sprite,
        *(void **)((((g_game_work.view.viewAngle + status->facing + 0x100) >> 7) & 0x1C) +
            (u32)anim_table),
        0);
}

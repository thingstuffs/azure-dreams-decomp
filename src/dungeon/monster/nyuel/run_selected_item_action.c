#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

extern s32 get_cd_command_queue_depth(void);
extern void select_sprite_entry(void *, s32, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void create_actor_linked_effect(void *);

extern u8 D_80170E9C[];
extern u8 D_80174EE0[];

typedef struct S_8017293C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_8017293C_0;   /* arg0 in run_selected_item_action */

typedef struct S_8017293C_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017293C_1_pre;   /* the 0x14 bytes before active in run_selected_item_action, addressed as active[-1] */

typedef struct S_8017293C_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017293C_2;   /* linked in run_selected_item_action */

typedef struct S_8017293C_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8017293C_5;   /* global in run_selected_item_action */

/* Runs the actor's selected item action and handles its wait and completion phases. */
void run_selected_item_action(void *action, ObjectPosition *motion, void *sprite, void *actor)
{
    s32 is_special;
    u8 *item_slot;
    void *target;
    u8 *scratch_pointer;

    is_special = 0;
    item_slot = (u8 *)(((S_8017293C_0 *)action)->unk_9B);
    switch ((u8)item_slot) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
            u32 kind_index;

            kind_index = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
            switch (kind_index) {
            case 7:
                is_special = 1;
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 6:
                is_special = 1;
                /* fall through */
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 5:
                is_special = 1;
                /* fall through */
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            s32 item_kind;

            item_kind = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
            switch (item_kind) {
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        }
        if (*item_slot != 0) {
            ((S_8017293C_0 *)action)->unk_98 &= 0xFF7F;
            {
                s16 use_special;

                use_special = is_special;
                if (use_special != 0) {
                    target = D_800814A8;
                    (*(void * *)((u8 *)actor + 0x60)) = target;
                    scratch_pointer = ((S_8017293C_1_pre *)target)[-1].unk_00;
                    (*(u8 *)((u8 *)actor + 0x72)) = ((S_8017293C_2 *)scratch_pointer)->unk_24;
                    (*(u8 *)((u8 *)actor + 0x73)) = ((S_8017293C_2 *)scratch_pointer)->unk_25;
                } else {
                    u8 item_id;

                    item_id = *item_slot;
                    if (D_8006DE24[item_id].kind == 2) {
                        target = (*(void * *)((u8 *)actor + 0x60));
                        if (target != 0) {
                            scratch_pointer = ((S_8017293C_1_pre *)target)[-1].unk_00;
                            (*(u8 *)((u8 *)actor + 0x72)) = ((S_8017293C_2 *)scratch_pointer)->unk_24;
                            (*(u8 *)((u8 *)actor + 0x73)) = ((S_8017293C_2 *)scratch_pointer)->unk_25;

                        }
                    } else {
                        s32 dx;
                        s32 dy;

                        dx = (s32)scan_monster_along_heading(
                            actor, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25,
                            (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
                        (*(void * volatile *)((u8 *)actor + 0x60)) = (void *)dx;
                        dx = (*(s8 *)((u8 *)actor + 0x72));
                        dy = (*(s8 *)((u8 *)actor + 0x73));
                        if (dx < 0) {
                            dx = -dx;
                        }
                        if (dy < 0) {
                            dy = -dy;
                        }
                        (*(u8 *)((u8 *)actor + 0x72)) = dx;
                        (*(u8 *)((u8 *)actor + 0x73)) = dy;
                    }
                }

            }

            if (create_actor_spell_effect(actor, item_slot, is_special,
                (u8 *)action + 0x98) == 0) {
                return;
            }
            create_actor_linked_effect(actor);
            ((S_8017293C_0 *)action)->unk_9B++;
            return;

        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        advance_status_timers(actor);
        (*(u8 *)((u8 *)actor + 0x6D))--;
        ((S_8017293C_0 *)action)->unk_8C = D_80170E9C;
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            return;
        }
        ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        ((S_8017293C_0 *)action)->unk_9B++;

    case 2:
        if ((((SpriteFrameState *)sprite)->unk_04 == 3 &&
            (((SpriteFrameState *)sprite)->flags & 0x1000)) ||
            (((SpriteFrameState *)sprite)->flags & 0xE000)) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            ((S_8017293C_0 *)action)->unk_96 = 1;
            ((S_8017293C_0 *)action)->unk_98 |= 0x80;
        }
        {
            s16 wait_ticks;

            wait_ticks = ((S_8017293C_0 *)action)->unk_96 - 1;
            ((S_8017293C_0 *)action)->unk_96 = wait_ticks;
            if (wait_ticks <= 0) {
                ((S_8017293C_0 *)action)->unk_96 = 0;
                ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            }
        }
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable != D_80174EE0) {
            u8 *direction_frames;
            s32 direction;

            direction_frames = D_80174EE0;
            ((SpriteFrameState *)sprite)->frameTable = direction_frames;
            direction = ((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, direction_frames[direction], 0);
        }
        {
            scratch_pointer = (u8 *)&g_dungeon_status.turn_scale;
            if (((S_8017293C_5 *)scratch_pointer)->unk_0C != 0) {
                return;
            }
            ((S_8017293C_5 *)scratch_pointer)->unk_0A--;
            ((S_8017293C_0 *)action)->unk_8C = D_80170E9C;
            advance_status_timers(actor);
            (*(u8 *)((u8 *)actor + 0x73)) = 0;
            (*(u8 *)((u8 *)actor + 0x72)) = 0;
            (*(u8 *)((u8 *)actor + 0x6D))--;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            play_sound_if_enabled(0xB4);
        }

        return;
    default:
        return;
    }
}

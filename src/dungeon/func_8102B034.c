#include "common.h"
extern int abs(int);
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

typedef struct ItemSlots {
    u8 pad_00[8];
    u8 first;
    u8 pad_09[2];
    u8 second;
    u8 pad_0C[2];
    u8 third;
} ItemSlots;

typedef struct PlayerActionCounter {
    u8 pad_00[0xA6];
    u16 pendingActions;
} PlayerActionCounter;



typedef struct ActionState {
    u8 pad_00[0x8C];
    void * handler;
    u8 pad_90[0x8];
    u16 flags;
    u8 pad_9A[0x1];
    u8 phase;
} ActionState;

typedef struct ObjectHeaderTail {
    void * sprite;
    u8 pad_04[0x10];
} ObjectHeaderTail;   /* the 0x14 bytes before object in start_actor_action_and_reset, addressed as object[-1] */

typedef struct TilePosition {
    u8 pad_00[0x24];
    u8 tileX;
    u8 tileY;
} TilePosition;

extern s32 get_cd_command_queue_depth(void);
extern void func_80047784(void *, s32, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *, u8 *, s32, u16 *);
extern void create_two_row_object_group(u16 *, s32);

extern u8 D_8014D058[];
extern u8 D_80150888[];

/* Starts the selected actor action, waits for completion, and resets its state. */
void start_actor_action_and_reset(ActionState *action_state, EntityRec *motion, SpriteAnimationTableView *sprite, EntityRec *actor)
{
    u8 *item_slot;
    s32 phase;
    s32 use_player_target;
    void *target;
    s16 flags_or_target_mode;
    TilePosition *target_sprite;
    u16 position[3];

    phase = action_state->phase;
    use_player_target = 0;
    switch (phase) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->unk_46 & 0x3FFF) {
            case 7:
                use_player_target = 1;
                /* fall through */
            case 3:
                item_slot = &((ItemSlots *)actor)->third;
                break;
            case 6:
                use_player_target = 1;
                /* fall through */
            case 2:
                item_slot = &((ItemSlots *)actor)->second;
                break;
            case 5:
                use_player_target = 1;
                /* fall through */
            case 1:
                item_slot = &((ItemSlots *)actor)->first;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            switch (actor->unk_46 & 0x3FFF) {
            case 3:
                item_slot = &((ItemSlots *)actor)->third;
                break;
            case 2:
                item_slot = &((ItemSlots *)actor)->second;
                break;
            case 1:
                item_slot = &((ItemSlots *)actor)->first;
                break;
            default:
                item_slot = 0;
                break;
            }
        }
        if (*item_slot != 0) {
            flags_or_target_mode = action_state->flags;
            flags_or_target_mode &= 0xFF7F;
            action_state->flags = flags_or_target_mode;
            flags_or_target_mode = use_player_target;
            if (flags_or_target_mode != 0) {
                target = D_800814A8;
                actor->target = target;
                target_sprite = ((ObjectHeaderTail *)target)[-1].sprite;
                actor->unk_72 = target_sprite->tileX;
                actor->unk_73 = target_sprite->tileY;
            } else if (D_8006DE24[*item_slot].kind == 2) {
                target = actor->target;
                if (target != 0) {
                    target_sprite = ((ObjectHeaderTail *)target)[-1].sprite;
                    actor->unk_72 = target_sprite->tileX;
                    actor->unk_73 = target_sprite->tileY;
                }
            } else {
                actor->target =
                    scan_monster_along_heading(actor,
                                  sprite->unk_24,
                                  sprite->unk_25,
                                  actor->facing, 0x10);
                {
                    s32 abs_x = abs(actor->unk_72);
                    s32 abs_y = abs(actor->unk_73);
                    actor->unk_72 = abs_x;
                    actor->unk_73 = abs_y;
                }
            }

            position[0] = ((u16)motion->x.w.i);
            position[1] = ((u16)motion->y.w.i);
            position[2] = ((u16)motion->z.w.i);
            if (create_actor_spell_effect(actor, item_slot, use_player_target,
                              &action_state->flags) == 0) {
                return;
            }
            sprite->unk_14 &= 0xF7FF;
            create_two_row_object_group(position, (s16)(((s32)*item_slot - 1) % 3));
            play_sound_if_enabled(0x703);
            action_state->phase++;
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);
        g_dungeon_status.unk_0C = 0;
        ((PlayerActionCounter *)D_800814A8)->pendingActions--;
        advance_status_timers(actor);
        (*(u8 *)&actor->unk_6D)--;
        action_state->handler = D_8014D058;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->unk_14 |= 0x800;
            return;
        }
        sprite->unk_14 &= 0xF7FF;
        action_state->phase++;

    case 2:
        if (!((sprite->unk_04 == 3) &&
              (sprite->unk_14 & 0x1000)) &&
            !(sprite->unk_14 & 0xE000)) {
            return;
        }
        action_state->flags |= 0x80;
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);
        if (sprite->unk_2C != D_80150888) {
            sprite->unk_2C = D_80150888;
            func_80047784(
                sprite,
                D_80150888[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        {

            if (((s32)g_dungeon_status.unk_0C) != 0) {
                return;
            }
            g_dungeon_status.unk_0A--;
        }
        sprite->unk_14 &= 0xF7FF;
        action_state->handler = D_8014D058;
        advance_status_timers(actor);
        if (actor->unk_6D > 0) {
            (*(u8 *)&actor->unk_6D)--;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);

        return;
    default:
        return;
    }
}

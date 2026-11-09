#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "sdk/libc.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/monster/death.h"
#include "dungeon/monster/metal.h"
#include "dungeon/system.h"
#include "dungeon/data.h"

extern void select_sprite_entry(void *, s32, s32);

extern u8 metal_action_resume_address[];

/* Updates an item action, its animation, particle effects, and completion state. */
/* Starts a targeted spell with returning particles and a 20-particle burst, then restores idle after a
 * 32-tick wait. */
void update_item_action_animation_and_effects(ActorRecord *action, ObjectPosition *movement, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 *item_slot;
    s16 special;
    s32 count;
    s32 next_state;
    u8 state;
    ObjectNodeHeader *target;

    special = 0;
    state = action->action_phase;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        if ((u32)actor->flags1C & ACTOR_PLAYER_SIDE) {
            switch (actor->action_flags & 0x3FFF) {
            case 7:
                special = 1;
                /* fallthrough */
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 6:
                special = 1;
                /* fallthrough */
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 5:
                special = 1;
                /* fallthrough */
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            switch (actor->action_flags & 0x3FFF) {
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
            SpriteFrameState *item_id;

            action->action_state_flags &= 0xFF7F;
            if (special != 0) {
                target = (ObjectNodeHeader *)primary_actor_record;
                actor->target = target;
                item_id = (target - 1)->sprite;
                actor->target_tile_x = item_id->tile_x;
                actor->target_tile_y = item_id->tile_y;
            } else {
                item_id = (SpriteFrameState *)(*item_slot);
                if (item_action_definitions[((u8)item_id)].kind == 2) {
                    target = actor->target;
                    if (target != 0) {
                        item_id = (target - 1)->sprite;
                        actor->target_tile_x = item_id->tile_x;
                        actor->target_tile_y = item_id->tile_y;
                    }
                } else {
                    s32 dx;
                    s32 dy;

                    dx = (s32)scan_actor_along_heading(
                        actor, sprite->tile_x, sprite->tile_y,
                        actor->facing, 0x10);
                    actor->target = (void *)dx;
                    dx = abs(actor->target_tile_x);
                    dy = abs(actor->target_tile_y);
                    actor->target_tile_x = dx;
                    actor->target_tile_y = dy;
                }
            }

                if (create_actor_spell_effect(actor, item_slot, special, (u8 *)action + 0x98) == 0) {
                return;
        }
        next_state = action->action_phase + 1;
        action->action_phase = next_state;
        return;
        }

        movement->velocity_z = 0;
        movement->velocity_y = 0;
        movement->velocity_x = 0;
        set_record_integer_tile_center(movement, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        primary_actor_record->unk_A4.halves.high.u--;
        advance_status_timers(actor);
        actor->pending_turn_updates = (u8)((u8)actor->pending_turn_updates - 1);
        action->unk_8C.address = metal_action_resume_address;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        action->action_phase++;
        play_sound_if_enabled(0x703);

    case 2:
        {
            u16 flags;
            s16 timer;

            flags = sprite->flags;
            if (flags & 0x8000) {
                next_state = action->action_phase + 1;
                action->action_timer = 0;
                action->action_phase = next_state;
                return;
            }
            if (sprite->unk_04 == 2 && (flags & 0x1000)) {
                sprite->flags = flags | 0x800;
                action->action_timer = 0x16;
            }
            if (sprite->unk_04 < 2) {
                return;
            }
            timer = action->action_timer - 1;
            action->action_timer = timer;
            if (timer <= 0) {
                action->action_timer = 0;
                action->action_phase++;
                sprite->flags &= 0xF7FF;
            }
            if (action->action_timer < 7) {
                return;
            }
        }

        count = 0;
        do {
            register s32 x;
            register s32 y;
            s16 z;

            count++;
            sprite = (void *)(rand() & 0xFF);
            sprite = (void *)((u32)sprite | 0x80);
            x = rand();
            x &= 0x7F;
            x -= 0x40;
            x <<= 16;
            x >>= 16;
            y = rand();
            y &= 0x7F;
            y -= 0x40;
            y <<= 16;
            y >>= 16;
            z = (rand() & 0x7F) - 0x40;
            create_parent_return_effect(NODE_HEADER(action), 0, 0x00C0C0C0,
                          (s32)sprite, x, y, z);
        } while ((u16)count < 5);
        return;

    case 3:
        if ((sprite->unk_04 == 4 &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x800;
            action->action_timer = 0x20;
            action->action_state_flags |= 0x80;
            action->action_phase++;
            count = 0;
            do {
                s32 brightness;

                count++;
                brightness = (rand() & 0xFF) | 0x80;
                spawn_parent_offset_random_motion_effect(NODE_HEADER(action), 0, 0x00C0C0C0,
                              brightness, 0, 0, 0);
            } while ((u16)count < 20);
        }
    case 4:
        {
            s16 timer;

            if ((g_dungeon_status.active_actor) == 0) {
                action->action_timer = 0;
            }
            timer = action->action_timer - 1;
            action->action_timer = timer;
            if (timer <= 0) {
                action->action_timer = 0;
                sprite->flags &= 0xF7FF;
            }
            if (!(sprite->flags & 0xE000)) {
                return;
            }
            movement->velocity_z = 0;
            movement->velocity_y = 0;
            movement->velocity_x = 0;
            set_record_integer_tile_center(movement, sprite->tile_x, sprite->tile_y);
            if (*(u8 * *)&sprite->frameTable != metal_frame_set_1) {
                u8 *animation_table;
                s32 direction;

                animation_table = metal_frame_set_1;
                sprite->frameTable = animation_table;
                direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
                select_sprite_entry(sprite, animation_table[direction], 0);
            }
            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            action->unk_8C.address = metal_action_resume_address;
            advance_status_timers(actor);
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            actor->pending_turn_updates = (u8)((u8)actor->pending_turn_updates - 1);
            actor->action_flags &= 0x7FFF;
            play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        }
    }
}

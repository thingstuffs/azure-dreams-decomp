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

extern void select_sprite_entry(void *, s32, s32);
extern s32 rand(void);
extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern void play_sound_if_enabled(s32);
extern void *create_actor_spell_effect(void *actor, void *effect_record, s16 mode, void *context);
extern void create_parent_return_effect(void *, s32, s32, s32, s32, s32, s32);
extern void spawn_parent_offset_random_motion_effect(void *, s32, s32, s32, s32, s32, s32);

extern u8 metal_action_resume_address[];
extern u8 metal_frame_set_1[];

typedef struct S_80173078_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80173078_0;   /* arg0 in update_item_action_animation_and_effects */

typedef struct S_80173078_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173078_2;   /* linked in update_item_action_animation_and_effects */

/* Updates an item action, its animation, particle effects, and completion state. */
/* Starts a targeted spell with returning particles and a 20-particle burst, then restores idle after a
 * 32-tick wait. */
void update_item_action_animation_and_effects(void *action, ObjectPosition *movement, SpriteFrameState *sprite, void *actor)
{
    u8 *item_slot;
    s16 special;
    s32 count;
    s32 next_state;
    u8 state;
    void *target;

    special = 0;
    state = ((S_80173078_0 *)action)->unk_9B;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & ACTOR_PLAYER_SIDE) {
            switch ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) {
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
            switch ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) {
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
            u8 *item_id;

            ((S_80173078_0 *)action)->unk_98 &= 0xFF7F;
            if (special != 0) {
                target = primary_actor_record;
                (*(void * *)((u8 *)actor + 0x60)) = target;
                item_id = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                (*(u8 *)((u8 *)actor + 0x72)) = ((S_80173078_2 *)item_id)->unk_24;
                (*(u8 *)((u8 *)actor + 0x73)) = ((S_80173078_2 *)item_id)->unk_25;
            } else {
                item_id = (u8 *)(*item_slot);
                if (item_action_definitions[((u8)item_id)].kind == 2) {
                    target = (*(void * *)((u8 *)actor + 0x60));
                    if (target != 0) {
                        item_id = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                        (*(u8 *)((u8 *)actor + 0x72)) = ((S_80173078_2 *)item_id)->unk_24;
                        (*(u8 *)((u8 *)actor + 0x73)) = ((S_80173078_2 *)item_id)->unk_25;
                    }
                } else {
                    s32 dx;
                    s32 dy;

                    dx = (s32)scan_actor_along_heading(
                        actor, sprite->tile_x, sprite->tile_y,
                        (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
                    (*(void * *)((u8 *)actor + 0x60)) = (void *)dx;
                    dx = abs(*(s8 *)((u8 *)actor + 0x72));
                    dy = abs(*(s8 *)((u8 *)actor + 0x73));
                    (*(u8 *)((u8 *)actor + 0x72)) = dx;
                    (*(u8 *)((u8 *)actor + 0x73)) = dy;
                }
            }

                if (create_actor_spell_effect(actor, item_slot, special, (u8 *)action + 0x98) == 0) {
                return;
        }
        next_state = ((S_80173078_0 *)action)->unk_9B + 1;
        ((S_80173078_0 *)action)->unk_9B = next_state;
        return;
        }

        movement->velocity_z = 0;
        movement->velocity_y = 0;
        movement->velocity_x = 0;
        set_record_integer_tile_center(movement, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
        advance_status_timers(actor);
        (*(u8 *)((u8 *)actor + 0x6D))--;
        ((S_80173078_0 *)action)->unk_8C = metal_action_resume_address;
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        ((S_80173078_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x703);

    case 2:
        {
            u16 flags;
            s16 timer;

            flags = sprite->flags;
            if (flags & 0x8000) {
                next_state = ((S_80173078_0 *)action)->unk_9B + 1;
                ((S_80173078_0 *)action)->unk_96.u = 0;
                ((S_80173078_0 *)action)->unk_9B = next_state;
                return;
            }
            if (sprite->unk_04 == 2 && (flags & 0x1000)) {
                sprite->flags = flags | 0x800;
                ((S_80173078_0 *)action)->unk_96.u = 0x16;
            }
            if (sprite->unk_04 < 2) {
                return;
            }
            timer = ((S_80173078_0 *)action)->unk_96.u - 1;
            ((S_80173078_0 *)action)->unk_96.u = timer;
            if (timer <= 0) {
                ((S_80173078_0 *)action)->unk_96.u = 0;
                ((S_80173078_0 *)action)->unk_9B++;
                sprite->flags &= 0xF7FF;
            }
            if (((S_80173078_0 *)action)->unk_96.s < 7) {
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
            create_parent_return_effect((u8 *)action - 0x20, 0, 0x00C0C0C0,
                          (s32)sprite, x, y, z);
        } while ((u16)count < 5);
        return;

    case 3:
        if ((sprite->unk_04 == 4 &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x800;
            ((S_80173078_0 *)action)->unk_96.u = 0x20;
            ((S_80173078_0 *)action)->unk_98 |= 0x80;
            ((S_80173078_0 *)action)->unk_9B++;
            count = 0;
            do {
                s32 brightness;

                count++;
                brightness = (rand() & 0xFF) | 0x80;
                spawn_parent_offset_random_motion_effect((u8 *)action - 0x20, 0, 0x00C0C0C0,
                              brightness, 0, 0, 0);
            } while ((u16)count < 20);
        }
    case 4:
        {
            s16 timer;

            if ((g_dungeon_status.active_actor) == 0) {
                ((S_80173078_0 *)action)->unk_96.u = 0;
            }
            timer = ((S_80173078_0 *)action)->unk_96.u - 1;
            ((S_80173078_0 *)action)->unk_96.u = timer;
            if (timer <= 0) {
                ((S_80173078_0 *)action)->unk_96.u = 0;
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
                direction = ((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
                select_sprite_entry(sprite, animation_table[direction], 0);
            }
            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((S_80173078_0 *)action)->unk_8C = metal_action_resume_address;
            advance_status_timers(actor);
            (*(u8 *)((u8 *)actor + 0x73)) = 0;
            (*(u8 *)((u8 *)actor + 0x72)) = 0;
            (*(u8 *)((u8 *)actor + 0x6D))--;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        }
    }
}

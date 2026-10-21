#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
extern int abs(int);

extern s32 D_8015EF68;
extern u8 D_80161FB8[8];

s32 get_cd_command_queue_depth(void);
#include "engine/graphics/select_sprite_entry_api.h"
extern void *scan_monster_along_heading();
#include "dungeon/player/object/set_record_integer_tile_center_api.h"
#include "dungeon/actor/state/advance_status_timers_api.h"
extern void play_sound_if_enabled();
extern s32 create_actor_spell_effect();
void create_two_row_object_group(void *, s16);

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
    u8 pad_90[0x6];
    u16 ticks;
    u16 flags;
    u8 pad_9A[0x1];
    u8 phase;
} ActionState;

typedef struct ObjectHeaderTail {
    void * sprite;
    u8 pad_04[0x10];
} ObjectHeaderTail;   /* the 0x14 bytes before root in advance_actor_animation_and_reset_motion, addressed as root[-1] */

typedef struct TilePosition {
    u8 pad_00[0x24];
    u8 tileX;
    u8 tileY;
} TilePosition;

typedef struct ActorSprite {
    u8 pad_00[0x4];
    s8 frame;
    u8 pad_05[0xF];
    u16 flags;
    u8 pad_16[0xE];
    u8 tileX;
    u8 tileY;
    u8 pad_26[0x6];
    void * directionFrames;
} ActorSprite;

/* Advance the actor animation state and reset movement when it finishes. */
void advance_actor_animation_and_reset_motion(ActionState *action, ObjectPosition *motion, ActorSprite *sprite, ActorRecord *actor)
{
    u16 position[3];
    u8 *animation;
    s16 use_player_target;
    s32 target_mode;
    s32 state;
    s32 anim_kind;
    void *target_root;
    void *target_source;
    void *new_target;
    s32 abs_x;
    s32 abs_y;

    state = action->phase;
    use_player_target = 0;
    switch (state) {
    case 0:
        if (actor->flags1C & 0x2000) {
            anim_kind = (actor->action_flags & 0x3FFF) - 1;
            switch (anim_kind) {
            case 6:
                use_player_target = 1;
                /* fall through */
            case 2:
                animation = &((ItemSlots *)actor)->third;
                break;
            case 5:
                use_player_target = 1;
                /* fall through */
            case 1:
                animation = &((ItemSlots *)actor)->second;
                break;
            case 4:
                use_player_target = 1;
                /* fall through */
            case 0:
                animation = &((ItemSlots *)actor)->first;
                break;
            case 3:
            default:
                animation = 0;
                break;
            }
        } else {
            anim_kind = actor->action_flags & 0x3FFF;
            switch (anim_kind) {
            case 3:
                animation = &((ItemSlots *)actor)->third;
                break;
            case 2:
                animation = &((ItemSlots *)actor)->second;
                break;
            case 1:
                animation = &((ItemSlots *)actor)->first;
                break;
            default:
                animation = 0;
                break;
            }
        }

        if (*animation != 0) {
            action->flags &= 0xFF7F;
            target_mode = use_player_target;
            if (target_mode != 0) {
                target_root = D_800814A8;
                actor->target = target_root;
                target_source = ((ObjectHeaderTail *)target_root)[-1].sprite;
                actor->target_tile_x = ((TilePosition *)target_source)->tileX;
                actor->target_tile_y = ((TilePosition *)target_source)->tileY;
            } else {
                new_target = scan_monster_along_heading(
                    actor, sprite->tileX, sprite->tileY,
                    actor->facing, 0x10);
                actor->target = new_target;
                abs_x = abs(actor->target_tile_x);
                abs_y = abs(actor->target_tile_y);
                actor->target_tile_x = abs_x;
                actor->target_tile_y = abs_y;
            }
            position[0] = ((u16)motion->x.w.i);
            position[1] = ((u16)motion->y.w.i);
            position[2] = ((u16)motion->z.w.i);
            if (create_actor_spell_effect(actor, animation, use_player_target, &action->flags) != 0) {
                sprite->flags &= 0xF7FF;
                play_sound_if_enabled(0x703);
                create_two_row_object_group(position, (s16)((*animation - 1) % 3));
                action->phase++;
                return;
            }
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tileX, sprite->tileY);
        g_dungeon_status.active_actor = 0;
        ((PlayerActionCounter *)D_800814A8)->pendingActions--;
        advance_status_timers(actor);
        (*(u8 *)&actor->pending_turn_updates)--;
        action->handler = &D_8015EF68;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        action->phase++;

        /* fall through */
    case 2:
        if ((sprite->frame == 8 &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x800;
            action->ticks = 3;
            action->flags |= 0x80;
        }
        action->ticks--;
        if ((s16)action->ticks <= 0) {
            action->ticks = 0;
            sprite->flags &= 0xF7FF;
        }
        if (sprite->flags & 0xE000) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tileX, sprite->tileY);
            if (sprite->directionFrames != D_80161FB8) {
                (*(void * *)((u8 *)sprite + (0x2C))) = D_80161FB8;
                select_sprite_entry(
                    (struct S_80047784 *)(sprite),
                    D_80161FB8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
            if (((s32)g_dungeon_status.active_actor) == 0) {
                g_dungeon_status.activity_counts.parts.pending_action_count--;
                sprite->flags &= 0xF7FF;
                action->handler = &D_8015EF68;
                advance_status_timers(actor);
                if (actor->pending_turn_updates > 0) {
                    (*(u8 *)&actor->pending_turn_updates)--;
                }
                actor->target_tile_y = 0;
                actor->target_tile_x = 0;
                actor->action_flags &= 0x7FFF;
                play_sound_if_enabled(0xB4);
            }
        }

        return;
    }
}

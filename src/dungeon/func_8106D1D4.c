#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
extern int abs(int);

extern s32 D_8015EF68;
extern u8 D_80161FB8[8];

extern s32 get_cd_command_queue_depth();
extern void select_sprite_entry();
extern void *scan_monster_along_heading();
extern void set_record_integer_tile_center();
extern void advance_status_timers();
extern void play_sound_if_enabled();
extern s32 create_actor_spell_effect();
extern void create_two_row_object_group();

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
void advance_actor_animation_and_reset_motion(ActionState *action, EntityRec *motion, ActorSprite *sprite, EntityRec *actor)
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
            anim_kind = (actor->unk_46 & 0x3FFF) - 1;
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
            anim_kind = actor->unk_46 & 0x3FFF;
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
                actor->unk_72 = ((TilePosition *)target_source)->tileX;
                actor->unk_73 = ((TilePosition *)target_source)->tileY;
            } else {
                new_target = scan_monster_along_heading(
                    actor, sprite->tileX, sprite->tileY,
                    actor->facing, 0x10);
                actor->target = new_target;
                abs_x = abs(actor->unk_72);
                abs_y = abs(actor->unk_73);
                actor->unk_72 = abs_x;
                actor->unk_73 = abs_y;
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
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->tileX, sprite->tileY);
        g_dungeon_status.unk_0C = 0;
        ((PlayerActionCounter *)D_800814A8)->pendingActions--;
        advance_status_timers(actor);
        (*(u8 *)&actor->unk_6D)--;
        action->handler = &D_8015EF68;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
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
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, sprite->tileX, sprite->tileY);
            if (sprite->directionFrames != D_80161FB8) {
                (*(void * *)((u8 *)sprite + (0x2C))) = D_80161FB8;
                select_sprite_entry(
                    sprite,
                    D_80161FB8[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
            if (((s32)g_dungeon_status.unk_0C) == 0) {
                g_dungeon_status.unk_0A--;
                sprite->flags &= 0xF7FF;
                action->handler = &D_8015EF68;
                advance_status_timers(actor);
                if (actor->unk_6D > 0) {
                    (*(u8 *)&actor->unk_6D)--;
                }
                actor->unk_73 = 0;
                actor->unk_72 = 0;
                actor->unk_46 &= 0x7FFF;
                play_sound_if_enabled(0xB4);
            }
        }

        return;
    }
}

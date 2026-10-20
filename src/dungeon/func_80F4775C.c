#include "shared/object_node.h"
#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

/* Partial action view: timer loads keep their observed signedness. */
typedef struct ActorActionView {
    u8 pad_00[0x8C];
    union { s32 code; void *record; u8 *frames; s32 *word; } nextAction;
    Fixed1616 motionOffset;
    u8 pad_94[2];
    union { u16 unsignedTicks; s16 signedTicks; } timer;
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[4];
    s16 frameParameter;
    u8 pad_A2[4];
    u16 effectTicks;
    union { s16 signedPhase; u16 phase; u16 startX; } effectState;
    union { u16 facing; u16 startY; } saved;
    u16 effectX;
    u16 effectY;
    u16 effectZ;
} ActorActionView;

typedef union TilePairView {
    struct { u8 x; u8 y; } tile;
    u16 packed;
} TilePairView;

typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 frame;
    u8 pad_05[3];
    s32 animationKey;
    u8 pad_0C[8];
    u16 flags;
    u8 pad_16[0xE];
    TilePairView position;
    union { s8 signedIndex; u8 unsignedIndex; } tileIndex;
    u8 pad_27[5];
    u8 *directionFrames;
} ActorSpriteView;

/* The selected three-byte action records overlap the entity's position view. */
typedef struct ActorActionSlotsView {
    u8 pad_00[8];
    u8 first[3];
    u8 second[3];
    u8 third[3];
} ActorActionSlotsView;

/* Halfword view of the player's action counter at EntityRec + 0xA6. */
typedef struct PlayerActionCountView {
    u8 pad_00[0xA6];
    u16 remaining;
} PlayerActionCountView;

extern int abs(int);

extern s32 get_cd_command_queue_depth(void);
extern void select_sprite_entry(void *, s32, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);

extern u8 D_8015EE94[];
extern u8 D_80162A7C[];

void update_effect_action_variant(ActorActionView *action, EntityRec *transform, ActorSpriteView *sprite, EntityRec *actor)
{
    /* Retail keeps these position saves in the action-start path. */
    u16 saved_pos[3];
    u8 *action_slot;
    s16 use_player_target;
    void *target;
    s32 abs_x;
    s32 abs_y;
    s32 wait_ticks;
    EntityRec *target_position;
    DungeonGlobalStatus *status;

    use_player_target = 0;
    switch (action->phase) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->unk_46 & 0x3FFF) {
            case 7:
                use_player_target = 1;
                /* fall through */
            case 3:
                action_slot = ((ActorActionSlotsView *)actor)->third;
                break;
            case 6:
                use_player_target = 1;
                /* fall through */
            case 2:
                action_slot = ((ActorActionSlotsView *)actor)->second;
                break;
            case 5:
                use_player_target = 1;
                /* fall through */
            case 1:
                action_slot = ((ActorActionSlotsView *)actor)->first;
                break;
            default:
                action_slot = (u8 *)0;
                break;
            }
        } else {
            switch (actor->unk_46 & 0x3FFF) {
            case 3:
                action_slot = ((ActorActionSlotsView *)actor)->third;
                break;
            case 2:
                action_slot = ((ActorActionSlotsView *)actor)->second;
                break;
            case 1:
                action_slot = ((ActorActionSlotsView *)actor)->first;
                break;
            default:
                action_slot = (u8 *)0;
                break;
            }
        }

        if (*action_slot != 0) {
            action->flags &= 0xFF7F;
            if (use_player_target != 0) {
                target = D_800814A8;
                actor->target = target;
                target_position = ((ObjectNodeHeader *)target)[-1].unk_0C;
                actor->unk_72 = target_position->tileX;
                actor->unk_73 = target_position->tileY;
            } else if (D_8006DE24[*action_slot].kind == 2) {
                target = actor->target;
                if (target != 0) {
                    target_position = ((ObjectNodeHeader *)target)[-1].unk_0C;
                    actor->unk_72 = target_position->tileX;
                    actor->unk_73 = target_position->tileY;
                }
            } else {
                actor->target =
                    scan_monster_along_heading(actor, sprite->position.tile.x, sprite->position.tile.y,
                                  actor->facing, 0x10);
                abs_x = abs(actor->unk_72);
                abs_y = abs(actor->unk_73);
                actor->unk_72 = abs_x;
                actor->unk_73 = abs_y;
            }
            saved_pos[0] = ((u16)transform->x.w.i);
            saved_pos[1] = ((u16)transform->y.w.i);
            saved_pos[2] = ((u16)transform->z.w.i);
            if (create_actor_spell_effect(actor, action_slot, use_player_target, &action->flags) == 0) {
                return;
            }
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x703);
            action->phase = action->phase + 1;
            return;
        }

        transform->flags14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        set_record_integer_tile_center(transform, sprite->position.tile.x, sprite->position.tile.y);
        g_dungeon_status.unk_0C = 0;
        ((PlayerActionCountView *)D_800814A8)->remaining = ((PlayerActionCountView *)D_800814A8)->remaining - 1;
        advance_status_timers(actor);
        actor->unk_6D = ((u8)actor->unk_6D) - 1;
        action->nextAction.record = D_8015EE94;
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
        action->phase = action->phase + 1;
    case 2:
        if ((sprite->frame == 6 && (sprite->flags & 0x1000)) ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x800;
            action->flags |= 0x80;
        }
        if ((sprite->frame == 7 && (sprite->flags & 0x1000)) ||
            (sprite->flags & 0x8000)) {
            sprite->flags |= 0x800;
            action->timer.unsignedTicks = 8;
        }
        wait_ticks = action->timer.unsignedTicks - 1;
        action->timer.unsignedTicks = wait_ticks;
        if ((s16)wait_ticks <= 0) {
            action->timer.unsignedTicks = 0;
            sprite->flags &= 0xF7FF;
        }
        if ((sprite->flags & 0xE000) == 0) {
            return;
        }
        transform->flags14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        set_record_integer_tile_center(transform, sprite->position.tile.x, sprite->position.tile.y);
        {
            u8 *direction_frames = D_80162A7C;

            if (sprite->directionFrames != direction_frames) {
                sprite->directionFrames = direction_frames;
                select_sprite_entry(sprite,
                    direction_frames[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        status = &g_dungeon_status;
        if (status->unk_0C != 0) {
            return;
        }
        status->unk_0A = status->unk_0A - 1;
        sprite->flags &= 0xF7FF;
        action->nextAction.record = D_8015EE94;
        advance_status_timers(actor);
        if (actor->unk_6D > 0) {
            actor->unk_6D = ((u8)actor->unk_6D) - 1;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        break;
    }
}

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

/* The action record shares its timer bytes between signed tests and unsigned updates. */
typedef struct ActorActionView {
    u8 pad_00[0x8C];
    void *nextBehavior;
    s32 scratch;
    u8 pad_94[2];
    union { u16 raw; s16 signedValue; } timer;
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[2];
    s16 idleElapsed;
    s16 idleDelay;
    u8 pad_A2[0xA];
    union { u16 raw; s16 signedValue; } startHeight;
} ActorActionView;

/* The sprite pointer is in the object header, 0x14 bytes before its entity record. */
typedef struct ActorSpriteLink {
    void *sprite;
    u8 pad_04[0x10];
} ActorSpriteLink;

/* Sprite state passed to the frame selector; the tile pair is also compared as one halfword. */
typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 framePhase;
    u8 pad_05[0xF];
    u16 flags;
    u8 pad_16[6];
    u16 scaleX;
    u16 scaleY;
    u8 pad_20[4];
    union { struct { u8 x, y; } bytes; u16 packed; } tile;
    union { u8 raw; s8 signedValue; } room;
    u8 pad_27[5];
    u8 *frameTable;
} ActorSpriteView;

/* Three adjacent three-byte ability slots, selected by action kinds 1, 2 and 3. */
typedef struct ActorAbilityView {
    u8 pad_00[8];
    u8 slots[3][3];
} ActorAbilityView;

typedef struct PlayerActionCounterView {
    u8 pad_00[0xA6];
    u16 activeActions;
} PlayerActionCounterView;
extern int abs(int);

extern void update_actor_dungeon_behavior(void *, void *, void *, void *);
extern u8 D_8016EEB8[];

extern s32 get_cd_command_queue_depth();
extern void func_80047784();
extern s32 func_80069EF8();
extern void *scan_monster_along_heading();
extern void set_record_integer_tile_center();
extern s32 advance_status_timers(void *);
extern s32 play_sound_if_enabled(s32);
extern void *create_actor_spell_effect();
extern s32 func_8016B498();

/* Updates an actor action through targeting, particle effects, and recovery. */
void advance_targeted_actor_action(ActorActionView *action, EntityRec *motion, ActorSpriteView *sprite, EntityRec *actor) {
    s32 use_player_target;
    s32 particle_count;
    s32 offset_z;
    s32 direction;
    s32 action_kind;
    void *target;
    SpriteFrameState *target_sprite;
    s32 particle_zero;
    s32 particle_color;
    s32 offset_x;
    s32 offset_y;
    u16 timer;
    u16 sprite_flags;
    u16 raw_kind;
    u32 kind_index;
    u8 state;
    u8 *action_data;
    u8 *particle_origin;

    state = action->phase;
    use_player_target = 0;
    switch (state) {
    case 0:
        if (actor->flags1C & 0x2000) {
            raw_kind = actor->unk_46 & 0x3FFF;
            kind_index = raw_kind - 1;
            switch (kind_index) {
            case 6:
                use_player_target = 1;
                /* fall through */
            case 2:
                action_data = ((ActorAbilityView *)actor)->slots[2];
                break;
            case 5:
                use_player_target = 1;
                /* fall through */
            case 1:
                action_data = ((ActorAbilityView *)actor)->slots[1];
                break;
            case 4:
                use_player_target = 1;
                /* fall through */
            case 0:
                action_data = ((ActorAbilityView *)actor)->slots[0];
                break;
            default:
                action_data = 0;
                break;
            }
        } else {
            action_kind = actor->unk_46 & 0x3FFF;
            switch (action_kind) {
            case 3:
                action_data = ((ActorAbilityView *)actor)->slots[2];
                break;
            case 2:
                action_data = ((ActorAbilityView *)actor)->slots[1];
                break;
            case 1:
                action_data = ((ActorAbilityView *)actor)->slots[0];
                break;
            default:
                action_data = 0;
                break;
            }
        }
        if (*action_data != 0) {

            direction = action->flags;
            direction &= 0xFF7F;
            action->flags = direction;
            direction = use_player_target;
            if (direction != 0) {
                target = D_800814A8;
                actor->target = target;
                {
                    u8 tile_coord;

                    target_sprite = ((ActorSpriteLink *)target)[-1].sprite;
                    tile_coord = target_sprite->unk_24;
                    actor->unk_72 = tile_coord;
                    tile_coord = target_sprite->unk_25;
                    actor->unk_73 = tile_coord;
                }
            } else if (D_8006DE24[*action_data].kind == 2) {
                target = actor->target;
                if (target != 0) {
                    {
                        u8 tile_coord;

                        target_sprite = ((ActorSpriteLink *)target)[-1].sprite;
                        tile_coord = target_sprite->unk_24;
                        actor->unk_72 = tile_coord;
                        tile_coord = target_sprite->unk_25;
                        actor->unk_73 = tile_coord;
                    }
                }
            } else {

                actor->target = scan_monster_along_heading(
                    actor,
                    sprite->tile.bytes.x,
                    sprite->tile.bytes.y,
                    actor->facing,
                    0x10);

                actor->unk_72 = abs(actor->unk_72);
                actor->unk_73 = abs(actor->unk_73);
            }

            if (create_actor_spell_effect(actor, action_data, use_player_target, &action->flags) == 0) {
                return;
            }
            action->phase++;
            return;

        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->tile.bytes.x, sprite->tile.bytes.y);
        g_dungeon_status.unk_0C = 0;
        ((PlayerActionCounterView *)D_800814A8)->activeActions--;
        advance_status_timers(actor);
        actor->unk_6D--;
        action->nextBehavior = update_actor_dungeon_behavior;
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
        play_sound_if_enabled(0x703);
        /* fallthrough */
    case 2:
        sprite_flags = sprite->flags;
        if (sprite_flags & 0x8000) {
            action->timer.raw = 0;
            action->phase++;
            action->flags |= 0x80;
            return;
        }

        if ((sprite->framePhase == 2) && (sprite_flags & 0x1000)) {
            sprite->flags = sprite_flags | 0x800;
            action->timer.raw = 0x16;
        }
        if (sprite->framePhase < 2) {
            return;
        }

        timer = action->timer.raw - 1;
        action->timer.raw = timer;
        if ((s16)timer <= 0) {
            action->timer.raw = 0;
            action->phase++;
        }
        if (action->timer.signedValue == 2) {
            action->flags |= 0x80;
        }
        if (action->timer.signedValue < 0xA) {
            return;
        }

        particle_count = 0;
        do {
            particle_count++;
            offset_x = (s16)((func_80069EF8() & 0x3F) - 0x20);
            offset_y = (s16)((func_80069EF8() & 0x3F) - 0x20);
            offset_z = func_80069EF8();
            particle_origin = (u8 *)action - 0x20;
            particle_zero = 0;
            particle_color = 0xC0C0C0;
            offset_z = (s16)((offset_z & 0x3F) - 0x20);
            func_8016B498(
                particle_origin,
                particle_zero,
                particle_color,
                (s16)(action->timer.raw - 2),
                offset_x,
                offset_y,
                offset_z);
            if ((u32)(particle_count & 0xFFFF) >= 3U) {
                return;
            }
        } while (1);

    case 3:
        action->timer.raw = 0x14;
        action->phase++;
        /* fallthrough */
    case 4:
        if (((s32)g_dungeon_status.unk_0C) == 0) {
            action->timer.raw = 0;
        }
        timer = action->timer.raw - 1;
        action->timer.raw = timer;
        if ((s16)timer <= 0) {
            action->timer.raw = 0;
            sprite->flags &= 0xF7FF;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->tile.bytes.x, sprite->tile.bytes.y);

        if (sprite->frameTable != D_8016EEB8) {
            (sprite->frameTable) = D_8016EEB8;
            direction = ((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7;
            func_80047784(sprite, D_8016EEB8[direction], 0);
        }
        if (((s32)g_dungeon_status.unk_0C) != 0) {
            return;
        }

        g_dungeon_status.unk_0A--;
        action->nextBehavior = update_actor_dungeon_behavior;
        advance_status_timers(actor);
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_6D--;
        actor->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);
    }
}

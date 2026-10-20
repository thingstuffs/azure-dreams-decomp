#include "shared/object_node.h"
#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "shared/actor_action.h"

/* Partial action view: timer loads keep their observed signedness. */


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


extern int abs(int);

extern u8 D_8015FCE8[];
extern u8 D_80162EB8[];

extern s32 get_cd_command_queue_depth();
extern s32 select_sprite_entry();
extern s32 func_80069EF8();
extern void *scan_monster_along_heading();
extern s32 set_record_integer_tile_center();
extern s32 advance_status_timers();
extern s32 play_sound_if_enabled();
extern s32 create_actor_spell_effect();
extern s32 func_8015F498();

void advance_actor_action_variant_c(ActorActionView *action, EntityRec *motion, ActorSpriteView *sprite, EntityRec *actor)
{
    s32 use_player_target;
    s32 particle_count;
    s32 offset_z;
    s32 selection;
    s32 selected;
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
    ObjectNodeHeader *particle_origin;

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
                action_data = ((ActorActionSlotsView *)actor)->third;
                break;
            case 5:
                use_player_target = 1;
        /* fall through */
            case 1:
                action_data = ((ActorActionSlotsView *)actor)->second;
                break;
            case 4:
                use_player_target = 1;
        /* fall through */
            case 0:
                action_data = ((ActorActionSlotsView *)actor)->first;
                break;
            default:
                action_data = 0;
                break;
            }
        } else {
            selected = actor->unk_46 & 0x3FFF;
            switch (selected) {
            case 3:
                action_data = ((ActorActionSlotsView *)actor)->third;
                break;
            case 2:
                action_data = ((ActorActionSlotsView *)actor)->second;
                break;
            case 1:
                action_data = ((ActorActionSlotsView *)actor)->first;
                break;
            default:
                action_data = 0;
                break;
            }
        }
        if (*action_data != 0) {

            selection = action->flags;
            selection = (s32)(selection & 0xFF7F);
            action->flags = selection;
            selection = use_player_target;
            if (selection != 0) {
                selection = (s32)(D_800814A8);
                actor->target = ((EntityRec *)selection);
                {
                    u8 target_coordinate;

                    selected = (s32)(((ObjectNodeHeader *)((EntityRec *)selection))[-1].unk_0C);
                    target_coordinate = ((EntityRec *)selected)->tileX;
                    actor->unk_72 = target_coordinate;
                    target_coordinate = ((EntityRec *)selected)->tileY;
                    actor->unk_73 = target_coordinate;
                }
            } else if (D_8006DE24[*action_data].kind == 2) {
                selection = (s32)(actor->target);
                if (((EntityRec *)selection) != 0) {
                    {
                        u8 target_coordinate;

                        selected = (s32)(((ObjectNodeHeader *)((EntityRec *)selection))[-1].unk_0C);
                        target_coordinate = ((EntityRec *)selected)->tileX;
                        actor->unk_72 = target_coordinate;
                        target_coordinate = ((EntityRec *)selected)->tileY;
                        actor->unk_73 = target_coordinate;
                    }
                }
            } else {

                actor->target = scan_monster_along_heading(
                    actor,
                    sprite->position.tile.x,
                    sprite->position.tile.y,
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
        set_record_integer_tile_center(motion, sprite->position.tile.x, sprite->position.tile.y);
        g_dungeon_status.unk_0C = 0;
        ((PlayerRemainingActionsView *)D_800814A8)->remaining--;
        advance_status_timers(actor);
        actor->unk_6D--;
        action->nextAction.record = D_8015FCE8;
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
        /* fall through */
    case 2:
        sprite_flags = sprite->flags;
        if (sprite_flags & 0x8000) {
            action->timer.unsignedTicks = 0;
            action->phase++;
            action->flags |= 0x80;
            return;
        }

        if ((sprite->frame == 2) && (sprite_flags & 0x1000)) {
            sprite->flags = sprite_flags | 0x800;
            action->timer.unsignedTicks = 0x16;
        }
        if (sprite->frame < 2) {
            return;
        }

        timer = action->timer.unsignedTicks - 1;
        action->timer.unsignedTicks = timer;
        if ((s16)timer <= 0) {
            action->timer.unsignedTicks = 0;
            action->phase++;
        }
        if (action->timer.signedTicks == 2) {
            action->flags |= 0x80;
        }
        if (action->timer.signedTicks < 0xA) {
            return;
        }

        particle_count = 0;
        do {
            particle_count++;
            offset_x = (s16)((func_80069EF8() & 0x3F) - 0x20);
            offset_y = (s16)((func_80069EF8() & 0x3F) - 0x20);
            offset_z = func_80069EF8();
            particle_origin = ((ObjectNodeHeader *)action) - 1;
            particle_zero = 0;
            particle_color = 0xC0C0C0;
            offset_z = (s16)((offset_z & 0x3F) - 0x20);
            func_8015F498(
                particle_origin,
                particle_zero,
                particle_color,
                (s16)(action->timer.unsignedTicks - 2),
                offset_x,
                offset_y,
                offset_z);
        } while ((u32)(particle_count & 0xFFFF) < 3U);
        return;

    case 3:
        action->timer.unsignedTicks = 0x14;
        action->phase++;

        /* fall through */
    case 4:
        if (((s32)g_dungeon_status.unk_0C) == 0) {
            action->timer.unsignedTicks = 0;
        }
        timer = action->timer.unsignedTicks - 1;
        action->timer.unsignedTicks = timer;
        if ((s16)timer <= 0) {
            action->timer.unsignedTicks = 0;
            sprite->flags &= 0xF7FF;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->position.tile.x, sprite->position.tile.y);

        if (sprite->directionFrames != D_80162EB8) {
            sprite->directionFrames = D_80162EB8;
            selection = ((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, D_80162EB8[selection], 0);
        }
        if (((s32)g_dungeon_status.unk_0C) != 0) {
            return;
        }

        g_dungeon_status.unk_0A--;
        action->nextAction.record = D_8015FCE8;
        advance_status_timers(actor);
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_6D--;
        actor->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);
    }
}

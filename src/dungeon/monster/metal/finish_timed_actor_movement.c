#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "dungeon/item.h"

typedef struct {
    u8 pad00[0x8C];
    void *field8C;
    s32 position90;
    u8 pad94[2];
    s16 countdown96;
    u16 flags98;
    u8 pad9A;
    u8 state9B;
    u8 pad9C[2];
    s16 timer9E;
    s32 velocityA0;
} State;

typedef struct {
    u8 pad00[2];
    s16 x2;
    u8 pad04[2];
    s16 y6;
    u8 pad08[4];
    s32 dxC;
    s32 dy10;
    s32 dz14;
} Motion;

typedef struct {
    u8 pad00[0x14];
    u16 flags14;
    u8 pad16[0xE];
    u8 x24;
    u8 y25;
    u8 pad26[6];
    u8 *table2C;
} Actor;

typedef struct {
    u8 pad00[0x1C];
    u32 flags1C;
    u8 pad20[0xA];
    s16 direction2A;
    u8 pad2C[0x1A];
    u16 field46;
} Entity;

extern u8 metal_action_resume_address[];
extern u8 metal_movement_frames[];
extern u8 metal_frame_set_2[];

struct SpriteFrameState;
extern void select_sprite_entry(void *, s16, s16);
extern s32 rsin(s32);
extern void set_record_integer_tile_center(Motion *, u8, u8);
extern void spend_actor_mp(Entity *, s32);


/* Advance movement to the actor's tile and finish the timed action. */
void finish_timed_actor_movement(State *action, Motion *motion, SpriteFrameState *actor, Entity *entity)
{
    s32 direction_work[2];
    s32 direction_index;
    u8 phase;
    u32 entity_flags;

    phase = action->state9B;
    switch (phase) {
    case 0:
        if ((actor->flags & 0x6000) == 0) {
            break;
        }
        actor->frameTable = metal_movement_frames;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->direction2A + 0x100) >> 9;
        select_sprite_entry(actor, metal_movement_frames[direction_index & 7], 0);
        action->flags98 |= 8;
        entity->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        action->timer9E = 5;
        action->velocityA0 = 0;
        action->state9B++;
                        /* fallthrough */
    case 1:
        action->position90 -= action->velocityA0;
        if (action->timer9E != 0) {
            s32 target_x;
            s32 current_x;
            s32 x_velocity;
            s32 current_y;

            target_x = actor->tile_x << 6;
            current_x = motion->x2 - 0x20;
            x_velocity = ((target_x - current_x) << 16) /
                         action->timer9E;
            current_y = motion->y6 - 0x20;
            motion->dxC = x_velocity;
            motion->dy10 = (((actor->tile_y << 6) - current_y) << 16) /
                         action->timer9E;
            action->velocityA0 = -rsin(action->timer9E * 0x199) << 10;
        }
        action->position90 += action->velocityA0;
        action->timer9E--;
        if (action->timer9E < 0) {
            action->flags98 &= 0xFFF7;
            action->position90 = 0;
            entity->flags1C |= ACTOR_GROUNDED;
            action->state9B++;
        }
                        /* fallthrough */
    case 2:
        if ((entity->flags1C & ACTOR_GROUNDED) == 0) {
            break;
        }
        action->flags98 &= 0xFFF7;
        motion->dz14 = 0;
        motion->dy10 = 0;
        motion->dxC = 0;
        set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);
        actor->frameTable = metal_frame_set_2;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->direction2A + 0x100) >> 9;
        select_sprite_entry(actor, metal_frame_set_2[direction_index & 7], 0);
        action->state9B++;
        break;
    default:
        break;
    }

    action->countdown96--;
    if (action->countdown96 > 0) {
        return;
    }

    motion->dz14 = 0;
    motion->dy10 = 0;
    motion->dxC = 0;
    set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);
    spend_actor_mp(entity, 4);
    advance_status_timers(entity);

    {

        if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
            g_dungeon_status.activity_counts.parts.pending_movement_count -= 1;
        }
    }

    entity_flags = entity->flags1C;
    if ((entity_flags & 0x2000) != 0) {
        if ((entity->field46 & 0x8000) != 0) {
            entity->field46 &= 0x7FFF;
        }
    } else if ((entity_flags & 0x410) == 0) {
        if ((entity_flags & 0x20000) != 0) {
            entity->direction2A = get_rounded_facing_and_rounding_flag(
                actor->tile_x, actor->tile_y, reference_tile_object.tile_position.parts.tile_x,
                reference_tile_object.tile_position.parts.tile_y, direction_work);
        }
    }

    if ((check_actor_floor_trap(actor, entity) << 16) > 0) {
        action->field8C = metal_action_resume_address;
        on_actor_status_updated(entity);
    }
}

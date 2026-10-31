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
    u8 pad9C[4];
    s32 velocityA0;
    s16 timerA4;
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

extern u8 killer_action_resume_address[];
extern u8 D_80174050[];
extern u8 D_80174058[];

struct SpriteFrameState;
extern void select_sprite_entry(void *, s16, s16);
extern s32 rsin(s32);
extern void set_record_integer_tile_center(Motion *, u8, u8);
extern void spend_actor_mp(Entity *, s32);


/* Moves toward the actor's tile and restores entity state when the countdown expires. */
void move_toward_actor_tile_center(ActorRecord *body, Motion *motion, SpriteFrameState *sprite, Entity *entity)
{
    s32 direction_scratch[2];
    s32 direction_index;
    u8 phase;
    u32 entity_flags;

    phase = body->action_phase.u;
    switch (phase) {
    case 0:
        if ((sprite->flags & 0x6000) == 0) {
            break;
        }
        sprite->frameTable = D_80174050;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->direction2A + 0x100) >> 9;
        select_sprite_entry(sprite, D_80174050[direction_index & 7], 0);
        body->action_state_flags |= 8;
        entity->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        body->unk_A4.halves.low.s = 5;
        body->unk_A0.value = 0;
        body->action_phase.u++;
                        /* fallthrough */
    case 1:
        body->unk_90.value -= body->unk_A0.value;
        if (body->unk_A4.halves.low.s != 0) {
            s32 target_x;
            s32 x_origin;
            s32 x_velocity;
            s32 y_origin;

            target_x = sprite->tile_x << 6;
            x_origin = motion->x2 - 0x20;
            x_velocity = ((target_x - x_origin) << 16) /
                         body->unk_A4.halves.low.s;
            y_origin = motion->y6 - 0x20;
            motion->dxC = x_velocity;
            motion->dy10 = (((sprite->tile_y << 6) - y_origin) << 16) /
                         body->unk_A4.halves.low.s;
            body->unk_A0.value = -rsin(body->unk_A4.halves.low.s * 0x199) << 10;
        }
        body->unk_90.value += body->unk_A0.value;
        body->unk_A4.halves.low.s--;
        if (body->unk_A4.halves.low.s < 0) {
            body->action_state_flags &= 0xFFF7;
            body->unk_90.value = 0;
            entity->flags1C |= ACTOR_GROUNDED;
            body->action_phase.u++;
        }
                        /* fallthrough */
    case 2:
        if ((entity->flags1C & ACTOR_GROUNDED) == 0) {
            break;
        }
        body->action_state_flags &= 0xFFF7;
        motion->dz14 = 0;
        motion->dy10 = 0;
        motion->dxC = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        sprite->frameTable = D_80174058;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->direction2A + 0x100) >> 9;
        select_sprite_entry(sprite, D_80174058[direction_index & 7], 0);
        body->action_phase.u++;
        break;
    default:
        break;
    }

    body->action_timer.s--;
    if (body->action_timer.s > 0) {
        return;
    }

    motion->dz14 = 0;
    motion->dy10 = 0;
    motion->dxC = 0;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
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
                sprite->tile_x, sprite->tile_y, reference_tile_object.tile_position.parts.tile_x,
                reference_tile_object.tile_position.parts.tile_y, direction_scratch);
        }
    }

    if ((check_actor_floor_trap(sprite, entity) << 16) > 0) {
        body->unk_8C.address = killer_action_resume_address;
        on_actor_status_updated(entity);
    }
}

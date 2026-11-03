#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "shared/vector.h"
#include "town/player/motion.h"
#include "town/player/object.h"


typedef struct Position {
    s32 x;
    s32 y;
    s32 z;
    s32 half_dx;
    s32 half_dy;
    s32 half_dz;
} Position;

extern u8 D_8009AE88[];
extern u8 town_scene_record_handlers[];


extern IntVector3 D_800D0624;

extern void call_the_handler_selects_nonzero_entry();

/* Compute half the offset to the target, then snap to it and advance state when the timer expires. */
void move_player_halfway_to_target(TownObjectRecord *state, ObjectPosition *position, SpriteFrameState *context)
{
    u16 timer;
    IntVector3 *target;

    target = &D_800D0624;
    position->velocity_x = (target->x - position->x.v) / 2;
    position->velocity_y = (target->y - position->y.v) / 2;
    position->velocity_z = (target->z - position->z.v) / 2;

    timer = state->unk_0A.as_u16 - 1;
    state->unk_0A.as_u16 = timer;
    if ((s16)timer < 0) {
        position->x.v = target->x;
        position->y.v = target->y;
        position->z.v = target->z;
        clear_entity_record_fields(position);

        state->unk_30 = ((u16)position->x.w.i);
        state->unk_32 = ((u16)position->y.w.i);
        call_the_handler_selects_nonzero_entry(town_scene_record_handlers, state, context);

        state->unk_04.as_pv = D_8009AE88;
        state->unk_10.as_s16 = 0x400;
    }
}

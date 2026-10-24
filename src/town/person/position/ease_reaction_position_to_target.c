#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"


#include "town/person/object_setup.h"

/* Ease the position toward its target, snapping to it when the timer expires. */
void ease_reaction_position_to_target(Rec_func_80094268_arg0 *state, EntityRec *position, void *update_arg) {
    s32 x_delta;
    s32 y_delta;
    s32 z_delta;
    u16 timer;

    timer = state->unk_6C.as_u16 - 1;
    state->unk_6C.as_u16 = timer;
    if ((timer << 16) <= 0) {
        apply_object_setup_and_update(state, position, update_arg);
        position->x.w.i = state->unk_84.as_u16;
        position->y.w.i = state->unk_86.as_u16;
        position->z.w.i = 0;
        return;
    }

    x_delta = (s16)state->unk_84.as_u16 -
            (s16)((u16)position->x.w.i);
    position->x.w.i =
        (u16)(((u16)position->x.w.i) + (x_delta / 8));

    y_delta = (s16)state->unk_86.as_u16 - position->y.w.i;
    position->y.w.i =
        (s16)((u16)position->y.w.i + (y_delta / 8));

    z_delta = -position->z.w.i;
    position->z.w.i =
        (s16)((u16)position->z.w.i + (z_delta / 8));
}

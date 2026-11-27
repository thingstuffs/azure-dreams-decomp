#include "common.h"

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 velocity_x;
    s32 velocity_y;
} Func8009990CState;

extern s32 update_object_and_clear_status_fields(Func8009990CState *);

/* Process the state when either trailing field is nonzero, otherwise return zero. */
s32 update_state_when_active(Func8009990CState *state) {
    if (state->velocity_x != 0 || state->velocity_y != 0) {
        return update_object_and_clear_status_fields(state);
    }
    return 0;
}

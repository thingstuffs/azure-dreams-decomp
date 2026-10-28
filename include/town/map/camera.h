#ifndef TOWN_MAP_CAMERA_H
#define TOWN_MAP_CAMERA_H

#include "common.h"
#include "shared/vector.h"

typedef struct TownCameraState TownCameraState;
typedef void (*TownCameraCallback)(TownCameraState *);

/* Primary camera state. Offsets are the 32-bit image offsets; pointer members
 * and callback pairs stay pointers when the source is compiled natively. */
struct TownCameraState {
    /* 0x00 */ IntVector3 *target;
    /* 0x04 */ IntVector3 *previous_target;
    /* 0x08 */ s32 x;
    /* 0x0C */ s32 y;
    /* 0x10 */ s32 z;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 steps;
    /* 0x24 */ TownCameraCallback select_target;
    /* 0x28 */ TownCameraCallback track_target;
    /* 0x2C */ IntVector3 *other;
    /* 0x30 */ IntVector3 *override_target;
    /* 0x34 */ s32 idle_calls;
};

extern TownCameraState town_camera_chase_state;
extern TownCameraCallback saved_camera_callbacks[2];
extern IntVector3 town_position_reference_state;

void initialize_control_block(TownCameraState *state);
void initialize_transition_state(TownCameraState *state);
void set_object_callback_when_active(TownCameraState *state);
void select_object_value_with_idle_fallback(TownCameraState *state);
void reset_or_copy_state_values(TownCameraState *state);
void restart_or_advance_target_interpolation(TownCameraState *state);
void restart_or_update_midpoint_tracking(TownCameraState *state);
void reset_or_advance_target_midpoint(TownCameraState *state);
void tcame_chase_set(void);
void tcame_chase2_set(void);
void tcame_chase_fix(IntVector3 *target);
void tcame_chase_fix_reset(void);
void tcame_chase_tgt_reset(void);
void tcame_lock(void);
void tcame_return(void);
void tcame_return_plus(void);

extern IntVector3 *D_80100D90;
void apply_and_store_setting(IntVector3 *setting);

#endif

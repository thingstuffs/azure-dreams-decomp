#ifndef TOWN_MENU_RANDOMIZED_EFFECT_MOTION_G00570_H
#define TOWN_MENU_RANDOMIZED_EFFECT_MOTION_G00570_H
/* inferred-strong randomized_effect_motion_g00570; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0B20. */

#include "common.h"
#include "engine/node/registration.h"
#include "shared/sprite_source.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "sdk/libgte.h"

/* Body installed by allocate_object_with_initial_state and called through dispatch_menu_state_callback. */
typedef struct RandomizedEffectMotionBody {
    /* 0x00 */ void (*callback)();
    /* 0x04 */ u8 pad_04[0x1E];
    /* 0x22 */ s16 variant;
    /* 0x24 */ s32 ticks_left;
    /* 0x28 */ u8 pad_28[4];
    /* 0x2C */ s32 velocity_x;
    /* 0x30 */ s32 velocity_y;
    /* 0x34 */ s32 velocity_z;
} RandomizedEffectMotionBody;

extern void select_record_entry_and_value(void *,void *, s32);
extern s16 D_800D0B18[];
extern u8 *D_800D0B50[];
/* extern */
void advance_sprite_animation_and_textures(void *entity);
/* extern */
extern void decrease_primitive_brightness_and_mark_cleanup(RandomizedEffectMotionBody *state,
                                                 ObjectPosition *unused_context, SpriteFrameState *appearance);

extern SpriteSourceEntry *D_800D0B20[];

/* Functions defined in this translation unit. */
void initialize_randomized_motion_vector(RandomizedEffectMotionBody *obj, s32 *vec, SpriteFrameState *record);
void advance_motion_and_reset_appearance(RandomizedEffectMotionBody *state, ObjectPosition *transform, SpriteFrameState *appearance);

#endif

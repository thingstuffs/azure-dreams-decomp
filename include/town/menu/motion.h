#ifndef TOWN_MENU_MOTION_H
#define TOWN_MENU_MOTION_H

#include "common.h"
#include "sdk/libgte_matrix.h"
#include "shared/entity.h"

struct ObjectPosition;
struct SpriteFrameState;

/* The factory installs the initializer in the first body word. The initializer
 * installs the fade update there and seeds both radii and their per-frame increments. */
struct S_800A32F0_0 {
    void (*update)(struct S_800A32F0_0 *, struct ObjectPosition *);
    u8 pad_04[4];
    s16 timer;
    u8 pad_0A[6];
    s32 radius_a, delta_a;
    s32 radius_b, delta_b;
    s16 shade;
};
typedef struct S_800A32F0_0 MenuRingAnimationState;
struct ObjectNodeHeader;

/* The entrance door uses this same state for its textured quad and the two
 * three-node groups transformed by its spin animation. */
typedef struct DoorTransitionEffect {
    u16 angle_x, angle_y, angle_z;
    u8 pad_06[2];
    s16 extent, finished;
    s32 timer;
    s16 intensity;
    u16 brightness;
    MATRIX matrices[2];
    struct ObjectNodeHeader *children[6];
    s16 texture_x, texture_y;
    u16 texture_width, texture_height;
    u8 pad_74[4];
    u16 half_width;
    s16 half_height;
} DoorTransitionEffect;

/* Body of the resource display object advanced by advance_animation_phase_and_frame. */
typedef struct MenuAnimationPhaseObject {
    /* 0x00 */ s16 frame;
    /* 0x02 */ s16 transition;
    /* 0x04 */ u8 pad_04[2];
    /* 0x06 */ u16 phase;
    /* 0x08 */ u16 offset;
    /* 0x0A */ u8 pad_0A[2];
    /* 0x0C */ s16 state;
    /* 0x0E */ u8 pad_0E[4];
    /* 0x12 */ u16 step;
    /* 0x14 */ s16 target;
    /* 0x16 */ s16 value;
} MenuAnimationPhaseObject;

void invoke_menu_motion_handler(void *obj, struct ObjectPosition *position, void *sprite);
void tick_menu_motion_fade(MenuRingAnimationState *obj, struct ObjectPosition *center);
void advance_animation_phase_and_frame(MenuAnimationPhaseObject *anim, struct ObjectPosition *unused);

void draw_textured_sprite_quad(void *sprite, struct ObjectPosition *position);
void step_door_transition_sprite(struct DoorTransitionEffect *effect, struct ObjectPosition *position, struct SpriteFrameState *unused_sprite);

/* Animated menu ring callback installed by its object creator. */
void initialize_animated_menu_ring(MenuRingAnimationState *state);

#endif

#ifndef DUNGEON_EFFECT_MOTION_H
#define DUNGEON_EFFECT_MOTION_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"
struct S_7FFE83DC_3;
struct S_80024EF8_0;
void create_positioned_color_sprite(struct S_7FFE83DC_3 *source, s32 color);
s32 create_indexed_color_sprite(MovingPosition *origin, u16 index);
s32 draw_counter_rotating_cylinders(struct S_80024EF8_0 *effect, s32 center, s32 unused_value);
void spawn_jittered_child_effect( void *source, s16 field_34, s32 field_28, s16 field_52, s16 offset_x, s16 offset_y, s16 offset_z);
void spawn_variant_effect_with_random_motion(s32 pos_x, s32 pos_y, s32 pos_z, u32 variant);


void animate_object_motion_and_scale(void *object, ObjectPosition *motion, void *display);


/* Body allocated with flags 0x201 by the bank timed-visual sequence and its
 * relinks. create_cylindrical_effect decrements +0x48, advances +0x4C and
 * toggles +0x58. The spawner copies the attachment origin to +0x0C..+0x10. */
typedef struct CylindricalEffectWork {
    u8 pad_00[0xC];
    s16 origin_x, origin_y, origin_z;
    u8 pad_12[0x36];
    union { s16 s; u16 u; } timer;
    u8 pad_4A[2];
    s16 stage;
    u8 pad_4E[0xA];
    s32 shade;
} CylindricalEffectWork;

/* Set to 1 by running particle/point effects every frame; the effect
 * controller in entry_play_sound_if_enabled clears it and finishes the effect
 * once a whole period passes with it still clear. */
extern s16 particle_effect_active;

#endif

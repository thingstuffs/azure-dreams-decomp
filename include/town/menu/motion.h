#ifndef TOWN_MENU_MOTION_H
#define TOWN_MENU_MOTION_H

#include "common.h"
#include "records/Rec_D_80100B70.h"
#include "shared/entity.h"

struct Obj800A5BC0;
struct ObjectPosition;

/* Body of the resource display object advanced by advance_animation_phase_and_frame. */
typedef struct MenuAnimationPhaseObject {
    /* 0x00 */ union { u16 u; s16 s; } frame;
    /* 0x02 */ s16 transition;
    /* 0x04 */ u8 pad_04[2];
    /* 0x06 */ union { u16 word; u8 byte; } phase;
    /* 0x08 */ union { u16 s; s16 u; } offset;
    /* 0x0A */ u8 pad_0A[2];
    /* 0x0C */ s16 state;
    /* 0x0E */ u8 pad_0E[4];
    /* 0x12 */ u16 step;
    /* 0x14 */ union { s16 s; u16 u; } target;
    /* 0x16 */ union { s16 s; u16 u; } value;
} MenuAnimationPhaseObject;

void invoke_menu_motion_handler(void *obj, void *position, void *sprite);
void tick_menu_motion_fade(struct Obj800A5BC0 *obj, void *ctx);
void advance_animation_phase_and_frame(MenuAnimationPhaseObject *anim, struct ObjectPosition *unused);

void draw_textured_sprite_quad(void *sprite, s32 position);
void decrease_value_and_advance_counter(Rec_D_80100B70 *record, s32 value, s32 unused_context);

#endif

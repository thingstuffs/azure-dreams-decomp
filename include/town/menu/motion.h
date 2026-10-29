#ifndef TOWN_MENU_MOTION_H
#define TOWN_MENU_MOTION_H

#include "common.h"
#include "records/Rec_D_80100B70.h"

struct Obj800A5BC0;

void invoke_menu_motion_handler(void *obj, void *position, void *sprite);
void tick_menu_motion_fade(struct Obj800A5BC0 *obj, void *ctx);

void draw_textured_sprite_quad(void *sprite, s32 position);
void decrease_value_and_advance_counter(Rec_D_80100B70 *record, s32 value, s32 unused_context);

#endif

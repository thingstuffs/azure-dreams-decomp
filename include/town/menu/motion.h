#ifndef TOWN_MENU_MOTION_H
#define TOWN_MENU_MOTION_H

#include "common.h"

struct Obj800A5BC0;

void invoke_menu_motion_handler(void *obj, void *position, void *sprite);
void tick_menu_motion_fade(struct Obj800A5BC0 *obj, void *ctx);

#endif

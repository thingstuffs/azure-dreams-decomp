#include "common.h"
#include "engine/menu/animated_panel.h"

/* Ease a struct's current x/y position (at offsets 0x28/0x2A) halfway toward
 * its target x/y (at offsets 0x4/0x6) each call: pos += (target - pos) >> 1. */

/*
 * Adds half the signed target-minus-current delta to each X/Y coordinate, using arithmetic shifts
 * for rounding.
 */
void menu_move_the_position_halfway_toward_target_position(AnimatedMenuPanelBody *position) {
    s32 delta_x, delta_y;
    delta_x = position->target_x - position->elements[0].block.fields.x;
    position->elements[0].block.fields.x = position->elements[0].block.fields.x + (delta_x >> 1);
    delta_y = position->target_y - position->elements[0].block.fields.y;
    position->elements[0].block.fields.y = position->elements[0].block.fields.y + (delta_y >> 1);
}

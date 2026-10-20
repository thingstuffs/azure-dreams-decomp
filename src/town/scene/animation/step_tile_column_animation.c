#include "common.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 state;
    u16 counter;
    s16 x;
    s16 y;
    s16 step;
    s16 angle;
} TownAnimState;

extern void draw_wrapped_tile_column_vertical(s32 x, s32 y, s32 angle);

/* Advance one town animation state machine step and redraw it at its current angle. */
void step_tile_column_animation(TownAnimState *anim)
{
    s32 state = anim->state;

    switch (state) {
    case 0:
    anim->step = anim->angle = 0;
    draw_wrapped_tile_column_vertical(anim->x, anim->y, anim->angle);
    anim->state = 1;
    return;

    case 2:
    if (anim->counter++ & 1) {
        if (anim->step < 12) {
            anim->step++;
        } else {
            anim->state = 3;
        }
    }

    case 3:
    anim->angle -= anim->step;
    while (anim->angle < 0) {
        anim->angle += 32;
        anim->y = (anim->y + 1) % 12;
    }
    draw_wrapped_tile_column_vertical(anim->x, anim->y, anim->angle);
    break;

    case 4:
    anim->angle -= anim->angle >> 2;
    if (anim->angle < 4) {
        anim->angle = 0;
        anim->state = 0;
    }

    draw_wrapped_tile_column_vertical(anim->x, anim->y, anim->angle);

    case 1:
        break;
    }
}

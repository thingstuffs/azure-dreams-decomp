#include "common.h"
#include "town/menu/motion.h"
#include "town/menu.h"

/* Decrease the value with a floor of four, advance the cyclic counter, and update the record. */
void step_door_transition_sprite(struct DoorTransitionEffect *effect, struct ObjectPosition *position, struct SpriteFrameState *unused_sprite) {
    s16 reduced_value;

    reduced_value = effect->brightness - 4;
    effect->brightness = reduced_value;
    if (reduced_value < 4) {
        effect->brightness = 4U;
    }
    effect->texture_y = (effect->texture_y + 1) & 0x7F;
    draw_textured_sprite_quad(effect, position);
}

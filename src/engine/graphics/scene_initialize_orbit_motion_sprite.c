#include "engine/effect/sine_motion.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/sprite_source.h"
#include "common.h"
#include "engine/node.h"
#include "slus/data.h"
#include "engine/graphics.h"
#include "engine/effect.h"

/* Global >8-byte struct accessed via %hi/%lo (passed by address to func_8003DB94
 * as its `Elem`-shaped table argument). */

/* callback/update-function pointers, assigned by address only */
struct ObjectPosition;
struct SpriteFrameState;

/* struct Elem / struct Dst mirror the layout used by the already-matched
 * func_8003DB94 (src/code.c), extended with the extra fields (0x1C/0x1E)
 * this function also touches — the real struct is larger than what
 * func_8003DB94 alone accesses. */


/* Sub-record living at offset 0x20 of the top-level object: a word value
 * followed by three shorts. */
/* Top-level object initialized by this function. */
/* Initializes the object's slot state, callbacks, and default rendering values. */
void scene_initialize_orbit_motion_sprite(SineMotionEffectNode *object, struct Controller *slot)
{
    EffectState800517CC *slot_state;
    SpriteFrameState *render_state;
    ObjectPosition *render_vector;

    object->header.update_callback = update_sine_motion_effect;
    slot_state = &object->body;
    object->body.parent = slot;
    slot_state->state = 0;
    slot_state->timer = 0;
    slot_state->wait = 0;

    render_state = object->header.sprite;
    render_state->color.word = 0x808080;
    select_record_entry_and_value(render_state, orbit_motion_sprite_source, 0);

    render_state->scale_y = 0x1000;
    render_state->scale_x = 0x1000;
    register_node(&object->header, (void *)draw_linked_sprites);

    render_vector = object->header.position;
    render_vector->x.v = 0x01A00000;
    render_vector->y.v = 0x00600000;
    render_vector->z.v = 0x00700000;
}

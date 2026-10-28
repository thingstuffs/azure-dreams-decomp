#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/sprite_source.h"
#include "common.h"
#include "engine/node.h"
#include "slus.h"
#include "slus/data.h"
#include "engine/graphics.h"

/* Global >8-byte struct accessed via %hi/%lo (passed by address to func_8003DB94
 * as its `Elem`-shaped table argument). */

/* callback/update-function pointers, assigned by address only */
extern void update_sine_motion_effect(void);
struct ObjectPosition;
struct SpriteFrameState;

/* struct Elem / struct Dst mirror the layout used by the already-matched
 * func_8003DB94 (src/code.c), extended with the extra fields (0x1C/0x1E)
 * this function also touches — the real struct is larger than what
 * func_8003DB94 alone accesses. */


typedef struct S_80051BFC_Dst {
    SpriteSourceEntry *f0;
    u8 f4;
    u8 f5;
    u8 pad6;
    u8 pad7;
    s32 f8;
    s32 fc;
    s32 f10;
    u16 f14;
    u8 pad16[0x1C - 0x16];
    u16 f1c;
    u16 f1e;
} S_80051BFC_Dst;

/* Sub-record living at offset 0x20 of the top-level object: a word value
 * followed by three shorts. */
typedef struct S_80051BFC_Sub {
    void *val;
    s16 x;
    s16 y;
    s16 z;
} S_80051BFC_Sub;

/* Top-level object initialized by this function. */
typedef struct S_80051BFC_Obj {
    ObjectNodeHeader header;
    S_80051BFC_Sub sub;
} S_80051BFC_Obj;

/* Initializes the object's slot state, callbacks, and default rendering values. */
void scene_initialize_orbit_motion_sprite(void *object_ptr, void *slot)
{
    S_80051BFC_Obj *object = object_ptr;
    S_80051BFC_Sub *slot_state;
    SpriteFrameState *render_state;
    ObjectPosition *render_vector;

    object->header.update_callback = update_sine_motion_effect;
    slot_state = &object->sub;
    object->sub.val = slot;
    slot_state->x = 0;
    slot_state->y = 0;
    slot_state->z = 0;

    render_state = object->header.sprite;
    render_state->color.word = 0x808080;
    select_record_entry_and_value(render_state, (SpriteSourceEntry *)orbit_motion_sprite_source, 0);

    render_state->scale_y = 0x1000;
    render_state->scale_x = 0x1000;
    register_node(&object->header, (void *)draw_linked_sprites);

    render_vector = object->header.position;
    render_vector->x.v = 0x01A00000;
    render_vector->y.v = 0x00600000;
    render_vector->z.v = 0x00700000;
}

#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "shared/position_views.h"
#include "town/minigame/state.h"
#include "shared/object_node.h"

   /* the 0x2 bytes before obj in update_object_state_and_size, addressed as obj[-1] */


   /* (void *)work in update_object_state_and_size */


/* Advances object state, updates coordinates and size, or sets status flags. */
void update_object_state_and_size(SceneTileObject *object) {
    SceneTileObject *obj;
    s32 state;
    s32 size;
    u16 state_bits;

    obj = object;

    state = obj->state.s;
    state_bits = (u16) obj->state.s;

    switch (state) {
    case 0:
        obj->state.u = state_bits + 1;
        break;
    case 1:
    {
        ObjectPosition **coords_ref;
        s32 coord;
        s32 offset;

        coords_ref = obj->linked;
        coord = (*coords_ref)->x.w.i;
        if (coord < 0) {
            coord += 0x1F;
        }
        obj->x = (u16) ((coord >> 5) + 0x94);
        coord = (*coords_ref)->y.w.i;
        if (coord < 0) {
            coord += 0x1F;
        }
        obj->y.u = (u16) ((coord >> 5) + 0x75);
        coord = (*coords_ref)->z.w.i;
        coord = 0 - coord;
        offset = coord >> 6;
        if (coord < 0) {
            offset = (s32) (coord + 0x3F) >> 6;
        }
        if (offset < 0) {
            offset = 0;
        }
        size = offset + 3;
        obj->height = size;
        obj->width = size;
        obj->x =
            (u16) (obj->x - offset);
        obj->y.u =
            (u16) (obj->y.u - offset);
        break;
    }
    case 2:
        ((ObjectNodeHeader *)obj - 1)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;
    }
}

/* MECHANISM: The signed 0/1/2 dispatch is laid out in retail block order and
   joins the true-space epilogue at 0x80023D98, so the leaf stays frameless.
   ABI $a0 holds the object; $v1/$v0 carry the two-level pointer loads. */

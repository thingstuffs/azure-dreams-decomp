#include "common.h"
#include "shared/object_flags.h"
#include "engine/node.h"

typedef struct {
    s8 pad00[0x98];
    u8 *field_98;
    u8 *field_9C;
} Obj;

typedef struct {
    u8 pad00[0x1A];
    u16 field_1A;
} State;

/* Mark inactive objects or advance their wrapped 12-bit state value. */
void update_inactive_object_state(Obj *obj, void *unused, State *state)
{
    s32 t;
    if (*obj->field_98 == 0) {
        unlink_node_if_registered(obj);
        *(u16 *)((u8 *)obj - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    state->field_1A += *(s8 *)(obj->field_9C + 0x97);
    t = state->field_1A;
    state->field_1A = t & 0xFFF;
}

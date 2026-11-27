#include "shared/sprite_frame_state.h"
/* Allocate and initialize display object.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_800A48A0.
 */
#include "town/menu/object/allocate_and_initialize_display_object_g01137.h"
#include "shared/object_flags.h"
#include "town/menu/object.h"

#include "shared/object_node.h"/* Allocate an object and initialize its payload, display transform, and color. */
#include "town/menu/position_callbacks_api.h"
#include "town/menu/state_callbacks_api.h"
struct ObjectNodeHeader *allocate_and_initialize_display_object(struct TownObjectRecord *owner, u8 *active_flag, ObjectPosition *origin, s32 part_index, DoorDisplayCallback update,
    DoorDisplayCallback initialize) {
    ObjectNodeHeader *obj = allocate_list_node(0x136, &NODE_HEADER(owner)->next);
    SpriteFrameState *display;
    DoorDisplayBody *payload;

    if (obj == 0) {
        return 0;
    }
    display = obj->sprite;
    obj->update_callback = update;
    payload = NODE_BODY(obj);
    payload->callback = initialize;
    payload->owner = owner;
    payload->origin = origin;
    payload->part_index = part_index;
    payload->active_flag = active_flag;
    display->offset_x = 0x1000;
    display->scale_y = 0x1000;
    display->scale_x = 0x1000;
    display->clut = 0;
    display->flags = 0;
    display->tpage_abr = 0;
    display->color.c.r = g_game_work.view.tint.parts.tint_r;
    display->color.c.g = g_game_work.view.tint.parts.tint_g;
    display->color.c.b = g_game_work.view.tint.parts.tint_b;
    display->flags = 0;
    return obj;
}

/* Create objects with descending indices until allocation fails or index zero is reached. */
s32 create_display_object_series(struct TownObjectRecord *owner, u8 *active_flag, ObjectPosition *origin, s32 count) {
    s32 index;
    index = count;
    do {
        index -= 1;
        if (allocate_and_initialize_display_object(owner, active_flag, origin, index, &D_800A2180, &D_800A21EC) == 0) {
            index += 1;
            break;
        }
    } while (index != 0);
    return index;
}

/* Set object and global flags when the state is zero, otherwise invoke the callback. */
void run_callback_until_state_clears(DoorDisplayBody *object, ObjectPosition *position, struct LitMeshSprite *mesh)
{
    u8 *state;

    state = object->active_flag;
    if (state != 0 && *state == 0) {
        NODE_HEADER(object)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    object->callback(object, position, mesh);
}

/* Initialize object state and placement with a direction-dependent offset. */
void initialize_directional_object_state(DoorDisplayBody *object, ObjectPosition *placement, LitMeshSprite *state) {
    state->frame_entry = 0;
    state->frame_index = 0;
    state->frame_ticks = 0;
    register_node(NODE_HEADER(object), &lit_mesh_renderer_address);
    placement->x.v = object->origin->x.v;
    placement->y.v = object->origin->y.v;
    placement->z.v = object->origin->z.v;
    object->callback = &copy_directional_value;
    if (object->part_index == 0) {
        s32 heading;
        heading = 1;
        state->mesh_index = heading;
        heading = (u16) placement->x.unsigned_parts.integer;
        placement->x.unsigned_parts.integer = (u16) (heading + 0x90);
    } else {
        s32 flags = (u16) state->flags;
        s32 enabled = 1;
        state->mesh_index = enabled;
        state->flags = (u16) (flags | 1);
        placement->x.unsigned_parts.integer = (u16) (placement->x.unsigned_parts.integer - 0x90);
    }
    state->rotation[2] = 0;
}

/* Copy the inner value into the output, negated unless the object's flag is set. */
void copy_directional_value(DoorDisplayBody *object, ObjectPosition *unused, struct LitMeshSprite *mesh) {
    TownObjectRecord *owner = object->owner;

    if (object->part_index != 0) {
        mesh->rotation[2] = owner->origin_heading;
        return;
    }
    mesh->rotation[2] = -owner->origin_heading;
}

/* Forward four inputs to allocate_and_initialize_display_object with two fixed data pointers. */
struct ObjectNodeHeader *create_default_display_object(struct TownObjectRecord *owner, u8 *active_flag, ObjectPosition *origin, s32 part_index) {
    return allocate_and_initialize_display_object(owner, active_flag, origin, part_index, flag_inactive_object_or_run_callback, initialize_lit_mesh_object_with_phase);
}

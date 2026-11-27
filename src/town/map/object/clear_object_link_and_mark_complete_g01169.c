/* Clear object link and mark complete.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_800BDDA8, CL:town/func_800BDE1C.
 */
#include "town/map/object/clear_object_link_and_mark_complete_g01169.h"
#include "shared/object_flags.h"
#include "town/map/object.h"
#include "town/scene.h"
#include "town/scene/object.h"
#include "shared/sprite_frame_state.h"

/* On a successful object check, clear its linked byte and set object and global flags. */
void retire_object_when_out_of_bounds(TownObjectRecord *object, ObjectPosition *context) {
    if (classify_object_against_bounds(object, context) != 0) {
        unlink_scene_list_node(object);
        if (object->spawn_active != 0) {
            *object->spawn_active = 0;
        }
        unlink_node_if_registered(object);
        NODE_HEADER(object)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Initialize object state, scale, and color, then offset and configure the object. */
void init_lit_mesh_object(void *object_id, ObjectPosition *object, LitMeshSprite *sprite) {
    register_node(NODE_HEADER(object_id), lit_mesh_renderer_address);

    sprite->clut = 0;
    sprite->flags = 0;
    sprite->tpage_abr = 0;
    sprite->rotation[0] = 0;
    sprite->rotation[1] = 0;
    sprite->rotation[2] = 0;
    sprite->frame_entry = 0;
    sprite->frame_index = 0;
    sprite->frame_ticks = 0;
    sprite->scale[0] = 0x1000;
    sprite->scale[1] = 0x1000;
    sprite->scale[2] = 0x1000;
    sprite->color.c.r = g_game_work.view.tint.parts.tint_r;
    sprite->color.c.g = g_game_work.view.tint.parts.tint_g;
    sprite->color.c.b = g_game_work.view.tint.parts.tint_b;
    object->z.v += 0x200000;

    init_scene_node_mode_3(object_id, object, D_800D1BDC);
}

/* Update the object and advance its state angle by 0x20 modulo 0x1000. */
void update_spinning_object(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *state) {
    u16 *angle = &state->angle_z;
    s32 t;
    retire_object_when_out_of_bounds(object, position);
    *angle += 0x20;
    t = *angle;
    *angle = t & 0xFFF;
}

/* Install the update handler and select mesh 30. */
void init_spinning_object_long_delay(TownObjectRecord *object, ObjectPosition *context, SpriteFrameState *sprite) {
    LitMeshSprite *state = (LitMeshSprite *)sprite;

    NODE_HEADER(object)->update_callback = D_800BB640;
    init_lit_mesh_object(object, context, state);
    state->mesh_index = 30;
}

/* Forward the object and value to retire_object_when_out_of_bounds. */
void update_static_object(TownObjectRecord *object, ObjectPosition *position) {
    retire_object_when_out_of_bounds(object, position);
}

/* Install the update handler and select mesh 30. */
void init_static_object_long_delay(void *object, ObjectPosition *context, LitMeshSprite *state) {
    NODE_HEADER(object)->update_callback = D_800BB6C4;
    init_lit_mesh_object(object, context, state);
    state->mesh_index = 30;
}

/* Install the update handler and select mesh 14. */
void init_spinning_object_short_delay(TownObjectRecord *object, ObjectPosition *context, SpriteFrameState *sprite) {
    LitMeshSprite *state = (LitMeshSprite *)sprite;

    NODE_HEADER(object)->update_callback = D_800BB640;
    init_lit_mesh_object(object, context, state);
    state->mesh_index = 14;
}

/* Install the update handler and select mesh 14. */
void init_static_object_short_delay(void *object, ObjectPosition *context, LitMeshSprite *state) {
    NODE_HEADER(object)->update_callback = D_800BB6C4;
    init_lit_mesh_object(object, context, state);
    state->mesh_index = 14;
}

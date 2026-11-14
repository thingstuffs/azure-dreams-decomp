#include "shared/entity.h"
#include "town/minigame/object_setup.h"
#include "slus.h"
#include "engine/graphics.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "records/Rec_func_8008F074_arg0.h"
#include "shared/vector.h"
#include "engine/node.h"
#include "town/scene/list_setup.h"
#include "town/minigame.h"
#include "town/minigame/object.h"
#include "town/minigame/state.h"

   /* arg1 in initialize_actor_with_visual_child */

struct Dst;
struct Elem;






extern u8 D_800D2364[];
extern s32 D_800D237C[];
extern u8 D_800F9F78[];

/* Initialize the object and create a positioned visual child linked to it. */
void initialize_actor_with_visual_child(void *object_arg, ObjectPosition *placement, SpriteFrameState *resource_context) {
    Rec_func_8008F074_arg0 *object = object_arg;
    ObjectPosition *position = placement;
    ObjectNodeHeader *child;
    BoundedMovementObject *child_data;
    SpriteFrameState *child_visual;
    ObjectPosition *child_position;

    NODE_HEADER(object)->update_callback = advance_actor_state_nearby_activation;
    object->unk_50 = 0;
    register_node(NODE_HEADER(object), project_sprite_chain);
    position->x.v = 0x0F200000;
    position->y.v = 0x02600000;
    position->z.v = 0;
    init_scene_node_mode_1(object, position, &D_800D2364[0]);
    select_record_entry_and_value(resource_context, &D_800F9F78[0], 0);
    object->unk_48 = D_800D237C[0];
    child = allocate_flagged_object_node(0x136);
    if (child != 0) {
        child_data = NODE_BODY(child);
        register_node(child, draw_linked_lit_meshes);
        child_visual = child->sprite;
        child->update_callback = advance_object_bounded_movement_phases;
        child_visual->scale_x = 0x1000;
        child_visual->scale_y = 0x1000;
        child_visual->offset_x = 0x1000;
        child_visual->angle_z = 0;
        child_visual->color.word = 0x808080;
        child_visual->source = 0x75;
        child_position = child->position;
        child_position->x.v = 0x0FA00000;
        child_position->y.v = 0x02300000;
        child_position->z.v = 0;
        child_data->linked_object = object;
    }
}

/* MECHANISM: Natural argument liveness gives the 0x20 frame and s2/s0/s1 save order. This restores the
   0xA0(v0) store and its upstream branch displacement; aligned residue is zero. */

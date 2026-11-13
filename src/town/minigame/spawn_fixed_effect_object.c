#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "slus.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/object_links.h"
#include "shared/vector.h"
#include "engine/node.h"
#include "town/minigame.h"
#include "town/scene.h"
#include "town/minigame/state.h"

#ifndef NULL
#define NULL 0
#endif



extern u8 D_800D232C[];
extern s32 D_800D2344[3];

/* Creates and initializes an object, then sets the caller and global flags. */
void spawn_fixed_effect_object(TownObjectRecord *caller_data, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
    FixedInteractionEffectBody *transform;
    ObjectPosition *position;
    ObjectNodeHeader *object;
    SpriteFrameState *render_state;
    s32 transform_value;
    u32 color;

    object = allocate_flagged_object_node(0x136);
    if (object != NULL) {
        register_node(object, draw_linked_lit_meshes);
        color = 0x00808080U;

        object->update_callback = advance_interaction_state_animating_cursor;
        render_state = object->sprite;
        render_state->scale_x = 0x1000;
        render_state->scale_y = 0x1000;
        render_state->offset_x = 0x1000;
        render_state->color.word = color;
        transform = NODE_BODY(object);
        render_state->angle_z = 0;
        render_state->source = 0x4A;
        position = object->position;
        position->x.v = 0x02C00000;
        position->y.v = 0x02300000;
        transform_value = D_800D2344[0];
        position->z.v = 0xFFC00000;
        transform->setup_value = transform_value;
        init_scene_node_mode_1(transform, position, D_800D232C);
    }
    NODE_HEADER(caller_data)->flags |= 0x8000;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}

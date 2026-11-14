#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "dungeon/effect/screen.h"
#include "engine/scene.h"
#include "dungeon/effect/shade.h"
#include "engine/node.h"
#include "dungeon/effect/shade_callbacks_api.h"


extern s32 D_80026490;
extern s32 linked_mesh_processor_address[3];

/* Creates three groups of sixteen objects at the supplied coordinates. */
void *create_effect_object_groups(s16 x, s16 y, s16 z)
{
    s32 group_index;
    s32 object_index;
    s32 object_flags;
    s32 init_value = 0;
    u16 render_flags;
    ObjectNodeHeader *object;
    ObjectPosition *coords;
    SpriteFrameState *render;
    EffectObjectGroupsBody *state;
    void *callback;
    void *texture;

    if (has_enough_available_nodes(0x30) == 0) {
        return 0;
    }
    group_index = 2;

    callback = update_staged_effect_fade;
    texture = &D_80026490;

    do {
        object_index = 15;
        do {
            object_flags = 2;
            if (object_index != 0) {
                object_flags = 0x202;
            }
            object = allocate_flagged_object_node(object_flags);
            if (object != 0) {
                object->update_callback = callback;
                register_node(object, &linked_mesh_processor_address);
                coords = object->position;
                *((s16 *)&coords->velocity_x + 1) = x;
                coords->x.w.i = x;
                *((s16 *)&coords->velocity_y + 1) = y;
                coords->y.w.i = y;
                *((s16 *)&coords->velocity_z + 1) = z;
                coords->z.w.i = z;
                render = object->sprite;
                render->depth_bias = 0x10;
                if (group_index != 0) {
                    render->scale_y = 0x100;
                } else {
                    render->scale_y = 0x800;
                }
                render_flags = render->scale_y;
                render->flags = 0xC;
                render->tpage_abr = 0x20;
                state = NODE_BODY(object);
                init_value = 8;
                render->source = texture;
                render->scale_x = render_flags;
                state->unk_1A.s = init_value;
                state->unk_64.s = init_value;
                state->unk_22 = object_index;
                state->unk_24 = group_index;
                state->unk_5C = x;
                state->unk_5E = y;
                state->unk_60 = z;
            }

            object_index--;
        } while (object_index >= 0);
        group_index--;
    } while (group_index >= 0);
    return object;
}

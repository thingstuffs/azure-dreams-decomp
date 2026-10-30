#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "engine/scene.h"


typedef struct S_800262AC_3 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    u8 pad_1C[0x6];
    s16 unk_22;
    s16 unk_24;
    u8 pad_26[0x36];
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    u8 pad_62[0x2];
    s16 unk_64;
} S_800262AC_3;   /* state in create_effect_object_groups */

extern void register_node(void *, void *);

extern s32 D_80025E48;
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
    S_800262AC_3 *state;
    void *callback;
    void *texture;

    if (has_enough_available_runtime_nodes(0x30) == 0) {
        return 0;
    }
    group_index = 2;

    callback = &D_80025E48;
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
                state = (u8 *)object + 0x20;
                init_value = 8;
                render->source = texture;
                render->scale_x = render_flags;
                state->unk_1A = init_value;
                state->unk_64 = init_value;
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

#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "engine/node.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "dungeon/monster/cyclone.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x12];
    u16 field_12;
} RenderDataFieldView_80E12058;

#ifndef NULL
#define NULL 0
#endif



typedef struct {
    s32 words[6];
} Copy24;

extern u8 D_8017573C;
extern u8 cyclone_view_direction_entries[];

/* Allocate and initialize an object with source direction, render properties, and copied data. */
void *create_directional_render_object(void *direction_src, Copy24 *initial_data, void *render_src) {
    SpriteFrameState *render_data;
    DirectionalRenderObjectBody *object_state;
    ObjectNodeHeader *object;
    void *data_dst;
    u16 render_attr;
    ActorRecord *direction_ref = direction_src;
    Copy24 *data_src = initial_data;
    SpriteFrameState *render_ref = render_src;

    object = allocate_flagged_object_node(0x312);
    if (object != NULL) {
        object->update_callback = &D_8017573C;
        register_node(object, project_sprite_chain);
        object_state = NODE_BODY(object);
        object_state->facing_angle.u =
            (u16)(u16)(direction_ref->facing);
        render_data = object->sprite;
        render_data->animation_resource =
            render_ref->animation_resource;
        render_attr = render_ref->clut;
        render_data->color.word = 0x808080;
        render_data->scale_y = 0x800;
        render_data->scale_x = 0x800;
        render_data->clut = render_attr;
        select_sprite_entry(
            render_data,
            cyclone_view_direction_entries[
                ((g_game_work.view.camera_rotation.parts.viewAngle + object_state->facing_angle.s + 0x100) >> 9) &
                7],
            0);
        data_dst = object->position;
        *(Copy24 *)data_dst = *data_src;
        return object;
    }
    return NULL;
}

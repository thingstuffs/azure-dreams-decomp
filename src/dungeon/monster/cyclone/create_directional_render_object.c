#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x12];
    u16 field_12;
} RenderDataFieldView_80E12058;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80175858_1 {
    u8 pad_00[0x4];
    union { u16 s; s16 u; } unk_04;   /* accessed as both */
} S_80175858_1;

typedef struct S_80175858_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80175858_2;   /* arg0_hold in create_directional_render_object */

typedef struct S_80175858_4 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x14];
    s32 unk_28;
} S_80175858_4;   /* arg2_hold in create_directional_render_object */

typedef struct {
    s32 words[6];
} Copy24;

void register_node(void *, void *);
void select_sprite_entry(void *, u8, s32);
extern u8 D_8017573C;
extern u8 cyclone_view_direction_entries[];

/* Allocate and initialize an object with source direction, render properties, and copied data. */
void *create_directional_render_object(void *direction_src, Copy24 *initial_data, void *render_src) {
    SpriteFrameState *render_data;
    void *object_state;
    ObjectNodeHeader *object;
    void *data_dst;
    u16 render_attr;
    void *direction_ref = direction_src;
    Copy24 *data_src = initial_data;
    void *render_ref = render_src;

    object = allocate_flagged_object_node(0x312);
    if (object != NULL) {
        object->update_callback = &D_8017573C;
        register_node(object, project_sprite_chain);
        object_state = ((void *)object) + 0x20;
        ((S_80175858_1 *)object_state)->unk_04.s =
            (u16)((S_80175858_2 *)direction_ref)->unk_2A;
        render_data = object->sprite;
        render_data->animation_resource =
            ((S_80175858_4 *)render_ref)->unk_28;
        render_attr = ((S_80175858_4 *)render_ref)->unk_12;
        render_data->color.word = 0x808080;
        render_data->scale_y = 0x800;
        render_data->scale_x = 0x800;
        render_data->clut = render_attr;
        select_sprite_entry(
            render_data,
            cyclone_view_direction_entries[
                ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80175858_1 *)object_state)->unk_04.u + 0x100) >> 9) &
                7],
            0);
        data_dst = object->position;
        *(Copy24 *)data_dst = *data_src;
        return object;
    }
    return NULL;
}

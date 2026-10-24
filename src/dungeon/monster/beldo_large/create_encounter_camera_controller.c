#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"


typedef struct {
    s32 x;
    s32 y;
    s32 z;
} __attribute__((packed)) PackedVec;

extern s32 register_node();
extern s32 D_801717A8;
extern PackedVec encounter_object_position_template;
extern void *beldo_camera_object;


typedef struct S_80171C7C_0 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80171C7C_0;

typedef struct S_80171C7C_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80171C7C_1;

typedef struct S_80171C7C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80171C7C_2;

/* Creates an object with default coordinates and initializes its rendering state. */
void create_encounter_camera_controller(void) {
    ObjectPosition *coords;
    SpriteFrameState *render_state;
    ObjectNodeHeader * object;
    u16 render_flags;

    object = allocate_flagged_object_node(0x12);
    if (object != 0) {
        (*(s16 *)((u8 *)object + 0x38)) = 0;
        (*(s32 * *)((u8 *)object + 0x10)) = &D_801717A8;
        register_node(object, project_sprite_chain);
        render_state = object->sprite;
        render_state->depth_bias = 0;
        coords = object->position;
        coords->x.v = view_reference_entity.x.v;
        coords->y.v = view_reference_entity.y.v;
        coords->z.v = view_reference_entity.z.v;
        render_state = object->sprite;
        render_state->scale_y = 0x1000;
        render_state->scale_x = 0x1000;
        render_state->color.c.b = 0x80;
        render_state->color.c.g = 0x80;
        render_state->color.c.r = 0x80;
        render_flags = render_state->flags;
        beldo_camera_object = object;
        render_state->flags = render_flags | 0x80;
        (*(PackedVec *)((u8 *)object + 0x48)) = encounter_object_position_template;
        render_state->source = (u8 *)object + 0x48;
    }
}

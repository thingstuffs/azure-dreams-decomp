#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

typedef struct {
    s16 values[8][3][3];
} LocalPositionTable;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct {
    u8 pad_00[0x2A];
    u16 direction;
} EffectSource;

typedef struct {
    u8 pad_00[0x0C];
    u8 red;
    u8 green;
    u8 blue;
    u8 pad_0F;
    s16 intensity;
    u8 pad_12[2];
    u16 flags;
    u8 pad_16[6];
    s16 scale_x;
    s16 scale_y;
} RenderState;

typedef struct {
    u8 pad_00[0x18];
    s16 size_x;
    s16 size_y;
    u16 color_mode;
    u8 pad_1E[6];
    void *effect_data;
    u8 pad_28[0x34];
    s32 position[3];
    u8 pad_68[0x0C];
    s16 vertices[4][3];
} EffectPayload;

typedef struct {
    u8 pad_00[8];
    Vec3 *position;
    RenderState *render;
    void *callback;
    u8 pad_14[0x0C];
    EffectPayload payload;
} EffectObject;

extern void select_record_entry_and_value(void *state, void *entries, short index);
extern void register_node(EffectObject *, void *);

extern u8 ribbon_sprite_entries[];
extern LocalPositionTable D_8016484C;
extern u8 D_80167C74[];
extern s16 ribbon_vertices[][8][2][3];

/* Create a direction- and color-selected effect and initialize its vertices. */
void create_targeted_ribbon_trail(EffectSource *source, Vec3 *origin, void *unused,
                   void *effect_data, s32 input_color_mode)
{
    LocalPositionTable positions;
    EffectObject *object;
    EffectPayload *payload;
    SpriteFrameState *render;
    ObjectPosition *effect_position;
    register EffectSource *held_source;
    s32 mode;
    s32 vertex_sentinel;
    u32 intensity;
    s32 pair_index;
    s32 vertex_index;
    s32 axis;
    u16 color_mode;

    color_mode = (u16)input_color_mode;
    held_source = source;
    positions = D_8016484C;
    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        payload = &object->payload;
        payload->size_x = 0x50;
        payload->size_y = 0x50;
        payload->color_mode = color_mode;
        payload->effect_data = effect_data;
        object->callback = D_80167C74;
        register_node(object, project_sprite_chain);

        render = object->render;
        intensity = 0x60;
        render->tpage_abr = intensity;
        render->flags |= 0x8C;

        effect_position = object->position;
        effect_position->x.v = origin->x;
        effect_position->y.v = origin->y;
        effect_position->z.v = origin->z;

        vertex_sentinel = -1;
        payload->vertices[0][0] = vertex_sentinel;
        payload->vertices[1][0] = 1;
        payload->vertices[3][0] = 1;
        payload->vertices[2][0] = vertex_sentinel;
        payload->vertices[0][2] = -0x14;
        payload->vertices[1][2] = -0x14;
        payload->vertices[2][2] = -0x14;
        payload->vertices[3][2] = -0x14;

        render = ((ObjectNodeHeader *)object)->sprite;
        render->scale_y = 0x1000;
        render->scale_x = 0x1000;
        render->color.c.b = intensity;
        render->color.c.g = intensity;
        render->color.c.r = intensity;

        mode = (s16)color_mode;
        if (mode == 0) {
            render->color.c.r = 0xC0;
        }
        if (mode == 1) {
            render->color.c.g = 0xC0;
        }
        if (mode == 2) {
            render->color.c.b = 0xC0;
        }

        payload->position[0] =
            positions.values[(held_source->direction >> 9) & 7][mode][0] * 0x50000;
        payload->position[1] =
            positions.values[(held_source->direction >> 9) & 7][mode][1] * 0x50000;
        payload->position[2] =
            positions.values[(held_source->direction >> 9) & 7][mode][2] << 19;
        select_record_entry_and_value(render, ribbon_sprite_entries, 0);

        pair_index = 0;
        do {
            vertex_index = 0;
            do {
                axis = 0;
                do {
                    ribbon_vertices[(s16)payload->color_mode]
                    [pair_index][vertex_index][axis] =
                        payload->vertices[vertex_index][axis];
                    axis++;
                } while (axis < 3);
                vertex_index++;
            } while (vertex_index < 2);
            pair_index++;
        } while (pair_index < 8);
    }

    (void)unused;
}

#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define VS16_AT(p, o) (*(volatile s16 *)((u8 *)(p) + (o)))
#define VPTR_AT(p, o) (*(void * volatile *)((u8 *)(p) + (o)))

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

extern void func_8003DB94(RenderState *, void *, s16);
extern EffectObject *func_8003FC64(s32);
extern void func_8004491C(EffectObject *, void *);

extern u8 D_80045340;
extern u8 D_800DEAE0[];
extern LocalPositionTable D_8016484C;
extern u8 D_80167C74[];
extern s16 D_80175DD8[][8][2][3];

/* Create a direction- and color-selected effect and initialize its vertices. */
void func_801685CC(EffectSource *source, Vec3 *origin, void *unused,
                   void *effect_data, s32 input_color_mode)
{
    LocalPositionTable positions;
    EffectObject *object;
    EffectPayload *payload;
    RenderState *render;
    /* Retained legacy pin: retail reuses this pointer register for the -1
       vertex sentinel. Ordinary scalar forms move the sentinel stores. */
    register Vec3 *effect_position ASM_REG("$3");
    register EffectSource *held_source;
    s32 mode;
    u32 intensity;
    s32 pair_index;
    s32 vertex_index;
    s32 axis;
    u16 color_mode;

    color_mode = (u16)input_color_mode;
    held_source = source;
    positions = D_8016484C;
    object = func_8003FC64(0x212);
    if (object != NULL) {
        payload = &object->payload;
        payload->size_x = 0x50;
        payload->size_y = 0x50;
        payload->color_mode = color_mode;
        payload->effect_data = effect_data;
        object->callback = D_80167C74;
        func_8004491C(object, &D_80045340);

        render = object->render;
        intensity = 0x60;
        render->intensity = intensity;
        render->flags |= 0x8C;

        effect_position = object->position;
        effect_position->x = origin->x;
        effect_position->y = origin->y;
        effect_position->z = origin->z;

        effect_position = (Vec3 *)-1;
        VS16_AT(payload, 0x7A) = 1;
        VS16_AT(payload, 0x86) = 1;
        VS16_AT(payload, 0x74) = (s32)effect_position;
        VS16_AT(payload, 0x80) = (s32)effect_position;
        VS16_AT(payload, 0x78) = -0x14;
        VS16_AT(payload, 0x7E) = -0x14;
        VS16_AT(payload, 0x84) = -0x14;
        VS16_AT(payload, 0x8A) = -0x14;

        render = (RenderState *)VPTR_AT(object, 0xC);
        VS16_AT(render, 0x1E) = 0x1000;
        VS16_AT(render, 0x1C) = 0x1000;
        render->blue = intensity;
        render->green = intensity;
        render->red = intensity;

        mode = (s16)color_mode;
        if (mode == 0) {
            render->red = 0xC0;
        }
        if (mode == 1) {
            render->green = 0xC0;
        }
        if (mode == 2) {
            render->blue = 0xC0;
        }

        payload->position[0] =
            positions.values[(held_source->direction >> 9) & 7][mode][0] * 0x50000;
        payload->position[1] =
            positions.values[(held_source->direction >> 9) & 7][mode][1] * 0x50000;
        payload->position[2] =
            positions.values[(held_source->direction >> 9) & 7][mode][2] << 19;
        func_8003DB94(render, D_800DEAE0, 0);

        pair_index = 0;
        do {
            vertex_index = 0;
            do {
                axis = 0;
                do {
                    D_80175DD8[(s16)payload->color_mode]
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

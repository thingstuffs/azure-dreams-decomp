#include "shared/object_node.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
void register_node(void *, void *); /* extern */
s32 rsin();                             /* extern */
s32 rcos();                             /* extern */
extern u8 D_800250B4[];
extern u8 ring_effect_work[];

typedef struct S_81959B44_2 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0xE];
    s16 unk_30;
    u8 pad_32[0x6];
    s16 unk_38;
    u8 pad_3A[0x2];
    u16 unk_3C;
} S_81959B44_2;

/* Create sixteen objects in a ring around the given center with a scaled radius. */
void *create_ring_object_group(s16 center_x, s16 center_y, s16 center_z, s16 radius_scale) {
    s32 call_pad_4;
    s32 call_pad_6;
    s32 call_pad_8;
    s32 div6_magic;
    s32 object_flags;
    s16 pos_y;
    s16 pos_x;
    s32 ring_index;
    s32 y_scale_product;
    s32 y_component;
    s32 x_component;
    s32 x_offset;
    s32 angle;
    s32 neg_y_fixed;
    s32 x_fixed;
    S_81959B44_2 *state;
    ObjectPosition *position;
    SpriteFrameState *transform;
    ObjectNodeHeader *object;

    ring_index = 0;
    div6_magic = 0x2AAAAAAB;
    do {
        object_flags = 0x12;
        if (radius_scale != 0) {
            object_flags = 0x212;
        }
        object = allocate_flagged_object_node(object_flags);
        if (object != 0) {
            object->update_callback = &D_800250B4;
            register_node(object, draw_linked_sprites_clipped);
            angle = ring_index << 8;
            position = object->position;
            x_component = rcos(angle) >> 7;
            x_offset = x_component + ((s32) ((s16) x_component * radius_scale) >> 2);
            y_component = rsin(angle) >> 7;
            y_scale_product = (s16) y_component * radius_scale;
            state = ((void *)object) + 0x20;
            pos_x = center_x + x_offset;
            position->x.w.i = pos_x;
            state->unk_1C = pos_x;
            pos_y = center_y + (y_component + (y_scale_product >> 2));
            position->y.w.i = pos_y;
            state->unk_1E = pos_y;
            position->z.w.i = center_z;
            state->unk_20 = center_z;
            transform = object->sprite;
            transform->source = &ring_effect_work;
            transform->scale_x = 0x1000;
            transform->angle_z = (u16) (angle + 0x400);
            neg_y_fixed = 0 - (rsin(angle) << 0xC);
            transform->angle_x = (s16) ((neg_y_fixed / 6) >> 0xC);
            x_fixed = rcos(angle) << 0xC;
            transform->angle_y = (s16) ((x_fixed / 6) >> 0xC);
            state->unk_14 = pos_x;
            state->unk_16 = pos_y;
            state->unk_18 = center_z;
            state->unk_38 = ring_index;
            state->unk_30 = (s16) (radius_scale + 4);
            state->unk_3C = (u16) radius_scale;
        }
        ring_index += 1;
    } while (ring_index < 0x10);
    return object;
}

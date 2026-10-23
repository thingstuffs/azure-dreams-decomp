#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

typedef struct S_818C32F4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818C32F4_0;

typedef struct S_818C32F4_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_818C32F4_1;

typedef struct S_818C32F4_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xA];
    u16 unk_1A;
} S_818C32F4_3;   /* template_arg in create_dimmed_copy_effect */

typedef struct S_818C32F4_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818C32F4_4;   /* arg1 in create_dimmed_copy_effect */

typedef struct S_818C32F4_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818C32F4_5;

extern s32 select_record_entry_and_value();
extern s32 register_node();
extern u8 D_80024A08[9];
extern u8 D_80025B38[9];
extern u8 clipped_sprite_renderer_address[9];

/* Creates an object with the supplied identifier, data, and visual template. */
s32 create_dimmed_copy_effect(s32 *object_id, S_818C32F4_4 *source_data, void *visual_template) {
    u16 angle;
    void *init_data;
    SpriteFrameState *visual;
    ObjectNodeHeader *object;
    S_818C32F4_1 *object_state;
    S_818C32F4_5 *object_data;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        object->unk_10 = D_80024A08;
        ((S_818C32F4_0 *)object)->unk_20 = *object_id;
        object_state = (u8 *)object + 0x20;
        object_state->unk_04 = 0;
        object_state->unk_06 = 0;
        visual = object->sprite;
        visual->color.word = ((S_818C32F4_3 *)(visual_template))->unk_0C;
        if ((u8)visual->color.word != 0) {
            visual->color.c.r = 0xC0;
        }
        if (visual->color.c.g != 0) {
            visual->color.c.g = 0xC0;
        }
        if (visual->color.c.b != 0) {
            visual->color.c.b = 0xC0;
        }
        visual->flags = visual->flags | 0xC;
        visual->tpage_abr = visual->tpage_abr | 0x60;
        select_record_entry_and_value(visual, D_80025B38, 0);
        init_data = clipped_sprite_renderer_address;
        angle = ((S_818C32F4_3 *)(visual_template))->unk_1A;
        visual->scale_y = 0x1400;
        visual->scale_x = 0x1400;
        visual->angle_z = angle;
        register_node(object, init_data);
        object_data = object->position;
        *object_data = *(S_818C32F4_5 *)source_data;
        return (s32)object;
    }
    return 0;
}

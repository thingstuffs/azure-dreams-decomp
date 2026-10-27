#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "engine/node.h"

typedef struct S_818BCFB0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818BCFB0_0;   /* obj in create_offset_color_effect */

typedef struct S_818BCFB0_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s8 unk_0E;
} S_818BCFB0_1;   /* init_state in create_offset_color_effect */

typedef struct S_818BCFB0_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_818BCFB0_3;

typedef struct {
    s32 word[6];
} Copy24;

extern u8 D_80024088[];
extern u8 D_800241CC[];

/* Create an object, initialize its state, and copy data with a scaled component offset. */
s32 create_offset_color_effect(s32 *initial_word, void *source_data, s16 offset)
{
    s32 offset_numerator;
    ObjectPosition *object_data;
    ObjectNodeHeader *obj;
    SpriteFrameState *scale_state;

    obj = allocate_flagged_object_node(0x212);
    if (obj != 0) {
        obj->update_callback = D_80024088;
        register_node(obj, D_800241CC);

        {
            S_818BCFB0_1 *init_state;
            s32 init_value;

            init_value = 0x7DCF;
            ((S_818BCFB0_0 *)obj)->unk_20 = *initial_word;
            init_state = (u8 *)obj + 0x20;
            init_state->unk_04 = 0;
            init_state->unk_06 = 0;
            init_state->unk_08 = 0;
            init_state->unk_0A = offset;
            init_state->unk_0C = init_value;
            init_state->unk_0E = 0;
        }

        scale_state = obj->sprite;
        scale_state->scale_y = 0x1000;
        scale_state->scale_x = 0x1000;

        object_data = obj->position;
        offset_numerator = offset * 3;
        *(Copy24 *)object_data = *(Copy24 *)source_data;

        if (offset_numerator < 0) {
            offset_numerator += 3;
        }
        {
            s32 object_addr;
            s32 component;
            s32 component_offset;

            object_addr = (s32)obj;
            component = (u16)object_data->z.w.i;
            component_offset = offset_numerator >> 2;
            component += component_offset;
            object_data->z.w.i = component;
            return object_addr;
        }
    }
    return 0;
}

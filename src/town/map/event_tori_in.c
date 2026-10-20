#include "modules/town_map_props.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/entity.h"

extern M2C_UNK D_800E9E14;

typedef struct {
    s32 words[4];
} Copy16;

typedef struct {
    s32 words[2];
} Copy8;

typedef struct S_800BD980_0 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
} S_800BD980_0;

typedef struct S_800BD980_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_800BD980_1;

typedef struct LinkedMotionObject {
    u8 pad_00[0x10];
    union {
        void (*parent)(void *);
        void (*child)(void *, void *, s32);
    } update;
    u8 pad_14[0x14];
    Copy16 position;
    Copy8 motion;
} LinkedMotionObject;

typedef struct MotionSource {
    Copy16 position;
    Copy8 motion;
} MotionSource;

/* event_tori_in: Creates a parent object and two linked render objects offset from the supplied position. */
s32 event_tori_in(void *source) {
    void *source_data;
    s32 child_index;
    s32 x_step;
    SpriteFrameState *render_state;
    S_800BD980_1 *transform;
    void *object;
    S_800BD980_0 *origin;
    void *child_slot;
    void (*child_handler)(void *, void *, s32);

    source_data = source;
    child_slot = NULL;
    object = allocate_list_node(0x202, ((s32 *)&D_80083498.next));
    if (object != NULL) {
        child_slot = object + 0x20;
        ((LinkedMotionObject *)object)->update.parent = randomize_paired_object_motion;
        ((LinkedMotionObject *)object)->position = ((MotionSource *)source_data)->position;
        ((LinkedMotionObject *)object)->motion = ((MotionSource *)source_data)->motion;
    }
    child_index = 1;
    child_handler = advance_motion_and_flag_zero_velocity;
    x_step = 0x300000;
    child_slot = child_slot + 4;
    do {
        object = allocate_list_node(0x312, ((s32 *)&D_80083498.next));
        if (object != NULL) {
            s32 motion_base = 0;
            s32 color;
            u16 source_x_hi;
            u16 source_y_hi;
            s32 x_offset;
            s32 y_offset;
            s32 z_offset;

            register_node(object, project_sprite_chain);
            motion_base = 0xFFF88000;
            color = 0x800000;
            transform = ((ObjectNodeHeader *)object)->unk_08;
            color |= 0x8080;
            ((LinkedMotionObject *)object)->update.child = child_handler;
            *(void **)child_slot = transform;
            render_state = ((ObjectNodeHeader *)object)->unk_0C;
            source_x_hi = (u16)((EntityRec *)source_data)->x.w.i;
            origin = object + 0x20;
            origin->unk_0C = source_x_hi;
            source_y_hi = (u16)((EntityRec *)source_data)->y.w.i;
            origin->unk_0E = source_y_hi;
            origin->unk_10 = (u16)((EntityRec *)source_data)->z.w.i;
            x_offset = x_step + 0x01400000;
            transform->unk_00 = (s32) (((EntityRec *)source_data)->x.v + x_offset);
            {
                s32 source_y;
                source_y = ((EntityRec *)source_data)->y.v;
                y_offset = child_index << 0x15;
                transform->unk_04 = (s32) (source_y + y_offset);
            }
            z_offset = (child_index << 0x13) + 0xFF800000;
            transform->unk_08 = (s32) (((EntityRec *)source_data)->z.v + z_offset);
            transform->unk_0C = (s32) (motion_base - (child_index << 0x10));
            render_state->scale_y = 0x1000;
            render_state->scale_x = 0x1000;
            render_state->color.word = color;
            func_8003DB94(render_state, &D_800E9E14, 0);
        }
        x_step += 0xFFD00000;
        child_index -= 1;
        child_slot = (void *)((s8 *)child_slot - 4);
    } while (child_index >= 0);
    return 0;
}

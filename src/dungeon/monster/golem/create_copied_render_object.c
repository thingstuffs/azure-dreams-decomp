#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
#include "dungeon/monster/golem.h"

typedef struct { s32 word[6]; } Copy24;

typedef struct S_80174EB4_1 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
} S_80174EB4_1;   /* slot in create_copied_render_object */

typedef struct S_80174EB4_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174EB4_5;   /* dst in create_copied_render_object */

typedef struct S_80174EB4_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80174EB4_6;   /* query_arg in create_copied_render_object */

extern void *allocate_list_node(s32, s32);
extern void register_node(void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern s32 resolve_record_orientation_or_fallback(s32, void *, u16 *, s32);

/* Create a render object, copy its source state, and apply queried position offsets. */
s32 create_copied_render_object(s32 priority, EntityRec *source_state, Rec_func_800AA258_arg2 *render_data) {
    u16 offsets[3];
    ObjectNodeHeader *object;
    S_80174EB4_5 *state;
    SpriteFrameState *primitive;
    S_80174EB4_1 *context;

    object = allocate_list_node(0x312, priority - 0x20);
    if (object != 0) {
        object->update_callback = advance_timed_target_flags;
        register_node(object, project_sprite_chain);

        context = (u8 *)object + 0x20;
        context->unk_04 = source_state;
        context->unk_08 = render_data;

        primitive = object->sprite;
        primitive->animation_resource = render_data->unk_28;
        primitive->color.c.b = 0x80;
        primitive->color.c.g = 0x80;
        primitive->color.c.r = 0x80;
        primitive->scale_y = 0x1000;
        primitive->scale_x = 0x1000;
        primitive->flags |= 0xC;
        primitive->tpage_abr |= 0x20;
        select_sprite_entry(primitive, 0x38, 0);

        {
            S_80174EB4_6 *query_data = render_data;
            u16 *offset_out;

            render_data = object->position;
            state = (void *)render_data;
            *(Copy24 *)state = *(Copy24 *)source_state;
            offset_out = offsets;

            offsets[2] = 0;
            offsets[1] = 0;
            offsets[0] = 0;
            if (resolve_record_orientation_or_fallback(query_data->unk_08, query_data,
                              offset_out, 0) != 0) {
                state->unk_00.at02.v += offsets[0];
                state->unk_04.at02.v += offsets[1];
                state->unk_08.at02.v += offsets[2];
            }
        }
        return (s32)object;
    }
    return 0;
}

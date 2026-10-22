#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80172D08_arg1.h"

typedef struct { s32 word[6]; } Copy24;

typedef struct S_80174A6C_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174A6C_4;   /* dst in create_primitive_state_object */

typedef struct S_80174A6C_5 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80174A6C_5;   /* query_arg in create_primitive_state_object */

extern void register_node(void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern s32 resolve_record_orientation_or_fallback(s32, void *, u16 *, s32);

extern u8 D_80174A00[9];

/* Creates an object, initializes its primitive, copies state, and applies queried offsets. */
s32 create_primitive_state_object(void *unused, Rec_func_80172D08_arg1 *src_state, Rec_D_80082E80 *source)
{
    u16 offsets[3];
    ObjectNodeHeader *obj;
    S_80174A6C_4 *dst_state;
    SpriteFrameState *prim;

    obj = allocate_flagged_object_node(0x312);
    if (obj != 0) {
        obj->unk_10 = D_80174A00;
        register_node(obj, project_sprite_chain);

        prim = obj->sprite;
        prim->unk_28 = source->unk_28.at00_s32.v;
        prim->color.c.b = 0x80;
        prim->color.c.g = 0x80;
        prim->color.c.r = 0x80;
        prim->scale_y = 0x2000;
        prim->scale_x = 0x2000;
        prim->unk_06 = 1;
        prim->flags |= 0xC;
        prim->tpage_abr |= 0x20;
        select_sprite_entry(prim, 0x39, 0);

        {
            S_80174A6C_5 *query_arg = source;
            u16 *query_out;

            source = obj->position;
            dst_state = (void *)source;
            *(Copy24 *)dst_state = *(Copy24 *)src_state;
            query_out = offsets;

            offsets[2] = 0;
            offsets[1] = 0;
            offsets[0] = 0;
            if (resolve_record_orientation_or_fallback(query_arg->unk_08, query_arg,
                              query_out, 0) != 0) {
                dst_state->unk_00.at02.v += offsets[0];
                dst_state->unk_04.at02.v += offsets[1];
                dst_state->unk_08.at02.v += offsets[2];
            }
        }
        return (s32)obj;
    }
    return 0;
}

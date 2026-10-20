#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u32 words[6];
} Copy24;

extern void *allocate_list_node(s32, s32);
extern void register_node(void *, void *);
extern s32 rand(void);
extern void select_sprite_entry(void *, s32, s32);
extern s32 resolve_record_orientation_or_fallback(s32, void *, u16 *, s32);
extern u8 D_80175018;

typedef struct S_8017589C_0 {
    u8 pad_00[0x8];
    Copy24 * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8017589C_0;   /* object in create_randomized_offset_object */

typedef struct S_8017589C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    union { u16 u; s16 s; } unk_0E;   /* accessed as both */
    u8 pad_10[0x30];
    s32 unk_40;
    void * unk_44;
    void * unk_48;
    s32 unk_4C;
} S_8017589C_1;   /* work in create_randomized_offset_object */

typedef struct S_8017589C_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8017589C_4;   /* source in create_randomized_offset_object */

   /* copy in create_randomized_offset_object */

/* Creates an object with randomized initial state and source-derived offsets. */
void *create_randomized_offset_object(s32 allocation_param, Copy24 *initial_data, Rec_D_80082E80 *source_node)
{
    u16 delta[3];
    s32 random_value;
    void *object;
    S_8017589C_1 *work;
    SpriteFrameState *node;
    S_8017589C_4 *source;
    Copy24 *copy;

    object = allocate_list_node(0x312, allocation_param - 0x20);
    if (object != NULL) {
        ((S_8017589C_0 *)object)->unk_10 = &D_80175018;
        register_node(object, project_sprite_chain);
        work = (u8 *)object + 0x20;

        random_value = rand();
        work->unk_06 = (s16)(random_value % 0x1000);

        random_value = rand();
        work->unk_08 = (s16)(random_value % 0x1000);

        work->unk_40 = allocation_param;
        work->unk_44 = initial_data;
        work->unk_48 = source_node;
        work->unk_4C = allocation_param;

        node = ((S_8017589C_0 *)object)->unk_0C;
        node->unk_28 = source_node->unk_28.at00_s32.v;
        node->color.c.b = 0x80;
        node->color.c.g = 0x80;
        node->color.c.r = 0x80;
        node->scale_y = 0x1000;
        node->scale_x = 0x1000;
        node->flags |= 0xC;
        node->tpage_abr |= 0x20;
        select_sprite_entry(node, 0x3F, 0);

        copy = ((S_8017589C_0 *)object)->unk_08;
        *copy = *initial_data;

        delta[2] = 0;
        delta[1] = 0;
        delta[0] = 0;
        source = work->unk_48;
        if (resolve_record_orientation_or_fallback(source->unk_08, source, delta, 3) != 0) {
            ((MovingPosition *)copy)->unk_02 += delta[0];
            ((MovingPosition *)copy)->unk_06 += delta[1];
            ((MovingPosition *)copy)->unk_0A += delta[2];
            work->unk_0A = delta[0];
            work->unk_0C = delta[1];
            work->unk_0E.u = delta[2];
        } else {
            work->unk_0A = 0;
            work->unk_0C = 0;
            work->unk_0E.s = -0x40;
        }
        return object;
    }
    return NULL;
}

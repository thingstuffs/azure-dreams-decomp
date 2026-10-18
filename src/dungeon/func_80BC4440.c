#include "common.h"

typedef struct S_80173C40_0 {
    u8 pad_00[0xA4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_A4;   /* overlapping accesses */
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
} S_80173C40_0;   /* arg0 in initialize_object_and_clear_state */


extern void update_actor_hop_and_shrink(S_80173C40_0 *, void *, void *);


/* Initialize the object, save its A4 value, and clear its trailing state. */
void initialize_object_and_clear_state(S_80173C40_0 *object, void *init_data, void *init_context) {
    s32 saved_a4;

    update_actor_hop_and_shrink(object, init_data, init_context);
    saved_a4 = object->unk_A4.at00.v;
    object->unk_A4.at02.v = 0;
    object->unk_AC = 0;
    object->unk_B0 = 0;
    object->unk_A8 = saved_a4;
}

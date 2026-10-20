#include "common.h"
#include "shared/vector.h"

typedef struct S_800A21EC_0 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
} S_800A21EC_0;   /* arg2 in initialize_directional_object_state */

typedef struct S_800A21EC_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    s32 unk_04;
    s32 unk_08;
} S_800A21EC_1;   /* arg1 in initialize_directional_object_state */

typedef struct S_800A21EC_2 {
    s32 * unk_00;
    u8 pad_04[0x10];
    void * unk_14;
    u8 pad_18[0x8];
    s16 unk_20;
} S_800A21EC_2;   /* arg0 in initialize_directional_object_state */

   /* ((S_800A21EC_2 *)arg0)->unk_14 in initialize_directional_object_state */


extern s32 register_node();
extern u8 D_80046398[];
typedef struct Func800A4B70Output Func800A4B70Output;
typedef struct Func800A4B70Object Func800A4B70Object;
void copy_signed_inner_value_by_flag(Func800A4B70Object *object, s32 unused, Func800A4B70Output *out);

/* Initialize object state and placement with a direction-dependent offset. */
s32 initialize_directional_object_state(void *object, S_800A21EC_1 *placement, S_800A21EC_0 *state) {
    state->unk_00 = 0;
    state->unk_04 = 0;
    state->unk_05 = 0;
    register_node(object - 0x20, &D_80046398);
    placement->unk_00.at00.v = (s32) ((IntVector3 *)(((S_800A21EC_2 *)object)->unk_14))->x;
    placement->unk_04 = (s32) ((IntVector3 *)(((S_800A21EC_2 *)object)->unk_14))->y;
    placement->unk_08 = (s32) ((IntVector3 *)(((S_800A21EC_2 *)object)->unk_14))->z;
    ((S_800A21EC_2 *)object)->unk_00 = &copy_signed_inner_value_by_flag;
    if (((S_800A21EC_2 *)object)->unk_20 == 0) {
        s32 heading;
        heading = 1;
        state->unk_08 = heading;
        heading = (u16) placement->unk_00.at02.v;
        placement->unk_00.at02.v = (u16) (heading + 0x90);
    } else {
        s32 flags = (u16) state->unk_14;
        s32 enabled = 1;
        state->unk_08 = enabled;
        state->unk_14 = (u16) (flags | 1);
        placement->unk_00.at02.v = (u16) (placement->unk_00.at02.v - 0x90);
    }
    state->unk_1A = 0;
}

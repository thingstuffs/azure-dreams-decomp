#include "common.h"
#include "m2c_compat.h"
#include "shared/vector.h"
#include "engine/node.h"

typedef struct S_800A23D0_0 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0xE];
    s16 unk_1A;
} S_800A23D0_0;   /* arg2 in initialize_object_position_state */

typedef struct S_800A23D0_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_800A23D0_1;   /* arg1 in initialize_object_position_state */

typedef struct S_800A23D0_2 {
    void (*unk_00)();
    u8 pad_04[0x10];
    void * unk_14;
    u8 pad_18[0x8];
    s16 unk_20;
} S_800A23D0_2;   /* arg0 in initialize_object_position_state */

   /* ((S_800A23D0_2 *)arg0)->unk_14 in initialize_object_position_state */


extern u8 lit_mesh_renderer_address[];
extern void D_800A24A8();
extern M2C_UNK D_800D0A48;

/* Initialize object state and copy its position with an offset. */
void initialize_object_position_state(void *object, S_800A23D0_1 *position, S_800A23D0_0 *state) {
    s32 *value_table;
    state->unk_00 = 0;
    state->unk_04 = 0;
    state->unk_05 = 0;
    register_node(object - 0x20, &lit_mesh_renderer_address);
    position->unk_00.at00.v = (s32) ((IntVector3 *)(((S_800A23D0_2 *)object)->unk_14))->x;
    position->unk_04.at00.v = (s32) ((IntVector3 *)(((S_800A23D0_2 *)object)->unk_14))->y;
    position->unk_08 = (s32) ((IntVector3 *)(((S_800A23D0_2 *)object)->unk_14))->z;
    ((S_800A23D0_2 *)object)->unk_00 = &D_800A24A8;
    value_table = &D_800D0A48;
    state->unk_08 = (s32) value_table[((S_800A23D0_2 *)object)->unk_20];
    position->unk_00.at02.v = (u16) (position->unk_00.at02.v + 0x28);
    position->unk_04.at02.v = (u16) (position->unk_04.at02.v - 8);
    state->unk_1A = 0;
}

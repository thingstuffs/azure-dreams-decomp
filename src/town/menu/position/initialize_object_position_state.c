#include "common.h"
#include "m2c_compat.h"
#include "shared/vector.h"
#include "engine/node.h"
#include "shared/entity.h"
#include "town/map/object/clear_object_link_and_mark_complete_g01169.h"

typedef struct S_800A23D0_0 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0xE];
    s16 unk_1A;
} S_800A23D0_0;   /* arg2 in initialize_object_position_state */


typedef struct S_800A23D0_2 {
    void (*unk_00)();
    u8 pad_04[0x10];
    void * unk_14;
    u8 pad_18[0x8];
    s16 unk_20;
} S_800A23D0_2;   /* arg0 in initialize_object_position_state */

   /* ((S_800A23D0_2 *)arg0)->unk_14 in initialize_object_position_state */


extern void copy_negated_menu_phase();
extern M2C_UNK D_800D0A48;

/* Initialize object state and copy its position with an offset. */
void initialize_object_position_state(void *object_arg, ObjectPosition *position, S_800A23D0_0 *state) {
    S_800A23D0_2 *object = object_arg;
    s32 *value_table;
    state->unk_00 = 0;
    state->unk_04 = 0;
    state->unk_05 = 0;
    register_node(object_arg - 0x20, &lit_mesh_renderer_address);
    position->x.v = (s32) ((IntVector3 *)(object->unk_14))->x;
    position->y.v = (s32) ((IntVector3 *)(object->unk_14))->y;
    position->z.v = (s32) ((IntVector3 *)(object->unk_14))->z;
    object->unk_00 = &copy_negated_menu_phase;
    value_table = &D_800D0A48;
    state->unk_08 = (s32) value_table[object->unk_20];
    position->x.unsigned_parts.integer = (u16) (position->x.unsigned_parts.integer + 0x28);
    position->y.unsigned_parts.integer = (u16) (position->y.unsigned_parts.integer - 8);
    state->unk_1A = 0;
}

#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/vector.h"
void func_80033CD8(void *block_data, s32 registration_id);           /* extern */
struct Dst;
struct Elem;
void func_8003DB94(struct Dst *state, struct Elem *entries, short index);  /* extern */
void *func_8003FD64();            /* extern */
void load_indexed_state_value();      /* extern */
typedef struct S_800C8B8C_0 S_800C8B8C_0;
void call_owner_callback(S_800C8B8C_0 *owner);
extern M2C_UNK D_800EE344;


typedef struct S_800C8A68_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800C8A68_0;

typedef struct S_800C8A68_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_800C8A68_1;

   /* arg0 in func_800C8A68 */

typedef struct S_800C8A68_3 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_800C8A68_3;

typedef struct S_800C8A68_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800C8A68_4;

/* Allocate and initialize an object at an offset from the supplied position. */
s32 func_800C8A68(IntVector3 *source_pos) {
    S_800C8A68_1 *position;
    S_800C8A68_3 *object_state;
    S_800C8A68_4 *render_state;
    void *object;
    s32 offset_z;

    object = func_8003FD64(0x136, ((s32 *)&D_80083498.next));
    if (object == NULL) {
        return 0;
    }
    position = ((S_800C8A68_0 *)object)->unk_08;
    render_state = ((S_800C8A68_0 *)object)->unk_0C;
    object_state = object + 0x20;
    position->unk_00 = source_pos->x;
    position->unk_04 = source_pos->y;
    offset_z = source_pos->z + 0xFFDC0000;
    position->unk_0C = 0x100000;
    position->unk_10 = 0;
    position->unk_08 = offset_z;
    ((S_800C8A68_0 *)object)->unk_10 = &call_owner_callback;
    object_state->unk_90 = 2;
    load_indexed_state_value(object_state, position, render_state);
    render_state->unk_1E = 0x1000;
    render_state->unk_1C = 0x1000;
    render_state->unk_0C = 0x808080;
    func_8003DB94(render_state, &D_800EE344, 0);
    func_80033CD8(object_state, func_80045340);
    return (s32) object;
}

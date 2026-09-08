#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033CD8();           /* extern */
M2C_UNK func_8003DB94();  /* extern */
void *func_8003FD64();            /* extern */
M2C_UNK func_800C8B5C();      /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800C8B8C;
extern M2C_UNK D_800EE344;


typedef struct S_800C8A68_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800C8A68_0;   /* temp_v0 in func_800C8A68 */

typedef struct S_800C8A68_1 {
    volatile s32 unk_00;
    volatile s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_800C8A68_1;   /* temp_a1 in func_800C8A68 */

typedef struct S_800C8A68_2 {
    volatile s32 unk_00;
    volatile s32 unk_04;
    volatile s32 unk_08;
} S_800C8A68_2;   /* arg0 in func_800C8A68 */

typedef struct S_800C8A68_3 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_800C8A68_3;   /* temp_s0 in func_800C8A68 */

typedef struct S_800C8A68_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800C8A68_4;   /* temp_s1 in func_800C8A68 */

/* Allocate and initialize an object at an offset from the supplied position. */
s32 func_800C8A68(S_800C8A68_2 *source_pos) {
    S_800C8A68_1 *position;
    S_800C8A68_3 *object_state;
    S_800C8A68_4 *render_state;
    void *object;
    s32 offset_z;

    object = func_8003FD64(0x136, &D_80083498);
    if (object == NULL) {
        return 0;
    }
    position = ((S_800C8A68_0 *)object)->unk_08;
    render_state = ((S_800C8A68_0 *)object)->unk_0C;
    object_state = object + 0x20;
    position->unk_00 = source_pos->unk_00;
    position->unk_04 = source_pos->unk_04;
    offset_z = source_pos->unk_08 + 0xFFDC0000;
    position->unk_0C = 0x100000;
    position->unk_10 = 0;
    position->unk_08 = offset_z;
    ((S_800C8A68_0 *)object)->unk_10 = &D_800C8B8C;
    object_state->unk_90 = 2;
    func_800C8B5C(object_state, position, render_state);
    render_state->unk_1E = 0x1000;
    render_state->unk_1C = 0x1000;
    render_state->unk_0C = 0x808080;
    func_8003DB94(render_state, &D_800EE344, 0);
    func_80033CD8(object_state, &D_80045340);
    return (s32) object;
}

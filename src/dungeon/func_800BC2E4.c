#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
extern s32 D_80045C34[4];
extern s32 D_80083498[4];
extern s32 D_800C1718[4];
extern s32 D_800DF3C0[4];

typedef struct S_800C1A44_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800C1A44_0;   /* temp_v0 in func_800C1A44 */

typedef struct S_800C1A44_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800C1A44_1;   /* temp_v1 in func_800C1A44 */

typedef struct S_800C1A44_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    M2C_UNK * unk_08;
    s32 unk_0C;
} S_800C1A44_2;   /* temp_v1_2 in func_800C1A44 */

typedef struct S_800C1A44_3 {
    u8 pad_00[0x48];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_800C1A44_3;   /* temp_v1_3 in func_800C1A44 */

/* Create an object at the tile center and initialize its rendering and state. */
void *func_800C1A44(s32 tile_x, s32 tile_y, s32 z) {
    void *object;
    S_800C1A44_1 *position;
    S_800C1A44_2 *render_state;
    S_800C1A44_3 *object_state;

    object = func_8003FD64(0x12, &D_80083498[0]);
    if (object != NULL) {
        ((S_800C1A44_0 *)object)->unk_10 = &D_800C1718[0];
        func_8004491C(object, &D_80045C34[0]);
        position = ((S_800C1A44_0 *)object)->unk_08;
        position->unk_02 = (s16) (((s32) (tile_x << 0x10) >> 0xA) + 0x20);
        position->unk_06 = (s16) (((s32) (tile_y << 0x10) >> 0xA) + 0x20);
        position->unk_0A = z;
        render_state = ((S_800C1A44_0 *)object)->unk_0C;
        render_state->unk_08 = &D_800DF3C0[0];
        render_state->unk_0C = 0x808080;
        render_state->unk_06 = 8;
        object_state = object + 0x20;
        object_state->unk_4C = 8;
        object_state->unk_48 = 7;
    }
    return object;
}

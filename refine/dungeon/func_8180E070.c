#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80026FB0;
extern u8 D_80028808;
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;

typedef struct S_80027070_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80027070_0;   /* temp_v0 in func_80027070 */

typedef struct S_80027070_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80027070_1;   /* temp_v0_2 in func_80027070 */

typedef struct S_80027070_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80027070_2;   /* temp_a0 in func_80027070 */

typedef struct S_80027070_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x5E];
    s16 unk_66;
} S_80027070_3;   /* temp_v1 in func_80027070 */

/* Creates an object with the given position, graphic index, and state value. */
void *func_80027070(s16 x, s16 y, s16 z, s16 graphic_index, s32 state_value) {
    S_80027070_2 *graphics;
    void *object;
    S_80027070_1 *position;
    S_80027070_3 *state;

    object = func_8003FD64(0x12, &D_80083498);
    if (object != NULL) {
        ((S_80027070_0 *)object)->unk_10 = &D_80026FB0;
        func_8004491C(object, &D_80045340);
        position = ((S_80027070_0 *)object)->unk_08;
        position->unk_02 = x;
        position->unk_06 = y;
        position->unk_0A = z;
        graphics = ((S_80027070_0 *)object)->unk_0C;
        graphics->unk_08 = (void *) ((graphic_index * 0xC) + &D_80028808);
        graphics->unk_1E = 0x1000;
        graphics->unk_1C = 0x1000;
        graphics->unk_10 = 0x20;
        graphics->unk_14 = (u16) (graphics->unk_14 | 0xC);
        state = object + 0x20;
        state->unk_04 = state_value;
        state->unk_66 = 0x1C;
    }
    return object;
}

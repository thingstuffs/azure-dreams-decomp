#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();            /* extern */
s32 func_8004A658();                          /* extern */
M2C_UNK func_8008F0D4();   /* extern */
M2C_UNK func_8009B218(); /* extern */
M2C_UNK func_800A022C(); /* extern */
extern M2C_UNK D_8006E240;
extern M2C_UNK D_80083498;
extern M2C_UNK D_8009DEBC;
extern M2C_UNK D_800D073C;
extern M2C_UNK D_800D0754;
extern M2C_UNK D_800D076C;


typedef struct S_800A027C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800A027C_0;   /* temp_v0 in func_800A027C */

typedef struct S_800A027C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A027C_1;   /* temp_s2 in func_800A027C */

typedef struct S_800A027C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A027C_2;   /* arg1 in func_800A027C */

typedef struct S_800A027C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800A027C_3;   /* temp_s1 in func_800A027C */

typedef struct S_800A027C_4 {
    u8 pad_00[0xC];
    M2C_UNK * unk_0C;
    u8 pad_10[0x38];
    s32 unk_48;
    u8 unk_4C;
    u8 unk_4D;
    u8 unk_4E;
    u8 unk_4F;
    u8 pad_50[0x43];
    s8 unk_93;
    u8 pad_94[0x4];
    s32 unk_98;
} S_800A027C_4;   /* temp_s0 in func_800A027C */

typedef struct S_800A027C_5 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_800A027C_5;   /* arg0 in func_800A027C */

/* Creates an object at the supplied position and initializes its graphics and state. */
void *func_800A027C(S_800A027C_5 *config, S_800A027C_2 *position) {
    u8 type;
    S_800A027C_4 *state;
    S_800A027C_3 *render;
    S_800A027C_1 *coords;
    void *object;
    s32 graphic;

    object = func_8003FD64(0x136, &D_80083498);
    if (object == NULL) {
        return NULL;
    }
    coords = ((S_800A027C_0 *)object)->unk_08;
    render = ((S_800A027C_0 *)object)->unk_0C;
    coords->unk_02 = (u16) position->unk_02;
    coords->unk_06 = (u16) position->unk_06;
    state = object + 0x20;
    coords->unk_0A = (u16) position->unk_0A;
    render->unk_1E = 0x1000;
    render->unk_1C = 0x1000;
    render->unk_0C = 0x808080;
    state->unk_48 = 0;
    state->unk_98 = 0;
    state->unk_93 = 0;
    state->unk_4C = (u8) config->unk_00;
    state->unk_4D = (u8) config->unk_01;
    state->unk_4E = (u8) config->unk_02;
    state->unk_4F = (u8) config->unk_03;
    func_8008F0D4(state, coords, &D_800D073C);
    func_8009B218(state, coords, render, &D_800D076C);
    type = state->unk_4D;
    if (type == 0x12) {
        state->unk_0C = &D_800D0754;
        if (type == state->unk_4D) {
            graphic = (s32) &D_8006E240;
            goto set_graphic;
        }
    }
    graphic = func_8004A658(state->unk_4D, state->unk_4C);
set_graphic:
    render->unk_08 = graphic;
    ((S_800A027C_0 *)object)->unk_10 = &D_8009DEBC;
    ASM_SCHED_BARRIER();
    func_800A022C(state, state, coords, render);

    return object;
}

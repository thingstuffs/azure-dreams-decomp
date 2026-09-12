#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();  /* extern */
void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80099FDC();                      /* extern */
M2C_UNK func_8009A21C();             /* extern */
s8 func_8009FB34();                           /* extern */
M2C_UNK func_800A2B04();              /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80083498;
extern M2C_UNK D_800D2E9C;
extern M2C_UNK D_800D3140;
extern M2C_UNK D_800D36D0;
extern M2C_UNK D_800DEF08;

typedef struct S_800D2CB4_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x68];
    s16 unk_88;
    u8 pad_8A[0x2];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x1];
    s16 unk_9E;
} S_800D2CB4_0;   /* var_s2 in func_800D2CB4 */

typedef struct S_800D2CB4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800D2CB4_1;   /* temp_v0 in func_800D2CB4 */

typedef struct S_800D2CB4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D2CB4_2;   /* temp_s1 in func_800D2CB4 */

typedef struct S_800D2CB4_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800D2CB4_3;   /* temp_s0 in func_800D2CB4 */

/* Creates a dungeon object at the given tile and initializes its graphics and state. */
void *func_800D2CB4(s16 object_kind, u16 tile_x, u16 tile_y, s16 height) {
    M2C_UNK tile_flags;
    s16 saved_kind;
    S_800D2CB4_3 *graphics;
    S_800D2CB4_2 *position;
    void *object;
    S_800D2CB4_0 *state;
    u8 saved_x;
    s16 saved_height;
    u8 saved_y;
    s32 kind;
    u8 call_x;
    u8 call_y;

    saved_kind = object_kind;
    state = NULL;
    saved_x = tile_x;
    saved_height = height;
    saved_y = tile_y;
    object = func_8003FD64(0x112, &D_80083498);
    if (object != NULL) {
        state = object + 0x20;
        state->unk_13 = 0x34;
        kind = (s16) saved_kind;
        if (kind == 1) {
            state->unk_14 = (s32) (state->unk_14 | 0x2000);
            state->unk_1C = (s32) (state->unk_1C | 0x2000);
        }
        func_8004491C(object, &D_800D36D0);
        position = ((S_800D2CB4_1 *)object)->unk_08;
        position->unk_0A = saved_height;
        graphics = ((S_800D2CB4_1 *)object)->unk_0C;
        graphics->unk_24 = saved_x;
        graphics->unk_25 = saved_y;
        func_8003DB94(graphics, &D_800DEF08, 0);
        graphics->unk_12 = 0x7E02;
        graphics->unk_1C = 0x1800;
        graphics->unk_1E = 0x2000;
        graphics->unk_14 = (u16) (graphics->unk_14 | 0xC);
        graphics->unk_10 = (u16) (graphics->unk_10 | 0x20);
        graphics->unk_14 = (u16) (graphics->unk_14 | 0x100);
        ((S_800D2CB4_1 *)object)->unk_10 = &D_800D2E9C;
        state->unk_8C = &D_800D3140;
        graphics->unk_26 = func_8009FB34(graphics->unk_24, graphics->unk_25);
        func_800A2B04(position, graphics->unk_24, graphics->unk_25);
        state->unk_88 = func_800BCB04(position->unk_02, position->unk_06, position->unk_0A);
        graphics->unk_0C = 0x808080;
        graphics->unk_14 = (u16) (graphics->unk_14 | 0x8000);
        func_80099FDC(object);
        call_x = graphics->unk_24;
        call_y = graphics->unk_25;
        tile_flags = 0x3000;
        if (state->unk_1C & 0x2000) {
            tile_flags = 0x300;
        }
        func_8009A21C(call_x, call_y, tile_flags);
        state->unk_9A = 0xE;
        state->unk_9C = -1;
        state->unk_9E = 0;
        state->unk_1C = (s32) (state->unk_1C | 0x40000200);
    }
    return state;
}

#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D24A8_0 {
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
} S_800D24A8_0;   /* var_s2 in func_800D24A8 */

typedef struct S_800D24A8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800D24A8_1;   /* temp_v0 in func_800D24A8 */

typedef struct S_800D24A8_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D24A8_2;   /* temp_s1 in func_800D24A8 */

typedef struct S_800D24A8_3 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800D24A8_3;   /* temp_s0 in func_800D24A8 */


void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80099FDC();                      /* extern */
M2C_UNK func_8009A21C();             /* extern */
s8 func_8009FB34();                           /* extern */
M2C_UNK func_800A2B04();              /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800D2664;
extern M2C_UNK D_800D28E4;
extern M2C_UNK D_800E221C;

/* Create a dungeon object at the given tile and initialize its sprite and tile flags. */
void *func_800D24A8(s16 object_kind, u8 tile_x, u8 tile_y, s16 height) {
    M2C_UNK tile_flags;
    s16 saved_kind;
    S_800D24A8_3 *sprite;
    S_800D24A8_2 *position;
    void *object;
    S_800D24A8_0 *state;
    register u8 saved_tile_x ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s16 saved_height;
    register u8 saved_tile_y ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 kind;
    u8 flag_tile_x;
    u8 flag_tile_y;

    saved_kind = object_kind;
    state = NULL;
    saved_tile_x = tile_x;
    saved_height = height;
    saved_tile_y = tile_y;
    object = func_8003FD64(0x112, &D_80083498);
    if (object != NULL) {
        state = object + 0x20;
        state->unk_13 = 0x34;
        kind = (s16) saved_kind;
        if (kind == 1) {
            state->unk_14 = (s32) (state->unk_14 | 0x2000);
            state->unk_1C = (s32) (state->unk_1C | 0x2000);
        }
        func_8004491C(object, &D_80045340);
        position = ((S_800D24A8_1 *)object)->unk_08;
        position->unk_0A = saved_height;
        sprite = ((S_800D24A8_1 *)object)->unk_0C;
        sprite->unk_08 = &D_800E221C;
        sprite->unk_0C.at02.v = 0x80;
        sprite->unk_0C.at01.v = 0x80;
        sprite->unk_0C.at00.v = 0x80;
        sprite->unk_1E = 0x1400;
        sprite->unk_1C = 0x1400;
        sprite->unk_24 = saved_tile_x;
        sprite->unk_25 = saved_tile_y;
        ((S_800D24A8_1 *)object)->unk_10 = &D_800D2664;
        state->unk_8C = &D_800D28E4;
        sprite->unk_26 = func_8009FB34(sprite->unk_24, sprite->unk_25);
        func_800A2B04(position, sprite->unk_24, sprite->unk_25);
        state->unk_88 = func_800BCB04(position->unk_02, position->unk_06, position->unk_0A);
        sprite->unk_0C.at00u.v = 0x2C808080;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0x8000);
        func_80099FDC(object);
        flag_tile_x = sprite->unk_24;
        flag_tile_y = sprite->unk_25;
        tile_flags = 0x3000;
        if (state->unk_1C & 0x2000) {
            tile_flags = 0x300;
        }
        func_8009A21C(flag_tile_x, flag_tile_y, tile_flags);
        state->unk_9A = 0xE;
        state->unk_9C = -1;
        state->unk_1C = (s32) (state->unk_1C | 0x40000200);
    }
    return state;
}
/* MECHANISM: The exact 0x30 frame comes from one named live range for each
   retail s0/s2/s6/s4/s5/s3/s1 role, with s0 reused for the later object base.
   Preloading call bytes removes the displacement cascade; u8 color fields and
   the 2.7.2-cdk-G0 scheduler produce the final literal and load-slot ordering. */

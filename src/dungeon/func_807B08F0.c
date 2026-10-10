#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "m2c_compat.h"


typedef struct S_807B08F0_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
} S_807B08F0_0;   /* temp_v0 in func_800F80F0 */

typedef struct S_807B08F0_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
} S_807B08F0_1;   /* temp_s0 in func_800F80F0 */

/* Allocate and initialize an object at the center of the specified tile. */
void func_800F80F0(s16 tile_x, s16 tile_y, s16 initial_value) {
    S_807B08F0_1 *state;
    void *object;

    object = func_8003FC64(2);
    if (object != NULL) {
        ((S_807B08F0_0 *)object)->unk_10 = (void *)func_800F81A0;
        func_8004491C(object, (void *)func_800F833C);
        state = object + 0x20;
        ((S_807B08F0_0 *)object)->unk_20 = (u16) (tile_x * 0x40 + 0x20);
        state->unk_02 = (u16) (tile_y * 0x40 + 0x20);
        state->unk_04 = (s16)func_800BCB04(((S_807B08F0_0 *)object)->unk_20, state->unk_02, -0x400);
        state->unk_06 = initial_value;
        state->unk_08 = 0;
    }
}

#include "common.h"

typedef struct S_800DC988_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800DC988_0;   /* arg0 in func_800DC988 */

typedef struct S_800DC988_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x18];
    s32 unk_30;
    u8 pad_34[0x24];
    s32 unk_58;
} S_800DC988_1;   /* state in func_800DC988 */

typedef struct S_800DC988_2 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x16];
    u8 unk_28;
    u8 unk_29;
    u8 pad_2A[0xD2];
    s32 unk_FC;
} S_800DC988_2;   /* data in func_800DC988 */



extern s32 func_800DC724();
extern s32 func_800DC82C();
extern s16 D_8008146C[];
extern void *D_800814A8;

/* Initializes state with complemented global values and updates it until completion. */
void func_800DC988(void *context) {
    s16 global_value = D_8008146C[0];
    S_800DC988_2 *source_data = D_800814A8;
    S_800DC988_1 *state;

    ((S_800DC988_0 *)context)->unk_20 = ~global_value;
    state = (s8 *)context + 0x20;
    state->unk_04 = ~source_data->unk_FC;
    state->unk_10 = ~source_data->unk_28;
    state->unk_14 = ~source_data->unk_29;
    state->unk_30 = ~source_data->unk_11;
    func_800DC82C(state);
    do {
        func_800DC724(state);
    } while (state->unk_58 != 0);
}

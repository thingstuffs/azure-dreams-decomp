#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void *func_8003FD64();                  /* extern */
extern M2C_UNK D_80024830;

typedef struct S_80024908_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_80024908_0;   /* temp_v0 in func_80024908 */

typedef struct S_80024908_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x16];
    s16 unk_26;
    u8 pad_28[0x4];
    s16 unk_2C;
    u8 pad_2E[0x2];
    s16 unk_30;
} S_80024908_1;   /* temp_v0_2 in func_80024908 */

/* Allocate an object and initialize its handler and state fields. */
void func_80024908(s32 alloc_arg, s16 value_26, s16 value_30, s32 value_0c) {
    void *object;
    S_80024908_1 *state;

    object = func_8003FD64(0x200, alloc_arg);
    if (object != NULL) {
        ((S_80024908_0 *)object)->unk_10 = &D_80024830;
        state = object + 0x20;
        state->unk_26 = value_26;
        state->unk_0C = value_0c;
        state->unk_30 = value_30;
        state->unk_2C = 0x40;
    }
}

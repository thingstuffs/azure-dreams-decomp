#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80036110_0 {
    void * unk_00;
    u8 pad_04[0x64];
    M2C_UNK * unk_68;
} S_80036110_0;   /* arg0 in func_80036110 */

typedef struct S_80036110_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80036110_1;   /* temp_v0 in func_80036110 */

typedef struct S_80036110_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80036110_2;   /* temp_v1 in func_80036110 */


extern M2C_UNK func_80036154;

/* Decreases the state field at offset 0x0A by 0x140, clamping below zero and advancing the handler. */
void func_80036110(S_80036110_0 *object) {
    S_80036110_1 *state;
    S_80036110_2 *updated_state;

    state = object->unk_00;
    state->unk_0A = (u16) (state->unk_0A - 0x140);
    updated_state = object->unk_00;
    if ((s16) updated_state->unk_0A < 0) {
        updated_state->unk_0A = 0U;
        object->unk_68 = &func_80036154;
    }
}

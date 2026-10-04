#include "common.h"
#include "m2c_compat.h"

typedef struct S_8080BCD4_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    void * unk_04;
    u8 pad_08[0xE];
    u16 unk_16;
} S_8080BCD4_0;   /* ptr in func_805268D4 */

typedef struct S_8080BCD4_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8080BCD4_1;   /* context in func_805268D4 */


extern s32 D_80084D5C;

void func_805268D4(void *ptr) {
    s16 state;
    u16 remaining;
    u16 next_state;
    u16 flags;
    S_8080BCD4_1 *context;

    state = ((S_8080BCD4_0 *)ptr)->unk_00.s;
    context = ((S_8080BCD4_0 *)ptr)->unk_04;
    switch (state) {
    case 0:
        remaining = ((S_8080BCD4_0 *)ptr)->unk_02 - 1;
        ((S_8080BCD4_0 *)ptr)->unk_02 = remaining;
        if ((remaining << 0x10) <= 0) {
            next_state = ((S_8080BCD4_0 *)ptr)->unk_00.u;
            flags = ((S_8080BCD4_0 *)ptr)->unk_16;
            next_state++;
            flags &= 0xFFFD;
            ((S_8080BCD4_0 *)ptr)->unk_16 = flags;
            ((S_8080BCD4_0 *)ptr)->unk_00.u = next_state;
            return;
        }
        return;
    case 1:
        if (context->unk_2A & 1) {
            *(u16 *)((u8 *)ptr - 2) |= 0x8000;
            D_80084D5C |= 0x8000;
        }
    default:
        return;
    }
}

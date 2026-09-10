/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80126704_0 {
    u8 pad_00[0xA];
    u8 unk_0A;
    u8 pad_0B[0x4];
    u8 unk_0F;
    u8 unk_10;
    u8 unk_11;
    u8 pad_12[0x1];
    union { volatile s8 s; s8 u; } unk_13;   /* accessed as both */
} S_80126704_0;   /* arg0 in func_80126704 */


extern void (*D_80126B34[])();
extern void (*D_80126B74[])(void *);

/* Runs the initial handler, packs and bounds the state code, then runs the final handler. */
void func_80126704(S_80126704_0 *state) {
    register s32 middle_bits ASM_REG("$4");
    u32 packed_code;
    u32 code_bits;
    u16 below_limit;

    {
        u32 handler_index;
        void (*initial_handler)();

        handler_index = state->unk_0A;
        initial_handler = D_80126B34[handler_index];
        initial_handler();
    }
    code_bits = state->unk_0F;
    middle_bits = state->unk_10;
    packed_code = state->unk_11;
    code_bits <<= 4;
    middle_bits <<= 3;
    code_bits += middle_bits;
    packed_code += code_bits;
    code_bits = packed_code & 0xFF;
    state->unk_13.s = packed_code;
    below_limit = code_bits < 0x38U;
    if (below_limit == 0) {
        state->unk_13.u = 0x31;
    } else {
        below_limit = code_bits < 0x31U;
        if (below_limit == 0) {
            state->unk_13.u = 0x30;
        }
    }
    D_80126B74[state->unk_0A](state);
}

/* MECHANISM: The true-space body uses a 24-byte frame and a local join at 0x8012677C, not a phantom call.
   Pointer-table declarations restore 4-byte indexing; short-lived v0/v1/a0 pins reproduce the dispatch roles.
   A volatile byte commit plus a zero-word schedule fence preserves the retail sb/sltiu order. */

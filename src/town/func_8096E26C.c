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

void func_80126704(S_80126704_0 *arg0) {
    register s32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u32 temp_v0;
    u32 temp_v1;
    u32 temp_test;

    {
        u32 first_index;
        void (*first_func)();

        first_index = arg0->unk_0A;
        first_func = D_80126B34[first_index];
        first_func();
    }
    temp_v1 = arg0->unk_0F;
    temp_a0 = arg0->unk_10;
    temp_v0 = arg0->unk_11;
    temp_v1 <<= 4;
    temp_a0 <<= 3;
    temp_v1 += temp_a0;
    temp_v0 += temp_v1;
    temp_v1 = temp_v0 & 0xFF;
    arg0->unk_13.s = temp_v0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    temp_test = temp_v1 < 0x38U;
    if (temp_test == 0) {
        arg0->unk_13.u = 0x31;
    } else {
        temp_test = temp_v1 < 0x31U;
        if (temp_test == 0) {
            arg0->unk_13.u = 0x30;
        }
    }
    D_80126B74[arg0->unk_0A](arg0);
}

/* MECHANISM: The true-space body uses a 24-byte frame and a local join at 0x8012677C, not a phantom call.
   Pointer-table declarations restore 4-byte indexing; short-lived v0/v1/a0 pins reproduce the dispatch roles.
   A volatile byte commit plus a zero-word schedule fence preserves the retail sb/sltiu order. */

#include "common.h"


typedef void (*Callback)(void *, s32);

extern void func_800B180C(void *, s32);
extern s32 func_800B18E0();


typedef struct S_800B1890_0 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_800B1890_0;   /* temp_v1 in func_800B1890 */

void func_800B1890(void *arg0) {
    S_800B1890_0 *temp_v1;
    s32 temp_a3;
    s16 temp_a1;
    u16 temp_a2;
    s32 temp_v0;

    temp_v1 = (*(void * *)((u8 *)arg0 + 0x3C));
    temp_a3 = (*(s32 *)((u8 *)arg0 + 4));
    temp_a1 = temp_v1->unk_08.s;
    temp_a2 = temp_v1->unk_08.u;
    if (temp_a3 < temp_a1) {
        temp_v0 = temp_a1 + 4;
        temp_v0 = temp_a3 - temp_v0;
        temp_v0 >>= 2;
        temp_v1->unk_08.s = temp_a2 + temp_v0;
        func_800B18E0(arg0, temp_a1, temp_a2, temp_a3);
        return;
    }

    temp_v1->unk_08.u = (*(u16 *)((u8 *)arg0 + 4));
    (*(volatile Callback *)((u8 *)arg0 + -0x10)) = func_800B180C;
    func_800B180C(arg0, temp_a1);
}

/* MECHANISM: cdk-G0 gives the retail 0x18 frame with only ra saved.
   An explicit a1+4 temporary blocks reassociation into a3-4-a1.
   The volatile callback store stays before jal, restoring its trailing nop. */

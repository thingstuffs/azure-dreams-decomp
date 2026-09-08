#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();            /* extern */
s32 func_8004A658();                          /* extern */
M2C_UNK func_8008F0D4();   /* extern */
M2C_UNK func_8009B218(); /* extern */
M2C_UNK func_800A022C(); /* extern */
void func_800A0390() __attribute__((noreturn));   /* extern */
extern M2C_UNK D_8006E240;
extern M2C_UNK D_80083498;
extern M2C_UNK D_8009DEBC;
extern M2C_UNK D_800D073C;
extern M2C_UNK D_800D0754;
extern M2C_UNK D_800D076C;


typedef struct S_800A027C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800A027C_0;   /* temp_v0 in func_800A027C */

typedef struct S_800A027C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A027C_1;   /* temp_s2 in func_800A027C */

typedef struct S_800A027C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A027C_2;   /* arg1 in func_800A027C */

typedef struct S_800A027C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800A027C_3;   /* temp_s1 in func_800A027C */

typedef struct S_800A027C_4 {
    u8 pad_00[0xC];
    M2C_UNK * unk_0C;
    u8 pad_10[0x38];
    s32 unk_48;
    u8 unk_4C;
    u8 unk_4D;
    u8 unk_4E;
    u8 unk_4F;
    u8 pad_50[0x43];
    s8 unk_93;
    u8 pad_94[0x4];
    s32 unk_98;
} S_800A027C_4;   /* temp_s0 in func_800A027C */

typedef struct S_800A027C_5 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_800A027C_5;   /* arg0 in func_800A027C */

void *func_800A027C(S_800A027C_5 *arg0, S_800A027C_2 *arg1) {
    u8 temp_a0;
    S_800A027C_4 *temp_s0;
    S_800A027C_3 *temp_s1;
    S_800A027C_1 *temp_s2;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x136, &D_80083498);
    if (temp_v0 == NULL) {
        return NULL;
    }
    temp_s2 = ((S_800A027C_0 *)temp_v0)->unk_08;
    temp_s1 = ((S_800A027C_0 *)temp_v0)->unk_0C;
    temp_s2->unk_02 = (u16) arg1->unk_02;
    temp_s2->unk_06 = (u16) arg1->unk_06;
    temp_s0 = temp_v0 + 0x20;
    temp_s2->unk_0A = (u16) arg1->unk_0A;
    temp_s1->unk_1E = 0x1000;
    temp_s1->unk_1C = 0x1000;
    temp_s1->unk_0C = 0x808080;
    temp_s0->unk_48 = 0;
    temp_s0->unk_98 = 0;
    temp_s0->unk_93 = 0;
    temp_s0->unk_4C = (u8) arg0->unk_00;
    temp_s0->unk_4D = (u8) arg0->unk_01;
    temp_s0->unk_4E = (u8) arg0->unk_02;
    temp_s0->unk_4F = (u8) arg0->unk_03;
    func_8008F0D4(temp_s0, temp_s2, &D_800D073C);
    func_8009B218(temp_s0, temp_s2, temp_s1, &D_800D076C);
    temp_a0 = temp_s0->unk_4D;
    if (temp_a0 == 0x12) {
        temp_s0->unk_0C = &D_800D0754;
        if (temp_a0 == temp_s0->unk_4D) {
            void *tail_value;

            tail_value = &D_8006E240;
            ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_800A0390();
            return tail_value;
        }
    }
    temp_s1->unk_08 = func_8004A658(temp_s0->unk_4D, temp_s0->unk_4C);
    ((S_800A027C_0 *)temp_v0)->unk_10 = &D_8009DEBC;
    ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    func_800A022C(temp_s0, temp_s0, temp_s2, temp_s1);
    
    return temp_v0;
}

/* MECHANISM: Explicit call-then-constant returns select the retail LEAD-22/18 tail shapes.
   Pinning only the +8 base to s2 lets the +0xC base fall naturally to s1 and preserves the load-delay fill.
   A distinct reload plus ASM_TAILSLOT_PIN retains the CSE compare and sinks D_8006E240's low half into the tail-j.
   ASM_SCHED_BARRIER after the callback store preserves retail's store-before-final-argument order. */

#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(s32);
void func_8004491C(void *, void *);
void func_800A56E0(s32, void *);
extern M2C_UNK D_80046398;
extern void *D_800814A8;
extern s8 D_80083160[];
extern s8 D_800B1F34[];

typedef struct S_800B2074_0 {
    u8 pad_00[0x1DC];
    s32 unk_1DC;
    u8 pad_1E0[0x10];
    s16 unk_1F0;
} S_800B2074_0;   /* temp_s4 in func_800B2074 */

typedef struct S_800B2074_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    u16 * unk_20;
} S_800B2074_1;   /* temp_v0 in func_800B2074 */

typedef struct S_800B2074_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800B2074_2;   /* temp_v1 in func_800B2074 */

typedef struct S_800B2074_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_800B2074_3;   /* temp_a1 in func_800B2074 */

typedef struct S_800B2074_4 {
    s16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800B2074_4;   /* temp_s0 in func_800B2074 */

typedef struct S_800B2074_5 {
    u8 pad_00[0xE];
    u16 unk_0E;
    u8 pad_10[0x1A];
    u16 unk_2A;
} S_800B2074_5;   /* temp_dest in func_800B2074 */

void func_800B2074(s32 arg0, s32 arg1) {
    s32 temp_s0;
    void *temp_v0;
    s32 temp_s2;
    register s32 temp_s3 ASM_REG("$19");   /* MATCH pin: load-bearing for the whole function shape */
    void *temp_call0;
    void *temp_call1;
    void *temp_callback;
    S_800B2074_5 *temp_dest;
    register u16 temp_tail ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s8 *temp_s4;
    S_800B2074_3 *temp_a1;
    S_800B2074_2 *temp_v1;

    temp_s2 = arg0;
    temp_s3 = arg1;
    temp_s4 = D_80083160;
    temp_s0 = ((S_800B2074_0 *)temp_s4)->unk_1DC;
    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 != NULL) {
        temp_call0 = temp_v0;
        ASM_KEEP(temp_call0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_callback = D_800B1F34;
        temp_call1 = &D_80046398;
        ASM_KEEP(temp_call1);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_800B2074_1 *)temp_v0)->unk_10 = temp_callback;
        func_8004491C(temp_call0, temp_call1);
        temp_v1 = ((S_800B2074_1 *)temp_v0)->unk_0C;
        temp_v1->unk_20 = 0x1000;
        temp_v1->unk_1E = 0x1000;
        temp_v1->unk_1C = 0x1000;
        temp_v1->unk_08 = 2;
        temp_v1->unk_0C = 0x808080;
        temp_a1 = ((S_800B2074_1 *)temp_v0)->unk_08;
        temp_a1->unk_16 = 6;
        temp_a1->unk_02 = temp_s2;
        temp_a1->unk_06 = temp_s3;
        temp_s0 += (((s32) (temp_s2 << 0xA) >> 0x10) + (((s32) (temp_s3 << 0xA) >> 0x10) << ((S_800B2074_0 *)temp_s4)->unk_1F0)) * 6;
        ASM_KEEP(temp_s3);   /* MATCH pin: keeps a statement from moving across a call/branch */
        ((S_800B2074_1 *)temp_v0)->unk_20 = (u16 *) (temp_s0 + 2);
        ((S_800B2074_4 *)temp_s0)->unk_00 = 3;
        temp_a1->unk_0A = (s16) (0 - *((S_800B2074_1 *)temp_v0)->unk_20);
        ((S_800B2074_4 *)temp_s0)->unk_02 = (u16) (((S_800B2074_4 *)temp_s0)->unk_02 + 0x20);
        ((S_800B2074_4 *)temp_s0)->unk_04 = (u16) (((S_800B2074_4 *)temp_s0)->unk_04 | 1);
        func_800A56E0(0x603, temp_a1);
        temp_dest = D_800814A8;
        temp_tail = temp_dest->unk_2A;
        temp_dest = temp_v0 + 0x20;
        ASM_KEEP(temp_dest);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        temp_dest->unk_0E = temp_tail;
    }
}

/* MECHANISM: The 0x28 frame comes from a held D_80083160 base; s0 mutates into the selected record.
   Guarded roles fix s0/s1/s2/s3 and the short v0/v1 tail lifetimes.
   Ordered a0/v0/a1 keeps force the callback page before the call-argument page.
   Split tail source/destination reproduces the final lhu/addiu/store schedule. */

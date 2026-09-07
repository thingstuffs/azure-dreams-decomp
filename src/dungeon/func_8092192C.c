#include "common.h"
#include "m2c_compat.h"

typedef struct S_8092192C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8092192C_0;   /* temp_v0 in func_8092192C */

typedef struct S_8092192C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x8];
    s16 unk_10;
    u8 pad_12[0x2];
    union { u16 s; volatile u16 u; } unk_14;   /* accessed as both */
} S_8092192C_1;   /* temp_a0 in func_8092192C */

typedef struct S_8092192C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8092192C_2;   /* arg0 in func_8092192C */

typedef struct S_8092192C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; volatile u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { volatile s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_8092192C_3;   /* temp_v1 in func_8092192C */

typedef struct S_8092192C_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_8092192C_4;   /* temp_a0_2 in func_8092192C */


extern u8 D_80045340[];
extern u8 D_800DEC70[];
void *func_8003FC64();
s32 func_8004491C();
void func_8003DB94();
extern M2C_UNK D_800F68AC;

void func_8092192C(S_8092192C_2 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u16 temp_v0_2;
    S_8092192C_1 *temp_a0;
    S_8092192C_4 *temp_a0_2;
    S_8092192C_0 *temp_v0;
    register S_8092192C_3 *temp_v1 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    u32 temp_page;
    s32 temp_input0;
    s32 temp_input4;
    s32 temp_input8;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = &D_800F68AC;
        func_8004491C(temp_v0, D_80045340);
        temp_a0 = temp_v0->unk_0C;
        temp_a0->unk_10 = 0x20;
        temp_a0->unk_06 = 6;
        temp_v0_2 = temp_a0->unk_14.s;
        temp_v0_2 = temp_v0_2 | 0xC;
        temp_a0->unk_14.u = temp_v0_2;
        ASM_KEEP(temp_v0_2);   /* MATCH pin: load-bearing for the whole function shape */
        temp_v0_2 = temp_v0_2 | 2;
        temp_a0->unk_14.u = temp_v0_2;
        temp_v1 = temp_v0->unk_08;
        temp_input0 = (s32) arg0->unk_00;
        temp_page = 0x800E0000;
        temp_v1->unk_00.at00.v = temp_input0;
        temp_input4 = (s32) arg0->unk_04;
        ASM_KEEP_DEP_NV(temp_page, temp_input4);   /* MATCH pin: load-bearing for the whole function shape */
        temp_page -= 5008;
        ASM_KEEP(temp_page);   /* MATCH pin: load-bearing for the whole function shape */
        temp_v1->unk_04.at00.v = temp_input4;
        temp_input8 = (s32) arg0->unk_08;
        temp_v1->unk_00.at02.v = (u16) (temp_v1->unk_00.at02.v + arg1);
        temp_v1->unk_08.at00.v = temp_input8;
        temp_v1->unk_04.at02.v = (u16) (temp_v1->unk_04.at02.v + arg2);
        temp_v1->unk_08.at02.v = (u16) (temp_v1->unk_08.at02.v + arg3);
        temp_a0_2 = temp_v0->unk_0C;
        temp_a0_2->unk_1E = 0x800;
        temp_a0_2->unk_1C = 0x800;
        temp_a0_2->unk_0E = 0x80;
        temp_a0_2->unk_0D = 0x80;
        temp_a0_2->unk_0C = 0x80;
        func_8003DB94(temp_a0_2, (void *) temp_page, 0);
    }
}

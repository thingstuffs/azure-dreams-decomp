#include "common.h"
#include "m2c_compat.h"

extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_800DEC70[];
void *func_8003FC64();
s32 func_8004491C();
extern u8 D_800F6000[];
extern M2C_UNK D_800F6A44;


typedef struct S_80921B2C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80921B2C_0;   /* temp_v0 in func_80921B2C */

typedef struct S_80921B2C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x8];
    s16 unk_10;
    u8 pad_12[0x2];
    union { u16 n; volatile u16 v; } unk_14;   /* accessed as both */
} S_80921B2C_1;   /* temp_a0 in func_80921B2C */

typedef struct S_80921B2C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
} S_80921B2C_2;   /* temp_a0_2 in func_80921B2C */

typedef struct S_80921B2C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80921B2C_3;   /* arg0 in func_80921B2C */

typedef struct S_80921B2C_4 {
    u8 pad_00[0x2A];
    volatile u16 unk_2A;
} S_80921B2C_4;   /* temp_s6 in func_80921B2C */

typedef struct S_80921B2C_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_80921B2C_5;   /* temp_a0_3 in func_80921B2C */

typedef struct S_80921B2C_6 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80921B2C_6;   /* (s8 *)temp_buf + (((u16) ((S_80921B2C_4 *)temp_s6)->unk_2A >> 7) & 0x1C) in func_80921B2C */

void func_80921B2C(S_80921B2C_3 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp[32];
    u8 *temp_source;
    s32 saved_arg2 = arg2;
    s32 saved_arg3 = arg3;
    u16 temp_v0_2;
    register s32 temp_call_arg ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u8 *temp_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *temp_s6 ASM_REG("$22");   /* MATCH pin: load-bearing for the whole function shape */
    S_80921B2C_2 *temp_a0_2;
    S_80921B2C_5 *temp_a0_3;
    S_80921B2C_0 *temp_v0;

    temp_source = D_800F6000;
    memcpy(sp, temp_source, 0x20);
    temp_call_arg = 0x212;
    ASM_USE_NV(temp_call_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_page = D_80083498;
    temp_s6 = temp_page + 0x20;
    temp_v0 = func_8003FC64(temp_call_arg);
    if (temp_v0 != NULL) {
        u8 *temp_buf = sp;

        temp_v0->unk_10 = &D_800F6A44;
        func_8004491C(temp_v0, D_80045340);
        {
            S_80921B2C_1 *temp_a0;

            temp_a0 = temp_v0->unk_0C;
            temp_v0_2 = temp_a0->unk_14.n;
            ASM_USE(temp_v0_2);   /* MATCH pin: keeps a statement from moving across a call/branch */
            temp_a0->unk_10 = 0x20;
            temp_a0->unk_06 = 6;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            temp_v0_2 |= 0xC;
            temp_a0->unk_14.v = temp_v0_2;
            temp_v0_2 |= 2;
            temp_a0->unk_14.v = temp_v0_2;
        }
        temp_a0_2 = temp_v0->unk_08;
        temp_a0_2->unk_00.at00.v = (s32) arg0->unk_00;
        temp_a0_2->unk_04.at00.v = (s32) arg0->unk_04;
        temp_a0_2->unk_08.at00.v = (s32) arg0->unk_08;
        temp_a0_2->unk_00.at02.v = (u16) (temp_a0_2->unk_00.at02.v + arg1);
        temp_a0_2->unk_04.at02.v = (u16) (temp_a0_2->unk_04.at02.v + saved_arg2);
        temp_a0_2->unk_08.at02.v = (u16) (temp_a0_2->unk_08.at02.v + saved_arg3);
        temp_a0_2->unk_0C = (s32) ((*(s16 *)((u8 *)temp_buf + (((u16) ((S_80921B2C_4 *)temp_s6)->unk_2A >> 7) & 0x1C))) * 0x180000);
        temp_a0_2->unk_10 = (s32) ((s16) ((S_80921B2C_6 *)((s8 *)temp_buf + (((u16) ((S_80921B2C_4 *)temp_s6)->unk_2A >> 7) & 0x1C)))->unk_02 * 0x180000);
        temp_a0_3 = temp_v0->unk_0C;
        temp_a0_3->unk_1E = 0x800;
        temp_a0_3->unk_1C = 0x800;
        temp_a0_3->unk_0E = 0x80;
        temp_a0_3->unk_0D = 0x80;
        temp_a0_3->unk_0C = 0x80;
        func_8003DB94(temp_a0_3, D_800DEC70, 0);
    }
}

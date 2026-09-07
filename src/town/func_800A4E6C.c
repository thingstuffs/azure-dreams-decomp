#include "common.h"


extern s32 func_800374F4(u32);
extern void *func_8003FC64(s32);
extern s32 func_800A2674(void);
extern u8 D_800A2690[9];


typedef struct S_800A25CC_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_800A25CC_0;   /* temp_s2 in func_800A25CC */

typedef struct S_800A25CC_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x2];
    s32 unk_10;
    s32 unk_14;
} S_800A25CC_1;   /* temp_s1 in func_800A25CC */

void *func_800A25CC(s32 arg0)
{
    s32 temp_s0;
    s16 temp_v0;
    S_800A25CC_1 *temp_s1;
    void *temp_s2;

    temp_s2 = func_8003FC64(0x136);
    if (temp_s2 == 0) {
        return 0;
    }
    ((S_800A25CC_0 *)temp_s2)->unk_10 = D_800A2690;
    temp_s1 = temp_s2 + 0x20;
    temp_v0 = func_800374F4(0xB4) + 0x3C;
    temp_s1->unk_04 = temp_v0;
    temp_s1->unk_06 = temp_v0;
    temp_s1->unk_10 = (func_800374F4(0x28) & 0xFFFF) + 0x80;
    temp_s1->unk_14 = arg0;
    temp_s0 = func_800374F4(0x40);
    temp_s1->unk_08 = temp_s0 + func_800374F4(0x40) - 0x40;
    temp_s1->unk_0A = func_800374F4(0x40);
    temp_s1->unk_0C = func_800374F4(0x40);
    ASM_MEM_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    func_800A2674();
    return temp_s2;
}

/* MECHANISM: Natural long-lived locals produce the retail 0x20 frame and s0/s1/s2 save roles.
   ASM_MEM_BARRIER keeps the final halfword store before the tail call; removing the stale
   disabled noreturn prototype lets SHAPE-C emit j func_800A2674 with move v0,s2 in its slot. */

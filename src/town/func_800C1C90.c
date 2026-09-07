#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800BF3F0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800BF3F0_0;   /* temp_v0 in func_800BF3F0 */

typedef struct S_800BF3F0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u32 unk_0C;
    u8 pad_10[0xA];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800BF3F0_1;   /* temp_v1 in func_800BF3F0 */

typedef struct S_800BF3F0_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BF3F0_2;   /* temp_a1 in func_800BF3F0 */

typedef struct S_800BF3F0_3 {
    u8 pad_00[0x48];
    s32 unk_48;
} S_800BF3F0_3;   /* temp_a0 in func_800BF3F0 */

typedef struct S_800BF3F0_4_pre {
    u16 unk_00;
} S_800BF3F0_4_pre;   /* the 0x2 bytes before arg0 in func_800BF3F0, addressed as arg0[-1] */



extern void *func_8003FC64(u32);
extern void func_8004491C(void *, void *);
extern void func_8008F074(void *, void *, void *);

extern u8 D_80046398[];
extern u8 D_800BF1C8[];
extern u8 D_800D232C[];
extern s32 D_800D2344[3];
extern s32 D_800814A0[3];

void func_800BF3F0(void *arg0)
{
    S_800BF3F0_3 *temp_a0;
    S_800BF3F0_2 *temp_a1;
    void *temp_v0;
    S_800BF3F0_1 *temp_v1;
    s32 value;
    u32 color;

    temp_v0 = func_8003FC64(0x136);
    if (temp_v0 != NULL) {
        func_8004491C(temp_v0, D_80046398);
        color = 0x00808080U;
        
        ((S_800BF3F0_0 *)temp_v0)->unk_10 = D_800BF1C8;
        temp_v1 = ((S_800BF3F0_0 *)temp_v0)->unk_0C;
        temp_v1->unk_1C = 0x1000;
        temp_v1->unk_1E = 0x1000;
        temp_v1->unk_20 = 0x1000;
        temp_v1->unk_0C = color;
        temp_a0 = temp_v0 + 0x20;
        temp_v1->unk_1A = 0;
        temp_v1->unk_08 = 0x4A;
        temp_a1 = ((S_800BF3F0_0 *)temp_v0)->unk_08;
        temp_a1->unk_00 = 0x02C00000;
        temp_a1->unk_04 = 0x02300000;
        value = D_800D2344[0];
        temp_a1->unk_08 = 0xFFC00000;
        temp_a0->unk_48 = value;
        func_8008F074(temp_a0, temp_a1, D_800D232C);
    }
    ((S_800BF3F0_4_pre *)arg0)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
}

/* MECHANISM: The 0x20 frame holds arg0 in s1 and the allocated object in s0.
   Loading D_800D2344 before the final buffer store creates retail's a0 handoff
   and schedules the global lui/lw pair before the 0xFFC00000 store. */

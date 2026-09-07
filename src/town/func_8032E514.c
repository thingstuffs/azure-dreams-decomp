#include "common.h"


typedef void (*TownCall3)(void *, void *, s32);
typedef void (*TownCall1)(s32);

typedef struct S_80018D14_0 {
    u8 pad_00[0x6000];
    u8 * unk_6000;
} S_80018D14_0;   /* page in func_80018D14 */

typedef struct S_80018D14_1 {
    u8 pad_00[0x20];
    u8 * unk_20;
    u8 pad_24[0x14];
    u8 * unk_38;
} S_80018D14_1;   /* root in func_80018D14 */

typedef struct S_80018D14_2 {
    u8 pad_00[0x20];
    u8 * unk_20;
} S_80018D14_2;   /* root2 in func_80018D14 */


extern s8 D_80016000[];
extern u8 D_80016034[16];
extern u8 D_8001605C[];

void func_80018D14(u8 *arg0)
{
    void **page;
    u8 *root;
    register u8 *loaded_base ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register u32 raw_index ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *call_table;
    TownCall3 call3;
    u8 *root2;
    u8 *call_table2;
    TownCall1 call1;
    u8 *base;
    u8 *objects;
    u8 *record;
    u8 *small;
    s32 index;
    u32 raw_final;
    s32 scaled;
    s32 scaled2;

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    page = (void **)0x80010000;
    root = ((S_80018D14_0 *)page)->unk_6000;
    loaded_base = ((S_80018D14_1 *)root)->unk_38;
    objects = loaded_base + 0x2F0;
    base = loaded_base;
    raw_index = arg0[3];
    ASM_KEEP(raw_index);   /* MATCH pin: retail schedule: same instructions, different order without it */
    index = raw_index & 0x1F;

    if (arg0[0] != objects[index * 0x54 + 0x13]) {
        call_table = ((S_80018D14_1 *)root)->unk_20;
        call3 = (*(TownCall3 *)((u8 *)call_table + 0x168));
        ASM_KEEP(call3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        call3(D_80016034, D_8001605C, 0x41);
        root2 = ((S_80018D14_0 *)page)->unk_6000;
        call_table2 = ((S_80018D14_2 *)root2)->unk_20;
        call1 = (*(TownCall1 *)((u8 *)call_table2 + 0x174));
        call1(1);
        ASM_KEEP(index);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    }

    scaled = index * 4;
    record = (u8 *)((u32)(((scaled + index) * 4 + index) * 4) +
                    (u32)objects);
    record[0x13] = 0;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    raw_final = record[0x43];
    index = raw_final & 0x3F;
    scaled2 = index * 4;
    small = base + scaled2;
    small[0x980] = 0;
    small[0x981] = 0;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    record = (((scaled2 + index) * 4 + index) * 4) + base;
    record[0xA93] = 0;
}

/* MECHANISM: Four values span the call region: literal page base, root-derived base,
   object-table base, and masked index, inducing retail's s3/s2/s1/s0 hold set.
   The record address is recomputed at the branch join instead of held across calls. */

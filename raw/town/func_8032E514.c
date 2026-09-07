#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*TownCall3)(void *, void *, s32);
typedef void (*TownCall1)(s32);

extern s8 D_80016000[];
extern u8 D_80016034[16];
extern u8 D_8001605C[];

void func_80018D14(u8 *arg0)
{
    register void **page ASM_REG("$19");
    register u8 *root ASM_REG("$5");
    register u8 *loaded_base ASM_REG("$2");
    register u32 raw_index ASM_REG("$2");
    register u8 *call_table ASM_REG("$2");
    register TownCall3 call3 ASM_REG("$2");
    register u8 *root2 ASM_REG("$2");
    register u8 *call_table2 ASM_REG("$2");
    register TownCall1 call1 ASM_REG("$2");
    register u8 *base ASM_REG("$18");
    register u8 *objects ASM_REG("$17");
    u8 *record;
    u8 *small;
    register s32 index ASM_REG("$16");
    register u32 raw_final ASM_REG("$2");
    s32 scaled;
    s32 scaled2;

    ASM_SCHED_BARRIER();
    page = (void **)0x80010000;
    root = FIELD(page, u8 *, 0x6000);
    ASM_KEEP(root);
    loaded_base = FIELD(root, u8 *, 0x38);
    ASM_KEEP(loaded_base);
    objects = loaded_base + 0x2F0;
    base = loaded_base;
    raw_index = arg0[3];
    ASM_KEEP(raw_index);
    index = raw_index & 0x1F;

    if (arg0[0] != objects[index * 0x54 + 0x13]) {
        call_table = FIELD(root, u8 *, 0x20);
        ASM_KEEP(call_table);
        call3 = FIELD(call_table, TownCall3, 0x168);
        ASM_KEEP(call3);
        call3(D_80016034, D_8001605C, 0x41);
        root2 = FIELD(page, u8 *, 0x6000);
        ASM_KEEP(root2);
        call_table2 = FIELD(root2, u8 *, 0x20);
        ASM_KEEP(call_table2);
        call1 = FIELD(call_table2, TownCall1, 0x174);
        ASM_KEEP(call1);
        call1(1);
        ASM_KEEP(index);
    }

    scaled = index * 4;
    record = (u8 *)((u32)(((scaled + index) * 4 + index) * 4) +
                    (u32)objects);
    record[0x13] = 0;
    ASM_SCHED_BARRIER();
    raw_final = record[0x43];
    ASM_KEEP(raw_final);
    index = raw_final & 0x3F;
    scaled2 = index * 4;
    small = base + scaled2;
    small[0x980] = 0;
    small[0x981] = 0;
    ASM_SCHED_BARRIER();
    record = (((scaled2 + index) * 4 + index) * 4) + base;
    record[0xA93] = 0;
    ASM_KEEP(page);
    ASM_KEEP(base);
    ASM_KEEP(objects);
    ASM_KEEP(index);
}

/* MECHANISM: Four values span the call region: literal page base, root-derived base,
   object-table base, and masked index, inducing retail's s3/s2/s1/s0 hold set.
   The record address is recomputed at the branch join instead of held across calls. */

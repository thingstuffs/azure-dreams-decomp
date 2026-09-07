#include "common.h"

extern s32 func_8001A934(void);
extern s32 func_8001A64C(s32);
extern void func_8001A554(s32);

extern s16 D_8001AA58[];
extern s32 D_8001AA6C[][5];
extern s32 D_8001B160[];

s32 func_80016E48(s32 arg0)
{
    s32 index;
    s32 count;
    register s32 less ASM_REG("$2");
    register s32 result ASM_REG("$2");
    s32 *base;
    register s16 *award_base ASM_REG("$2");
    register s32 *reward_base ASM_REG("$5");
    s32 *slot;
    s16 *event_base;
    s16 *events;
    s32 *result_base;

    index = arg0;
    if (index == 0x34) {
        index = 0;
    } else {
        if (index == 0x35) {
            index = 1;
        } else {
            index = 2;
        }
    }

    base = D_8001B160;
    slot = &base[index];
    ASM_KEEP(index);
    if (*slot != 0) {
        goto done;
    }

    count = func_8001A934();
    less = count < 5;
    ASM_KEEP(less);
    if (less) {
        goto award_first;
    }

    event_base = (s16 *)((u8 *)D_8001AA6C - 0x14);
    events = &event_base[index * 3];
    if (func_8001A64C(events[0]) == 0) {
award_first:
        award_base = D_8001AA58;
        ASM_KEEP(award_base);
        func_8001A554(award_base[index * 3]);
        result = 1;
        goto store;
    }

    ASM_SCHED_BARRIER();
    less = count < 10;
    ASM_KEEP(less);
    if (less) {
        goto award_second;
    }
    if (func_8001A64C(events[1]) == 0) {
award_second:
        func_8001A554(events[1]);
        result = 2;
        goto store;
    }

    less = count < 20;
    ASM_KEEP(less);
    if (less) {
        goto award_third;
    }
    if (func_8001A64C(events[2]) == 0) {
award_third:
        func_8001A554(events[2]);
        result = 3;
        goto store;
    }

    result = 5;
    if (func_8001A64C(0x1391) != 0) {
        *slot = 5;
        goto done;
    }
    *slot = 4;
    goto done;

store:
    *slot = result;

done:
    {
        register s32 scaled ASM_REG("$3");
        register s32 row_offset ASM_REG("$4");
        register s32 *fresh_base ASM_REG("$2");
        register s32 reward ASM_REG("$2");
        register s32 *reward_addr ASM_REG("$3");

        reward_base = &D_8001AA6C[0][0];
        ASM_KEEP(reward_base);
        scaled = index * 4;
        ASM_KEEP(scaled);
        row_offset = (scaled + index) * 4;
        ASM_KEEP(row_offset);
        fresh_base = (s32 *)((u8 *)D_8001AA58 + 0x708);
        ASM_KEEP(fresh_base);
        reward_addr = (s32 *)(u32)(scaled + (u32)fresh_base);
        ASM_KEEP(reward_addr);
        reward = *(volatile s32 *)reward_addr;
        ASM_KEEP(reward);
        result_base = (s32 *)(u32)(row_offset + (u32)reward_base);
        return result_base[reward - 1];
    }
}

/* MECHANISM: The true-space function uses local CFG joins, not phantom calls.
   Four long-lived roles map naturally to s1=index, s3=slot, s2=count, s0=events;
   halfword event rows and sibling global arrays preserve the retail address math. */

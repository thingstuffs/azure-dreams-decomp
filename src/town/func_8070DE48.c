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
    s32 less;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 *base;
    register s16 *award_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 *reward_base;
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
    if (*slot != 0) {
        goto done;
    }

    count = func_8001A934();
    less = count < 5;
    if (less) {
        goto award_first;
    }

    event_base = (s16 *)((u8 *)D_8001AA6C - 0x14);
    events = &event_base[index * 3];
    if (func_8001A64C(events[0]) == 0) {
award_first:
        award_base = D_8001AA58;
        func_8001A554(award_base[index * 3]);
        result = 1;
        goto store;
    }

    less = count < 10;
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
        s32 scaled;
        s32 row_offset;
        s32 *fresh_base;
        s32 reward;
        s32 *reward_addr;

        reward_base = &D_8001AA6C[0][0];
        scaled = index * 4;
        row_offset = (scaled + index) * 4;
        fresh_base = (s32 *)((u8 *)D_8001AA58 + 0x708);
        reward_addr = (s32 *)(u32)(scaled + (u32)fresh_base);
        reward = *(volatile s32 *)reward_addr;
        result_base = (s32 *)(u32)(row_offset + (u32)reward_base);
        return result_base[reward - 1];
    }
}

/* MECHANISM: The true-space function uses local CFG joins, not phantom calls.
   Four long-lived roles map naturally to s1=index, s3=slot, s2=count, s0=events;
   halfword event rows and sibling global arrays preserve the retail address math. */

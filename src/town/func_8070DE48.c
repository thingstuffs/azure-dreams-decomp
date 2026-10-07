#include "common.h"

extern s32 func_8001A934(void);
extern s32 func_8001A64C(s32);
extern void func_8001A554(s32);

extern s16 D_8001AA58[];
extern s32 D_8001AA6C[][5];
extern s32 D_8001B160[];

/* Award the first unearned 5/10/20 milestone for one of the three counters and return its reward. */
s32 func_80016E48(s32 counter_id)
{
    s32 index;
    s32 count;
    s32 less;
    s16 result;
    s32 *base;
    s16 *award_base;
    s32 *reward_base;
    s32 *slot;
    s16 *event_base;
    s16 *events;
    s32 *result_base;

    index = counter_id;
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
    if (*slot == 0) {
        count = func_8001A934();
        less = count < 5;
        if (less || (event_base = (s16 *)((u8 *)D_8001AA6C - 0x14), events = &event_base[index * 3],
            func_8001A64C(events[0])) == 0) {
            award_base = D_8001AA58;
            func_8001A554(award_base[index * 3]);
            result = 1;
            *slot = result;
        } else {
            less = count < 10;
            if (less || func_8001A64C(events[1]) == 0) {
                func_8001A554(events[1]);
                result = 2;
                *slot = result;
            } else {
                less = count < 20;
                if (less || func_8001A64C(events[2]) == 0) {
                    func_8001A554(events[2]);
                    result = 3;
                    *slot = result;
                } else {
                    result = 5;
                    if (func_8001A64C(0x1391) != 0) {
                        *slot = 5;
                    } else {
                        *slot = 4;
                    }
                }
            }
        }
    }

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
        reward = *reward_addr;
        result_base = (s32 *)(u32)(row_offset + (u32)reward_base);
        return result_base[reward - 1];
    }
}

/* MECHANISM: The true-space function uses local CFG joins, not phantom calls.
   Four long-lived roles map naturally to s1=index, s3=slot, s2=count, s0=events;
   halfword event rows and sibling global arrays preserve the retail address math. */

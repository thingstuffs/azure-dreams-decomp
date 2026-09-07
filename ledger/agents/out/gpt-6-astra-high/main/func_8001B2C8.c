#include "common.h"

extern void func_800702F0(s32 arg0);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern void func_8007CAE8(void *arg0);
extern s32 func_8040153C(void);
extern void func_80401578(void);
extern void func_80401BF4(void *arg0, s32 arg1);
extern void func_80408654(s32 arg0);
extern u8 D_80400038[];
extern u8 D_804000F8[];
extern s32 D_804094EC[];
extern s32 D_8009DDD8[];
extern s32 D_8009EB58[];

/* Run the slot operation to completion and update its counters. */
s32 func_804022C8(s32 slot_index)
{
    u8 state[32];
    s32 poll_count;
    s32 result;

    poll_count = 0;
    func_80401BF4(state, slot_index);
    func_80408654(0);
    func_80408654(1);
    func_80401578();
    func_8007CAE8(state);
    do {
        result = func_8040153C();
        if (result == 0) {
            poll_count++;
            func_800702F0(0);
        }
    } while (result == 0);
    func_8007C040(D_80400038, D_804000F8, poll_count);

    if (slot_index < 5) {
        s32 *counters;
        s32 *counter_dst;
        s32 *counter_src;
        s32 alternate_counter;

        counters = D_8009EB58;
        counter_dst = counters;
        alternate_counter = D_804094EC[0];
        D_8009DDD8[slot_index * 32] = 0;
        if (alternate_counter != 0) {
            counter_dst++;
        }
        counter_src = counters;
        if (alternate_counter != 0) {
            counter_src++;
        }
        *counter_dst = *counter_src + 3;
    }
    return result == 1;
}

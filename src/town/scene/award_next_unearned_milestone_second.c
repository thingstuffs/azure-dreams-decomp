#include "script_symbols.h"
#include "common.h"
#include "town/scene/milestone_rewards.h"
#include "town/player.h"
#include "town/player/state.h"

extern s32 D_8001B160[];

/* Award the first unearned 5/10/20 milestone for one of the three counters and return its reward. */
void *award_next_unearned_milestone(s32 counter_id)
{
    s32 index;
    s32 count;
    s32 less;
    s16 result;
    s32 *base;
    s16 *award_base;
    void **reward_base;
    s32 *slot;
    s16 *event_base;
    s16 *events;
    void **result_base;

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
        count = get_linked_record_field_2_d_60();
        less = count < 5;
        if (less || (event_base = (s16 *)((u8 *)milestone_response_table - 0x14), events = &event_base[index * 3],
            get_script_flag_mask(events[0])) == 0) {
            award_base = milestone_flag_ids;
            set_script_flag_bit(award_base[index * 3]);
            result = 1;
            *slot = result;
        } else {
            less = count < 10;
            if (less || get_script_flag_mask(events[1]) == 0) {
                set_script_flag_bit(events[1]);
                result = 2;
                *slot = result;
            } else {
                less = count < 20;
                if (less || get_script_flag_mask(events[2]) == 0) {
                    set_script_flag_bit(events[2]);
                    result = 3;
                    *slot = result;
                } else {
                    result = 5;
                    if (get_script_flag_mask(F_veld_kill) != 0) {
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

        reward_base = &milestone_response_table[0][0];
        scaled = index * 4;
        row_offset = (scaled + index) * sizeof(*reward_base);
        fresh_base = (s32 *)((u8 *)milestone_flag_ids + 0x708);
        reward_addr = (s32 *)((u8 *)fresh_base + scaled);
        reward = *reward_addr;
        result_base = (void **)((u8 *)reward_base + row_offset);
        return result_base[reward - 1];
    }
}

/* MECHANISM: The true-space function uses local CFG joins, not phantom calls.
   Four long-lived roles map naturally to s1=index, s3=slot, s2=count, s0=events;
   halfword event rows and sibling global arrays preserve the retail address math. */

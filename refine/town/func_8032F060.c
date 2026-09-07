#include "common.h"

extern void func_8001ACE8(s16 arg0);
extern void func_8001AD60(s16 arg0);
extern s32 func_8001ADE0(s16 arg0);

/* Updates two dependent IDs according to the checked ID's status, then updates the checked ID. */
void func_80019860(s16 checked_id, s16 first_id, s16 second_id)
{
    register s16 saved_first_id ASM_REG("$16");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s16 first_id_copy;
    register s16 saved_second_id ASM_REG("$18");   /* MATCH pin: load-bearing for the whole function shape */
    s16 saved_checked_id;

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    saved_first_id = first_id;
    saved_second_id = second_id;
    saved_checked_id = checked_id;
    first_id_copy = saved_first_id;
    ASM_KEEP(saved_first_id);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(first_id_copy);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_KEEP(saved_second_id);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(saved_checked_id);   /* MATCH pin: retail schedule: same instructions, different order without it */

    if (func_8001ADE0(checked_id) != 0) {
        func_8001ACE8(saved_first_id);
        func_8001ACE8(saved_second_id);
    } else {
        func_8001AD60(first_id_copy);
    }
    func_8001ACE8(saved_checked_id);
}

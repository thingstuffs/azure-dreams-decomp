#include "common.h"

extern void load_bin_nametwin(void);
extern void drainCdCommandQueue(void);
extern void func_800B6A0C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* Forwards five arguments to func_800B6A0C after calling load_bin_nametwin and drainCdCommandQueue. */
void loadAndOpenMonsterStatusDisplay(s32 first_arg, s32 second_arg, s32 third_arg, s32 fourth_arg, s32 fifth_arg)
{
    load_bin_nametwin();
    drainCdCommandQueue();
    func_800B6A0C(first_arg, second_arg, third_arg, fourth_arg, fifth_arg);
}

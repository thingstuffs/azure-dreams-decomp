#include "common.h"

extern void func_8004B634(void);
extern void drain_cd_command_queue(void);
extern void func_800253A0(void *a0, void *a1, s32 a2, void *a3);

/* Calls func_8004B634 and drain_cd_command_queue, then forwards the pointers to func_800253A0 with mode 3. */
void func_8004B774(void *first_data, void *second_data, void *extra_data)
{
    func_8004B634();
    drain_cd_command_queue();
    func_800253A0(first_data, second_data, 3, extra_data);
}

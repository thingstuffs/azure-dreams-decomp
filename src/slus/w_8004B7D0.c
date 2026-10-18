#include "common.h"

typedef struct { u32 v; } __attribute__((packed)) UA32;

extern void func_8004B634(void);
extern void drain_cd_command_queue(void);
extern void func_800253A0(void *a0, void *a1, s32 a2, void *a3);
extern UA32 D_80080B50[];

/* Calls func_8004B634 and drain_cd_command_queue, then forwards the target and a copy of D_80080B50 to func_800253A0. */
void func_8004B7D0(void *target)
{
    UA32 local_copy;
    *(UA32 *)&local_copy = *(UA32 *)D_80080B50;
    func_8004B634();
    drain_cd_command_queue();
    func_800253A0(target, 0, 0, &local_copy);
}

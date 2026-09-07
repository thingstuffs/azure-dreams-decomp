/* Global register variables must precede every function definition in the TU (gcc 2.7.2
   hard error), including the static __inline__ gte_port_* bodies common.h emits under
   -DNON_MATCHING — so they sit above the include.
   That ordering is why these four cannot use common.h's guarded ASM_REG(): the macro is
   not defined yet at this point in the TU. The port build needs no pin at all AND cannot
   take one anyway (`register` is illegal in a file-scope declaration on any hosted C
   compiler), so the pinned group is compiled only for the match build and re-declared as
   plain globals after the include. The match build sees byte-identical text. */
#ifndef NON_MATCHING
register int *g_sp asm("$sp");
register int g_v1 asm("$3");
register int g_t0 asm("$8");
register void *g_a1 asm("$5");
#endif

#include "common.h"

#ifdef NON_MATCHING
int *g_sp;
int g_v1;
int g_t0;
void *g_a1;
#endif

/* Coroutine/stack-switch trampoline: stash $sp at the top of PSX scratchpad RAM (0x1F8003FC),
   swap to a temporary mini-stack there, call func_8004C36C(a0, a2), then restore $sp. */
extern void func_8004C36C(void *a0, void *a1);

int func_8004CAA0(void *a0, int a1, void *a2)
{
    g_a1 = a2;
    g_v1 = 0x1F8003FC;
    g_t0 = g_v1;
    *(int *)g_t0 = (int)g_sp;
    g_t0 = g_t0 - 4;
    g_sp = (int *)g_t0;
    func_8004C36C(a0, g_a1);
    g_sp = (int *)((char *)g_sp + 4);
    g_sp = *(int **)g_sp;
    return 0;
}

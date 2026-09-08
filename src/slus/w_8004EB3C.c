#include "common.h"

extern int func_8003E4FC(int a0, void *a1, void *a2);
extern void func_8003E140(unsigned char *a0);

/* opaque global buffer registered as a task/timer entry; size unknown but
   must be >8 bytes to force %hi/%lo addressing (matches gp-vs-hilo rule) */
extern unsigned char D_8007164C[12];

/* Clears the task state and registers task 6 and its follow-up callback. */
void func_8004EB3C(unsigned char *task_state)
{
    *task_state = 0;
    func_8003E4FC(6, D_8007164C, 0);
    func_8003E4FC(0xFF, func_8003E140, task_state);
}

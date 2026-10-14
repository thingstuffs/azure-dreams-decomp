#include "common.h"
#include "slus/spadstk.h"

extern void func_8004C36C(void *a0, void *a1);

/* Calls func_8004C36C on a temporary scratchpad stack (SDK SetSpadStack/ResetSpadStack), restores the original stack, and returns zero. */
int func_8004CAA0(void *forwarded_ptr, int unused_arg, void *second_ptr)
{
    SetSpadStack(SPAD_STACK_ADDR);
    func_8004C36C(forwarded_ptr, second_ptr);
    ResetSpadStack();
    return 0;
}

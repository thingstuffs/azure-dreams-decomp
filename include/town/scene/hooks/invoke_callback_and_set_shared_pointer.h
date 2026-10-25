#ifndef TOWN_OVL_480100_H
#define TOWN_OVL_480100_H
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
extern u8 D_80017478[];
extern void *D_80017548[];
extern void func_80017350(); /* Unprototyped: one or two arguments; the second register argument is ignored. */
void invoke_callback_and_set_shared_pointer(void);
s16 invoke_state_callback_with_zero(void);
#endif

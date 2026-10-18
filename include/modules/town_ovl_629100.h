#ifndef TOWN_OVL_629100_H
#define TOWN_OVL_629100_H
#include "common.h"
#include "shared/town_root.h"
#include "shared/record_ptrs.h"
typedef void (*Callback)(u32);
extern u8 D_80017420[];
extern void *D_800174D4[];
void invoke_callback_and_set_shared_pointer(void);
#endif

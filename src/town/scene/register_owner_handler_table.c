#include "common.h"

extern void func_80047358(void *, void *, s32);
extern u8 D_80408D28[];
void register_owner_handler_table(void *owner) { func_80047358(owner, D_80408D28, 0x15); }

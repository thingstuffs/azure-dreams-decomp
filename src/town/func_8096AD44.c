#include "common.h"

extern u8 D_80123124[];
extern void remove_runtime_callback(void *);
void func_801231DC(void) { remove_runtime_callback(D_80123124); }

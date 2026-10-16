#include "common.h"

extern u8 D_80123124[];
extern void removeRuntimeCallback(void *);
void func_801231DC(void) { removeRuntimeCallback(D_80123124); }

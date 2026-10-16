#include "common.h"
extern u32 D_80700768, D_80700E44;
void func_80700D24(void) { u32 *index = &D_80700768; *index = (*index << 3) + D_80700E44; }

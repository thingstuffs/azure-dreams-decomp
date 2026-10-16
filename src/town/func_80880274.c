#include "common.h"
extern u32 D_80700A3C, D_807013AC;
void func_80701274(void) { u32 *index = &D_80700A3C; *index = (*index << 3) + D_807013AC; }

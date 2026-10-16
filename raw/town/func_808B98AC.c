#include "common.h"
extern u32 D_A0700A60, D_A0700B48;
void func_A07008AC(void) { u32 *index = &D_A0700A60; *index = (*index << 3) + D_A0700B48; }

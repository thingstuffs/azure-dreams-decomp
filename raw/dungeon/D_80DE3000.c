#include "common.h"
extern void *func_80170854(s16,s16,s16,s16);

/* Logical entry allocation; the native TU owns the physical typed entry. */
void *(*const D_80170800)(s16,s16,s16,s16)=func_80170854;

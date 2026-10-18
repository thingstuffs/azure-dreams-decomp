#include "common.h"
extern void *spawn_mode_dependent_112_object(s16,s16,s16,s16);

/* Logical entry allocation; the native TU owns the physical typed entry. */
void *(*const D_80170800)(s16,s16,s16,s16)=spawn_mode_dependent_112_object;

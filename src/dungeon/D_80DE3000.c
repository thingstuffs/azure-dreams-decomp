#include "common.h"
extern void *dungeonSpawnModeDependent112Object(s16,s16,s16,s16);

/* Logical entry allocation; the native TU owns the physical typed entry. */
void *(*const D_80170800)(s16,s16,s16,s16)=dungeonSpawnModeDependent112Object;

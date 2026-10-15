#ifndef SLUS_STATE_DEFAULTS_H
#define SLUS_STATE_DEFAULTS_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"

#include "common.h"

extern void bzero(void *dst, s32 len);
extern void func_8004D0C8(void *entity);

extern s32 D_80080B58;
extern s32 D_80080B5C;
extern s32 D_80080B60;
extern s32 D_80080B64;

/* Initialize state fields from globals and clear associated state. */

void func_8004D614(void);

#endif

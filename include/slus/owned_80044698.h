#ifndef SLUS_OWNED_80044698_H
#define SLUS_OWNED_80044698_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"

extern s32 func_80053EF0(s32 a0);
extern s16 SD_Call(s32 a0);
extern void func_80044618(s32 a0);
extern s32 VSync(s32 mode);

extern u16 D_80080B00;

/* Pumps frames until polling returns zero, handling the first poll and caching the VSync field. */

void func_80044698(void);

#endif

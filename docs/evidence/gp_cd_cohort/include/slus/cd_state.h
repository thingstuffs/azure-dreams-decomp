#ifndef SLUS_CD_STATE_H
#define SLUS_CD_STATE_H
#include "common.h"

/* CdSync/CdControl may write eight bytes; location recovery saves word zero. */
typedef union {
    u32 first_word;
    u8 bytes[8];
} SlusCdResult;

extern SlusCdResult D_80081450;
extern u8 D_80080AD0;
extern u16 D_80080AD2;
extern u16 D_80080AD4;
extern s32 D_80080AD8;
extern void *D_80080ADC;
extern u32 D_800814CC;
extern u8 D_800814D0;
extern u8 D_800814D4;
extern s32 D_800814B0;
extern s32 D_800814B4;
u8 func_8003F240(void);
#endif

/* Stand-in declarations for the Psy-Q SDK library libcd. The SDK is copyrighted and not distributed here; builders who own it can replace this file with the SDK header. */
/* Generated call contracts; maintained by tools/headers. */
#ifndef SDK_LIBCD_H
#define SDK_LIBCD_H

#include "common.h"

s32 CdControl(u8, u8 *, u8 *);
s32 CdControlB(u8, u8 *, u8 *);
s32 CdControlF(u8, u8 *);
s32 CdInit(void);
void * CdIntToPos(s32, void *);
s32 CdPosToInt(void *);
s32 CdRead(s32, u32 *, s32);
s32 CdRead2(s32);
s32 CdReadSync(s32, u8 *);
s32 CdReset(s32);
s32 CdSync(s32, u8 *);
void StUnSetRing(void);

#endif

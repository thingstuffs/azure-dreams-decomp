#ifndef SLUS_LIST_CURSOR_E0_H
#define SLUS_LIST_CURSOR_E0_H

#include "common.h"

/* Word view of external storage; its complete extent is not established. */
extern s32 D_80083C68[];
extern s32 *D_800814E0;

void resetSceneFrameCallbackList(void);
void appendTerminatedRuntimeWord(s32 value);
void removeRuntimeCallback(s32 value);

#endif

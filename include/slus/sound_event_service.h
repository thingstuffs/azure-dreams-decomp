#ifndef SLUS_SOUND_EVENT_SERVICE_H
#define SLUS_SOUND_EVENT_SERVICE_H

#include "slus/sound_dma_lifecycle.h"

extern s32 D_80079954;
extern s32 D_800794EC;
void EnterCriticalSection(void);
void ExitCriticalSection(void);
void set_dma_channel_4_callback(s32 callback);
s32 OpenEvent(u32 class, s32 spec, s32 mode, void (*callback)(void));
s32 EnableEvent(s32 event);
s32 CloseEvent(s32 event);
s32 DisableEvent(s32 event);
void func_8005CB88(void);
void func_8005D7BC(void);

#endif

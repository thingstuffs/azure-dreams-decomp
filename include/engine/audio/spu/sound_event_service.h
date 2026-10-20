#ifndef SLUS_SOUND_EVENT_SERVICE_H
#define SLUS_SOUND_EVENT_SERVICE_H

#include "slus/sound_dma_lifecycle.h"

extern s32 spu_event_service_active;
extern s32 spu_transfer_event_handle;
void EnterCriticalSection(void);
void ExitCriticalSection(void);
void set_dma_channel_4_callback(s32 callback);
s32 OpenEvent(u32 class, s32 spec, s32 mode, void (*callback)(void));
s32 EnableEvent(s32 event);
s32 CloseEvent(s32 event);
s32 DisableEvent(s32 event);
void start_spu_dma_event_service(void);
void stop_spu_dma_event_service(void);

#endif

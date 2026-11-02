#ifndef SLUS_SOUND_EVENT_SERVICE_H
#define SLUS_SOUND_EVENT_SERVICE_H

#include "slus/sound_dma_lifecycle.h"

extern s32 spu_event_service_active;
extern s32 spu_transfer_event_handle;
void set_dma_channel_4_callback(s32 callback);
void SpuStart(void);
void SpuQuit(void);

#endif

#include "engine/audio/spu/sound_event_service.h"

#include "engine/audio/spu/sound_event_service.h"
#include "engine/audio/spu.h"

/* Starts the SPU callback/event service once when it is not already active. */
void start_spu_dma_event_service(void)
{
    s32 event_handle;

    if (spu_event_service_active == 0) {
        spu_event_service_active = 1;
        EnterCriticalSection();
        set_dma_channel_4_callback((s32)complete_spu_dma_and_signal_event);
        event_handle = OpenEvent(0xF0000009, 0x20, 0x2000, 0);
        spu_transfer_event_handle = event_handle;
        EnableEvent(event_handle);
        ExitCriticalSection();
    }
}

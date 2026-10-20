#include "engine/audio/spu/sound_event_service.h"

#include "engine/audio/spu/sound_event_service.h"

/* Starts the SPU callback/event service once when it is not already active. */
void func_8005CB88(void)
{
    s32 event_handle;

    if (D_80079954 == 0) {
        D_80079954 = 1;
        EnterCriticalSection();
        set_dma_channel_4_callback((s32)func_8005D064);
        event_handle = OpenEvent(0xF0000009, 0x20, 0x2000, 0);
        D_800794EC = event_handle;
        EnableEvent(event_handle);
        ExitCriticalSection();
    }
}

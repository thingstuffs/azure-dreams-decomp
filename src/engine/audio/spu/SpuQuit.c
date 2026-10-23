#include "common.h"
#include "engine/audio/spu.h"
#include "slus.h"

extern s32 spu_event_service_active[3];
extern s32 spu_register_buffer_flags[];
extern s32 spu_transfer_callback[3];
extern s32 D_80079994[4];
extern s32 spu_transfer_event_handle[3];
extern s32 spu_active_voice_mask[3];

extern void EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern s32 CloseEvent(s32 event);
extern s32 DisableEvent(s32 event);

/* Shuts down SPU event/callback state when the SPU service flag is active. */
void SpuQuit(void)
{
    if (spu_event_service_active[0] == 1) {
        spu_register_buffer_flags[1] = 0;
        EnterCriticalSection();
        {
            s32 null_callback = 0;

            spu_transfer_callback[0] = 0;
            D_80079994[0] = 0;
            set_dma_channel_4_callback(null_callback);
        }
        CloseEvent(spu_transfer_event_handle[0]);
        DisableEvent(spu_active_voice_mask[-1]);
        ExitCriticalSection();
    }
}

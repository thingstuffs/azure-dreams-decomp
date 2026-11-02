#ifndef ENGINE_GRAPHICS_FRAME_CONTEXT_H
#define ENGINE_GRAPHICS_FRAME_CONTEXT_H
#include "shared/gpu_packets.h"
/* View of GameWork's borrowed current-context slot. Consumers reload this
 * pointer after SDK calls; no ownership or full GameWork extent is inferred. */
typedef struct FrameDrawContextSlot {
    GpuContext *context;
} FrameDrawContextSlot;
#endif

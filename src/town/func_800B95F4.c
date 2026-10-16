#include "common.h"

extern void townInitializeModeOffsetEntry(s16 a, s16 b, void *c, void *d);

/* Set the object data pointer and initialize its coordinate-based data. */
void townInitializeCoordinateEntry(void *object) {
    *(void **)((u8 *)object + 0xE0) = (void *)0x8002B800;
    townInitializeModeOffsetEntry(*(s16 *)((u8 *)object + 8), *(s16 *)((u8 *)object + 0xA),
                  (u8 *)object + 0xD8, (void *)0x8002B800);
}

#include "common.h"

extern void initialize_mode_offset_entry(s16 a, s16 b, void *c, void *d);

/* Set the object data pointer and initialize its coordinate-based data. */
void initialize_coordinate_entry(void *object) {
    *(void **)((u8 *)object + 0xE0) = (void *)0x8002B800;
    initialize_mode_offset_entry(*(s16 *)((u8 *)object + 8), *(s16 *)((u8 *)object + 0xA),
                  (u8 *)object + 0xD8, (void *)0x8002B800);
}

#include "common.h"

extern u8 D_80100D98[];
extern s32 D_800A5340;

extern s32 runtime_estimate_vector_length(s32 a0, s32 a1);

/* Set the record parameter and handler when the global value check is below 0xE0000. */
void set_record_handler_below_threshold(void *record) {
    u8 *base = D_80100D98;

    if (runtime_estimate_vector_length(*(s32 *) (base + 0xC), *(s32 *) (base + 0x10)) <= 0xDFFFF) {
        *(s16 *) ((u8 *) record + 4) = 0x400;
        *(void **) ((u8 *) record + 0x1C) = &D_800A5340;
    }
}

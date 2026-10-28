#include "common.h"

extern s32 scene_object_flags;

/* Waits for linked flag 8, then decreases field +8 until the object is marked for removal. */
void reset_effect_callback_state(void *ptr) {
    u8 *inner;
    s32 state;
    s32 value;

    state = *(s16 *)ptr;
    inner = *(u8 **)((u8 *)ptr + 4);
    switch (state) {
    case 0:
        if (*(u16 *)(inner + 0x1A) & 8) {
            (*(s16 *)ptr)++;
        }
        break;
    case 1:
        value = *(s32 *)((u8 *)ptr + 8) - 0x80808;
        *(s32 *)((u8 *)ptr + 8) = value;
        if (value <= 0x80808) {
            *(u16 *)((u8 *)ptr - 2) |= 0x8000;
            scene_object_flags |= 0x8000;
        }
        break;
    }
}

#include "common.h"
#ifndef NULL
#define NULL 0
#endif
extern void *func_800B0214(s32);
extern s32 D_800AFD00[4];

/* Create an object and initialize its handler table and state value. */
void *func_800B02D4(s32 object_id) {
    void *object = func_800B0214(object_id);
    if (object != NULL) {
        void *state = *(void **)((u8 *)object + 0xBC);
        *(void **)((u8 *)object + 0x10) = D_800AFD00;
        *(s16 *)((u8 *)state + 6) = 0x1000;
    }
    return object;
}

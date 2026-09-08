#include "common.h"

extern u32 D_800C3960[4];
extern u32 D_800C3988[4];
typedef struct {
    u8 pad0;
    s8 val;
    u8 pad2[6];
} Rec8;

extern Rec8 D_80082660[2];

/* Installs object handlers, sets its status, and clears its object and slot state bytes. */
void func_800C4134(void *object) {
    *(void **) ((u8 *) object + 0x50) = &D_800C3960[0];
    *(s8 *) ((u8 *) object + 0x92) = 1;
    *(void **) ((u8 *) object + 0x54) = &D_800C3988[0];
    *(s8 *) ((u8 *) object + 0x15) = 0;
    D_80082660[*(s32 *) ((u8 *) object + 0x60)].val = 0;
}

#include "common.h"

typedef struct {
    u8 pad[0x2A];
    s16 timer;
} DungeonObject;

extern s16 D_8002571C;
extern volatile s32 D_800814A0;
extern void func_800478B8(void *arg0);

void func_8002492C(DungeonObject *arg0, s32 arg1, void *arg2)
{
    volatile s32 *globalFlags;

    D_8002571C = 1;
    arg0->timer--;
    func_800478B8(arg2);
    globalFlags = &D_800814A0;
    if (arg0->timer <= 0) {
        ((volatile u16 *)arg0)[-1] |= 0x8000;
        *globalFlags |= 0x8000;
    }
}

#include "common.h"

typedef struct {
    u8 pad[0x2A];
    s16 timer;
} DungeonObject;

extern s16 D_8002571C;
extern volatile s32 D_800814A0;
extern void func_800478B8(void *arg0);

// Decrement the object's timer, call its handler, and set expiry flags when the timer runs out.
void func_8002492C(DungeonObject *object, s32 unused, void *handlerContext)
{
    volatile s32 *globalFlags;

    D_8002571C = 1;
    object->timer--;
    func_800478B8(handlerContext);
    globalFlags = &D_800814A0;
    if (object->timer <= 0) {
        ((volatile u16 *)object)[-1] |= 0x8000;
        *globalFlags |= 0x8000;
    }
}

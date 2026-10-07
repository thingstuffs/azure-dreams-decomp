#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    u8 pad[0x2A];
    s16 timer;
} DungeonObject;

extern s16 D_8002571C;
extern void func_800478B8(void *handlerContext);

// Decrement the object's timer, call its handler, and set expiry flags when the timer runs out.
void func_8002492C(DungeonObject *object, s32 unused, void *handlerContext)
{
    D_8002571C = 1;
    object->timer--;
    func_800478B8(handlerContext);
    if (object->timer <= 0) {
        ((u16 *)object)[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}

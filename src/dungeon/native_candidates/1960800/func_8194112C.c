#include "modules/dungeon_ovl_1960800.h"
#include "common.h"
#include "shared/object_flags.h"




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

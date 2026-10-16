#include "common.h"
#include "m2c_compat.h"

s32 dungeonResolveActorFloorTrapOnce();                                /* extern */
extern u8 D_800D4494;

typedef struct S_800D491C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_800D491C_0;   /* arg0 in dungeonSetActorDataPointer */

/* Sets the object data pointer when the status check is positive. */
void dungeonSetActorDataPointer(S_800D491C_0 *object) {
    if (dungeonResolveActorFloorTrapOnce() > 0) {
        object->unk_8C = &D_800D4494;
    }
}

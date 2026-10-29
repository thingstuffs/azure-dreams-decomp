#include "common.h"
#include "m2c_compat.h"
#include "town/player.h"

typedef struct S_80097D2C_0 {
    u8 pad_00[0x4];
    s32 (*unk_04)(struct S_80097D2C_0 *, void *, void *);
} S_80097D2C_0;   /* arg0 in func_80097D2C */


/* Invoke the object's callback. */
void invoke_object_state_callback(S_80097D2C_0 *object, void *position, void *sprite) {
    object->unk_04(object, position, sprite);
}

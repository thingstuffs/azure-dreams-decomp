#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C3960_0 {
    u8 pad_00[0x54];
    s32 (*unk_54)(struct S_800C3960_0 *);
} S_800C3960_0;   /* arg0 in func_800C3960 */


/* Calls the object's callback. */
void func_800C3960(S_800C3960_0 *object) {
    object->unk_54(object);
}

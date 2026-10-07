#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009C46C_0 {
    u8 pad_00[0x50];
    s32 (*unk_50)(struct S_8009C46C_0 *);
} S_8009C46C_0;   /* arg0 in func_8009C46C */


/* Invoke the object's callback. */
void func_8009C46C(S_8009C46C_0 *object) {
    object->unk_50(object);
}

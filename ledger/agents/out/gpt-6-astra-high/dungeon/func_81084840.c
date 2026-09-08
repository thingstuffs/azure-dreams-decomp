#include "common.h"
#include "m2c_compat.h"

typedef struct S_80172040_0 {
    u8 pad_00[0x9A];
    s8 unk_9A;
    s8 unk_9B;
} S_80172040_0;   /* arg0 in func_80172040 */

/* Initialize the object's two state bytes to 0x10 and zero. */
void func_80172040(S_80172040_0 *object) {
    object->unk_9A = 0x10;
    object->unk_9B = 0;
}

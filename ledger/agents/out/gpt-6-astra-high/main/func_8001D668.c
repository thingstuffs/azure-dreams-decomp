#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001D668_0 {
    u8 pad_00[0x1C0];
    s32 unk_1C0;
    u8 pad_1C4[0x58];
    s32 * unk_21C;
} S_8001D668_0;   /* arg0 in func_8001D668 */

/* Set the object's default value and clear its linked state if present. */
void func_8001D668(S_8001D668_0 *object) {
    if (object != NULL) {
        object->unk_1C0 = 0x606868;
        *object->unk_21C = 0;
    }
}

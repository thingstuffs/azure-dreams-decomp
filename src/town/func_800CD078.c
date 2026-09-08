#include "common.h"
#include "m2c_compat.h"

extern s8 D_800826B8;

typedef struct S_800CA7D8_0 {
    u8 pad_00[0x6E];
    s16 unk_6E;
} S_800CA7D8_0;   /* arg0 in func_800CA7D8 */

/* Clear the global flag and set the object's field at 0x6E to 0xC00. */
void func_800CA7D8(S_800CA7D8_0 *object) {
    D_800826B8 = 0;
    object->unk_6E = 0xC00;
}

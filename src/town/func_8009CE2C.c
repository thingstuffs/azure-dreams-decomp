#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_8009A58C_0 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_8009A58C_0;   /* arg0 in func_8009A58C */


void func_80098988(S_8009A58C_0 *, s32);
/* Clear the indexed table entry and call func_80098988. */
void func_8009A58C(S_8009A58C_0 *object, s32 value) {
    D_80082660[object->unk_40].unk_00 = 0;
    func_80098988(object, value);
}

#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct S_800A2DF0_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800A2DF0_0;   /* arg0 in func_800A2DF0 */


/* Add three record increments to the corresponding 16-bit components. */
void func_800A2DF0(S_800A2DF0_0 *components, EntityRec *increments) {
    components->unk_00 = (u16) (components->unk_00 + ((u16)increments->x.w.i));
    components->unk_02 = (u16) (components->unk_02 + ((u16)increments->y.w.i));
    components->unk_04 = (u16) (components->unk_04 + ((u16)increments->z.w.i));
}

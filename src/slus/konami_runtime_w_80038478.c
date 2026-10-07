#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80038478_0 {
    u8 pad_00[0x84];
    s8 unk_84;
} S_80038478_0;   /* arg0 in func_80038478 */


typedef struct Rec_func_800384A8_arg0 Rec_func_800384A8_arg0;
void func_800384A8(Rec_func_800384A8_arg0 *state);                            /* extern */

/* Call func_800384A8 when the object's flag is set. */
void func_80038478(S_80038478_0 *object) {
    if (object->unk_84 != 0) {
        func_800384A8((Rec_func_800384A8_arg0 *)object);
    }
}

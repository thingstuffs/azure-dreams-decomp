#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80099754();                     /* extern */
extern M2C_UNK D_80098078;

typedef struct S_80098B70_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_80098B70_0;   /* arg0 in func_80098B70 */

/* Sets the object's data pointer and forwards the argument to func_80099754. */
void func_80098B70(S_80098B70_0 *object, M2C_UNK forwarded_arg) {
    object->unk_04 = &D_80098078;
    func_80099754(forwarded_arg);
}

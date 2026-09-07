#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80099754();                     /* extern */
extern M2C_UNK D_80098078;

typedef struct S_80098B70_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_80098B70_0;   /* arg0 in func_80098B70 */

void func_80098B70(S_80098B70_0 *arg0, M2C_UNK arg1) {
    arg0->unk_04 = &D_80098078;
    func_80099754(arg1);
}

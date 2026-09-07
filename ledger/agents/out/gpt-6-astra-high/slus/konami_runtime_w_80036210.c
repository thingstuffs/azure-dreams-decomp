#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80036210_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_80036210_1;   /* arg0 in func_80036210 */

typedef struct S_80036210_2 {
    u8 pad_00[0x80];
    s32 unk_80;
} S_80036210_2;   /* ((S_80036210_1 *)arg0)->unk_74 in func_80036210 */


typedef struct S_80036210_0 {
    u8 pad_00[0x4C];
    s8 unk_4C;
    u8 pad_4D[0x1B];
    M2C_UNK * unk_68;
} S_80036210_0;   /* arg0 in func_80036210 */


M2C_UNK func_80036B10(); /* extern */
extern M2C_UNK D_80081FDC;
extern M2C_UNK D_80082414;
extern M2C_UNK func_8003626C;

/* Initialize the object's runtime state and set its next handler. */
void func_80036210(S_80036210_0 *object) {
    func_80036B10(&D_80082414, &D_80081FDC, object, 0, ((S_80036210_2 *)(((S_80036210_1 *)object)->unk_74))->unk_80);
    object->unk_4C = 0;
    object->unk_68 = &func_8003626C;
}

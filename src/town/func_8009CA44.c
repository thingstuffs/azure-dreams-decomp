#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009A1A4_1 {
    u8 pad_00[0x44];
    void * unk_44;
} S_8009A1A4_1;   /* arg0 in func_8009A1A4 */

typedef struct S_8009A1A4_2 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_8009A1A4_2;   /* ((S_8009A1A4_1 *)arg0)->unk_44 in func_8009A1A4 */




M2C_UNK func_80094984();                 /* extern */
extern M2C_UNK D_80099B70;

typedef struct S_8009A1A4_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_8009A1A4_0;   /* arg0 in func_8009A1A4 */

void func_8009A1A4(S_8009A1A4_0 *arg0) {
    func_80094984(((S_8009A1A4_2 *)(((S_8009A1A4_1 *)arg0)->unk_44))->unk_20, arg0);
    arg0->unk_04 = &D_80099B70;
}

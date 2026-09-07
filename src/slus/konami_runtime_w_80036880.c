#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80036880_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_80036880_1;   /* arg0 in func_80036880 */

typedef struct S_80036880_2 {
    u8 pad_00[0x27];
    u8 unk_27;
} S_80036880_2;   /* ((S_80036880_1 *)arg0)->unk_74 in func_80036880 */


typedef struct S_80036880_0 {
    u8 pad_00[0x4D];
    u8 unk_4D;
    u8 pad_4E[0x16];
    s16 unk_64;
    u8 pad_66[0x2];
    M2C_UNK * unk_68;
} S_80036880_0;   /* arg0 in func_80036880 */


M2C_UNK func_80053DA8();                     /* extern */
extern M2C_UNK func_80036484;

void func_80036880(S_80036880_0 *arg0) {
    ((S_80036880_2 *)(((S_80036880_1 *)arg0)->unk_74))->unk_27 = (u8) arg0->unk_4D;
    arg0->unk_64 = 0x11;
    arg0->unk_68 = &func_80036484;
    arg0->unk_4D = (u8) (arg0->unk_4D | 0x80);
    func_80053DA8(0x503);
}

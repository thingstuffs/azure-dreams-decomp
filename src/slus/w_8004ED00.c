#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8004ED00_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_8004ED00_0_pre;   /* the 0x10 bytes before arg0 in func_8004ED00, addressed as arg0[-1] */

typedef struct S_8004ED00_0 {
    u8 pad_00[0x8];
    u8 unk_08;
} S_8004ED00_0;   /* arg0 in func_8004ED00 */


M2C_UNK DrawSync();                          /* extern */
M2C_UNK func_80041344();                /* extern */
M2C_UNK func_8004EB8C();                      /* extern */
extern s32 D_80081480;
extern M2C_UNK func_8004ECAC;

void func_8004ED00(void *arg0) {
    if (((S_8004ED00_0 *)arg0)->unk_08 != 0) {
        func_80041344(0x80020000, D_80081480);
        DrawSync(0);
        func_8004EB8C(arg0 + 9);
        ((S_8004ED00_0_pre *)arg0)[-1].unk_00 = &func_8004ECAC;
    }
}

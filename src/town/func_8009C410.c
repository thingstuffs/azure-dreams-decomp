#include "common.h"
#include "m2c_compat.h"

typedef struct S_80099B70_0 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80099B70_0;   /* arg1 in func_80099B70 */


M2C_UNK func_80095388();                 /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80098928();        /* extern */
M2C_UNK func_80099BF8();                            /* extern */
extern M2C_UNK D_800FE488;

void func_80099B70(s32 arg0, S_80099B70_0 *arg1, M2C_UNK arg2) {
    s16 temp_v0;

    arg1->unk_08.at00.v = (s32) (arg1->unk_08.at00.v + arg1->unk_14);
    temp_v0 = func_80095978(arg1, &D_800FE488);
    if (temp_v0 < arg1->unk_08.at02.v) {
        func_80095A94(arg1, temp_v0, &D_800FE488);
        func_80098928(arg0, arg1, arg2);
        return;
    }
    func_80095388(arg1, temp_v0);
}

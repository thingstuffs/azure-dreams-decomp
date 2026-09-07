#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s8 x;
    s8 y;
    s8 z;
} Vec3s;

M2C_UNK func_8004E5A0();      /* extern */
M2C_UNK *func_8004E634();             /* extern */
M2C_UNK strcat();           /* extern */
s32 func_800B555C();               /* extern */
extern M2C_UNK D_800892D8;
extern Vec3s D_800892F0;
extern M2C_UNK D_800892F4;
extern M2C_UNK D_800892F8;
extern M2C_UNK D_800892FC;
extern M2C_UNK D_80089304;

typedef struct S_800B557C_0 {
    u8 pad_00[0x26];
    u8 unk_26;
    u8 unk_27;
    u8 pad_28[0x40];
    u8 unk_68;
    u8 unk_69;
} S_800B557C_0;   /* arg1 in func_800B557C */

void *func_800B557C(void *arg0, S_800B557C_0 *arg1) {
    M2C_UNK sp10[3];
    s32 temp_v0;
    s32 temp_v0_2;
    Vec3s *src;

    src = &D_800892F0;
    *(Vec3s *)arg0 = *src;
    temp_v0 = func_800B555C(arg1->unk_68, arg1->unk_26);
    if (temp_v0 != 0) {
        strcat(arg0, &D_800892F4);
        strcat(arg0, func_8004E634(temp_v0, &sp10));
    }
    strcat(arg0, &D_800892F8);
    func_8004E5A0(arg1->unk_26, 3, &sp10);
    strcat(arg0, &sp10);
    strcat(arg0, &D_800892F4);
    strcat(arg0, func_8004E634(0, &sp10));
    strcat(arg0, &D_800892FC);
    temp_v0_2 = func_800B555C(arg1->unk_69, arg1->unk_27);
    if (temp_v0_2 != 0) {
        strcat(arg0, &D_800892F4);
        strcat(arg0, func_8004E634(temp_v0_2, &sp10));
    }
    func_8004E5A0(arg1->unk_27, 3, &sp10);
    strcat(arg0, &sp10);
    strcat(arg0, &D_800892F4);
    strcat(arg0, func_8004E634(0, &sp10));
    strcat(arg0, &D_800892D8);
    strcat(arg0, &D_80089304);
    func_8004E5A0(arg1->unk_68, 3, &sp10);
    strcat(arg0, &sp10);
    strcat(arg0, &D_800892FC);
    func_8004E5A0(arg1->unk_69, 3, &sp10);
    strcat(arg0, &sp10);
    return arg0;
}

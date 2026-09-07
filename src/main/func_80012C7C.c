#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800220DC();                            /* extern */
M2C_UNK func_8002223C();                            /* extern */
s32 func_800238D4();                          /* extern */
s32 func_80024D58();            /* extern */
M2C_UNK func_80025B40();                 /* extern */
void *func_8003FE78();   /* extern */
s32 func_8004F418();                  /* extern */
extern M2C_UNK D_80025BD4;
extern M2C_UNK D_8002B7E0;

typedef struct S_80025C7C_0 {
    u8 pad_00[0x18];
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0x4];
    s32 unk_24;
    s32 unk_28;
    u8 pad_2C[0x1C];
    s32 unk_48;
} S_80025C7C_0;   /* temp_s1 in func_80025C7C */

typedef struct S_80025C7C_1 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80025C7C_1;   /* temp_v0 in func_80025C7C */

void *func_80025C7C(s32 arg0) {
    S_80025C7C_0 *temp_s1;
    void *temp_v0;

    temp_v0 = func_8003FE78(0, &D_8002B7E0, 0x1C);
    temp_s1 = temp_v0 + 0x20;
    func_80025B40(temp_s1, arg0);
    func_8002223C();
    func_800220DC();
    temp_s1->unk_48 = 1;
    ((S_80025C7C_1 *)temp_v0)->unk_20 = func_8004F418(temp_v0, temp_v0 + 0x68);
    temp_s1->unk_18 = func_800238D4(temp_v0);
    temp_s1->unk_1C = func_80024D58(temp_v0, temp_s1->unk_28, 0);
    temp_s1->unk_24 = 0;
    ((S_80025C7C_1 *)temp_v0)->unk_10 = &D_80025BD4;
    return temp_v0;
}

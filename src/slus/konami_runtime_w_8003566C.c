#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003566C_3 {
    void * unk_00;
} S_8003566C_3;   /* arg0 in func_8003566C */

typedef struct S_8003566C_4 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8003566C_4;   /* ((S_8003566C_3 *)arg0)->unk_00 in func_8003566C */


typedef struct S_8003566C_0 {
    void * unk_00;
    u8 pad_04[0x49];
    s8 unk_4D;
    u8 pad_4E[0x1A];
    M2C_UNK * unk_68;
    u8 pad_6C[0x8];
    s32 unk_74;
} S_8003566C_0;   /* arg0 in func_8003566C */

typedef struct S_8003566C_1 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8003566C_1;   /* temp_v0 in func_8003566C */

typedef struct S_8003566C_2 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8003566C_2;   /* temp_v1 in func_8003566C */


M2C_UNK func_80035E58(); /* extern */
extern M2C_UNK D_8006A86C;
extern M2C_UNK D_80081F78;
extern M2C_UNK D_800822F0;
extern M2C_UNK func_8003571C;

void func_8003566C(S_8003566C_0 *arg0) {
    S_8003566C_1 *temp_v0;
    S_8003566C_2 *temp_v1;

    temp_v0 = arg0->unk_00;
    temp_v0->unk_08 = (u16) (temp_v0->unk_08 - 0xA0);
    temp_v1 = arg0->unk_00;
    if ((s16) temp_v1->unk_08 < 0) {
        temp_v1->unk_08 = 0U;
    }
    if ((s16) ((S_8003566C_4 *)(((S_8003566C_3 *)arg0)->unk_00))->unk_08 < 0x100) {
        func_80035E58(&D_800822F0, &D_80081F78, &D_8006A86C, arg0, 1, arg0->unk_74);
        arg0->unk_4D = 0;
        arg0->unk_68 = &func_8003571C;
    }
}

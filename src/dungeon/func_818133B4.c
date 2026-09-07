#include "common.h"

typedef struct S_800283B4_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} S_800283B4_0_pre;   /* the 0x10 bytes before temp_s0 in func_800283B4, addressed as temp_s0[-1] */

typedef struct S_800283B4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0xC];
    s32 unk_28;
    u8 pad_2C[0xC];
    s32 unk_38;
    u8 pad_3C[0xC];
    void * unk_48;
    s32 unk_4C;
    u8 pad_50[0x30];
    void * unk_80;
    s32 unk_84;
    s32 unk_88;
} S_800283B4_0;   /* temp_s0 in func_800283B4 */

typedef struct S_800283B4_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800283B4_1;   /* ((S_800283B4_0 *)temp_s0)->unk_80 in func_800283B4 */

typedef struct S_800283B4_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800283B4_2;   /* ((S_800283B4_0 *)temp_s0)->unk_48 in func_800283B4 */



extern s32 func_80027454();
extern s32 func_80027FA4();
extern s32 func_80027FF4();
extern s32 func_80028534();
extern s32 func_80028648();
extern s32 D_80027D7C;

void func_800283B4(s32 arg0) {
    void *temp_s0;

    temp_s0 = arg0 + 0x20;
    ((S_800283B4_0 *)temp_s0)->unk_14 = 1;
    ((S_800283B4_1 *)(((S_800283B4_0 *)temp_s0)->unk_80))->unk_02 = 0;
    ((S_800283B4_0 *)temp_s0)->unk_08 = 0;
    ((S_800283B4_0 *)temp_s0)->unk_28 = ((S_800283B4_2 *)(((S_800283B4_0 *)temp_s0)->unk_48))->unk_1C;
    ((S_800283B4_0 *)temp_s0)->unk_38 = ((S_800283B4_0 *)temp_s0)->unk_18;
    func_80027454(arg0 + 0x58, ((S_800283B4_0 *)temp_s0)->unk_14, 0, ((S_800283B4_0 *)temp_s0)->unk_28);
    func_80027FF4(((S_800283B4_0 *)temp_s0)->unk_4C, ((S_800283B4_0 *)temp_s0)->unk_14);
    ((S_800283B4_0 *)temp_s0)->unk_84 = func_80027FA4(((S_800283B4_0 *)temp_s0)->unk_88);
    func_80028534(((S_800283B4_0 *)temp_s0)->unk_88);
    func_80028648(arg0);
    ((S_800283B4_0_pre *)temp_s0)[-1].unk_00 = &D_80027D7C;
}

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AF254_arg1.h"

extern int func_80049490();
extern M2C_UNK func_800AF254();
extern M2C_UNK func_800AF448(Rec_func_800AF254_arg1 *);
extern M2C_UNK func_800AF520();
extern M2C_UNK func_800AF674();
extern M2C_UNK func_800AF784();
extern M2C_UNK func_800AF858();


typedef struct S_800AFFA8_1 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0x4];
    s32 * unk_20;
} S_800AFFA8_1;   /* temp_v1 in func_800AFFA8 */

void func_800AFFA8(Rec_func_800AF254_arg1 *arg0) {
    S_800AFFA8_1 *temp_v1;

    func_800AF448(arg0);
    func_800AF520(arg0);
    func_800AF674(arg0);
    func_800AF784(arg0);
    func_800AF254(arg0->unk_A8.as_s32, arg0);
    func_800AF858(arg0->unk_A8.as_s32, arg0);
    temp_v1 = arg0->unk_00;
    func_80049490(temp_v1->unk_20[temp_v1->unk_18]);
}

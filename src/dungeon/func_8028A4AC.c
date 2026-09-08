#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8001CE44_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80016000[];
M2C_UNK func_8001CEC0();                 /* extern */
M2C_UNK func_8001CFB8();                 /* extern */
M2C_UNK func_8001D0F4();                 /* extern */
M2C_UNK func_8001D328();                 /* extern */
M2C_UNK func_8001D5C0() __attribute__((noreturn));  /* extern */
s32 func_800A6D30();                                /* extern */
extern M2C_UNK D_8001F670;



typedef struct S_8001D4AC_1 {
    s32 unk_00;
} S_8001D4AC_1;   /* &D_8001F670 in func_8001D4AC */

void func_8001D4AC(Rec_func_8001CE44_arg0 *arg0, s16 arg1) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    u32 temp_v1;

    arg0->unk_0A = 1;
    temp_v1 = func_800A6D30() & 0xFF;
    if (temp_v1 >= 0xDU) {
        goto block_14;
    }
    (void)jt_keep; goto *D_80016000[(u32)(temp_v1)];
jt_c0:
    arg0->unk_0A = 2;
    func_8001D5C0();
    return;
jt_c1:
    if (((S_8001D4AC_1 *)(&D_8001F670))->unk_00 != 0) {
        goto block_14;
    }
    arg0->unk_0A = 3;
    D_8001F670 = 1;
    func_8001CFB8(arg0, arg1);
    func_8001D5C0();
    return;
jt_c2:
    if (((S_8001D4AC_1 *)(&D_8001F670))->unk_00 != 0) {
        goto block_14;
    }
    D_8001F670 = 1;
    arg0->unk_0A = 2;
    func_8001D328(arg0, arg1);
    func_8001D5C0();
    return;
jt_c4:
    if (((S_8001D4AC_1 *)(&D_8001F670))->unk_00 != 0) {
        goto block_14;
    }
    D_8001F670 = 1;
    arg0->unk_0A = 4;
    func_8001D0F4(arg0, arg1);
    func_8001D5C0();
    return;
jt_c5:
jt_c6:
jt_c7:
jt_c8:
jt_c9:
jt_c10:
jt_c11:
jt_c12:
    func_8001CEC0(arg0, arg1);
block_14:
jt_c3:
    return;
}

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8001CE44_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80016000[];
M2C_UNK func_8001CEC0();                 /* extern */
M2C_UNK func_8001CFB8();                 /* extern */
M2C_UNK func_8001D0F4();                 /* extern */
M2C_UNK func_8001D328();                 /* extern */
s32 func_800A6D30(Rec_func_8001CE44_arg0 *arg0, s32 arg1, s32 arg2, s32 arg3);                                /* extern */
extern M2C_UNK D_8001F670;



typedef struct S_8001D4AC_1 {
    s32 unk_00;
} S_8001D4AC_1;   /* &D_8001F670 in func_8001D4AC */

/* Choose a random region feature, allowing only one special placement. */
void func_8001D4AC(Rec_func_8001CE44_arg0 *region, s32 update_id, s32 rng_input_2, s32 rng_input_3) {
    static void *const case_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    u32 feature_roll;
    s16 saved_update_id = update_id;

    region->unk_0A = 1;
    feature_roll = func_800A6D30(region, update_id, rng_input_2, rng_input_3) & 0xFF;
    if (feature_roll >= 0xDU) {
        goto done;
    }
    (void)case_labels;
    goto *D_80016000[(u32)(feature_roll)];
jt_c0:
    region->unk_0A = 2;
    return;
jt_c1:
    if (((S_8001D4AC_1 *)(&D_8001F670))->unk_00 != 0) {
        goto done;
    }
    region->unk_0A = 3;
    D_8001F670 = 1;
    func_8001CFB8(region, saved_update_id);
    return;
jt_c2:
    if (((S_8001D4AC_1 *)(&D_8001F670))->unk_00 != 0) {
        goto done;
    }
    D_8001F670 = 1;
    region->unk_0A = 2;
    func_8001D328(region, saved_update_id);
    return;
jt_c4:
    if (((S_8001D4AC_1 *)(&D_8001F670))->unk_00 != 0) {
        goto done;
    }
    D_8001F670 = 1;
    region->unk_0A = 4;
    func_8001D0F4(region, saved_update_id);
    return;
jt_c5:
jt_c6:
jt_c7:
jt_c8:
jt_c9:
jt_c10:
jt_c11:
jt_c12:
    func_8001CEC0(region, saved_update_id);
done:
jt_c3:
    return;
}

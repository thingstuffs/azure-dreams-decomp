#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "records/Rec_func_8001CE44_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
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
    u32 feature_roll;
    s16 saved_update_id = update_id;

    region->unk_0A = 1;
    feature_roll = func_800A6D30(region, update_id, rng_input_2, rng_input_3) & 0xFF;
    switch (feature_roll) {
    case 0:
    region->unk_0A = 2;
    return;
    case 1:
    if (((S_8001D4AC_1 *)(&D_8001F670))->unk_00 != 0) {
        break;
    }
    region->unk_0A = 3;
    D_8001F670 = 1;
    func_8001CFB8(region, saved_update_id);
    return;
    case 2:
    if (((S_8001D4AC_1 *)(&D_8001F670))->unk_00 != 0) {
        break;
    }
    D_8001F670 = 1;
    region->unk_0A = 2;
    func_8001D328(region, saved_update_id);
    return;
    case 4:
    if (((S_8001D4AC_1 *)(&D_8001F670))->unk_00 != 0) {
        break;
    }
    D_8001F670 = 1;
    region->unk_0A = 4;
    func_8001D0F4(region, saved_update_id);
    return;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    func_8001CEC0(region, saved_update_id);
    }
    return;
}

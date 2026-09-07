#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017480();     /* extern */
s32 func_80017BEC();                             /* extern */
M2C_UNK func_8001D4AC();                 /* extern */
M2C_UNK func_8001D5D8();                 /* extern */

typedef struct S_8001CE44_0 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
} S_8001CE44_0;   /* arg0 in func_8001CE44 */

/* Update the region until its completion check succeeds, then finalize it. */
void func_8001CE44(S_8001CE44_0 *region, s16 update_id) {
    do {
        func_8001D5D8(region, update_id);
        func_8001D4AC(region, update_id);
    } while ((func_80017BEC(update_id) << 0x10) == 0);
    func_80017480(region->unk_00, region->unk_02, region->unk_04, region->unk_06, 0xF);
}

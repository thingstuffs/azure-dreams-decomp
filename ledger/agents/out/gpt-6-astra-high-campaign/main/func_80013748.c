#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026748_0 {
    s32 * unk_00;
} S_80026748_0;   /* arg0 in func_80026748; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800265B8[];
M2C_UNK func_80025DC8(void *);                            /* extern */

/* Update the record, run the shared follow-up, and install its next table. */
void func_80026748(void *record_data) {
    func_80025DC8(record_data);
    func_80020984();
    ((S_80026748_0 *)((u8 *)record_data - 0x10))->unk_00 = D_800265B8;
}

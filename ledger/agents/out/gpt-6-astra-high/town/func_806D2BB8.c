/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_806D2BB8_0 {
    s32 unk_00;
    u8 pad_04[0x4];
    union { s32 * s; s32 u; } unk_08;   /* accessed as both */
    s32 unk_0C;
} S_806D2BB8_0;   /* arg1 in func_806D2BB8 */

typedef struct S_806D2BB8_1 {
    s32 unk_00;
    union { s32 * s; s32 u; } unk_04;   /* accessed as both */
    u8 pad_08[0x4];
    s32 unk_0C;
} S_806D2BB8_1;   /* temp_v0 in func_806D2BB8 */


void *func_8001637C();                           /* extern */
extern M2C_UNK D_80017008;

/* Gets an entry by its masked key and initializes its offset slot if empty. */
void *func_806D2BB8(void *context, S_806D2BB8_0 *descriptor) {
    s32 entry_key;
    s32 slot_addr;
    void *result;
    S_806D2BB8_1 *entry;

    entry_key = descriptor->unk_00 & 0x3FFF0000;
    entry = func_8001637C(context, entry_key);
    result = entry;
    if (entry->unk_04.s == NULL) {
        *descriptor->unk_08.s = ((s8 *) descriptor->unk_0C - (s8 *) &D_80017008) + 4;
        slot_addr = descriptor->unk_08.u;
        entry->unk_00 = entry_key;
        entry->unk_0C = 0;
        entry->unk_04.u = slot_addr;
    }
    return result;
}

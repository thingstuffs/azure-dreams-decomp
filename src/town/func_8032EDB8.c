/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800195B8_0 {
    s32 unk_00;
} S_800195B8_0;   /* (((var_s1 * 8) - var_s1) * 4) + arg0 in func_800195B8 */

typedef struct S_800195B8_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800195B8_1;   /* ((var_s1 * 0x1C) + arg0) in func_800195B8 */

typedef struct S_800195B8_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800195B8_2;   /* ((((var_s1 * 8) - var_s1) * 4) + arg0) in func_800195B8 */

typedef struct S_800195B8_3 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_800195B8_3;   /* page in func_800195B8 */

typedef struct S_800195B8_4 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800195B8_4;   /* ((S_800195B8_3 *)page)->unk_6000 in func_800195B8 */

typedef struct S_800195B8_5 {
    u8 pad_00[0x168];
    M2C_UNK (*unk_168)(M2C_UNK *, M2C_UNK *, M2C_UNK);
    u8 pad_16C[0x8];
    M2C_UNK (*unk_174)(M2C_UNK);
} S_800195B8_5;   /* ((S_800195B8_4 *)(((S_800195B8_3 *)page)->unk_6000))->unk_20 in func_800195B8 */


extern u8 D_80010000[];
extern M2C_UNK D_80016064[];
extern M2C_UNK D_8001608C[];

/* Find the index of an entry by ID, reporting an error if it is missing. */
s32 func_800195B8(void *entries, s32 entry_id) {
    s32 entry_index;

    entry_index = 0;
    if ((*(s32 *)((u8 *)entries + 8)) != 0) {
check_entry:
        if (((S_800195B8_0 *)((((entry_index * 8) - entry_index) * 4) + entries))->unk_00 != entry_id) {
            entry_index += 1;
            if (((S_800195B8_1 *)(((entry_index * 0x1C) + entries)))->unk_08 == 0) {
                goto search_done;
            }
            goto check_entry;
        }
    } else {
search_done:
    }
    if (((S_800195B8_2 *)(((((entry_index * 8) - entry_index) * 4) + entries)))->unk_08 == 0) {
        u8 *page = (u8 *)0x80010000;
        M2C_UNK (*report_missing)(M2C_UNK *, M2C_UNK *, M2C_UNK);
        do {
            report_missing = ((S_800195B8_5 *)(((S_800195B8_4 *)(((S_800195B8_3 *)page)->unk_6000))->unk_20))->unk_168;
        } while (0);
        report_missing(&D_80016064, &D_8001608C, 0x37);
        ((S_800195B8_5 *)(((S_800195B8_4 *)(((S_800195B8_3 *)page)->unk_6000))->unk_20))->unk_174(1);
    }
    return entry_index;
}

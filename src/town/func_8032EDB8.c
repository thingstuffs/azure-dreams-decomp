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

s32 func_800195B8(void *arg0, s32 arg1) {
    s32 var_s1;

    var_s1 = 0;
    if ((*(s32 *)((u8 *)arg0 + 8)) != 0) {
loop_2:
        if (((S_800195B8_0 *)((((var_s1 * 8) - var_s1) * 4) + arg0))->unk_00 != arg1) {
            var_s1 += 1;
            if (((S_800195B8_1 *)(((var_s1 * 0x1C) + arg0)))->unk_08 == 0) {
                goto block_4;
            }
            goto loop_2;
        }
    } else {
block_4:
    }
    if (((S_800195B8_2 *)(((((var_s1 * 8) - var_s1) * 4) + arg0)))->unk_08 == 0) {
        u8 *page = (u8 *)0x80010000;
        M2C_UNK (*call0)(M2C_UNK *, M2C_UNK *, M2C_UNK);
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        call0 = ((S_800195B8_5 *)(((S_800195B8_4 *)(((S_800195B8_3 *)page)->unk_6000))->unk_20))->unk_168;
        ASM_KEEP(call0);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        call0(&D_80016064, &D_8001608C, 0x37);
        ((S_800195B8_5 *)(((S_800195B8_4 *)(((S_800195B8_3 *)page)->unk_6000))->unk_20))->unk_174(1);
    }
    return var_s1;
}

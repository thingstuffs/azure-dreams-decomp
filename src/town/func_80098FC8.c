#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */
extern s8 D_800CFCED;

typedef struct S_80096728_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_80096728_0;   /* arg0 in townSetGlobal800CFCEDInitializeCallCallee800954DC */


void townClearTheGlobalStateSFifthWordCopySourceSSecond(S_80096728_0 *);
/* Set D_800CFCED, initialize the record, and call townClearTheGlobalStateSFifthWordCopySourceSSecond. */
void townSetGlobal800CFCEDInitializeCallCallee800954DC(S_80096728_0 *record, s32 initial_value) {
    D_800CFCED = 1;
    record->unk_04 = initial_value;
    record->unk_10 = 0;
    townClearTheGlobalStateSFifthWordCopySourceSSecond(record);
}

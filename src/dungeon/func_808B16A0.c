#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_80016BDC(s16);                         /* extern */

typedef struct S_808B16A0_0 {
    s16 unk_00;
    s16 unk_02;
} S_808B16A0_0;   /* var_s0 in func_808B16A0 */

/* Pass both signed 16-bit values in each pair to func_80016BDC. */
void func_808B16A0(void *pairs, s32 pairCount) {
    char pad[8];
    s16 secondValue;
    s32 pairsProcessed;
    void *currentPair;

    pairsProcessed = 0;
    if (pairCount > 0) {
        currentPair = pairs;
        do {
            pairsProcessed += 1;
            func_80016BDC(((S_808B16A0_0 *)currentPair)->unk_00);
            secondValue = ((S_808B16A0_0 *)currentPair)->unk_02;
            currentPair += 4;
            func_80016BDC(secondValue);
        } while (pairsProcessed < pairCount);
    }
}

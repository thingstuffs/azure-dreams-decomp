#include "common.h"

/* Sets the enable flag for mode 1, or mode 0 when incrementing the value preserves its quotient by five. */
s32 func_800A6780(void) {
    s8 *flagBase = (s8 *)0x80080000;     /* integer pages, two genuine accesses each (decision 44) */
    s32 *stateBase = (s32 *)0x80010000;
    s32 mode;
    s32 boundaryValue;

    mode = stateBase[0x2090 / 4];
    ODDITY_SCHED_FENCE();   /* oddity (ledger/oddities.jsonl): retail keeps this flag clear after the mode load; cdk's alias analysis proves the two constant pages disjoint for every C spelling, so only a zero-byte barrier orders them (r118_opus_o8; body recovered from the JP build: JP distance 0 at stock 2.7.2) */
    flagBase[0xA88] = 0;
    if (mode == 1 || (mode == 0 && (boundaryValue = stateBase[0x234 / 4], boundaryValue / 5 == (boundaryValue + 1) / 5))) {
        flagBase[0xA88] = 1;
        return 1;
    }
    return 0;
}

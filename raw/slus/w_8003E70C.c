#include "common.h"

typedef struct S_80083958 {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    /* 0x6 */ u16 counter1;
    /* 0x8 */ u16 counter2;
    /* 0xA */ u16 flags;
} S_80083958;

extern S_80083958 D_80083958;

extern void CdInit(void);

/* summary: increment two u16 counters in D_80083958; if the first counter
 * (offset 0x6) reaches 0x401, call CdInit() and reset it to 0. */
void cdIncRetryCounters(void)
{
    D_80083958.counter2++;
    D_80083958.counter1++;
    if (D_80083958.counter1 >= 0x401) {
        D_80083958.counter1 = 0;
        CdInit();
    }
}

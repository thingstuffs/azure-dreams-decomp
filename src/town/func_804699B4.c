#include "common.h"

extern void townCopyCallbackValueToDestination(void *, void *);
extern void townDispatchRecordsByKind(void *, void *);

extern u8 D_80017ADC;
extern u8 D_80017AE8;
extern u8 D_80017AF4;
extern u8 D_80017B00;
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern u8 D_80017D50;

/* Builds the entry list and flags entries according to the selected index. */
void *func_8001A9B4(s32 entry_index) {
    u8 *entries = &D_80017D50;

    if (entry_index != 0) {
        *(s16 *)(entries + (entry_index * 0x14) + 2) = 0x400;
    }

    townDispatchRecordsByKind(entries, &D_80017ADC);
    townCopyCallbackValueToDestination(entries, &D_80017AE8);

    if (entry_index == 1) {
        *(s16 *)(entries + 0xA2) = 0x400;
        townCopyCallbackValueToDestination(entries + 0xA0, &D_80017B00);
    } else {
        *(s16 *)(entries + 0xB6) = 0x400;
        townCopyCallbackValueToDestination(entries + 0xB4, &D_80017B0C);
    }

    townCopyCallbackValueToDestination(entries + 0xDC, &D_80017AF4);
    townCopyCallbackValueToDestination(entries + 0xC8, &D_80017B18);
    return entries;
}

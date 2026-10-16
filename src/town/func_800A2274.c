#include "common.h"

extern void townGetFirstFreeFourByteEntryIndexN1NoneAvailable(void *entry, s32 entry_count);
extern s32 func_800B28A0(void);
extern s32 D_800D0728[];

/* sarch_koyaw_free: search for a free entry using the selected capacity. */
void sarch_koyaw_free(void) {
    s32 capacity_index;

    capacity_index = func_800B28A0();
    townGetFirstFreeFourByteEntryIndexN1NoneAvailable((void *)0x80010980, D_800D0728[capacity_index]);
}

#include "common.h"
#include "shared/record_ptrs.h"

typedef struct S_800161C0_0 {
    u8 pad_00[0x24];
    void * unk_24;
} S_800161C0_0;   /* *(void **)D_80016000 in townAdvanceFloorEventCounter */

typedef struct S_800161C0_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_800161C0_1;   /* ((S_800161C0_0 *)(*(void **)D_80016000))->unk_24 in townAdvanceFloorEventCounter */

typedef struct S_800161C0_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_800161C0_2;   /* ((S_800161C0_1 *)(((S_800161C0_0 *)(*(void **)D_80016000))->unk_24))->unk_74 in townAdvanceFloorEventCounter */


extern s32 townSetIndexedEntryFlag();
extern s32 townGetScriptFlagMask();
extern s32 townReadScriptFlagRange();
extern s32 townWriteScriptFlagRange();
extern s32 func_8001DCD4();

#define CURRENT_FLOOR() \
((S_800161C0_2 *)(((S_800161C0_1 *)(((S_800161C0_0 *)(*(void **)((s8 *)(&D_80016000))))->unk_24))->unk_74))->unk_2A

/* Advance the counter up to five and process the current floor unless an early exit applies. */
s32 townAdvanceFloorEventCounter(s32 fallback_arg_a, s32 fallback_arg_b) {
    s32 count;
    s32 next_count;
    s32 capped_count;

    if (townGetScriptFlagMask(0x1462) != 0) {
        townSetIndexedEntryFlag(fallback_arg_a, fallback_arg_b);
        return 1;
    }

    count = townReadScriptFlagRange(0xD84, 3);
    if ((CURRENT_FLOOR() == 7) && (count >= 5)) {
        return 1;
    }

    next_count = count + 1;
    capped_count = 5;
    if (next_count < 6) {
        capped_count = next_count;
    }
    townWriteScriptFlagRange(0xD84, capped_count, 3);
    func_8001DCD4(CURRENT_FLOOR());
    return 0;
}

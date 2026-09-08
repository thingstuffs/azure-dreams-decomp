#include "common.h"

typedef struct S_800161C0_0 {
    u8 pad_00[0x24];
    void * unk_24;
} S_800161C0_0;   /* *(void **)D_80016000 in func_800161C0 */

typedef struct S_800161C0_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_800161C0_1;   /* ((S_800161C0_0 *)(*(void **)D_80016000))->unk_24 in func_800161C0 */

typedef struct S_800161C0_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_800161C0_2;   /* ((S_800161C0_1 *)(((S_800161C0_0 *)(*(void **)D_80016000))->unk_24))->unk_74 in func_800161C0 */


extern s32 func_80019958();
extern s32 func_8001ADE0();
extern s32 func_8001B0E8();
extern s32 func_8001B168();
extern s32 func_8001DCD4();
extern s8 D_80016000[];

#define CURRENT_FLOOR() \
    ((S_800161C0_2 *)(((S_800161C0_1 *)(((S_800161C0_0 *)(*(void **)D_80016000))->unk_24))->unk_74))->unk_2A

/* Advance the counter up to five and process the current floor unless an early exit applies. */
s32 func_800161C0(s32 fallback_arg_a, s32 fallback_arg_b) {
    s32 count;
    s32 next_count;
    s32 capped_count;

    if (func_8001ADE0(0x1462) != 0) {
        func_80019958(fallback_arg_a, fallback_arg_b);
        return 1;
    }

    count = func_8001B0E8(0xD84, 3);
    if ((CURRENT_FLOOR() == 7) && (count >= 5)) {
        return 1;
    }

    next_count = count + 1;
    capped_count = 5;
    if (next_count < 6) {
        capped_count = next_count;
    }
    func_8001B168(0xD84, capped_count, 3);
    func_8001DCD4(CURRENT_FLOOR());
    return 0;
}

#include "common.h"

typedef struct S_80017EF0_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80017EF0_0;   /* arg0 in func_80017EF0 */

typedef struct S_80017EF0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80017EF0_1;   /* (arg1 * 0x10) + ((S_80017EF0_0 *)arg0)->unk_10 in func_80017EF0 */



extern s32 func_80017EA0();
extern s32 func_80017F44(void) __attribute__((noreturn));
extern s32 D_80019BB0;
extern s32 D_80019BB4;

s32 func_80017EF0(S_80017EF0_0 *arg0, s32 arg1) {
    s32 result;

    if (D_80019BB0 == 3) {
        result = 0;
        ASM_TAILSLOT_PIN(result);   /* MATCH pin: retail delay-slot contents depend on it */
        return func_80017F44();
    }
    ((S_80017EF0_1 *)((arg1 * 0x10) + arg0->unk_10))->unk_08 =
        func_80017EA0(D_80019BB4);
    return 1;
}

/* MECHANISM: Preserved the seed's 0x20 frame, s0/s1 argument holds, and early noreturn CFG.
   A guarded $v0 pin materializes zero; ASM_TAILSLOT_PIN lets LEAD 28b sink it into
   the LEAD 18-converted tail-j delay slot, closing retail word 11. */

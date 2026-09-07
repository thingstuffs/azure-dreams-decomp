#include "common.h"

/* Walks a chain of entries (skipping ones with flag 0x80 set), invoking func_800453E0 on each live entry and bailing out early if func_80045310 signals a stop condition on the current global-state target. Advances to the next group via the caller's sub-pointer (stored 8 bytes before it), or terminates the whole walk when that pointer is null. */
/* set to 0 at entry and again on the "list exhausted" exit path */
extern s32 D_80081510;

/* size >8B to force %hi/%lo codegen; D_80083160[0] points at the "current state" struct */
extern void *D_80083160[3];

/* target of D_80083160[0]; only offset 0x8D0 (u32) is read here */
typedef struct {
    u8 pad[0x8D0];
    u32 unk8D0;
} S_80045340_Target;

/* Node struct chained via unk0C (sibling) and, through the caller's sub-pointer minus 8,
 * via unk18 (next-group). unk08 carries forward as the next call's arg1. */
typedef struct S_80045340_Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct S_80045340_Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
    u8 pad16[2];
    struct S_80045340_Entry *unk18;
    u8 pad1C[4];
} S_80045340_Entry; /* size >= 0x20 */

extern void func_800453E0(void *a0, s32 a1, S_80045340_Entry *a2, s16 a3);
extern s32 func_80045310(u32 a0);

/* Scratchpad hardware-flag word at fixed address 0x1F80013C, reached by casting the
 * scratchpad base (0x1F800000) to a padded struct so gcc folds the whole address into
 * a single store immediate (lui $at,hi; sw $0,lo($at)) instead of materializing it. */
typedef struct {
    u8 pad[0x13C];
    u32 flag;
} S_80045340_HwFlag;

s32 func_80045340(void *a0, s32 a1, S_80045340_Entry *a2, s32 a3)
{
    void *s0 = a0;
    S_80045340_Entry *cur = a2;
    S_80045340_Entry *nxt;

    D_80081510 = 0;
    ((S_80045340_HwFlag *)0x1F800000)->flag = 0;

    for (;;) {
        if (!(cur->unk14 & 0x80)) {
            func_800453E0(s0, a1, cur, cur->unk06);
            if (func_80045310(((S_80045340_Target *)D_80083160[0])->unk8D0)) {
                return 0;
            }
        }

        nxt = *(S_80045340_Entry **)((u8 *)s0 - 8);
        if (nxt == 0) {
            D_80081510 = 0;
            return 0;
        }
        s0 = (u8 *)nxt + 0x20;
        a1 = (s32)nxt->unk08;
        cur = nxt->unk0C;
    }
}

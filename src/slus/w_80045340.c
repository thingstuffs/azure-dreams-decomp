#include "common.h"

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

/* Processes unflagged entries across groups until the stop condition or end of the chain. */
s32 func_80045340(void *group_data, s32 context, S_80045340_Entry *entry, s32 unused)
{
    void *current_data = group_data;
    S_80045340_Entry *current_entry = entry;
    S_80045340_Entry *next_group;

    D_80081510 = 0;
    ((S_80045340_HwFlag *)0x1F800000)->flag = 0;

    for (;;) {
        if (!(current_entry->unk14 & 0x80)) {
            func_800453E0(current_data, context, current_entry, current_entry->unk06);
            if (func_80045310(((S_80045340_Target *)D_80083160[0])->unk8D0)) {
                return 0;
            }
        }

        next_group = *(S_80045340_Entry **)((u8 *)current_data - 8);
        if (next_group == 0) {
            D_80081510 = 0;
            return 0;
        }
        current_data = (u8 *)next_group + 0x20;
        context = (s32)next_group->unk08;
        current_entry = next_group->unk0C;
    }
}

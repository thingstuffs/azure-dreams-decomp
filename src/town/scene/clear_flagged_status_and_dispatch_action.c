#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef struct S_800167E4_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800167E4_0;   /* arg0 in clear_flagged_status_and_dispatch_action */

typedef struct S_800167E4_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_800167E4_1;   /* town in clear_flagged_status_and_dispatch_action */

typedef struct S_800167E4_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_800167E4_2;   /* town2 in clear_flagged_status_and_dispatch_action */

typedef struct S_800167E4_3 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_800167E4_3;   /* ((S_800167E4_1 *)town)->unk_08 * 8 + ((S_800167E4_1 *)town)->unk_40 in clear_flagged_status_and_dispatch_action */

typedef struct S_800167E4_4 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_800167E4_4;   /* index * 8 + ((S_800167E4_2 *)town2)->unk_40 in clear_flagged_status_and_dispatch_action */


extern s32 check_are_nonzero(void);
extern void func_80017E1C(void);
extern void func_80018308(void *, s32);
extern void func_800193E0(s32);
extern void func_80019458(s32);
extern s32 func_800194D8(s32);

extern s16 D_80019676;
extern s32 scene_cell_dispatch_code;

/* Clears flagged town status and dispatches the action when its conditions are met. */
s32 clear_flagged_status_and_dispatch_action(S_800167E4_0 *entity, s32 action_arg)
{
    S_800167E4_1 *town;
    s32 flag_id;

    town = *(void **)((s8 *)(&D_80016000));
    flag_id = entity->unk_18;
    scene_cell_dispatch_code = ((S_800167E4_3 *)(town->unk_08 * 8 + town->unk_40))->unk_04;

    if (func_800194D8(flag_id) != 0) {
        {
            S_800167E4_2 *clear_town;
            s32 entry_index;

            clear_town = *(void **)((s8 *)(&D_80016000));
            entry_index = clear_town->unk_08;
            ((S_800167E4_4 *)(entry_index * 8 + clear_town->unk_40))->unk_04 = 0;
        }
        flag_id = entity->unk_18;
        scene_cell_dispatch_code = 0;
        func_80019458(flag_id);
    }

    if (check_are_nonzero() != 0 && func_800194D8(F_sbs14_pad19) != 0) {
        if (func_800194D8(D_80019676) == 0 && scene_cell_dispatch_code == 0) {
            func_80019458(F_sbs14_pad19);
            func_80018308(entity, action_arg);
            return 1;
        }
    } else {
        func_800193E0(F_sbs14_pad19);
    }

    func_80017E1C();
    return 0;
}

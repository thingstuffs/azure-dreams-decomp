#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef struct S_80016B0C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    u8 * unk_40;
} S_80016B0C_0;   /* state in process_current_cell_and_clear */

typedef struct S_80016B0C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    u8 * unk_40;
} S_80016B0C_1;   /* *(void **)D_80016000 in process_current_cell_and_clear */

typedef struct S_80016B0C_2 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_80016B0C_2;   /* (u8 *)((S_80016B0C_1 *)(*(void **)D_80016000))->unk_40
                + ((S_80016B0C_1 *)(*(void **)D_80016000))->unk_08 * 8 in process_current_cell_and_clear */


extern s32 scene_cell_dispatch_code;
extern void *D_80019B90;

extern s32 func_80018504(void);
extern void set_scene_entry_flag_k(void);
extern void func_80018D54(void *, u8 *);
extern void func_80019458(s32);
extern s32 func_800194D8(s32);
extern void func_80019638(void);

/* Process the current cell value and clear it when the handler returns nonzero. */
s32 process_current_cell_and_clear(void) {
    u8 fallback_args[2] = { 2, 0xFF };
    S_80016B0C_0 *state;
    s32 result;
    s32 cell_index;
    u8 *cells;

    state = *(void **)((s8 *)(&D_80016000));
    cell_index = state->unk_08;
    cells = state->unk_40;
    scene_cell_dispatch_code = cells[cell_index * 8 + 4];
    result = func_80018504();

    if (result != 0) {
        if (func_800194D8(F_sbs14_pad14) == 0) {
            func_80019458(F_sbs14_pad08);
            func_80019458(F_sbs14_pad09);
        }

        ((S_80016B0C_2 *)((u8 *)((S_80016B0C_1 *)(*(void **)((s8 *)(&D_80016000))))->unk_40
                + ((S_80016B0C_1 *)(*(void **)((s8 *)(&D_80016000))))->unk_08 * 8))->unk_04 = 0;
        scene_cell_dispatch_code = 0;
        set_scene_entry_flag_k();
    } else {
        func_80018D54(D_80019B90, fallback_args);
        func_80019638();
    }

    return result;
}

#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"

typedef struct S_805D2FC4_2 {
    u8 pad_00[0x4];
    union { u8 s; s8 u; } unk_04;   /* accessed as both */
} S_805D2FC4_2;   /* ((D_80016000->unk_08.at00_s32.v * 8) + D_80016000->unk_40.as_s32) in func_805D2FC4 */


typedef struct S_805D2FC4_1 {
    s32 unk_00;
} S_805D2FC4_1;   /* &D_80019AFC in func_805D2FC4 */


s32 func_80017E1C(void);
s32 func_80018504();                    /* extern */
s32 func_800194D8();                         /* extern */
extern s32 scene_cell_dispatch_code;

/* Dispatches the current cell's action and clears its status after completion or a status-1 fallback. */
s32 process_current_town_cell(s32 input_value, s32 input) {
    s32 result;
    u8 field_value;

    field_value = ((S_805D2FC4_2 *)(((D_80016000->unk_08 * 8) + ((s32)D_80016000->unk_40))))->unk_04.s;
    scene_cell_dispatch_code = (s32) field_value;
    result = 0;
    if ((field_value != 2) && (func_800194D8(F_sbs14_pad21) != 0)) {
        result = func_80018504(input_value, input);
    }
    if (result != 0) {
        ((S_805D2FC4_2 *)(((D_80016000->unk_08 * 8) + ((s32)D_80016000->unk_40))))->unk_04.u = 0;
        scene_cell_dispatch_code = 0;
    } else {
        func_80017E1C();
        if (scene_cell_dispatch_code == 1) {
            ((S_805D2FC4_2 *)(((D_80016000->unk_08 * 8) + ((s32)D_80016000->unk_40))))->unk_04.u = 0;
            scene_cell_dispatch_code = 0;
        }
    }
    return result;
}

/* MECHANISM: The retail prologue is driven by arg0/arg1 held in s1/s2 and
   the conditional helper result held in s0; the if/else around the tail
   (instead of an early `return`) keeps s0 across the zero-edge. The tail
   pseudo-call func_8001709C (true base +0xD8, this row's own epilogue) was
   replaced by a return 2026-09-22 (byte-exact). */

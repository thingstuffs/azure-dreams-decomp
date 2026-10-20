#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct S_80016D18_1 {
    u8 pad_00[0x78];
    s32 (*unk_78)(s32);
} S_80016D18_1;   /* ((S_80016D18_0 *)(*(void **)D_80016000))->unk_20 in get_local_global_table */


extern s32 func_800197FC();
void func_8001A554(s32);
void func_8001A5CC(s32);
extern s32 func_8001A64C();
extern s32 D_8002116C;

typedef struct S_80016D18_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80016D18_0;   /* *(void **)D_80016000 in get_local_global_table */

/* Processes event conditions and returns the corresponding data pointer, or null. */
s32 *get_local_global_table(void) {
    if (func_800197FC(0xD, 6) != 0) {
        D_80016000->unk_20->callback_078(0);
        func_8001A554(F_sbs32_pad02);
        func_8001A554(F_sbs32_pad03);
        func_8001A554(F_sbs32_pad04);
        func_8001A554(F_sbs32_pad05);
        func_8001A554(F_sbs32_pad06);
        func_8001A5CC(F_sbs32_pad25);
        return &D_8002116C;
    }
    if (func_8001A64C(F_sbs32_pad06) != 0) {
        return (s32 *)((s8 *)&D_8002116C + 0x21A);
    }
    return 0;
}

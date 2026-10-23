#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/resource.h"


extern void func_80016CC4(void);
extern void update_entry_flags(void);
extern s32 func_8001991C(s32, s32);
extern void func_8001A554(s32);
extern void func_8001A7AC(void);

typedef struct S_80017604_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80017604_0;   /* *(void **)D_80016000 in run_three_teardown_passes */

typedef struct S_80017604_1 {
    u8 pad_00[0x2F8];
    void (*unk_2F8)(s32, s32);
} S_80017604_1;   /* ((S_80017604_0 *)(*(void **)D_80016000))->unk_20 in run_three_teardown_passes */


/* Run the three teardown passes; when the check fails, stop the scene object and report failure. */
s32 run_three_teardown_passes(s32 kind, s32 value)
{
    s32 result;

    func_80016CC4();
    initialize_resources_assigns_pointer_lookup();
    update_entry_flags();
    if (func_8001991C(kind, value) == 0) {
        func_8001A7AC();
        ((S_80017604_1 *)(((S_80017604_0 *)(*(void **)((s8 *)(&town_scene_root))))->unk_20))
        ->unk_2F8(0xE, 0x200);
        result = 0;
    } else {
        func_8001A554(F_sbs32_pad07);
        result = 1;
    }

    return result;
}

/* MECHANISM: True-space naming makes the apparent func_80017684 jump a local
   epilogue edge; a shared result local preserves the retail failure-first CFG.
   Two call-spanning arguments naturally occupy s0/s1, while the wide array
   declaration forces D_80016000 through its retail hi/lo access. */

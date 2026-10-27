#include "script_symbols.h"
#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/player/script_flags.h"

typedef struct SceneActionEntry {
    u8 pad_00[0x18];
    s16 unk_18;
} UnkStruct;

extern void process_value_with_fixed_tables(UnkStruct *, s32);
extern s16 D_80018CFA[5];

/* Processes an entry and applies updates based on its status and the global status. */
s32 dispatch_first(UnkStruct *entry, s32 value) {
    s32 status;

    process_value_with_fixed_tables(entry, value);
    if (func_80018B5C(entry->unk_18) != 0) {
        status = func_80018B5C(D_80018CFA[0]);
    } else {
        status = 0;
    }

    if (status != 0) {
        func_80018ADC(F_sbs11_pad25);
    } else {
        func_80018A64(F_sbs11_pad25);
    }
    func_80018A64(F_sbs11_pad26);
    return status;
}

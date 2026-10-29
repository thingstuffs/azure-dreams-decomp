#include "script_symbols.h"
#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/player/script_flags.h"
#include "town/scene.h"

typedef struct SceneActionEntry {
    u8 pad_00[0x18];
    s16 unk_18;
} UnkStruct;

extern void process_value_with_fixed_tables(UnkStruct *, s32);
extern s16 D_80018CFA[5];

/* Update the object and select the action for 0x5BC from the combined status checks. */
s32 update_scene_and_select_action(UnkStruct *object, s32 value) {
    s32 status;

    process_value_with_fixed_tables(object, value);
    if (func_80018B5C(object->unk_18) != 0) {
        status = func_80018B5C(D_80018CFA[0]);
    } else {
        status = 0;
    }

    if (status != 0) {
        func_80018ADC(F_sbs11_pad25);
    } else {
        func_80018A64(F_sbs11_pad25);
    }
    return status;
}

#include "script_symbols.h"
#include "shared/town_pointees.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"



extern s32 D_80018FE0;
extern s32 *D_8001917C;
extern s32 D_8001C328;
extern s32 D_8001C7C4;

extern s32 func_80018B5C(s32);
extern void func_80018ADC(s32);

/* Initializes the data pointer, conditionally selects a data source, and dispatches an action. */
void initialize_scene_action(void) {
    D_8001917C = &D_80018FE0;
    if (func_80018B5C(F_sbs11_pad31) != 0) {
        if (func_80018B5C(F_sbs11_pad28) != 0) {
            ((TownPositionState *)D_80016000->unk_1C)->unk_40 =
                &D_8001C328;
        } else {
            ((TownPositionState *)D_80016000->unk_1C)->unk_40 =
                &D_8001C7C4;
        }
        func_80018ADC(F_sbs11_pad31);
        return;
    }
    func_80018ADC(F_sbs11_pad33);
}

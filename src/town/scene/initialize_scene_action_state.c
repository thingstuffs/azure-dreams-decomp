#include "script_symbols.h"
#include "common.h"

typedef struct {
    u8 pad_00[0x18];
    s16 unk_18;
} UnkStruct;

extern void process_value_with_fixed_tables(UnkStruct *);
extern void func_800160D4(void);
extern void func_80018A64(s32);
extern void func_80018ADC(s32);
extern s32 func_80018B5C(s32);
extern s16 D_80018CFA[5];

/* Initializes the object and selects follow-up actions from status checks. */
s32 initialize_scene_action_state(UnkStruct *object) {
    s32 status;

    process_value_with_fixed_tables(object);
    if (func_80018B5C(object->unk_18) != 0) {
        status = func_80018B5C(D_80018CFA[0]);
    } else {
        status = 0;
    }

    if (status != 0) {
        func_80018ADC(F_sbs11_pad25);
    } else {
        if (func_80018B5C(Frg_vivian_fine) != 0) {
            func_800160D4();
            return 1;
        }
        func_80018A64(F_sbs11_pad25);
        func_80018A64(F_sbs11_pad27);
        func_80018A64(F_sbs11_pad34);
    }
    return status;
}

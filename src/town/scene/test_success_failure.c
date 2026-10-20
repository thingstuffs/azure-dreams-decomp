#include "script_symbols.h"
#include "common.h"

extern void func_80018B58(s32);
extern void func_80018BD0(s32);
extern s32 func_80018C50(s32);

/* Test 0xFC0 and process 0xFB5 on success or 0xFB7 and 0xFB8 on failure. */
s32 test_success_failure(void) {
    if (func_80018C50(Fr_cheriru_scene03) != 0) {
        func_80018B58(Fr_hospital_scene00);
        return 1;
    }

    func_80018BD0(F_hos_first_cheriru);
    func_80018BD0(F_hos_first_hush);
    return 0;
}

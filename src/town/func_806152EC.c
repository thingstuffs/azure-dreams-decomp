#include "common.h"

typedef s32 (*TownCallback)();

extern s32 func_80018B58();
extern s32 func_80018BD0();
extern s32 func_80018C50();
extern s8 D_80016000[];
extern s8 D_8001BD48[];

s32 func_80016AEC(void) {
    void *town;

    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);

    if (func_80018C50(0xFE7) == 0) {
        town = *(void **)D_80016000;
        *(void **)((s8 *)*(void **)((s8 *)town + 0x1C) + 0x40) = D_8001BD48;
        (*(TownCallback *)((s8 *)*(void **)((s8 *)town + 0x20) + 0x2F8))(0x10, 0x200);
        return 0;
    }

    if ((func_80018C50(0x679) != 0) &&
        (func_80018C50(0x67A) == 0) &&
        (func_80018C50(0xFD8) != 0)) {
        func_80018B58(0x67F);
        return 1;
    }

    (*(TownCallback *)((s8 *)*(void **)((s8 *)*(void **)D_80016000 + 0x20) + 0x2F8))(0x10, 0x200);
    return 0;
}

/* MECHANISM: The apparent in-row callees are a shared callback site and epilogue.
   Duplicated indirect-call expressions retain each arm's load/argument setup;
   cdk then cross-jumps only the jalr suffix and schedules symbolic page loads. */

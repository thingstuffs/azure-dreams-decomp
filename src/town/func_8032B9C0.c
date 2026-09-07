#include "common.h"

typedef struct S_800161C0_0 {
    u8 pad_00[0x24];
    void * unk_24;
} S_800161C0_0;   /* *(void **)D_80016000 in func_800161C0 */

typedef struct S_800161C0_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_800161C0_1;   /* ((S_800161C0_0 *)(*(void **)D_80016000))->unk_24 in func_800161C0 */

typedef struct S_800161C0_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_800161C0_2;   /* ((S_800161C0_1 *)(((S_800161C0_0 *)(*(void **)D_80016000))->unk_24))->unk_74 in func_800161C0 */


extern s32 func_80019958();
extern s32 func_8001ADE0();
extern s32 func_8001B0E8();
extern s32 func_8001B168();
extern s32 func_8001DCD4();
extern s8 D_80016000[];

#define CURRENT_FLOOR() \
    ((S_800161C0_2 *)(((S_800161C0_1 *)(((S_800161C0_0 *)(*(void **)D_80016000))->unk_24))->unk_74))->unk_2A

s32 func_800161C0(s32 arg0, s32 arg1) {
    s32 result;
    s32 next;
    s32 selected;

    if (func_8001ADE0(0x1462) != 0) {
        func_80019958(arg0, arg1);
        return 1;
    }

    result = func_8001B0E8(0xD84, 3);
    if ((CURRENT_FLOOR() == 7) && (result >= 5)) {
        return 1;
    }

    next = result + 1;
    selected = 5;
    if (next < 6) {
        selected = next;
    }
    func_8001B168(0xD84, selected, 3);
    func_8001DCD4(CURRENT_FLOOR());
    return 0;
}

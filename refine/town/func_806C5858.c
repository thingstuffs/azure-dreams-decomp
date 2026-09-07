#include "common.h"

typedef struct S_80016858_0 {
    void * unk_00;
} S_80016858_0;   /* D_80016000 in func_80016858 */

typedef struct S_80016858_1 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_80016858_1;   /* ((S_80016858_0 *)D_80016000)->unk_00 in func_80016858 */

typedef struct S_80016858_2 {
    u8 pad_00[0x40];
    void * unk_40;
} S_80016858_2;   /* ((S_80016858_1 *)(((S_80016858_0 *)D_80016000)->unk_00))->unk_1C in func_80016858 */



extern s8 D_80016000[];
extern s8 D_8001ABF9;

extern void func_80018C74(s32);
extern void func_80018CEC(s32);
extern s32 func_80018D6C(s32);

/* Selects event data when flag conditions match, otherwise clears two event flags. */
s32 func_80016858(void) {
    if ((func_80018D6C(0x7D1) != 0) &&
        (func_80018D6C(0x7D2) == 0) &&
        (func_80018D6C(0xFDC) != 0)) {
        func_80018C74(0x7D9);
        ((S_80016858_2 *)(((S_80016858_1 *)(((S_80016858_0 *)D_80016000)->unk_00))->unk_1C))->unk_40 = &D_8001ABF9;
        return 1;
    }
    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    return 0;
}

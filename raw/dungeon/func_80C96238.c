#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_800AC82C(void *,void *,void *,void *);                                /* extern */
s32 func_800AD9B4(void *, void *);                  /* extern */

extern u8 D_801752AC[8];
extern u8 D_801752FC[8];
extern void func_8017102C(void *,void *,void *,void *);


typedef struct S_80173A38_0 {
    u8 pad_00[0x8C];
    void (*unk_8C)(void *,void *,void *,void *);
} S_80173A38_0;   /* arg0 in func_80173A38 */

typedef struct S_80173A38_1 {
    u8 pad_00[0x2C];
    M2C_UNK * unk_2C;
} S_80173A38_1;   /* arg2 in func_80173A38 */

typedef struct S_80173A38_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_80173A38_2;   /* arg3 in func_80173A38 */

/* Restore the main action handler after movement, or select its fallback animation. */
void func_80173A38(S_80173A38_0 *arg0, void *arg1, S_80173A38_1 *arg2, S_80173A38_2 *arg3) {
    if (func_800AC82C(arg0,arg1,arg2,arg3) != 0) {
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            arg0->unk_8C = func_8017102C;
        }
    } else if ((arg2->unk_2C == D_801752FC) && !(arg3->unk_1C & 0x208)) {
        arg2->unk_2C = D_801752AC;
        func_80047784(arg2, *((((s32) (gameWork.view.viewAngle + arg3->unk_2A + 0x100) >> 9) & 7) + D_801752AC), 0);
    }
}

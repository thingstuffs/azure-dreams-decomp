#include "common.h"


extern void func_80093D48(void *, void *, s32);
extern void func_80093E98(void *, void *, s32);
extern u8 D_80083160[];


typedef struct S_80091114_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80091114_0;   /* state in func_80091114 */

typedef struct S_80091114_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80091114_1;   /* arg1 in func_80091114 */


extern void func_80091000(s32 *, S_80091114_1 *, s32);
/* Updates the value and dispatches follow-up handling if it remains unchanged. */
void func_80091114(s32 *value, S_80091114_1 *context, s32 update_arg) {
    register s32 saved_update_arg ASM_REG("$19") = update_arg;   /* Required for the retail saved-register set and frame layout. */
    s32 previous_value;
    register u8 *state = D_80083160;

    previous_value = *value;
    func_80091000(value, context, update_arg);

    if (previous_value == *value) {
        if (!(((S_80091114_0 *)state)->unk_08 & 0x20)) {
            func_80093D48(value, context, saved_update_arg);
            return;
        }

        if ((context->unk_0C == 0) &&
            (context->unk_10 == 0)) {
            func_80093E98(value, context, saved_update_arg);
        }
    }
}

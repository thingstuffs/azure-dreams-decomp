#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80093D48();     /* extern */
M2C_UNK func_80093ED8();     /* extern */
M2C_UNK func_800942B0();     /* extern */
M2C_UNK func_80094378();     /* extern */
M2C_UNK func_80095094();                      /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
s32 func_8009FF50();                                /* extern */
extern u8 D_80083160[];
extern u8 D_800CFCEF;
extern u8 D_800FE488[];


typedef struct S_800930E4_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800930E4_0;   /* target in func_800930E4 */

typedef struct S_800930E4_1 {
    u8 unk_00;
} S_800930E4_1;   /* &D_800CFCEF in func_800930E4 */

typedef struct S_800930E4_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800930E4_2;   /* self in func_800930E4 */

typedef struct S_800930E4_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800930E4_3;   /* state in func_800930E4 */

/* Updates the target and dispatches actions based on its value, a countdown, and state flags. */
void func_800930E4(void *self_arg, void *target_arg, M2C_UNK context_arg) {
    void *self;
    register void *target ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    M2C_UNK context;
    s16 target_value;
    u16 countdown;
    u16 busy_countdown;
    u8 *state;

    self = self_arg;
    target = target_arg;
    context = context_arg;
    state = D_80083160;

    func_80095C80(target);
    ASM_KEEP(self);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(target);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(context);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    func_80095094(target);
    if (func_8009FF50() == 0) {
        target_value = func_80095978(target, D_800FE488);
        if ((target_value - ((S_800930E4_0 *)target)->unk_0A) >= 4) {
            if (((S_800930E4_1 *)(&D_800CFCEF))->unk_00 == 0) {
                func_80094378(self, target, context);
                return;
            }
        } else if (((S_800930E4_1 *)(&D_800CFCEF))->unk_00 == 0) {
            func_80095A94(target, target_value, D_800FE488);
        }
        countdown = ((S_800930E4_2 *)self)->unk_0A - 1;
        ((S_800930E4_2 *)self)->unk_0A = countdown;
        if ((s16) countdown >= 0) {
            if (((S_800930E4_3 *)state)->unk_08 & 0xF000) {
                func_80093ED8(self, target, context);
                return;
            }
            if (((S_800930E4_3 *)state)->unk_10 & 0x10) {
                func_800942B0(self, target, context);
                return;
            }
        } else {
            goto countdown_expired;
        }
    } else {
        busy_countdown = ((S_800930E4_2 *)self)->unk_0A - 1;
        ((S_800930E4_2 *)self)->unk_0A = busy_countdown;
        if ((s16) busy_countdown < 0) {
countdown_expired:
            func_80093D48(self, target, context);
        }
    }
}

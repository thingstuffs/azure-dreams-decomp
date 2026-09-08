#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(base, type, offset) (*(type)((s8 *)(base) + (offset)))

extern void func_80033D08(void *arg0);
extern s32 func_8009CFE0(void *, M2C_UNK);
extern s32 D_800814A0[3];

void func_800A0708(void *arg0, M2C_UNK arg1, M2C_UNK arg2)
{
    s8 *p;
    M2C_UNK result;
    M2C_UNK (*callback)(void *, M2C_UNK, M2C_UNK, M2C_UNK);

    result = func_8009CFE0(arg0, arg1);
    {
        register void *callarg ASM_REG("$4") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        if (result != 0) {
            p = FIELD(arg0, s8 **, 0x98);
            if (p != 0) {
                *p = 0;
            }
            func_80033D08(arg0);
            FIELD(arg0, u16 *, -2) =
                (u16)(FIELD(arg0, u16 *, -2) | 0x8000);
            D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
            return;
        } else {
            register void *self ASM_REG("$5") = callarg;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            callback = FIELD(callarg,
                             M2C_UNK (**)(void *, M2C_UNK, M2C_UNK,
                                           M2C_UNK),
                             0x50);
            callback(callarg, self, arg1, arg2);
        }
    }
}

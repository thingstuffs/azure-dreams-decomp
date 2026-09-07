#include "common.h"

extern void func_800702F0(s32 arg0);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern void func_8007CAE8(void *arg0);
extern s32 func_8040153C(void);
extern void func_80401578(void);
extern void func_80401BF4(void *arg0, s32 arg1);
extern void func_80408654(s32 arg0);
extern u8 D_80400038[];
extern u8 D_804000F8[];
extern s32 D_804094EC[];
extern s32 D_8009DDD8[];
extern s32 D_8009EB58[];

s32 func_804022C8(s32 arg0)
{
    u8 state[32];
    s32 attempts;
    s32 result;

    attempts = 0;
    func_80401BF4(state, arg0);
    func_80408654(0);
    func_80408654(1);
    func_80401578();
    func_8007CAE8(state);
    do {
        result = func_8040153C();
        if (result == 0) {
            attempts++;
            func_800702F0(0);
        }
    } while (result == 0);
    func_8007C040(D_80400038, D_804000F8, attempts);

    if (arg0 < 5) {
        s32 *base;
        s32 *dst;
        s32 *src;
        s32 flag;

        base = D_8009EB58;
        dst = base;
        flag = D_804094EC[0];
        D_8009DDD8[arg0 * 32] = 0;
        if (flag != 0) {
            dst++;
        }
        src = base;
        if (flag != 0) {
            src++;
        }
        *dst = *src + 3;
    }
    return result == 1;
}

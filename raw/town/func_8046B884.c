#include "common.h"

typedef s32 (*StateQuery)(s32);

extern void *D_80016000[];
extern u8 *D_8001E950;

extern s8 D_8001602A[];
extern s8 D_80016359[];
extern s8 D_800164CC[];
extern s8 D_8001688A[];
extern s8 D_80016BCF[];
extern s8 D_80016C24[];
extern s8 D_80016C77[];
extern s8 D_80016CCE[];
extern s8 D_80016D77[];
extern s8 D_80016E0C[];
extern s8 D_80017152[];
extern s8 D_800172A3[];
extern s8 D_800173E4[];
extern s8 D_80017501[];

extern s32 func_8001A5D0(void);
extern void func_8001E578(s32);
extern s32 func_8001E670(s32);
extern s32 func_8001E82C(void);

s8 *func_8001C884(void) {
    s32 initial;
    s32 state_one;
    s32 state_five;
    s32 state_zero;
    s32 value;

    initial = 0;
    if (func_8001E670(0xA0) == 0) {
        func_8001E578(0xA0);
    } else {
        initial = 1;
    }

    if (func_8001E670(initial) != 0) {
        goto fallback;
    }
    if (func_8001E82C() == 0) {
        goto fallback;
    }
    if (func_8001E82C() >= 5) {
        if (func_8001E670(0x145E) == 0) {
            if (func_8001E670(0x9E) == 0) {
                func_8001E578(0x9E);
                return D_80017152;
            }
            return D_800172A3;
        }
    }

    if (func_8001E670(0x1460) != 0) {
        if (func_8001E670(0x5FD) == 0) {
            if (func_8001E670(0x5FB) == 0) {
                if (func_8001E670(0x9F) == 0) {
                    func_8001E578(0x9F);
                    return D_800173E4;
                }
                return D_80017501;
            }
        }
    }

    if ((u32)*(s32 *)((u8 *)*(void **)((u8 *)D_80016000[0] + 0x38) + 0x2D68) >= 10000U) {
        if (func_8001E670(0x14C9) == 0) {
            return D_800164CC;
        }
    }

    {
        void *root;

        root = D_80016000[0];
        if ((u32)*(s32 *)((u8 *)*(void **)((u8 *)root + 0x38) + 0x2D68) >= 20000U) {
            if ((*(StateQuery *)((u8 *)*(void **)((u8 *)root + 0x20) + 0x2D4))(0) == 0) {
                return D_8001688A;
            }
        }
    }

    value = (*(StateQuery *)((u8 *)*(void **)((u8 *)D_80016000[0] + 0x20) + 0x2D4))(0);
    if (value > 0) {
        u8 *town = *(u8 **)((u8 *)D_80016000[0] + 0x38);
        if (town[0x33A8] != 0x12 && town[0x33A9] != 0x12) {
            if (func_8001E670(0xAE) == 0) {
                func_8001E578(0xAE);
                return D_80016E0C;
            }
        }
    }

    {
        u8 *state;

        state = D_8001E950;
        state_zero = state[0];
        if (state_zero != 2) {
            goto fallback;
        }
        state_five = state[5];
        if (state_five != state_zero) {
            goto fallback;
        }
        state_one = state[1];
        if (state_one != 1) {
            goto fallback;
        }
    }

    if ((*(StateQuery *)((u8 *)*(void **)((u8 *)D_80016000[0] + 0x20) + 0x2D4))(0) == state_five) {
        if (func_8001A5D0() >= 3) {
            return D_80016D77;
        }
        if (func_8001A5D0() != state_one) {
            goto fallback;
        }

        {
            u8 *state;

            state = D_8001E950;
            value = state[4];
        }
        if (value == state_one) {
            goto return_one;
        }
        if (value == state_five) {
            goto return_five;
        }
        if (value == 3) {
            goto return_three;
        }
        goto compare_six;
    } else {
        {
            u8 *state;

            state = D_8001E950;
            value = state[4];
        }
    }

    if (value == state_one) {
return_one:
        return D_80016BCF;
    }
    if (value == state_five) {
return_five:
        return D_80016C77;
    }
    if (value == 3) {
return_three:
        return D_80016C24;
    }
compare_six:
    if (value == 6) {
        return D_80016CCE;
    }

fallback:
    if (func_8001E670(0x16) != 0) {
        return D_80016359;
    }
    return D_8001602A;
}

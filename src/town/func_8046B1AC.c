#include "common.h"

extern void func_8001C108(void);
extern s32 func_8001A58C(u8);
extern u8 func_8001A4F0(void);
extern u8 *func_8001B6F8(s32, s32, s32);

extern u8 D_8001786E[];
extern u8 D_8001914C[];
extern u8 *D_8001E950;
extern s32 D_8001E958;
extern u8 D_8001EEA7[];
extern u8 D_8001F0AA[];
extern u8 D_80021CC0[];

u8 *func_8001C1AC(s32 arg0, s32 arg1, s32 arg2) {
    u8 **page;
    u8 *result;

    if (arg2 == 0) {
        page = (u8 **)0x80020000;
        func_8001C108();
        if (func_8001A58C((*(u8 **)((u8 *)page - 0x16B0))[4]) == 0) {
            (*(u8 **)((u8 *)page - 0x16B0))[4] = func_8001A4F0();
        }
        if ((*(u8 **)((u8 *)page - 0x16B0))[4] != 0) {
            D_8001E958 = 1;
            return D_80021CC0;
        }
        return D_8001F0AA;
    }

    if (arg2 == 4) {
        return D_8001EEA7;
    }
    if (arg2 == 5) {
        return D_8001786E;
    }
    if (arg2 == 1) {
        goto case_one;
    }
    result = func_8001B6F8(arg0, arg1, arg2);
    goto done;

case_one:
    result = D_8001914C;
done:
    return result;
}

/* MECHANISM: The CFG begins with the arg2 nonzero split and shares one return epilogue.
   A live 0x80020000 page base supplies the repeated -0x16B0 pointer loads in the call arm.
   Only that page base crosses calls, targeting the retail 0x18 frame and sole s0 save. */

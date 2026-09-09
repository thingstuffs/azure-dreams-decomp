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

/* Selects a response buffer by request type, refreshing state for the initial request. */
u8 *func_8001C1AC(s32 context, s32 data, s32 request) {
    u8 **state_page;
    u8 *response;

    if (request == 0) {
        state_page = (u8 **)0x80020000;
        func_8001C108();
        if (func_8001A58C((*(u8 **)((u8 *)state_page - 0x16B0))[4]) == 0) {
            (*(u8 **)((u8 *)state_page - 0x16B0))[4] = func_8001A4F0();
        }
        if ((*(u8 **)((u8 *)state_page - 0x16B0))[4] != 0) {
            D_8001E958 = 1;
            return D_80021CC0;
        }
        return D_8001F0AA;
    }

    if (request == 4) {
        return D_8001EEA7;
    }
    if (request == 5) {
        return D_8001786E;
    }
    if (request == 1) {
        goto case_one;
    }
    response = func_8001B6F8(context, data, request);
    goto done;

case_one:
    response = D_8001914C;
done:
    return response;
}

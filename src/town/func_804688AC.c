#include "shared/town_event_state.h"
#include "common.h"


extern s32 func_8001E670(s32 id);
extern void func_8001E578(s32 id);
extern void func_8001E5F0(s32 id);
extern u8 func_8001A4F0(void);
extern s32 func_8001A2F0(void);
extern s32 func_8001A360(void);
extern s32 func_8001A414(void);

s32 func_800198AC(void) {
    u8 temp_v0;
    s32 var_a0;
    void *pv1;

    if ((func_8001E670(0x145D) != 0) && (func_8001E670(0x1455) == 0)) {
        func_8001E578(0x1455);
        func_8001E5F0(0x11FA);
        *((u8 *)D_8001E950 + 5) = 9;
        return;
    }
    if ((func_8001E670(0x1452) != 0) && (func_8001E670(0x407) == 0)) {
        func_8001E578(0x407);
        *((u8 *)D_8001E950 + 5) = 10;
        return;
    }
    if (func_8001E670(0xA2) == 0) {
        if ((func_8001E670(0x1389) != 0) && (func_8001E670(0x405) == 0)) {
            func_8001E578(0x405);
            *((u8 *)D_8001E950 + 3) = func_8001A4F0();
        }
        if ((func_8001E670(0x3FE) != 0) && (func_8001E670(0x3E8) == 0)) {
            pv1 = D_8001E950;
            temp_v0 = *((u8 *)pv1 + 3);
            if (temp_v0 != 0) {
                *((u8 *)pv1 + 4) = temp_v0;
                *((u8 *)D_8001E950 + 5) = 7;
            } else {
                *((u8 *)pv1 + 5) = 8;
            }
            return;
        }
        if (func_8001E670(0x3FE) != 0) {
            pv1 = D_8001E950;
            temp_v0 = *((u8 *)pv1 + 3);
            if (temp_v0 != 0) {
                *((u8 *)pv1 + 4) = temp_v0;
                *((u8 *)D_8001E950 + 5) = 5;
            } else {
                *((u8 *)pv1 + 5) = 6;
            }
            return;
        }
        if ((func_8001E670(0x1389) != 0) && (func_8001E670(0x3FE) == 0)) {
            func_8001E578(0x3FE);
            pv1 = D_8001E950;
            temp_v0 = *((u8 *)pv1 + 3);
            if (temp_v0 != 0) {
                *((u8 *)pv1 + 4) = temp_v0;
                *((u8 *)D_8001E950 + 5) = 3;
            } else {
                *((u8 *)pv1 + 5) = 4;
            }
            return;
        }
    }
    if (func_8001A2F0() != 0) {
        var_a0 = func_8001A360();
        if (var_a0 == 0) {
            var_a0 = func_8001A414();
        }
        *((u8 *)D_8001E950 + 4) = var_a0;
        *((u8 *)D_8001E950 + 5) = 2;
        return;
    }
    if ((func_8001E670(0x145B) == 0) || (func_8001E670(0x146E) != 0)) {
        *((s8 *)D_8001E950 + 5) = 0;
        return;
    }
    pv1 = D_8001E950;
    *((s8 *)pv1 + 5) = 1;
}

#include "common.h"

extern void *D_8001E950;

extern s32 func_8001E670(s32 id);
extern void func_8001E578(s32 id);
extern void func_8001E5F0(s32 id);
extern void func_80019AE8(void);
extern u8 func_8001A4F0(void);
extern s32 func_8001A2F0(void);
extern s32 func_8001A360(void);
extern s32 func_8001A414(void);

#define TAIL_AE8(code) \
    do { \
        register void *pv1 ASM_REG("$3") = D_8001E950; \
        ASM_KEEP(pv1); \
        func_80019AE8(); \
        return (code); \
    } while (0)

#define FIELD3_CHECK(if_code, else_code) \
    do { \
        void *pv1 = D_8001E950; \
        \
        temp_v0 = *((u8 *)pv1 + 3); \
        if (temp_v0 != 0) { \
            *((u8 *)pv1 + 4) = temp_v0; \
            TAIL_AE8(if_code); \
        } \
        \
        func_80019AE8(); \
        return (else_code); \
    } while (0)

s32 func_800198AC(void) {
    u8 temp_v0;
    s32 var_a0;

    if ((func_8001E670(0x145D) != 0) && (func_8001E670(0x1455) == 0)) {
        func_8001E578(0x1455);
        func_8001E5F0(0x11FA);
        TAIL_AE8(9);
    }
    if ((func_8001E670(0x1452) != 0) && (func_8001E670(0x407) == 0)) {
        func_8001E578(0x407);
        TAIL_AE8(10);
    }
    if (func_8001E670(0xA2) == 0) {
        if ((func_8001E670(0x1389) != 0) && (func_8001E670(0x405) == 0)) {
            func_8001E578(0x405);
            *((u8 *)D_8001E950 + 3) = func_8001A4F0();
        }
        if ((func_8001E670(0x3FE) != 0) && (func_8001E670(0x3E8) == 0)) {
            FIELD3_CHECK(7, 8);
        }
        if (func_8001E670(0x3FE) != 0) {
            FIELD3_CHECK(5, 6);
        }
        if ((func_8001E670(0x1389) != 0) && (func_8001E670(0x3FE) == 0)) {
            func_8001E578(0x3FE);
            FIELD3_CHECK(3, 4);
        }
    }
    if (func_8001A2F0() != 0) {
        var_a0 = func_8001A360();
        if (var_a0 == 0) {
            var_a0 = func_8001A414();
        }
        {
            s8 *pv0 = D_8001E950;
            ASM_KEEP(pv0);   /* MATCH pin: keeps a constant in a register as retail does */
            pv0[4] = var_a0;
        }
        TAIL_AE8(2);
    }
    if ((func_8001E670(0x145B) == 0) || (func_8001E670(0x146E) != 0)) {
        *((s8 *)D_8001E950 + 5) = 0;
        return;
    }
    *((s8 *)D_8001E950 + 5) = 1;
}

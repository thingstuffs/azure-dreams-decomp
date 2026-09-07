#include "common.h"

typedef struct {
    u16 value;
    u16 pad;
} Entry4;

extern u16 D_8070063A[5];
extern u16 D_80700658[5];
extern u16 D_8070065C[5];
extern u16 D_80700660[5];
extern Entry4 D_80700650[3];

extern s32 func_80700D74(s32);
extern s32 func_807008FC(s32);
extern void func_80700D20(s32);
extern void func_80700CD0(s32);
extern void func_8070096C(s32, s32);
extern void func_80700B4C(void);
extern void func_80700B10(void) __attribute__((noreturn));
extern void func_80700B38(void) __attribute__((noreturn));

#ifdef NON_MATCHING
#define OR_ZERO(value) (value)
#else
#define OR_ZERO(value)                                                      \
    ({                                                                      \
        register s32 zero ASM_REG("$0");                                    \
        ASM_KEEP(zero);                                                     \
        zero | (value);                                                     \
    })
#endif

s32 func_8088124C(s32 index) {
    if (func_80700D74(D_8070063A[0]) == 0 &&
        func_80700D74(OR_ZERO(0x278)) != 0 &&
        func_807008FC(index) != 0) {
        if (func_80700D74(OR_ZERO(0x281)) != 0) {
            func_80700D20(D_80700658[0]);
            func_80700D20(D_8070065C[0]);
            func_80700D20(D_80700660[0]);
            func_80700D20(OR_ZERO(0x281));
            func_80700D20(OR_ZERO(0x280));
            func_80700B10();
        }

        if (func_80700D74(OR_ZERO(0x288)) != 0) {
            func_80700CD0(D_80700650[index].value);
            func_80700D20(OR_ZERO(0x278));
            func_80700B4C();
            func_80700B38();
        }
    }

    func_8070096C(index, 0);
    return index;
}

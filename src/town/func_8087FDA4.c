#include "common.h"

#ifdef NON_MATCHING
#define ({                                                                       register s32 zero ASM_REG("$0");                                    ASM_KEEP(zero);                                                      zero | (value);                                                      }) (value)
#else
#endif

extern s32 func_80701134(s32);
extern s32 func_80700CE8(s32);
extern void func_80701090(s32);
extern void func_807010E0(s32);
extern void func_80700E3C(void);
extern void func_80700E28(void) __attribute__((noreturn));
extern void func_80700D58(s32, s32);

extern u8 D_807009BA[];
extern u16 D_807009DC[];

s32 func_8087FDA4(s32 arg0) {
    if (!func_80701134(*(u16 *)D_807009BA) &&
        func_80701134(({                                                                       register s32 zero ASM_REG("$0");                                                                                          zero | (0x152);                                                      })) &&
        func_80700CE8(arg0)) {
        func_80701090(D_807009DC[arg0 * 2]);
        func_807010E0(({                                                                       register s32 zero ASM_REG("$0");                                    ASM_KEEP(zero);                                                      zero | (0x152);                                                      }));
        func_80700E3C();
        func_80700E28();
    }

    func_80700D58(arg0, 0);
    return arg0;
}

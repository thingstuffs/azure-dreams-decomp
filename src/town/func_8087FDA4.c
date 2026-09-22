#include "common.h"

#ifdef NON_MATCHING
#define value (value)
#else
#endif

extern s32 func_80701134(s32);
extern s32 func_80700CE8(s32);
extern void func_80701090(s32);
extern void func_807010E0(s32);
extern s32 func_80700E3C();
extern void func_80700D58(s32, s32);

extern u8 D_807009BA[];
extern u16 D_807009DC[];

/* When the two queries and the entry check pass, run the stage updates and return the handler's result. */
s32 func_8087FDA4(s32 entry) {
    if (!func_80701134(*(u16 *)D_807009BA) &&
        func_80701134(0x152) &&
        func_80700CE8(entry)) {
        func_80701090(D_807009DC[entry * 2]);
        func_807010E0(0x152);
        return func_80700E3C();
    }

    func_80700D58(entry, 0);
    return entry;
}

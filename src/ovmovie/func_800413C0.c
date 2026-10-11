#include "common.h"

extern u32 *D_80178380;
extern s32 D_8017681C;
extern void func_80177D08(void *);
extern void func_80177C48(void);

s32 func_800413C0(void) {
    volatile s32 polls_left = 0x100000;
    if (*D_80178380 & 0x20000000) {
        do {
            if (--polls_left == -1) {
                func_80177D08(&D_8017681C);
                func_80177C48();
                return -1;
            }
        } while (*D_80178380 & 0x20000000);
    }
    return 0;
}

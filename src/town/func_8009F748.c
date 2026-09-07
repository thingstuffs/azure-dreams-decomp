#include "common.h"

extern void func_8009D5C0(void *);
extern void func_8009D73C(void *);
extern s32 D_801007F8[];
extern s32 D_80100900[];

void func_8009CEA8(void) {
    void *p = D_80100900;

    func_8009D5C0(p);
    func_8009D73C(p);
    D_801007F8[0] = 0;
}

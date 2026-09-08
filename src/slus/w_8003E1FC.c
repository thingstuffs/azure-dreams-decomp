#include "common.h"

#include "common.h"

extern void func_8003E4FC(s32, void *, s32);
extern s32 D_80080AC0;
extern s32 D_80080AC8;
extern u8 D_80082E6A[9];

/* Select a table based on D_80082E6A[0] and pass it to func_8003E4FC. */
void func_8003E1FC(void)
{
    void *table = &D_80080AC0;

    if (D_80082E6A[0] == 2) {
        table = &D_80080AC8;
    }
    func_8003E4FC(6, table, 0);
}

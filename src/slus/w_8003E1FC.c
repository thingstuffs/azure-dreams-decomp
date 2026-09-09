#include "common.h"

#include "common.h"

extern void Control_CD(s32, void *, s32);
extern s32 D_80080AC0;
extern s32 D_80080AC8;
extern u8 D_80082E6A[9];

/* Select a table based on D_80082E6A[0] and pass it to Control_CD. */
void func_8003E1FC(void)
{
    void *table = &D_80080AC0;

    if (D_80082E6A[0] == 2) {
        table = &D_80080AC8;
    }
    Control_CD(6, table, 0);
}

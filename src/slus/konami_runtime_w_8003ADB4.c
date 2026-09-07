#include "common.h"

#include "common.h"

extern unsigned char D_80082E6A[9];
extern short func_80053DA8(int a0);

short func_8003ADB4(int a0)
{
    if (D_80082E6A[0] != 2) {
        return func_80053DA8((unsigned short)a0);
    }

    return 0;
}

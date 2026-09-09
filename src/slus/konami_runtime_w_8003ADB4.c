#include "common.h"

#include "common.h"

extern unsigned char D_80082E6A[9];
extern short SD_Call(int a0);

// Forwards the low 16 bits of the input when D_80082E6A[0] is not 2.
short func_8003ADB4(int inputValue)
{
    if (D_80082E6A[0] != 2) {
        return SD_Call((unsigned short)inputValue);
    }

    return 0;
}

#include "common.h"

typedef struct {
    int val;
    int pad[2];
} S_800814A0;
extern S_800814A0 D_800814A0;

/* Set bit 15 in the preceding halfword and the global value. */
void func_7FDD2AB4(unsigned short *data)
{
    data[-1] |= 0x8000;
    D_800814A0.val |= 0x8000;
}

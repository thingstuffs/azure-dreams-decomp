#include "common.h"

extern void *D_800814A8[2];
extern u8 D_800DD704[];

void func_800990C8(u8 *arg0, u8 *arg1) {
    arg0[3] = ((u8 *) D_800814A8[0])[3];
    arg0[0x26] = D_800DD704[arg1[1]];
}

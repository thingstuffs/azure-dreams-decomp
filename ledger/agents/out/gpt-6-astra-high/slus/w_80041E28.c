#include "common.h"

typedef struct S_80041E28_Dst {
    u8  pad0[0x54];
    s32 f54;
} S_80041E28_Dst;

typedef struct S_80041E28_Src {
    u8  pad0[0x50];
    s32 f50;
} S_80041E28_Src;

extern void func_8003DB6C(int *a0, int *a1, int a2);
extern void func_80041E70(S_80041E28_Dst *a0);

/* Copy 0x13 words and the trailing field from src to dst, then finish initializing dst. */
void func_80041E28(S_80041E28_Dst *dst, S_80041E28_Src *src)
{
    func_8003DB6C((int *)dst, (int *)src, 0x13);
    dst->f54 = src->f50;
    func_80041E70(dst);
}

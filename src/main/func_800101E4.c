#include "common.h"

extern s32 func_80023194(void *arg0);
extern s32 D_80028808[4];

typedef struct {
    int val;
    int pad[2];
} S_800814A0;
extern S_800814A0 D_800814A0;

s32 func_800231E4(s32 arg0) {
    void *p = &D_80028808[0];
    if (arg0 != 0) {
        void *field14 = *(void **)((u8 *) p + 0x14);
        *(u16 *)((u8 *) field14 + 0x1E) |= 0x2000;
    }
    func_80023194(p);
    *(u16 *)((u8 *) p - 2) |= 0x8000;
    D_800814A0.val |= 0x8000;
    __asm__ __volatile__("" ::: "memory");
    return D_80028808[0];
}

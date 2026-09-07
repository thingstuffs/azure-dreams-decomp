#include "common.h"

#include "common.h"

/* Init table setup: fills a destination-buffer table (D_80084538, 4 pointers
   into the D_801B9000 staging buffer at fixed offsets) and two parallel
   size/offset tables (D_800847C0, D_80084768) consumed alongside
   D_80084538 by the func_80055D84 subsystem-add family (D_80084538[idx]/
   D_800847C0[idx] are passed to func_8005A778 there). */

typedef struct {
    void *f0;
    void *f1;
    void *f2;
    void *f3;
} S_80084538;
extern S_80084538 D_80084538;

typedef struct {
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
} S_800847C0;
extern S_800847C0 D_800847C0;

typedef struct {
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
} S_80084768;
extern S_80084768 D_80084768;

extern u8 D_801B9000[];

void func_80055864(void) {
    s32 sizeA = 0x3A980, sizeB = 0x3B990, sizeC = 0x1BD50;
    s32 sizeD = 0x576E0, sizeE = 0x11940, sizeF = 0x69020;

    D_80084538.f0 = D_801B9000;
    D_80084538.f1 = D_801B9000 + 0x3000;
    D_80084538.f2 = D_801B9000 + 0x4020;
    D_80084538.f3 = D_801B9000 + 0x4E40;

    D_800847C0.f0 = 0x1010;
    D_800847C0.f1 = sizeB;
    D_800847C0.f2 = sizeD;
    D_800847C0.f3 = sizeF;

    D_80084768.f0 = sizeA;
    D_80084768.f1 = sizeC;
    D_80084768.f2 = sizeE;
    D_80084768.f3 = 0xFA00;
}

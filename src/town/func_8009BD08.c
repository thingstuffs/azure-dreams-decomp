#include "common.h"

typedef struct {
    unsigned char pad04[0];
} Unknown;

extern void func_80094984(void *, void *);
extern void func_80099754(void *);
extern signed char D_80082668;
extern int D_80098764;
extern int D_800D01B8[];

void func_80099468(void *arg0, void *arg1) {
    unsigned short value;

    func_80094984(D_800D01B8, arg0);
    D_80082668 = 0;
    *(unsigned short *)((unsigned char *)arg0 + 0x30) =
        *(unsigned short *)((unsigned char *)arg1 + 2);
    value = *(unsigned short *)((unsigned char *)arg1 + 6);
    *(short *)((unsigned char *)arg0 + 0xA) = 8;
    *(int **)((unsigned char *)arg0 + 4) = &D_80098764;
    *(unsigned short *)((unsigned char *)arg0 + 0x32) = value;
    func_80099754(arg1);
}

/* MECHANISM: Both arguments remain live across calls, naturally producing the
   0x20 frame with s0/s1 saves. Loading arg1+6 into an early u16 local holds v1
   across the middle stores while the short arg1+2 lifetime uses v0. */

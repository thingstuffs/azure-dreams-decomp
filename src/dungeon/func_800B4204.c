#include "common.h"

typedef struct SubA {
    u8 pad0[2];
    s16 f2;
    u8 pad4[2];
    s16 f6;
    u8 pad8[2];
    s16 fA;
} SubA;

typedef struct SubB {
    u8 pad0[6];
    u16 f6;
    u8 pad8[4];
    u32 fC;
    u16 f10;
    u8 pad12[2];
    u16 f14;
    u8 pad16[6];
    u16 f1C;
    u16 f1E;
} SubB;

typedef struct Obj {
    u8 pad0[8];
    SubA *sub1;
    SubB *sub2;
    void (*stateFn)(void *);
    u8 pad14[0x20 - 0x14];
    void *owner;
} Obj;

typedef struct EntityHdr {
    u8 pad[0x88];
    u16 f88;
} EntityHdr;

typedef struct {
    u8 pad0[2];
    u16 f2;
    u8 pad4[2];
    u16 f6;
    u8 pad8[2];
    u16 fA;
} D_80083780_t;

extern void *D_80083498;
extern D_80083780_t D_80083780;
extern u8 D_80079444[];
extern s16 D_800DCE66[5];
extern void *D_8008346C;

extern void *func_8003FD64(s32 a0, void *a1);
extern void func_8004491C(void *a0, void *a1);
extern s32 func_80045C34(u8 *a0, s32 a1, void *a2);
extern void func_800B96C4(void *a0);
extern void func_8003DB94(void *a0, void *a1, s16 a2);
extern void func_800C77D0(void *a0, void *a1, s32 a2, s16 a3);

void *func_800B9964(EntityHdr **arg0) {
    Obj *s2;
    SubA *s1;
    SubB *s0;

    s2 = func_8003FD64(18, &D_80083498);
    if (s2 != 0) {
        func_8004491C(s2, (void *)func_80045C34);
        s2->stateFn = func_800B96C4;

        s1 = s2->sub1;
        s0 = s2->sub2;
        s1->f2 = D_80083780.f2;
        s1->f6 = D_80083780.f6;
        s1->fA = (*arg0)->f88;
        func_8003DB94(s0, D_80079444, 0);

        {
            Obj *call0;
            SubA *call1;
            s32 call2;
            u32 color;
            u16 flags;

            color = 0x2c808080;
            call0 = s2;
            call1 = s1;
            __asm__ __volatile__("" : "+r"(call0), "+r"(call1));

            s0->f1E = 256;
            s0->f1C = 256;
            s0->f10 = 32;
            flags = s0->f14;
            __asm__ __volatile__("" : : "r"(flags));
            call2 = 8;
            ASM_KEEP(call2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            s0->fC = color;
            s0->f6 = 4;
            __asm__ __volatile__("" : : "m"(s0->f6));
            s0->f14 = flags | 0xC;

            {
                u8 *tail = (u8 *)s2 + 0x20;
                *(s16 *)(tail + 0xE) = 4;
                __asm__ __volatile__("" : : "r"(tail));
            }
            s2->owner = arg0;

            D_8008346C = s2;
            func_800C77D0(call0, call1, call2, D_800DCE66[0]);
        }
    }

    return (void *)s2;
}

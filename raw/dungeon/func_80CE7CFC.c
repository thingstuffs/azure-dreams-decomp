#include "common.h"

#define FIELD(obj, type, offset) (*(type *)((u8 *)(obj) + (offset)))

typedef struct { s32 w0, w1, w2, w3; } Blk16;

extern void *func_8003FD64();
extern s32 func_8003DE58();
extern void func_8004491C();
extern void func_80047784();

extern s16 D_80083228;
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_800DDC40[];
extern u8 D_80170DC4[];
extern u8 D_80175EB4[];
extern u8 D_80175EBC[];

void func_801714FC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    void *s2;
    void *v1;
    void *s0v;
    void *src;
    void *q;
    u16 spbuf[4];

    if (FIELD(arg3, s32, 0x60) == 0 && FIELD(arg3, s8, 0x72) >= 0) {
        return;
    }
    s2 = func_8003FD64(0x112, &D_80083498);
    if (s2 == 0) {
        return;
    }
    v1 = (u8 *)s2 + 0x20;
    FIELD(v1, s16, 0x96) = 0xa;
    FIELD(v1, s16, 0x9e) = 0xa;
    FIELD(s2, void *, 0x10) = (void *)&D_80170DC4;
    FIELD(v1, s16, 0x94) = FIELD(arg3, u16, 0x2a);
    s0v = FIELD(s2, void *, 0xc);
    src = arg2;
    {
        Blk16 *sp = (Blk16 *)src;
        Blk16 *dp16 = (Blk16 *)s0v;
        Blk16 *ep = sp + 3;
        do {
            *dp16 = *sp;
            dp16++;
            sp++;
        } while (sp != ep);
    }
    FIELD(s0v, s16, 0x1e) = 0x1000;
    FIELD(s0v, s16, 0x1c) = 0x1000;
    FIELD(s0v, u8, 0xe) = 0x80;
    FIELD(s0v, u8, 0xd) = 0x80;
    FIELD(s0v, u8, 0xc) = 0x80;
    FIELD(s0v, u16, 0x14) = FIELD(s0v, u16, 0x14) & 0xfff3;
    func_8004491C(s2, &D_80045340);
    FIELD(s0v, void *, 0x2c) = (void *)&D_80175EB4;
    func_80047784(s0v,
        ((u8 *)&D_80175EB4)[(((s32)D_80083228 + (s32)FIELD(arg3, s16, 0x2a) + 0x100) >> 9) & 7],
        0);
    s0v = FIELD(s2, void *, 8);
    if (FIELD(arg3, s32, 0x60) != 0 && (FIELD(arg3, s32, 0x14) & 0x04000000) == 0) {
        u8 *ebc = (u8 *)&D_80175EBC;
        q = FIELD(FIELD(arg3, void *, 0x60), void *, -0x18);
        FIELD(s0v, s16, 2) = FIELD(q, u16, 2)
            - (FIELD(ebc, s16, ((FIELD(arg3, u16, 0x2a) >> 7) & 0x1c)) * 0x10);
        FIELD(s0v, s16, 6) = FIELD(q, u16, 6)
            - (FIELD(ebc, s16, (((FIELD(arg3, u16, 0x2a) >> 7) & 0x1c) + 2)) * 0x10);
        FIELD(s0v, u16, 0xa) = FIELD(q, u16, 0xa)
            - (D_800DDC40[FIELD(FIELD(arg3, void *, 0x60), u8, 0x13)] >> 1);
        return;
    }
    if (FIELD(arg3, s8, 0x72) < 0) {
        s32 t72, t73;
        FIELD(arg3, u8, 0x72) = -(u8)FIELD(arg3, u8, 0x72);
        if (FIELD(arg3, s8, 0x73) < 0) {
            FIELD(arg3, u8, 0x73) = -(u8)FIELD(arg3, u8, 0x73);
        }
        t72 = FIELD(arg3, s8, 0x72);
        FIELD(s0v, s16, 2) = (t72 << 6) + 0x20;
        t73 = FIELD(arg3, s8, 0x73);
        FIELD(s0v, s16, 6) = (t73 << 6) + 0x20;
        FIELD(s0v, u16, 0xa) = FIELD(arg1, u16, 0xa);
        {
            void *r = FIELD(arg0, void *, -0x14);
            if (func_8003DE58(FIELD(r, s32, 8), r, spbuf, 0) != 0) {
                FIELD(s0v, u16, 0xa) = FIELD(s0v, u16, 0xa) + spbuf[2];
                return;
            }
        }
        FIELD(s0v, u16, 0xa) = FIELD(s0v, u16, 0xa) - 0x28;
    }
}

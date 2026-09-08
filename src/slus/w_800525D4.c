#include "common.h"

/* Sub-object embedded at offset 0x20 of the allocated node. */
typedef struct S_800525D4_sub {
    s16 f0;     /* 0x00 */
    s16 f2;     /* 0x02 */
    s16 count;  /* 0x04 - incremented once per successfully attached slot */
    s16 f6;     /* 0x06 */
    void *f8;   /* 0x08 - set to &D_80071E44 */
    void *fC;   /* 0x0C - result of func_80051708 */
    void *f10;  /* 0x10 - result of func_80051BFC */
    void *f14;  /* 0x14 - result of func_80051E94 */
    void *f18;  /* 0x18 - result of func_800520B4 */
    void *f1C;  /* 0x1C - result of func_80053374 */
} S_800525D4_sub;

/* Allocated node (from func_8003FC64), size class 0x124 (see S_80081490 in
 * w_8003FC64.c); this function only touches the prefix up through the
 * embedded sub-object at 0x20. */
typedef struct S_800525D4_obj {
    u8 pad00[0x10];               /* 0x00 */
    void (*vtable)(void);         /* 0x10 - set to func_80052144 */
    u8 pad14[0x20 - 0x14];        /* 0x14 */
    S_800525D4_sub sub;           /* 0x20 */
} S_800525D4_obj;

extern u8 D_80071E44[0x10];

extern void *func_8003FC64(s32 a0);
extern void func_8003F540(int a0, int a1, int a2, int a3);
extern short func_80053DA8(int a0);
extern void *func_8003FD64(s32 a0, void *a1);
extern s32 func_80033B2C(s32 a0);
extern void func_80052144(void);
extern void func_80051708(void *a0, S_800525D4_sub *a1);
extern void func_80051BFC(void *a0, S_800525D4_sub *a1);
extern void func_80051E94(void *a0, S_800525D4_sub *a1);
extern void func_800520B4(void *a0, S_800525D4_sub *a1);
extern void func_80053374(void *a0, S_800525D4_sub *a1);

/* Allocates a node via func_8003FC64(0). On success, installs the node's
 * vtable (func_80052144), zeroes its embedded sub-object and points its
 * f8 field at D_80071E44, then runs global init (func_8003F540) and sets a
 * flag (func_80053DA8(0x300)). It then tries to attach up to 5 sub-slots,
 * each obtained via func_8003FD64(0x212, node); on success the slot pointer
 * is stashed in the sub-object and the sub-object's slot count is bumped.
 * The second slot is skipped entirely if func_80033B2C(0x1392) returns
 * non-zero. The retail binary never sets up a return value (leftover $v0
 * from the last operation performed); it is effectively void. */
void func_800525D4(void)
{
    S_800525D4_obj *s2;
    S_800525D4_sub *s0;
    register void *s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */

    s2 = (S_800525D4_obj *)func_8003FC64(0);
    if (s2 != 0) {
        s0 = &s2->sub;
        s2->vtable = func_80052144;
        s2->sub.f0 = 0;
        s0->f2 = 0;
        s0->count = 0;
        s0->f6 = 0;
        s0->f8 = D_80071E44;
        s0->fC = 0;
        s0->f10 = 0;
        s0->f14 = 0;
        s0->f18 = 0;
        s0->f1C = 0;
        func_8003F540(0, 0x15B7C, 0, 0x10093C8);
        func_80053DA8(0x300);

        s1 = func_8003FD64(0x212, s2);
        if (s1 != 0) {
            func_80051708(s1, s0);
            s0->fC = s1;
            s0->count++;
        }
        if (func_80033B2C(0x1392) == 0) {
            s1 = func_8003FD64(0x212, s2);
            if (s1 != 0) {
                func_80051BFC(s1, s0);
                s0->f10 = s1;
                s0->count++;
            }
        }
        s1 = func_8003FD64(0x212, s2);
        if (s1 != 0) {
            func_80051E94(s1, s0);
            s0->f14 = s1;
            s0->count++;
        }
        s1 = func_8003FD64(0x212, s2);
        if (s1 != 0) {
            func_800520B4(s1, s0);
            s0->f18 = s1;
            s0->count++;
        }
        s1 = func_8003FD64(0x212, s2);
        if (s1 != 0) {
            func_80053374(s1, s0);
            s0->f1C = s1;
            s0->count++;
        }
    }
}

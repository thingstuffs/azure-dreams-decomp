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
extern short SD_Call(int a0);
extern void *func_8003FD64(s32 a0, void *a1);
extern s32 func_80033B2C(s32 a0);
extern void func_80052144(void);
extern void func_80051708(void *a0, S_800525D4_sub *a1);
extern void func_80051BFC(void *a0, S_800525D4_sub *a1);
extern void func_80051E94(void *a0, S_800525D4_sub *a1);
extern void func_800520B4(void *a0, S_800525D4_sub *a1);
extern void func_80053374(void *a0, S_800525D4_sub *a1);

/* Allocates and initializes a node, then attaches up to five slots. */
void func_800525D4(void)
{
    S_800525D4_obj *node;
    S_800525D4_sub *slots;
    register void *slot ASM_REG("$17");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */

    node = (S_800525D4_obj *)func_8003FC64(0);
    if (node != 0) {
        slots = &node->sub;
        node->vtable = func_80052144;
        node->sub.f0 = 0;
        slots->f2 = 0;
        slots->count = 0;
        slots->f6 = 0;
        slots->f8 = D_80071E44;
        slots->fC = 0;
        slots->f10 = 0;
        slots->f14 = 0;
        slots->f18 = 0;
        slots->f1C = 0;
        func_8003F540(0, 0x15B7C, 0, 0x10093C8);
        SD_Call(0x300);

        slot = func_8003FD64(0x212, node);
        if (slot != 0) {
            func_80051708(slot, slots);
            slots->fC = slot;
            slots->count++;
        }
        if (func_80033B2C(0x1392) == 0) {
            slot = func_8003FD64(0x212, node);
            if (slot != 0) {
                func_80051BFC(slot, slots);
                slots->f10 = slot;
                slots->count++;
            }
        }
        slot = func_8003FD64(0x212, node);
        if (slot != 0) {
            func_80051E94(slot, slots);
            slots->f14 = slot;
            slots->count++;
        }
        slot = func_8003FD64(0x212, node);
        if (slot != 0) {
            func_800520B4(slot, slots);
            slots->f18 = slot;
            slots->count++;
        }
        slot = func_8003FD64(0x212, node);
        if (slot != 0) {
            func_80053374(slot, slots);
            slots->f1C = slot;
            slots->count++;
        }
    }
}

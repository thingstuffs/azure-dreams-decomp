#include "common.h"

#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))
#define SC32(p, o)   (*(s32 *)((u8 *)(p) + (o)))
#define VSC32(p, o)  (*(volatile s32 *)((u8 *)(p) + (o)))
#define SCU8(p, o)   (*(u8 *)((u8 *)(p) + (o)))
#define SCPTR(p, o)  (*(void **)((u8 *)(p) + (o)))
#define VSPTR(p, o)  (*(void * volatile *)((u8 *)(p) + (o)))

extern void func_8008F55C(void *, void *, void *);
extern void func_8008F5B4(void *, void *, void *);
extern void func_8008F60C(void *, void *, void *);

void func_8008F664(void *arg0, void *arg1) {
    u8 *scratch;
    void *root;
    void *cur;
    void *next_obj;
    void *part;
    void *p0;
    void *pc;
    s32 d0;
    s32 d1;
    s32 d2;
    s32 d3;
    s32 d4;
    s32 d5;
    s32 x;
    s32 y;
    s32 z;
    s32 ax;
    s32 ay;
    s32 az;
    s32 i;

    root = PTR_AT(arg0, 0xC);
    scratch = (u8 *)0x1F800000;
    SC32(scratch, 0x38) = 0;
    SCPTR(scratch, 0) = root;
    do {
        *(u8 *)((u32)arg0 + SC32(scratch, 0x38) + 0x3A) = 0;
        i = SC32(scratch, 0x38) + 1;
        SC32(scratch, 0x38) = i;
    } while (i < 6);

    SCPTR(scratch, 4) = PTR_AT(arg0, 4);
    if (SCPTR(scratch, 4) == arg0) {
        goto clear_tail;
    }

object_loop:
    {
    void *loop_cur;
    register void *loop_next ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    loop_cur = SCPTR(scratch, 4);
    loop_next = PTR_AT(VSPTR(scratch, 4), 8);
    SCPTR(scratch, 8) = loop_next;
    part = PTR_AT(loop_cur, 0xC);
    ASM_KEEP_NV(part);   /* MATCH pin: keeps a statement from moving across a call/branch */
    loop_next = loop_cur;
    ASM_KEEP_NV(loop_next);   /* MATCH pin: load-bearing for the whole function shape */
    SCPTR(scratch, 0xC) = part;
    if (U8_AT(loop_next, 0x15) == 0) {
        goto next_object;
    }
    }

    {
    void *q0;
    register void *q8 ASM_REG("$3");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 left;
    register s32 q0v ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 right ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 pv0;
    register s32 pvc ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

    q0 = VSPTR(scratch, 0);
    left = S32_AT(arg1, 0);
    q0v = S32_AT(q0, 0);
    q8 = VSPTR(scratch, 8);
    left += q0v;
    right = S32_AT(q8, 0);
    pv0 = S32_AT(part, 0);
    pvc = S32_AT(part, 0xC);
    right += pv0;
    right += pvc;
    left -= right;
    SC32(scratch, 0x10) = left;
    if (left > 0) {
        goto next_object;
    }
    }

    {
    register void *q0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    void *q8;
    register void *qc ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    s32 left;
    s32 q0v;
    s32 extra;
    s32 right;
    register s32 qcv ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

    q0 = VSPTR(scratch, 0);
    left = S32_AT(arg1, 0);
    q0v = S32_AT(q0, 0);
    extra = S32_AT(q0, 0xC);
    qc = VSPTR(scratch, 0xC);
    left += q0v;
    q8 = VSPTR(scratch, 8);
    qcv = S32_AT(qc, 0);
    right = S32_AT(q8, 0);
    left += extra;
    right += qcv;
    left -= right;
    SC32(scratch, 0x14) = left;
    if (left < 0) {
        goto next_object;
    }
    }

    {
    void *q0;
    register void *q8 ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *qc;
    s32 left;
    register s32 q0v ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 right;
    register s32 qcv ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    register s32 qce ASM_REG("$3");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    q0 = VSPTR(scratch, 0);
    left = S32_AT(arg1, 4);
    q0v = S32_AT(q0, 4);
    qc = VSPTR(scratch, 0xC);
    left += q0v;
    q8 = VSPTR(scratch, 8);
    qcv = S32_AT(qc, 4);
    right = S32_AT(q8, 4);
    qce = S32_AT(qc, 0x10);
    right += qcv;
    right += qce;
    left -= right;
    SC32(scratch, 0x18) = left;
    if (left > 0) {
        goto next_object;
    }
    }

    {
    register void *q0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    void *q8;
    register void *qc ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    s32 left;
    s32 q0v;
    s32 extra;
    s32 right;
    register s32 qcv ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

    q0 = VSPTR(scratch, 0);
    left = S32_AT(arg1, 4);
    q0v = S32_AT(q0, 4);
    extra = S32_AT(q0, 0x10);
    qc = VSPTR(scratch, 0xC);
    left += q0v;
    q8 = VSPTR(scratch, 8);
    qcv = S32_AT(qc, 4);
    right = S32_AT(q8, 4);
    left += extra;
    right += qcv;
    left -= right;
    SC32(scratch, 0x1C) = left;
    if (left < 0) {
        goto next_object;
    }
    }

    {
    void *q0;
    register void *q8 ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *qc;
    s32 left;
    register s32 q0v ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 right;
    register s32 qcv ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    register s32 qce ASM_REG("$3");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    q0 = VSPTR(scratch, 0);
    left = S32_AT(arg1, 8);
    q0v = S32_AT(q0, 8);
    qc = VSPTR(scratch, 0xC);
    left += q0v;
    q8 = VSPTR(scratch, 8);
    qcv = S32_AT(qc, 8);
    right = S32_AT(q8, 8);
    qce = S32_AT(qc, 0x14);
    right += qcv;
    right += qce;
    left -= right;
    SC32(scratch, 0x20) = left;
    if (left > 0) {
        goto next_object;
    }
    }

    {
    register void *q0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    void *q8;
    register void *qc ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    s32 left;
    s32 q0v;
    s32 extra;
    s32 right;
    register s32 qcv ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

    q0 = VSPTR(scratch, 0);
    left = S32_AT(arg1, 8);
    q0v = S32_AT(q0, 8);
    extra = S32_AT(q0, 0x14);
    qc = VSPTR(scratch, 0xC);
    left += q0v;
    q8 = VSPTR(scratch, 8);
    qcv = S32_AT(qc, 8);
    right = S32_AT(q8, 8);
    left += extra;
    right += qcv;
    left -= right;
    SC32(scratch, 0x24) = left;
    if (left < 0) {
        goto next_object;
    }
    }

    {
    s32 sx;
    s32 sy;
    register s32 say ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 pick ASM_REG("$3");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    sx = SC32(scratch, 0x10);
    sy = SC32(scratch, 0x14);
    if (sx < 0) {
        sx = -sx;
    }
    say = sy;
    if (sy < 0) {
        say = -say;
    }
    pick = sx < say;
    if (pick) {
        SCU8(scratch, 0x28) = U8_AT(arg0, 0x37);
        SC32(scratch, 0x2C) = 2;
    } else {
        SC32(scratch, 0x10) = sy;
        SCU8(scratch, 0x28) = U8_AT(arg0, 0x36);
        SC32(scratch, 0x2C) = 3;
    }

    sx = SC32(scratch, 0x18);
    sy = SC32(scratch, 0x1C);
    if (sx < 0) {
        sx = -sx;
    }
    say = sy;
    if (sy < 0) {
        say = -say;
    }
    pick = sx < say;
    if (pick) {
        SCU8(scratch, 0x29) = U8_AT(arg0, 0x39);
        SC32(scratch, 0x30) = 4;
    } else {
        SC32(scratch, 0x18) = sy;
        SCU8(scratch, 0x29) = U8_AT(arg0, 0x38);
        SC32(scratch, 0x30) = 5;
    }

    sx = SC32(scratch, 0x20);
    sy = SC32(scratch, 0x24);
    if (sx < 0) {
        sx = -sx;
    }
    say = sy;
    if (sy < 0) {
        say = -say;
    }
    pick = sx < say;
    if (pick) {
        SCU8(scratch, 0x2A) = U8_AT(arg0, 0x35);
        SC32(scratch, 0x34) = 0;
    } else {
        SC32(scratch, 0x20) = sy;
        SCU8(scratch, 0x2A) = U8_AT(arg0, 0x34);
        SC32(scratch, 0x34) = 1;
    }
    }

    x = SC32(scratch, 0x10);
    if (x == 0) {
        if (SC32(scratch, 0x18) == 0) {
            goto next_object;
        }
        if (SC32(scratch, 0x20) == 0) {
            goto next_object;
        }
    }
    y = SC32(scratch, 0x18);
    if (y == 0 && SC32(scratch, 0x20) == 0) {
        goto next_object;
    }
    z = SC32(scratch, 0x20);
    if (z > 0 && S32_AT(arg1, 0x14) >= z && x != 0 && y != 0) {
        goto call_60c;
    }

    {
    s32 dx;
    register s32 dax ASM_REG("$5");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 dy;
    s32 dz;
    register s32 daz ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

    dx = VSC32(scratch, 0x10);
    dy = VSC32(scratch, 0x18);
    dax = dx;
    if (dx < 0) {
        dax = -dax;
    }
    if (dy < 0) {
        dy = -dy;
    }
    ASM_KEEP_NV(dy);   /* MATCH pin: load-bearing for the whole function shape */
    if (dax < dy) {
        dz = VSC32(scratch, 0x20);
        daz = dz;
        if (dz < 0) {
            daz = -daz;
        }
        dz = dy < daz;
        if (dz) {
            goto call_55c;
        }
        dz = dax < daz;
        if (!dz) {
            goto call_60c;
        }
call_55c:
        func_8008F55C(arg0, arg1, scratch);
        goto next_object;
    } else {
        dz = VSC32(scratch, 0x20);
        if (dz < 0) {
            dz = -dz;
        }
        if (dy < dz) {
            goto call_5b4;
        }
    }
    }

call_60c:
    func_8008F60C(arg0, arg1, scratch);
    goto next_object;

call_5b4:
    func_8008F5B4(arg0, arg1, scratch);

next_object:
    SCPTR(scratch, 4) = PTR_AT(SCPTR(scratch, 4), 4);
    if (SCPTR(scratch, 4) != arg0) {
        goto object_loop;
    }

clear_tail:
    SC32(scratch, 0x38) = 0;
    do {
        *(u8 *)((u32)arg0 + SC32(scratch, 0x38) + 0x34) = 0;
        i = SC32(scratch, 0x38) + 1;
        SC32(scratch, 0x38) = i;
    } while (i < 6);
}

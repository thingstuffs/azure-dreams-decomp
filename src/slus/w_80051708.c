#include "common.h"

/* Initializes an object: sets its update-function pointer, stores the
 * passed-in sub-object pointer and clears two following fields, primes a
 * linked sub-record (offset 0xC) via func_8003DB94, sets two flag fields on
 * that sub-record, invokes func_8004491C with a callback, and finally fills
 * a 3-word vector (offset 0x8) with fixed constants. */
/* struct Elem / struct Dst as established in src/code.c for func_8003DB94 */
struct Elem {
    unsigned char b0;
    unsigned char pad1;
    unsigned char pad2;
    unsigned char pad3;
    int f4;
};

struct Dst {
    struct Elem *f0;
    unsigned char f4;
    unsigned char f5;
    unsigned char pad6;
    unsigned char pad7;
    int f8;
    int fc;
    int f10;
    unsigned short f14;
};

extern void func_8003DB94(struct Dst *a0, struct Elem *a1, short a2);
extern void func_8004491C(void *a0, void (*a1)(void));
extern void func_80051548(void);
extern void func_80044BB0(void);

/* Sized >8B to force %hi/%lo (not $gp) addressing, matching retail's lui/addiu. */
extern struct Elem D_80072044[2];

typedef struct {
    unsigned char pad00[8];
    int *f8;             /* 0x08: pointer to a 3-int vector */
    struct Dst *fc;      /* 0x0C */
    void (*func)(void);  /* 0x10 */
    unsigned char pad14[0x20 - 0x14];
    void *f20;           /* 0x20 */
    short f24;           /* 0x24 */
    short f26;           /* 0x26 */
} S_80051708;

void func_80051708(S_80051708 *a0, void *a1)
{
    struct Dst *s0;
    int *v1;
    char *p = (char *)&a0->f20;

    a0->func = func_80051548;
    a0->f20 = a1;
    ((short *)p)[2] = 0;
    ((short *)p)[3] = 0;

    s0 = a0->fc;
    s0->fc = 0x808080;
    func_8003DB94(s0, D_80072044, 0);

    *(short *)((char *)s0 + 0x1E) = 0x1000;
    *(short *)((char *)s0 + 0x1C) = 0x1000;
    func_8004491C(a0, func_80044BB0);

    v1 = a0->f8;
    v1[0] = 0x1C00000;
    v1[1] = 0xC00000;
    v1[2] = 0x800000;
}

#include "common.h"

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

/* Initializes the object callbacks, sub-object state, linked record, and fixed vector. */
void func_80051708(S_80051708 *object, void *sub_object)
{
    struct Dst *record;
    int *vector;
    char *sub_fields = (char *)&object->f20;

    object->func = func_80051548;
    object->f20 = sub_object;
    ((short *)sub_fields)[2] = 0;
    ((short *)sub_fields)[3] = 0;

    record = object->fc;
    record->fc = 0x808080;
    func_8003DB94(record, D_80072044, 0);

    *(short *)((char *)record + 0x1E) = 0x1000;
    *(short *)((char *)record + 0x1C) = 0x1000;
    func_8004491C(object, func_80044BB0);

    vector = object->f8;
    vector[0] = 0x1C00000;
    vector[1] = 0xC00000;
    vector[2] = 0x800000;
}

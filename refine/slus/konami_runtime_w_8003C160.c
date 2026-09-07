#include "common.h"

#include "common.h"

typedef struct Func8003C160Elem {
    u8 b0;
    u8 pad1;
    u8 pad2;
    u8 pad3;
    s32 f4;
} Func8003C160Elem;

typedef struct Func8003C160Dst {
    Func8003C160Elem *f0;
    u8 f4;
    u8 f5;
    u8 pad6[2];
    s32 f8;
    s32 fc;
    u16 f10;
    u8 pad12[2];
    u16 f14;
    u8 pad16[6];
    u16 f1c;
    u16 f1e;
} Func8003C160Dst;

typedef struct Func8003C160Vec {
    u8 pad0[2];
    u16 f2;
    u8 pad4[2];
    u16 f6;
    u8 pad8[2];
    u16 fA;
} Func8003C160Vec;

typedef struct Func8003C160Root {
    u8 pad0[8];
    Func8003C160Vec *vec;
    Func8003C160Dst *dst;
} Func8003C160Root;

typedef struct Func8003C160Context {
    void (*callback)(void);
    u8 pad4[4];
    Func8003C160Elem *source;
    Func8003C160Dst *dst;
} Func8003C160Context;

extern Func8003C160Context D_80082D58;
extern u8 D_800F26F8[12];
extern u8 D_80077784[12];
extern u8 D_800776FC[12];

extern void func_8003DB94(Func8003C160Dst *, Func8003C160Elem *, s16);
extern void func_8003C0A4(Func8003C160Context *, Func8003C160Dst *);
extern void func_8003C450(void);

/* Initialize the destination and vector for the current source and set the next callback. */
void func_8003C160(void) {
    Func8003C160Context *context = &D_80082D58;
    Func8003C160Root *root = (Func8003C160Root *)((u8 *)context - 0x20);
    Func8003C160Dst *dst = root->dst;
    Func8003C160Vec *vec = root->vec;

    dst->f1e = 0x200;
    dst->f1c = 0x200;
    dst->fc = 0x808080;
    dst->f8 = (s32)D_800F26F8;
    dst->f0 = 0;
    dst->f4 = 0;
    dst->f5 = 0;
    func_8003DB94(dst, context->source, 0);
    dst->f14 = 0;
    dst->f10 = 0;

    if (context->source == (Func8003C160Elem *)D_80077784 ||
        context->source == (Func8003C160Elem *)D_800776FC) {
        dst->f14 |= 0x400;
    }

    vec->f2 = 0x54;
    vec->f6 = 0x8D;
    vec->fA = 0x10;
    context->callback = func_8003C450;
    func_8003C0A4(context, dst);
}

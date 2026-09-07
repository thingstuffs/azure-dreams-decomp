#include "common.h"

extern void func_8004491C(void *, void *);
extern u8 D_80045340[];

#ifdef __mips__
extern void func_8014CA5C(void);
extern void func_8014CC24(void);
extern void func_8014D410(void);
extern void func_8014D43C(void);
extern void func_8014D3BC(void);
extern void func_8014D384(void);
extern void func_8014D400(void);
extern void func_8014ECF0(void);
extern void func_8014ECE8(void);
extern void func_8014ECE0(void);
extern void func_8014ECF8(void);
extern void func_8014ECA0(void);
extern void func_8014EC98(void);
extern void func_8014EC90(void);
extern void func_80150D74(void);
extern void func_80150D80(void);
extern void func_80150DB4(void);
extern void func_80150EA4(void);
extern void func_80150F78(void);
extern void func_80151084(void);
extern void func_801510B8(void);
extern void func_80151138(void);
extern void func_801511C0(void);

static void (*const func_80CB7000_table[])(void)
    __attribute__((section(".text.func_80CB7000"))) = {
        func_8014CA5C,
        func_8014CC24,
        func_8014D410,
        func_8014D410,
        func_8014D410,
        func_8014D43C,
        func_8014D3BC,
        func_8014D3BC,
        func_8014D3BC,
        func_8014D384,
        func_8014D384,
        func_8014D43C,
        func_8014D43C,
        func_8014D400,
        func_8014ECF0,
        func_8014ECE8,
        func_8014ECE0,
        func_8014ECF8,
        func_8014ECA0,
        func_8014EC98,
        func_8014EC90,
        0,
        func_80150D74,
        func_80150D80,
        func_80150DB4,
        func_80150EA4,
        func_80150F78,
        func_80151084,
        func_801510B8,
        func_80151138,
        func_801511C0,
};

#define FUNC_80CB7000_BODY func_80CB7000
#else
#define FUNC_80CB7000_BODY func_80CB7000
#endif

/* Initialize object state and primitive settings, and copy the source coordinates. */
void FUNC_80CB7000_BODY(void *object, s32 state_value, void *src_coords)
{
    void *prim;
    void *coords;

    *(s32 *)((u8 *)object + 0x60) = state_value;
    func_8004491C(object, D_80045340);

    prim = *(void **)((u8 *)object + 0xC);
    *(s16 *)((u8 *)prim + 0x10) = 0x20;
    *(u16 *)((u8 *)prim + 0x14) |= 0xC;

    coords = *(void **)((u8 *)object + 8);
    *(u16 *)((u8 *)coords + 2) = *(u16 *)((u8 *)src_coords + 2);
    *(u16 *)((u8 *)coords + 6) = *(u16 *)((u8 *)src_coords + 6);
    *(u16 *)((u8 *)coords + 0xA) = *(u16 *)((u8 *)src_coords + 0xA);

    prim = *(void **)((u8 *)object + 0xC);
    *(s16 *)((u8 *)prim + 0x1E) = 0x1000;
    *(s16 *)((u8 *)prim + 0x1C) = 0x1000;
    *(u8 *)((u8 *)prim + 0xE) = 0x80;
    *(u8 *)((u8 *)prim + 0xD) = 0x80;
    *(u8 *)((u8 *)prim + 0xC) = 0x80;
}

#ifdef __mips__
#endif

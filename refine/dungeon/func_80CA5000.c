#include "common.h"

extern void func_8004491C(void *, void *);
extern u8 D_80045340[];

#ifdef __mips__
extern void func_8015EA5C(void);
extern void func_8015EC24(void);
extern void func_8015F410(void);
extern void func_8015F43C(void);
extern void func_8015F3BC(void);
extern void func_8015F384(void);
extern void func_8015F400(void);
extern void func_80160CF0(void);
extern void func_80160CE8(void);
extern void func_80160CE0(void);
extern void func_80160CF8(void);
extern void func_80160CA0(void);
extern void func_80160C98(void);
extern void func_80160C90(void);
extern void func_80162D74(void);
extern void func_80162D80(void);
extern void func_80162DB4(void);
extern void func_80162EA4(void);
extern void func_80162F78(void);
extern void func_80163084(void);
extern void func_801630B8(void);
extern void func_80163138(void);
extern void func_801631C0(void);

static void (*const func_80CA5000_table[])(void)
    __attribute__((section(".text.func_80CA5000"))) = {
        func_8015EA5C,
        func_8015EC24,
        func_8015F410,
        func_8015F410,
        func_8015F410,
        func_8015F43C,
        func_8015F3BC,
        func_8015F3BC,
        func_8015F3BC,
        func_8015F384,
        func_8015F384,
        func_8015F43C,
        func_8015F43C,
        func_8015F400,
        func_80160CF0,
        func_80160CE8,
        func_80160CE0,
        func_80160CF8,
        func_80160CA0,
        func_80160C98,
        func_80160C90,
        0,
        func_80162D74,
        func_80162D80,
        func_80162DB4,
        func_80162EA4,
        func_80162F78,
        func_80163084,
        func_801630B8,
        func_80163138,
        func_801631C0,
};

#define FUNC_80CA5000_BODY func_80CA5000
#else
#define FUNC_80CA5000_BODY func_80CA5000
#endif

/* Initialize the object primitive and copy the supplied coordinates. */
void FUNC_80CA5000_BODY(void *object, s32 init_value, void *source_coords) {
    void *prim;
    void *coords;

    *(s32 *)((u8 *)object + 0x60) = init_value;
    func_8004491C(object, D_80045340);

    prim = *(void **)((u8 *)object + 0xC);
    *(s16 *)((u8 *)prim + 0x10) = 0x20;
    *(u16 *)((u8 *)prim + 0x14) |= 0xC;

    coords = *(void **)((u8 *)object + 8);
    *(u16 *)((u8 *)coords + 2) = *(u16 *)((u8 *)source_coords + 2);
    *(u16 *)((u8 *)coords + 6) = *(u16 *)((u8 *)source_coords + 6);
    *(u16 *)((u8 *)coords + 0xA) = *(u16 *)((u8 *)source_coords + 0xA);

    prim = *(void **)((u8 *)object + 0xC);
    *(s16 *)((u8 *)prim + 0x1E) = 0x1000;
    *(s16 *)((u8 *)prim + 0x1C) = 0x1000;
    *(u8 *)((u8 *)prim + 0xE) = 0x80;
    *(u8 *)((u8 *)prim + 0xD) = 0x80;
    *(u8 *)((u8 *)prim + 0xC) = 0x80;
}

#ifdef __mips__
#endif

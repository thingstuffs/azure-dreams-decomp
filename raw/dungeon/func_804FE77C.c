#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct DispatchInner {
    u8 pad_00[0x218];
    void (*callback)(void *);
} DispatchInner;

typedef struct DispatchOuter {
    u8 pad_00[0x20];
    DispatchInner *inner;
} DispatchOuter;

extern s32 func_80018964(s32);
extern void func_800188E4(s32);
extern void func_8001886C(s32);
extern void func_80064F20(s32);
extern void func_80064EE0(s32, s32, s32);
extern void func_80064D50(void *);
extern void func_80064D20(void *);
extern void func_80064624(s32, s32);
extern void func_80064EC0(s32, s32, s32);
extern void func_80064F00(s32, s32);

extern void func_8001D4FC(void);
extern void func_8001D508(void);
extern void func_8001D540(void);
extern void func_8001D5C0(void);
extern void func_8001D578(void);
extern void func_8001D5B0(void);
extern void func_8001E944(void);
extern void func_8001E87C(void);
extern void func_8001E8A4(void);
extern void func_8001E8E8(void);
extern void func_8001E8B8(void);
extern void func_8001E910(void);

extern DispatchOuter *D_80016000[];
extern u8 D_800190D4[];
extern u8 D_80083160[];
extern void *D_80083478;
extern u8 D_800DDC7C[];
extern u8 D_801C9E40[16];
extern u8 D_801DA714[16];

#ifdef __mips__
#define ROW_ATTR __attribute__((used, section(".text.func_8001677C")))
#else
#define ROW_ATTR
#endif

void func_8001677C(void) ROW_ATTR;
void func_8001677C(void)
{
#ifdef __mips__
    register u32 *stack ASM_REG("$29");
    register u32 return_address ASM_REG("$31");
#endif

    if (func_80018964(0x601) != 0) {
        func_800188E4(0x601);
    } else {
        func_8001886C(0x601);
    }

    if (func_80018964(0x1202) != 0) {
        func_800188E4(0x1202);
    } else {
        func_8001886C(0x1202);
    }

    D_80016000[0]->inner->callback(D_800190D4);

#ifdef __mips__
    return_address = stack[4];
    stack = (u32 *)((u8 *)stack + 24);
    ASM_KEEP(return_address);
    ASM_KEEP(stack);
    __asm__(".end func_8001677C\n.if 0");
#endif
}

#ifdef __mips__
__asm__(".endif");
static void (*const dispatch_table[])(void)
    __attribute__((used, section(".text.func_8001677C"), aligned(4))) = {
        func_8001D4FC,
        func_8001D508,
        func_8001D540,
        func_8001D5C0,
        func_8001D578,
        func_8001D5B0,
        func_8001D5B0,
        func_8001D5B0,
        func_8001D5B0,
        func_8001D5B0,
        func_8001D5B0,
        func_8001D5B0,
        func_8001D5B0,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E87C,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E8A4,
        func_8001E8E8,
        func_8001E8B8,
        func_8001E910,
    };
#endif

static void func_804FE87C(void) ROW_ATTR;
static void func_804FE87C(void)
{
    u8 *base = D_80083160;
    u8 *state = base + 0x18;
    register s32 c1 ASM_REG("$3");
    register s32 c2 ASM_REG("$2");
    register void *call_arg ASM_REG("$4");

    FIELD(state, s32, 0x88) = 0x200;
    func_80064F20(0x200);

    FIELD(state, s32, 0x78) = 0;
    FIELD(state, s32, 0x7C) = 0;
    FIELD(state, s32, 0x80) = 0;
    func_80064EE0(0, 0, 0);

    FIELD(state, s16, 0x58) = 0x200;
    FIELD(state, s16, 0x5E) = 0x200;
    FIELD(state, s16, 0x64) = 0x200;
    FIELD(state, s16, 0x5A) = -0x100;
    FIELD(state, s16, 0x60) = -0x100;
    FIELD(state, s16, 0x66) = -0x100;
    FIELD(state, s16, 0x5C) = 0;
    FIELD(state, s16, 0x62) = 0;
    FIELD(state, s16, 0x68) = 0;
    func_80064D50(base + 0x70);

    call_arg = base + 0x50;
    ASM_KEEP(call_arg);
    c1 = -0x800;
    c2 = 0x800;
    ASM_KEEP(c1);
    ASM_KEEP(c2);
    FIELD(state, s16, 0x38) = c1;
    FIELD(state, s16, 0x3C) = c1;
    c1 = 0x800;
    ASM_KEEP(c1);
    FIELD(state, s16, 0x3A) = c2;
    c2 = -0x800;
    ASM_KEEP(c2);
    FIELD(state, s16, 0x3E) = c1;
    FIELD(state, s16, 0x40) = c2;
    FIELD(state, s16, 0x42) = c1;
    FIELD(state, s16, 0x44) = 0;
    FIELD(state, s16, 0x46) = 0;
    FIELD(state, s16, 0x48) = 0;
    func_80064D20(call_arg);

    FIELD(state, s32, 0x84) = 0x1000;
    func_80064624(0x1000, FIELD(state, s32, 0x88));
    func_80064EC0(0xA0, 0xA0, 0xA0);

    D_801C9E40[0x19] = 0;
    D_801C9E40[0x1A] = 0;
    D_801C9E40[0x1B] = 0;
    D_801DA714[0x19] = 0;
    D_801DA714[0x1A] = 0;
    D_801DA714[0x1B] = 0;
    func_80064F00(0xA0, 0x78);

    FIELD(base, s16, 0x18) = -0xBC;
    FIELD(base, s16, 0x1A) = -0x88;
    FIELD(base, s16, 0x1C) = 0x172;
    FIELD(base, s16, 0x1E) = 0x19A;
    D_80083478 = D_800DDC7C;
}

#ifdef __mips__
__asm__(".size func_8001677C, 604");
#endif

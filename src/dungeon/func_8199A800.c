#include "common.h"

#define U8_AT(p, off) (*(u8 *)((u8 *)(p) + (off)))
#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define VOL_U16_AT(p, off) (*(volatile u16 *)((u8 *)(p) + (off)))
#define U32_AT(p, off) (*(u32 *)((u8 *)(p) + (off)))
#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define PTR_AT(p, off) (*(void **)((u8 *)(p) + (off)))

extern u8 D_80083160[];
extern void *D_80024008[];
extern u8 D_800814A8[12];
extern u8 D_80024A64[];
extern u16 D_80024A70[];
extern u8 D_80083460[];
extern s32 D_800814A0;
extern u16 D_80082E94[];

extern void func_800246F4(void *, void *);
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern void func_80024260(void) __attribute__((noreturn));
extern void func_80024208(void) __attribute__((noreturn));
extern void func_800B835C(void *, void *, s32, s32);
extern void func_8002401C(void);
extern void func_8002406C(void);
extern void func_800240A0(void);
extern void func_80024124(void);
extern void func_8002414C(void);
extern void func_80024218(void);

#define MANAGER_PTR() ((void *)(u32)U32_AT(D_800814A8, 0))

#ifdef __mips__
__asm__(".section .text.func_8199A800,\"a\",@progbits\n.globl func_8199A800\n.type func_8199A800,@function\nfunc_8199A800:");

static void (*const func_8199A800_table[])(void)
    __attribute__((section(".text.func_8199A800"))) = {
        func_8002401C,
        0,
        func_8002406C,
        func_800240A0,
        func_80024124,
        func_8002414C,
        func_80024218,
    };
#endif

#ifdef __mips__
void func_8199A800(void *arg0) __asm__("func_8199A800_body")
    __attribute__((section(".text.func_8199A800")));
#endif

void func_8199A800(void *arg0)
{
    u8 *state = (u8 *)arg0;
    u8 *global_table;
    void **dispatch;
    s32 mode;
    s32 result;
    static void *const keepalive[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&default_case
    };

    U16_AT(state, 0x16)++;
    mode = S16_AT(state, 0x0A);
    global_table = D_80083160;
    if ((u32)mode < 5U) {
        (void)keepalive;
        dispatch = D_80024008;
        goto *dispatch[mode];
    }
    goto default_case;

case_0:
    U32_AT(MANAGER_PTR(), 0xF4) = (u32)D_80024A64;
    func_800246F4((u8 *)PTR_AT(state, 0) - 0x20, PTR_AT(state, 4));
    VOL_U16_AT(state, 0x0A)++;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if ((U16_AT(PTR_AT(state, 4), 0) & 0x80) == 0) {
        goto default_case;
    }
    {
        u8 *manager_page = (u8 *)0x80080000;
        void *manager =
            *(void **)(manager_page + 0x14A8);
        ASM_KEEP(manager_page);   /* MATCH pin: keeps a constant in a register as retail does */

        U16_AT(state, 0x18) = 0x12;
        result = U16_AT(manager, 0xA6) - 1;
        U16_AT(manager, 0xA6) = result;
    }
    result = func_80053EF0(4);
    if (result != 2) {
        func_800A56E0(0x300);
    } else {
        func_800A56E0(0x4300);
    }
    U8_AT(MANAGER_PTR(), 0xA8) = U8_AT(state, 8);
    U16_AT(state, 0x14) = U16_AT(MANAGER_PTR(), 0x2A);
    U16_AT(state, 0x0A)++;
    func_80024260();

case_1:
    U16_AT(state, 0x18)--;
    if ((s16)U16_AT(state, 0x18) > 0) {
        goto default_case;
    }
    {
        u16 countdown = 0x10;
        u16 live = U16_AT(state, 0x0A);
        ASM_KEEP(live);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        U16_AT(state, 0x18) = countdown;
    }
    func_80024208();

case_2:
    {
        void *entry = PTR_AT(MANAGER_PTR(), 0x60);

        if (entry != 0) {
            s32 value = (s32)U32_AT(entry, 0x1C) | 0x10000000;
            register u32 effect ASM_REG("$4") = 0;   /* MATCH pin: retail register colouring depends on it */
            register void *child ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
            U32_AT(entry, 0x1C) = value;
            child = PTR_AT(entry, -0x14);
            if ((U16_AT(global_table, 4) & 1) != 0) {
                effect = 0x0080FF80;
            }
            U32_AT(child, 0x0C) = effect;
        }
    }
    if ((U16_AT(D_80082E94, 0) & 0x8000) == 0) {
        U16_AT(state, 0x18)--;
        if ((s16)U16_AT(state, 0x18) >= 0) {
            goto default_case;
        }
    }
    {
        register void *entry ASM_REG("$5") = PTR_AT(MANAGER_PTR(), 0x60);   /* MATCH pin: retail register colouring depends on it */

        if (entry != 0) {
            u32 mask = 0xEFFFFFFF;
            register u32 effect ASM_REG("$4") = 0x00808080;   /* MATCH pin: retail register colouring depends on it */
            void *child = PTR_AT(entry, -0x14);
            s32 value = (s32)U32_AT(entry, 0x1C) & mask;
            U32_AT(entry, 0x1C) = value;
            U32_AT(child, 0x0C) = effect;
        }
    }
    U16_AT(state, 0x0A)++;
    func_80024260();

case_3:
    if (S16_AT(D_80024A70, 0) != 0) {
        goto default_case;
    }
    {
        u8 *counter = D_80083460;
        U16_AT(counter, 0x0A)--;
        U32_AT(counter, 0x0C) = 0;
    }
    U16_AT(state, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

default_case:
    if (S16_AT(state, 0x0A) >= 2) {
        u8 *work = (u8 *)&D_80024A70[2];
        s32 params[2];

        params[0] = 0x01000360;
        params[1] = 0x00200020;
        func_800B835C(work, params, 1, 0);
        U8_AT(work, 8) += 0x10;
    }
    D_80024A70[0] = 0;
}

#ifdef __mips__
__asm__(".size func_8199A800, 724");
#endif

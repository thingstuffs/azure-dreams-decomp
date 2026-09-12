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
extern u8 D_80080000[];

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
void func_8199A800(void *state_data) __asm__("func_8199A800_body")
    __attribute__((section(".text.func_8199A800")));
#endif

/* Advances a timed effect sequence, updates the entry tint, and draws the animation. */
void func_8199A800(void *state_data)
{
    u8 *state = (u8 *)state_data;
    u8 *effect_flags;
    void **phase_handlers;
    s32 phase;
    s32 result;
    static void *const phase_labels[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&default_case
    };

    U16_AT(state, 0x16)++;
    phase = S16_AT(state, 0x0A);
    effect_flags = D_80083160;
    if ((u32)phase < 5U) {
        (void)phase_labels;
        phase_handlers = D_80024008;
        goto *phase_handlers[phase];
    }
    goto default_case;

case_0:
    U32_AT(MANAGER_PTR(), 0xF4) = (u32)D_80024A64;
    func_800246F4((u8 *)PTR_AT(state, 0) - 0x20, PTR_AT(state, 4));
    VOL_U16_AT(state, 0x0A)++;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if ((U16_AT(PTR_AT(state, 4), 0) & 0x80) == 0) {
        goto default_case;
    }
    {
        void *manager =
            *(void **)(D_80080000 + 0x14A8);

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
        u16 saved_phase = U16_AT(state, 0x0A);
        ASM_KEEP(saved_phase);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        U16_AT(state, 0x18) = countdown;
    }
    func_80024208();

case_2:
    {
        void *entry = PTR_AT(MANAGER_PTR(), 0x60);

        if (entry != 0) {
            s32 entry_flags = (s32)U32_AT(entry, 0x1C) | 0x10000000;
            register u32 tint ASM_REG("$4") = 0;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register void *child ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            U32_AT(entry, 0x1C) = entry_flags;
            child = PTR_AT(entry, -0x14);
            if ((U16_AT(effect_flags, 4) & 1) != 0) {
                tint = 0x0080FF80;
            }
            U32_AT(child, 0x0C) = tint;
        }
    }
    if ((U16_AT(D_80082E94, 0) & 0x8000) == 0) {
        U16_AT(state, 0x18)--;
        if ((s16)U16_AT(state, 0x18) >= 0) {
            goto default_case;
        }
    }
    {
        register void *entry ASM_REG("$5") = PTR_AT(MANAGER_PTR(), 0x60);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        if (entry != 0) {
            u32 clear_effect_mask = 0xEFFFFFFF;
            register u32 tint ASM_REG("$4") = 0x00808080;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            void *child = PTR_AT(entry, -0x14);
            s32 entry_flags = (s32)U32_AT(entry, 0x1C) & clear_effect_mask;
            U32_AT(entry, 0x1C) = entry_flags;
            U32_AT(child, 0x0C) = tint;
        }
    }
    U16_AT(state, 0x0A)++;
    func_80024260();

case_3:
    if (S16_AT(D_80024A70, 0) != 0) {
        goto default_case;
    }
    {
        u8 *sequence_state = D_80083460;
        U16_AT(sequence_state, 0x0A)--;
        U32_AT(sequence_state, 0x0C) = 0;
    }
    U16_AT(state, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

default_case:
    if (S16_AT(state, 0x0A) >= 2) {
        u8 *draw_data = (u8 *)&D_80024A70[2];
        s32 draw_params[2];

        draw_params[0] = 0x01000360;
        draw_params[1] = 0x00200020;
        func_800B835C(draw_data, draw_params, 1, 0);
        U8_AT(draw_data, 8) += 0x10;
    }
    D_80024A70[0] = 0;
}

#ifdef __mips__
__asm__(".size func_8199A800, 724");
#endif

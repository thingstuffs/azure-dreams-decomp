#include "common.h"

typedef struct S_80CBD000_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x6C];
    void * unk_8C;
} S_80CBD000_0;   /* work in BODY_NAME */

typedef struct S_80CBD000_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80CBD000_1;   /* part in BODY_NAME */

typedef struct S_80CBD000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80CBD000_2;   /* coord in BODY_NAME */

typedef struct S_80CBD000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80CBD000_3;   /* state in BODY_NAME */

typedef struct S_80CBD000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0xA];
    s8 unk_A7;
    s8 unk_A8;
} S_80CBD000_4;   /* actor in BODY_NAME */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800A48F0(void *, s32, s32);
extern s32 func_800A6D30(void);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern u8 D_80045340;
extern s32 D_80083498;
extern u8 D_800E2968;
extern u8 D_80170AE0[];
extern u8 D_80170F20[];
extern u8 D_80173B98[];
extern u8 D_801762C0[];
extern u8 D_80176300[];
extern u8 D_80176320[];

#ifdef __mips__
void func_80170800(void);
static const u32 split_prefix[] __asm__("func_80170800")
    __attribute__((section(".text.func_80170800"), aligned(4))) = {
    0x801708A4, 0x00000000,
    0x801712E8, 0x801712E8, 0x801712E8, 0x80171314,
    0x80171294, 0x80171294, 0x80171294,
    0x8017125C, 0x8017125C, 0x80171314, 0x80171314, 0x801712D8,
    0x801728B4, 0x801728AC, 0x801728A4, 0x801728BC,
    0x80172864, 0x8017285C, 0x80172854, 0x00000000,
    0x80173EF8, 0x80173EF8, 0x80173EF8, 0x80173F08,
    0x80173EF8, 0x80173EF8, 0x80173EF8, 0x80173EF8,
    0x80173ED4, 0x80173F08, 0x80173F08, 0x80173EF8,
    0x8017559C, 0x80175594, 0x8017558C, 0x801755A4,
    0x8017554C, 0x80175544, 0x8017553C,
};
__asm__(".globl func_80170800\n"
        ".size func_80170800, 736");
#define BODY_NAME func_801708A4
#else
#define BODY_NAME func_80170800
#endif

void *BODY_NAME(s16 arg0, s8 _arg1, s8 arg2, s16 _arg3)
{
    register s8 arg1 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register s16 arg3 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 kind;
    s32 random;
    s16 arg0_copy;
    s32 alloc_id;
    void *alloc_base;
    void *part;
    register void *work ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_80CBD000_2 *coord;
    S_80CBD000_3 *state;
    register void *actor ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    work = 0;
    alloc_id = 0x112;
    ASM_KEEP_NV(alloc_id);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    arg1 = _arg1;
    alloc_base = &D_80083498;
    arg3 = _arg3;
    ASM_KEEP_NV(alloc_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    part = func_8003FD64(alloc_id, alloc_base);
    ASM_KEEP(arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    arg0_copy = arg0;
    if (part == 0) {
        goto done;
    }

    work = (u8 *)part + 0x20;
    ((S_80CBD000_0 *)work)->unk_13 = 0x15;
    func_8004491C(part, &D_80045340);
    coord = ((S_80CBD000_1 *)part)->unk_08;
    kind = arg0 & 3;
    coord->unk_0A = arg3;
    ASM_KEEP(arg1);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    state = ((S_80CBD000_1 *)part)->unk_0C;
    state->unk_25 = arg2;
    actor = work;
    state->unk_24 = arg1;

    if (kind == 1) {
        ((S_80CBD000_0 *)work)->unk_8C = D_80170F20;
        ((S_80CBD000_0 *)work)->unk_14 |= 0x6000;
        ((S_80CBD000_0 *)work)->unk_1C |= 0x6000;
        state->unk_2C = D_801762C0;
        goto next_done;
    }
    if (kind >= 2) {
        ((S_80CBD000_0 *)work)->unk_8C = D_80170F20;
        ((S_80CBD000_0 *)work)->unk_14 |= 0x2000;
        ((S_80CBD000_0 *)work)->unk_1C |= 0x2000;
        state->unk_2C = D_801762C0;
        goto next_done;
    }

    if (((arg0 & -4) << 16) != 0) {
        goto nonzero_kind;
    }

    if (!(((S_80CBD000_0 *)work)->unk_14 & 0x200)) {
        random = func_800A6D30();
        if (random & 1) {
            random = func_800A6D30();
            func_800A48F0(work, 1, (random & 0x3F) | 0x20);
            state->unk_2C = D_80176300;
        }
    }

    if (D_800E2968 >= 10) {
        goto ordinary_kind;
    }
    ((S_80CBD000_4 *)actor)->unk_8C = D_80170F20;
    state->unk_2C = D_801762C0;
    goto next_done;

ordinary_kind:
    ((S_80CBD000_4 *)actor)->unk_A7 = 1;
    ((S_80CBD000_4 *)actor)->unk_8C = D_80173B98;
    state->unk_2C = D_80176320;
    goto next_done;

nonzero_kind:
    ((S_80CBD000_0 *)work)->unk_8C = D_80170F20;
    state->unk_2C = D_801762C0;
next_done:
    ((S_80CBD000_1 *)part)->unk_10 = D_80170AE0;
    func_800A9C18(part, coord, state, arg0_copy);
    ((S_80CBD000_4 *)actor)->unk_9A = 0xFF;
    ((S_80CBD000_4 *)actor)->unk_9C = -1;
    ((S_80CBD000_4 *)actor)->unk_A8 = 0;
    func_800AA36C(actor, coord, state, work);

done:
    return work;
}

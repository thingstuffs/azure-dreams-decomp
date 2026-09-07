#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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
    register s8 arg1 ASM_REG("$21");
    register s16 arg3 ASM_REG("$17");
    s32 kind;
    s32 random;
    s16 arg0_copy;
    register s32 alloc_id ASM_REG("$4");
    register void *alloc_base ASM_REG("$5");
    register void *part ASM_REG("$19");
    register void *work ASM_REG("$16");
    void *coord;
    void *state;
    register void *actor ASM_REG("$20");

    work = 0;
    alloc_id = 0x112;
    ASM_KEEP_NV(alloc_id);
    arg1 = _arg1;
    alloc_base = &D_80083498;
    arg3 = _arg3;
    ASM_KEEP_NV(alloc_base);
    part = func_8003FD64(alloc_id, alloc_base);
    ASM_KEEP(arg1);
    ASM_KEEP(arg3);
    ASM_KEEP(part);
    arg0_copy = arg0;
    if (part == 0) {
        goto done;
    }

    work = (u8 *)part + 0x20;
    FIELD(work, s8, 0x13) = 0x15;
    func_8004491C(part, &D_80045340);
    coord = FIELD(part, void *, 8);
    kind = arg0 & 3;
    FIELD(coord, s16, 0xA) = arg3;
    ASM_KEEP(arg1);
    state = FIELD(part, void *, 0xC);
    FIELD(state, s8, 0x25) = arg2;
    actor = work;
    FIELD(state, s8, 0x24) = arg1;

    if (kind == 1) {
        FIELD(work, void *, 0x8C) = D_80170F20;
        FIELD(work, u32, 0x14) |= 0x6000;
        FIELD(work, u32, 0x1C) |= 0x6000;
        FIELD(state, void *, 0x2C) = D_801762C0;
        goto next_done;
    }
    if (kind >= 2) {
        FIELD(work, void *, 0x8C) = D_80170F20;
        FIELD(work, u32, 0x14) |= 0x2000;
        FIELD(work, u32, 0x1C) |= 0x2000;
        FIELD(state, void *, 0x2C) = D_801762C0;
        goto next_done;
    }

    if (((arg0 & -4) << 16) != 0) {
        goto nonzero_kind;
    }

    if (!(FIELD(work, u32, 0x14) & 0x200)) {
        random = func_800A6D30();
        if (random & 1) {
            random = func_800A6D30();
            func_800A48F0(work, 1, (random & 0x3F) | 0x20);
            FIELD(state, void *, 0x2C) = D_80176300;
        }
    }

    if (D_800E2968 >= 10) {
        goto ordinary_kind;
    }
    FIELD(actor, void *, 0x8C) = D_80170F20;
    FIELD(state, void *, 0x2C) = D_801762C0;
    goto next_done;

ordinary_kind:
    FIELD(actor, s8, 0xA7) = 1;
    FIELD(actor, void *, 0x8C) = D_80173B98;
    FIELD(state, void *, 0x2C) = D_80176320;
    goto next_done;

nonzero_kind:
    FIELD(work, void *, 0x8C) = D_80170F20;
    FIELD(state, void *, 0x2C) = D_801762C0;
next_done:
    FIELD(part, void *, 0x10) = D_80170AE0;
    func_800A9C18(part, coord, state, arg0_copy);
    FIELD(actor, u8, 0x9A) = 0xFF;
    FIELD(actor, s8, 0x9C) = -1;
    FIELD(actor, s8, 0xA8) = 0;
    func_800AA36C(actor, coord, state, work);

done:
    return work;
}

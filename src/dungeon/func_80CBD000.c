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

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
void *BODY_NAME(s16 flags, s16 unused_kind_id, s16 variant, s16 unused_spawn)
{
    s8 kind_id;
    s16 spawn_value;
    s32 kind;
    s32 random;
    s16 arg0_copy;
    s32 alloc_id;
    void *alloc_base;
    void *part;
    void *work;
    S_80CBD000_2 *coord;
    S_80CBD000_3 *state;
    void *actor;

    work = 0;
    alloc_id = 0x112;
    kind_id = unused_kind_id;
    alloc_base = &D_80083498;
    spawn_value = unused_spawn;
    part = func_8003FD64(alloc_id, alloc_base);
    arg0_copy = flags;
    if (part == 0) {
        goto done;
    }

    work = (u8 *)part + 0x20;
    ((S_80CBD000_0 *)work)->unk_13 = 0x15;
    func_8004491C(part, &D_80045340);
    coord = ((S_80CBD000_1 *)part)->unk_08;
    kind = flags & 3;
    coord->unk_0A = spawn_value;
    state = ((S_80CBD000_1 *)part)->unk_0C;
    state->unk_25 = variant;
    actor = work;
    state->unk_24 = kind_id;

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

    if (((flags & -4) << 16) != 0) {
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

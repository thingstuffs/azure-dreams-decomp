#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30();
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern u8 D_80045340[16];
extern u8 D_80083498[16];
extern u8 D_80170DA8[16];
extern u8 D_801714D4[16];
extern u8 D_801740E0[16];
extern u8 D_80174158[16];

void *func_80170BB0(s16 arg0, s8 arg1, s8 arg2, s32 arg3)
{
    s32 kind;
    s32 flags14;
    s32 flags1c;
    register void *object ASM_REG("$17");
    void *part_a;
    void *part_b;
    register void *page ASM_REG("$2");
    void *handler;
    register void *actor ASM_REG("$16");
    void *actor2;

    actor = 0;
    object = func_8003FD64(0x112, D_80083498);
    if (object != 0) {
        actor = (u8 *)object + 0x20;
        ASM_KEEP(actor);
        FIELD(object, void *, 0x10) = D_80170DA8;
        FIELD(actor, s8, 0x13) = 1;
        func_8004491C(object, D_80045340);

        page = (void *)0x80170000;
        ASM_KEEP(page);
        do { part_a = FIELD(object, void *, 8); } while (0);
        handler = (u8 *)page + 0x40E0;
        FIELD(part_a, s16, 0xA) = arg3;
        part_b = FIELD(object, void *, 0xC);
        kind = arg0 & 3;
        FIELD(part_b, s8, 0x25) = arg2;
        actor2 = actor;
        FIELD(part_b, void *, 0x2C) = handler;
        FIELD(part_b, s8, 0x24) = arg1;
        FIELD(actor, s16, 0x9E) = 0;

        if (kind == 1) {
            flags14 = FIELD(actor, s32, 0x14) | 0x6000;
            flags1c = FIELD(actor, s32, 0x1C) | 0x6000;
            goto store_flags;
        }
        if (kind >= 2) {
            flags14 = FIELD(actor, s32, 0x14) | 0x2000;
            flags1c = FIELD(actor, s32, 0x1C) | 0x2000;
store_flags:
            FIELD(actor, s32, 0x14) = flags14;
            FIELD(actor, s32, 0x1C) = flags1c;
            goto finish_kind;
        }
        if (((arg0 & ~3) << 16) != 0)
            goto finish_kind;
        if (FIELD(actor, s32, 0x14) & 0x200)
            goto finish_kind;
        if (!(func_800A6D30() & 1))
            goto finish_kind;
        do {
            func_800A48F0(actor, 1, (func_800A6D30() & 0x3F) | 0x20);
            FIELD(part_b, void *, 0x2C) = D_80174158;
        } while (0);

finish_kind:
        func_800A9C18(object, part_a, part_b, arg0);
        ASM_KEEP(object);
        FIELD(actor2, u8, 0x9A) = 0xFF;
        FIELD(actor2, s8, 0x9C) = -1;
        FIELD(actor2, void *, 0x8C) = D_801714D4;
        FIELD(actor, s32, 0x1C) |= 0x40000;
        FIELD(actor2, s16, 0x92) = -0x20;
        FIELD(part_b, s16, 0x10) = 0x20;
        FIELD(part_b, u16, 0x14) |= 0xC;
        func_800AA36C(actor2, part_a, part_b, actor);
    }
    ASM_KEEP(actor);
    return actor;
}
/* MECHANISM: The true-space body holds actor/object in s0/s1 and splits the v0 page
   as 0x80170000 + 0x40E0 so its addiu fills the part_a load delay. ABI-word arg3
   flips the entry sched tie, placing the s2/a3 save pair before s5/a2 at 2.7.2-G0. */

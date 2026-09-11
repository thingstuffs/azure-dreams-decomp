#include "common.h"

typedef struct S_80170BB0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80170BB0_0;   /* object in func_80170BB0 */

typedef struct S_80170BB0_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x7E];
    s16 unk_9E;
} S_80170BB0_1;   /* actor in func_80170BB0 */

typedef struct S_80170BB0_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170BB0_2;   /* part_a in func_80170BB0 */

typedef struct S_80170BB0_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80170BB0_3;   /* part_b in func_80170BB0 */

typedef struct S_80170BB0_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80170BB0_4;   /* actor2 in func_80170BB0 */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30(void);
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
    void *object;
    S_80170BB0_2 *part_a;
    S_80170BB0_3 *part_b;
    void *page;
    void *handler;
    S_80170BB0_1 *actor;
    S_80170BB0_4 *actor2;

    actor = 0;
    object = func_8003FD64(0x112, D_80083498);
    if (object != 0) {
        actor = (u8 *)object + 0x20;
        ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ((S_80170BB0_0 *)object)->unk_10 = D_80170DA8;
        actor->unk_13 = 1;
        func_8004491C(object, D_80045340);

        page = (void *)0x80170000;
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        part_a = ((S_80170BB0_0 *)object)->unk_08;
        handler = (u8 *)page + 0x40E0;
        part_a->unk_0A = arg3;
        part_b = ((S_80170BB0_0 *)object)->unk_0C;
        kind = arg0 & 3;
        part_b->unk_25 = arg2;
        actor2 = actor;
        part_b->unk_2C = handler;
        part_b->unk_24 = arg1;
        actor->unk_9E = 0;

        if (kind == 1) {
            flags14 = actor->unk_14 | 0x6000;
            flags1c = actor->unk_1C | 0x6000;
            goto store_flags;
        }
        if (kind >= 2) {
            flags14 = actor->unk_14 | 0x2000;
            flags1c = actor->unk_1C | 0x2000;
store_flags:
            actor->unk_14 = flags14;
            actor->unk_1C = flags1c;
            goto finish_kind;
        }
        if (((arg0 & ~3) << 16) != 0)
            goto finish_kind;
        if (actor->unk_14 & 0x200)
            goto finish_kind;
        if (!(func_800A6D30() & 1))
            goto finish_kind;
        func_800A48F0(actor, 1, (func_800A6D30() & 0x3F) | 0x20);
        part_b->unk_2C = D_80174158;

finish_kind:
        func_800A9C18(object, part_a, part_b, arg0);
           /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        actor2->unk_9A = 0xFF;
        actor2->unk_9C = -1;
        actor2->unk_8C = D_801714D4;
        actor->unk_1C |= 0x40000;
        actor2->unk_92 = -0x20;
        part_b->unk_10 = 0x20;
        part_b->unk_14 |= 0xC;
        func_800AA36C(actor2, part_a, part_b, actor);
    }
    return actor;
}
/* MECHANISM: The true-space body holds actor/object in s0/s1 and splits the v0 page
   as 0x80170000 + 0x40E0 so its addiu fills the part_a load delay. ABI-word arg3
   flips the entry sched tie, placing the s2/a3 save pair before s5/a2 at 2.7.2-G0. */

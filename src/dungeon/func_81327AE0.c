#include "common.h"

typedef void (*Callback)(void *, void *, void *, void *);


extern void func_800353F4();
extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s32 func_800BCB04();
extern void func_8016F534() __attribute__((noreturn));
extern void func_8016F580() __attribute__((noreturn));
extern void func_8016F5A4() __attribute__((noreturn));
extern void func_8016F610() __attribute__((noreturn));
extern void func_8016F6A8() __attribute__((noreturn));
extern void func_8016F6C0() __attribute__((noreturn));
extern void func_8016F740() __attribute__((noreturn));

extern u16 D_80013714;
extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 *D_800E3D7C;
extern u8 D_800F8BBC[9];
extern u8 D_8016F78C[9];
extern Callback D_80174AD4[];


typedef struct S_8016F2E0_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8016F2E0_0;   /* slot in func_8016F2E0 */

typedef struct S_8016F2E0_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8016F2E0_1_pre;   /* the 0x14 bytes before node in func_8016F2E0, addressed as node[-1] */

typedef struct S_8016F2E0_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8016F2E0_2;   /* record in func_8016F2E0 */

typedef struct S_8016F2E0_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    union { volatile u8 v; s8 n; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_8016F2E0_3;   /* actor in func_8016F2E0 */

typedef struct S_8016F2E0_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    union { u16 n; volatile u16 v; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    s32 unk_2C;
} S_8016F2E0_4;   /* arg2 in func_8016F2E0 */

typedef struct S_8016F2E0_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8016F2E0_5;   /* arg1 in func_8016F2E0 */

void func_8016F2E0(void *a0, void *a1, void *a2)
{
    void *arg0 = a0;
    void *arg1 = a1;
    register void *arg2 ASM_REG("$19") = a2;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *actor ASM_REG("$17") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 old_direction;
    register s32 direction_copy ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    Callback callback;
    s32 floor;
    s16 actor_height;
    u16 actor_height_u;
    s32 direction_check;
    s32 direction_value;
    u8 *tile_slot;
    register u8 *direction_slot ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 return_flags;
    u16 flags;
    u16 new_flags;
    s32 previous_direction;
    s32 tile_map;
    s32 i;
    u8 *slot;
    void *node;
    S_8016F2E0_2 *record;

    if ((*(s32 *)((u8 *)arg0 + (0x14))) & 0x00800000) {
        (*(s32 *)((u8 *)arg0 + (0x14))) &= 0xFF7FFFFF;
        func_800353F4(&D_800F8BBC);
        (*(u8 *)((u8 *)arg0 + (0x6D))) = 0;
        (*(u8 *)((u8 *)arg0 + (0x9B))) = 0;
        (*(u8 *)((u8 *)arg0 + (0x71))) &= 0x7F;
    }

    if (D_80013714 & 8) {
        i = 1;
        slot = D_800E3D7C + 4;
        do {
            node = ((S_8016F2E0_0 *)slot)->unk_AC;
            if (node != 0) {
                record = ((S_8016F2E0_1_pre *)node)[-1].unk_00;
                record->unk_14 &= 0xFFBF;
            }
            i--;
            slot -= 4;
        } while (i >= 0);
    }

    if (D_80083462 & 0x2000) {
        callback = (*(Callback *)((u8 *)arg0 + (0x8C)));
        if (callback == (Callback)&D_8016F78C) {
            callback(arg0, arg1, arg2, actor);
            return;
        }
        ((S_8016F2E0_3 *)actor)->unk_71 &= 0x7F;
        return;
    }

    old_direction = ((S_8016F2E0_3 *)actor)->unk_6D.v;
    old_direction = (old_direction << 24) >> 24;
    if (func_800A9E70(arg0, arg1, arg2, actor) != 0) {
        return;
    }

    {
        Callback callback2 = (*(Callback *)((u8 *)arg0 + (0x8C)));
        if (callback2 != 0) {
            callback2(arg0, arg1, arg2, actor);
        }
    }
    D_80174AD4[(*(u8 *)((u8 *)arg0 + (0x9A)))](arg0, arg1, arg2, actor);

    ASM_KEEP(old_direction);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    direction_check = (s16)old_direction;
    if (direction_check != ((S_8016F2E0_3 *)actor)->unk_6D.n) {
        func_800AA36C(arg0, arg1, arg2, actor);
    }

    flags = ((S_8016F2E0_4 *)arg2)->unk_14.n;
    new_flags = flags & 0x8000;
    if (new_flags == 0) {
        old_direction = ((D_80083228 + ((S_8016F2E0_3 *)actor)->unk_2A + 0x100) >> 9) & 7;
        previous_direction = (*(s16 *)((u8 *)arg0 + (0x94)));
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        direction_value = old_direction;
        ASM_KEEP(old_direction);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        direction_copy = old_direction;
        if (previous_direction != direction_value) {
            tile_map = ((S_8016F2E0_4 *)arg2)->unk_2C;
            if (tile_map != 0) {
                tile_slot = (u8 *)tile_map + direction_value;
                func_80047738(arg2,
                    *tile_slot,
                    ((S_8016F2E0_4 *)arg2)->unk_04);
            }
            (*(s16 *)((u8 *)arg0 + (0x94))) = old_direction;
        }

        direction_slot = D_8006CCF8 + direction_copy;
        ASM_KEEP(direction_slot);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (*direction_slot != 0) {
            return_flags = ((S_8016F2E0_4 *)arg2)->unk_14.n;
            return_flags |= 1;
            ASM_TAILSLOT_PIN(return_flags);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_8016F534();
            return;
        }

        ((S_8016F2E0_4 *)arg2)->unk_14.v &= 0xFFFE;
        if (!(((S_8016F2E0_3 *)actor)->unk_1C & 0x20)) {
            if (!(((S_8016F2E0_4 *)arg2)->unk_14.v & 0x40)) {
                func_800478B8(arg2);
                func_8016F580();
                return;
            }
        } else {
            ((S_8016F2E0_4 *)arg2)->unk_14.v |= 0x7000;
        }

        func_800A020C(((S_8016F2E0_3 *)actor)->unk_1C, (u8 *)arg2 + 0xC);
        func_8016F5A4();
        return;
    }

    new_flags = flags & 0x0800;
    if (new_flags != 0) {
        new_flags = flags & 0x8FFF;
    } else {
        new_flags = flags | 0x7000;
    }
    ((S_8016F2E0_4 *)arg2)->unk_14.n = new_flags;

    ((S_8016F2E0_5 *)arg1)->unk_00.at00.v += ((S_8016F2E0_5 *)arg1)->unk_0C;
    ((S_8016F2E0_5 *)arg1)->unk_04.at00.v += ((S_8016F2E0_5 *)arg1)->unk_10;

    if ((*(u16 *)((u8 *)arg0 + (0x98))) & 8) {
        (*(u8 *)((u8 *)arg0 + (0x9D))) = 0;
        func_8016F610();
        return;
    }

    ((S_8016F2E0_5 *)arg1)->unk_14 += (*(s8 *)((u8 *)arg0 + (0x9D))) * 0x14000;
    (*(volatile u8 *)((u8 *)arg0 + (0x9D)))++;
    (*(s32 *)((u8 *)arg0 + (0x90))) += ((S_8016F2E0_5 *)arg1)->unk_14;

    if (!((*(volatile u16 *)((u8 *)arg0 + (0x98))) & 4)) {
        floor = func_800BCB04(((S_8016F2E0_5 *)arg1)->unk_00.at02.v,
                              ((S_8016F2E0_5 *)arg1)->unk_04.at02.v,
                              (s16)(((S_8016F2E0_3 *)actor)->unk_88.u - 0x20));
        if ((s16)floor < 0x200) {
            actor_height = ((S_8016F2E0_3 *)actor)->unk_88.s;
            actor_height_u = ((S_8016F2E0_3 *)actor)->unk_88.u;
            if ((*(s16 *)((u8 *)arg0 + (0x92))) + actor_height < (s16)floor) {
                ((S_8016F2E0_3 *)actor)->unk_1C &= 0xF7FFFFFF;
                func_8016F6C0(actor_height_u, floor, actor_height);
                return;
            }
            if ((s16)floor >= actor_height) {
                (*(s32 *)((u8 *)arg0 + (0x90))) = 0;
                func_8016F6A8(actor_height_u, floor, actor_height);
                return;
            }

            (*(s16 *)((u8 *)arg0 + (0x92))) = floor - actor_height_u;
            ((S_8016F2E0_5 *)arg1)->unk_14 = 0;
            ((S_8016F2E0_3 *)actor)->unk_1C |= 0x08000000;
            (*(u8 *)((u8 *)arg0 + (0x9D))) = 0;

            if (((S_8016F2E0_3 *)actor)->unk_1C & 0x40000000) {
                ((S_8016F2E0_3 *)actor)->unk_1C &= 0xBFFFFFFF;
                floor = func_800BCB04((((S_8016F2E0_4 *)arg2)->unk_24 << 6) | 0x20,
                                      (((S_8016F2E0_4 *)arg2)->unk_25 << 6) | 0x20,
                                      (s16)(((S_8016F2E0_3 *)actor)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)arg0 + (0x92))) += ((S_8016F2E0_3 *)actor)->unk_88.u - floor;
                ((S_8016F2E0_3 *)actor)->unk_88.u = floor;
                func_8016F740();
                return;
            }
            goto finish;
        }
    }

    ((S_8016F2E0_3 *)actor)->unk_1C &= 0xF7FFFFFF;

finish:
    ((S_8016F2E0_5 *)arg1)->unk_0A = ((S_8016F2E0_3 *)actor)->unk_88.u + (*(u16 *)((u8 *)arg0 + (0x92)));
    ((S_8016F2E0_4 *)arg2)->unk_14.n |= 0x40;
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(direction_copy);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
}

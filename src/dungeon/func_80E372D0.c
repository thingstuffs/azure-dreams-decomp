#include "common.h"

typedef void (*Callback)(void *, void *, void *, void *);


extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s16 func_800BCB04(u16, u16, s16);

extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80170EE4[];
extern Callback D_80176680[];


typedef struct S_80170AD0_0 {
    u8 pad_00[0x1C];
    union { u32 u; s32 s; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80170AD0_0;   /* actor in func_80170AD0 */

typedef struct S_80170AD0_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80170AD0_1;   /* monster in func_80170AD0 */

typedef struct S_80170AD0_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170AD0_2;   /* motion in func_80170AD0 */

void func_80170AD0(void *a0, void *a1, void *a2)
{
    void *entity = a0;
    register void *motion ASM_REG("$21") = a1;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *monster ASM_REG("$20") = a2;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *actor ASM_REG("$17") = entity;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 direction_index ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 direction;
    register u32 old_direction_raw ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    Callback callback;
    u16 flags;
    s16 floor;
    s16 actor_height;
    u8 kind;

    if (D_80083462 & 0x2000) {
        Callback first_callback;

        ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        first_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (first_callback == (Callback)D_80170EE4) {
            first_callback(a0, a1, a2, a0);
        } else {
            (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        }
        return;
    }

    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(monster);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    old_direction_raw = (*(volatile u8 *)((u8 *)entity + 0x6D));
    kind = (*(u8 *)((u8 *)entity + 0x9A));
    old_direction_raw = old_direction_raw << 24;
    direction_index = (s32)old_direction_raw >> 24;
    if (kind != 0x17 && kind != 0x19) {
        if (func_800A9E70(entity, motion, monster, entity) != 0) {
            return;
        }
    }

    callback = (*(Callback *)((u8 *)entity + 0x8C));
    if (callback != 0) {
        callback(entity, motion, monster, actor);
    }

    D_80176680[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, monster, actor);

    if ((s16)direction_index != ((S_80170AD0_0 *)actor)->unk_6D) {
        func_800AA36C(entity, motion, monster, actor);
    }

    flags = ((S_80170AD0_1 *)monster)->unk_14;
    if (!(flags & 0x8000)) {
        s32 direction_value;

        direction_value =
            (D_80083228 + ((S_80170AD0_0 *)actor)->unk_2A + 0x100) >> 9;
        direction = direction_value & 7;
        direction_index = direction;

        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_index) {
            u8 *tile_map = ((S_80170AD0_1 *)monster)->unk_2C;
            func_80047738(monster, tile_map[direction_index],
                          ((S_80170AD0_1 *)monster)->unk_04);
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }

        if (D_8006CCF8[direction_index] != 0) {
            ((S_80170AD0_1 *)monster)->unk_14 |= 1;
        } else {
            ((S_80170AD0_1 *)monster)->unk_14 &= 0xFFFE;
        }

        if (!(((S_80170AD0_0 *)actor)->unk_1C.u & 0x20)) {
            if (!(((S_80170AD0_1 *)monster)->unk_14 & 0x40)) {
                func_800478B8(monster);
            }
        } else {
            ((S_80170AD0_1 *)monster)->unk_14 |= 0x7000;
        }

        func_800A020C(((S_80170AD0_0 *)actor)->unk_1C.s, (u8 *)monster + 0xC);
    } else {
        ((S_80170AD0_1 *)monster)->unk_14 =
            (flags & 0x0800) ? (flags & 0x8FFF) : (flags | 0x7000);
    }

    ((S_80170AD0_2 *)motion)->unk_00.at00.v += ((S_80170AD0_2 *)motion)->unk_0C;
    ((S_80170AD0_2 *)motion)->unk_04.at00.v += ((S_80170AD0_2 *)motion)->unk_10;

    if ((*(u16 *)((u8 *)entity + 0x98)) & 8) {
        (*(u8 *)((u8 *)entity + 0x9D)) = 0;
    } else {
        ((S_80170AD0_2 *)motion)->unk_14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity + 0x9D))++;
    }

    (*(s32 *)((u8 *)entity + 0x90)) += ((S_80170AD0_2 *)motion)->unk_14;

    if (!((*(u16 *)((u8 *)entity + 0x98)) & 4)) {
        floor = func_800BCB04(((S_80170AD0_2 *)motion)->unk_00.at02.v,
                              ((S_80170AD0_2 *)motion)->unk_04.at02.v,
                              (s16)(((S_80170AD0_0 *)actor)->unk_88.u - 0x20));
        if (floor < 0x200) {
            actor_height = ((S_80170AD0_0 *)actor)->unk_88.s;
            if ((*(s16 *)((u8 *)entity + 0x92)) + actor_height < floor) {
                ((S_80170AD0_0 *)actor)->unk_1C.u &= 0xF7FFFFFF;
            } else {
                
                if (floor >= actor_height) {
                    (*(s32 *)((u8 *)entity + 0x90)) = 0;
                } else {
                    (*(s16 *)((u8 *)entity + 0x92)) = floor - ((S_80170AD0_0 *)actor)->unk_88.u;
                }
    

                ((S_80170AD0_2 *)motion)->unk_14 = 0;
                (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                ((S_80170AD0_0 *)actor)->unk_1C.u |= 0x08000000;
            }

            if (((S_80170AD0_0 *)actor)->unk_1C.u & 0x40000000) {
                ((S_80170AD0_0 *)actor)->unk_1C.u &= 0xBFFFFFFF;
                floor = func_800BCB04(
                    (((S_80170AD0_1 *)monster)->unk_24 << 6) | 0x20,
                    (((S_80170AD0_1 *)monster)->unk_25 << 6) | 0x20,
                    (s16)(((S_80170AD0_0 *)actor)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity + 0x92)) +=
                    ((S_80170AD0_0 *)actor)->unk_88.u - floor;
                ((S_80170AD0_0 *)actor)->unk_88.u = floor;
            }
            goto finish;
        }
    }

    ((S_80170AD0_0 *)actor)->unk_1C.u &= 0xF7FFFFFF;

finish:
    ((S_80170AD0_2 *)motion)->unk_0A =
        ((S_80170AD0_0 *)actor)->unk_88.u + (*(u16 *)((u8 *)entity + 0x92));
    ((S_80170AD0_1 *)monster)->unk_14 |= 0x40;

    ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(direction_index);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
}

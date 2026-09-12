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

/* Updates actor callbacks, facing, movement, and floor contact. */
void func_80170AD0(void *entity_arg, void *motion_arg, void *monster_arg)
{
    register void *motion ASM_REG("$21") = motion_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *monster ASM_REG("$20") = monster_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *actor = entity_arg;
    register s32 direction_index ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 direction;
    register u32 old_direction_raw ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    Callback callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    u8 entity_kind;

    if (D_80083462 & 0x2000) {
        Callback early_callback;

        early_callback = (*(Callback *)((u8 *)entity_arg + 0x8C));
        if (early_callback == (Callback)D_80170EE4) {
            early_callback(entity_arg, motion_arg, monster_arg, entity_arg);
        } else {
            (*(u8 *)((u8 *)entity_arg + 0x71)) &= 0x7F;
        }
        return;
    }

    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(monster);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    old_direction_raw = (*(volatile u8 *)((u8 *)entity_arg + 0x6D));
    entity_kind = (*(u8 *)((u8 *)entity_arg + 0x9A));
    old_direction_raw = old_direction_raw << 24;
    direction_index = (s32)old_direction_raw >> 24;
    if (entity_kind != 0x17 && entity_kind != 0x19) {
        if (func_800A9E70(entity_arg, motion, monster, entity_arg) != 0) {
            return;
        }
    }

    callback = (*(Callback *)((u8 *)entity_arg + 0x8C));
    if (callback != 0) {
        callback(entity_arg, motion, monster, actor);
    }

    D_80176680[(*(u8 *)((u8 *)entity_arg + 0x9A))](entity_arg, motion, monster, actor);

    if ((s16)direction_index != ((S_80170AD0_0 *)actor)->unk_6D) {
        func_800AA36C(entity_arg, motion, monster, actor);
    }

    monster_flags = ((S_80170AD0_1 *)monster)->unk_14;
    if (!(monster_flags & 0x8000)) {
        s32 direction_sector;

        direction_sector =
            (D_80083228 + ((S_80170AD0_0 *)actor)->unk_2A + 0x100) >> 9;
        direction = direction_sector & 7;
        direction_index = direction;

        if ((*(s16 *)((u8 *)entity_arg + 0x94)) != direction_index) {
            u8 *direction_tiles = ((S_80170AD0_1 *)monster)->unk_2C;
            func_80047738(monster, direction_tiles[direction_index],
                          ((S_80170AD0_1 *)monster)->unk_04);
            (*(s16 *)((u8 *)entity_arg + 0x94)) = direction;
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
            (monster_flags & 0x0800) ? (monster_flags & 0x8FFF) : (monster_flags | 0x7000);
    }

    ((S_80170AD0_2 *)motion)->unk_00.at00.v += ((S_80170AD0_2 *)motion)->unk_0C;
    ((S_80170AD0_2 *)motion)->unk_04.at00.v += ((S_80170AD0_2 *)motion)->unk_10;

    if ((*(u16 *)((u8 *)entity_arg + 0x98)) & 8) {
        (*(u8 *)((u8 *)entity_arg + 0x9D)) = 0;
    } else {
        ((S_80170AD0_2 *)motion)->unk_14 += (*(s8 *)((u8 *)entity_arg + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity_arg + 0x9D))++;
    }

    (*(s32 *)((u8 *)entity_arg + 0x90)) += ((S_80170AD0_2 *)motion)->unk_14;

    if (!((*(u16 *)((u8 *)entity_arg + 0x98)) & 4)) {
        floor_height = func_800BCB04(((S_80170AD0_2 *)motion)->unk_00.at02.v,
                              ((S_80170AD0_2 *)motion)->unk_04.at02.v,
                              (s16)(((S_80170AD0_0 *)actor)->unk_88.u - 0x20));
        if (floor_height < 0x200) {
            actor_height = ((S_80170AD0_0 *)actor)->unk_88.s;
            if ((*(s16 *)((u8 *)entity_arg + 0x92)) + actor_height < floor_height) {
                ((S_80170AD0_0 *)actor)->unk_1C.u &= 0xF7FFFFFF;
            } else {
                if (floor_height >= actor_height) {
                    (*(s32 *)((u8 *)entity_arg + 0x90)) = 0;
                } else {
                    (*(s16 *)((u8 *)entity_arg + 0x92)) = floor_height - ((S_80170AD0_0 *)actor)->unk_88.u;
                }

                ((S_80170AD0_2 *)motion)->unk_14 = 0;
                (*(u8 *)((u8 *)entity_arg + 0x9D)) = 0;
                ((S_80170AD0_0 *)actor)->unk_1C.u |= 0x08000000;
            }

            if (((S_80170AD0_0 *)actor)->unk_1C.u & 0x40000000) {
                ((S_80170AD0_0 *)actor)->unk_1C.u &= 0xBFFFFFFF;
                floor_height = func_800BCB04(
                    (((S_80170AD0_1 *)monster)->unk_24 << 6) | 0x20,
                    (((S_80170AD0_1 *)monster)->unk_25 << 6) | 0x20,
                    (s16)(((S_80170AD0_0 *)actor)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity_arg + 0x92)) +=
                    ((S_80170AD0_0 *)actor)->unk_88.u - floor_height;
                ((S_80170AD0_0 *)actor)->unk_88.u = floor_height;
            }
            goto finish;
        }
    }

    ((S_80170AD0_0 *)actor)->unk_1C.u &= 0xF7FFFFFF;

finish:
    ((S_80170AD0_2 *)motion)->unk_0A =
        ((S_80170AD0_0 *)actor)->unk_88.u + (*(u16 *)((u8 *)entity_arg + 0x92));
    ((S_80170AD0_1 *)monster)->unk_14 |= 0x40;

    ASM_KEEP(direction_index);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
}

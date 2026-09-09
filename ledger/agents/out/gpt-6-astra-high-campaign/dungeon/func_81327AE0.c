#include "common.h"

typedef void (*Callback)(void *, void *, void *, void *);


extern void func_800353F4();
extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s32 func_800BCB04();

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

/* Updates actor callbacks, facing, movement, and floor contact. */
void func_8016F2E0(void *actor_arg, void *motion_arg, void *sprite_arg)
{
    void *entity = actor_arg;
    void *motion = motion_arg;
    register void *sprite = sprite_arg;
    register void *actor ASM_REG("$17") = entity;
    s32 old_direction;
    register s32 direction_copy ASM_REG("$21");
    Callback paused_callback;
    s32 floor_height;
    s16 actor_height;
    register u16 actor_height_u ASM_REG("$4");
    s32 direction_check;
    s32 direction_value;
    u8 *tile_slot;
    register u8 *direction_slot ASM_REG("$2");
    u16 facing_flags;
    u16 sprite_flags;
    u16 updated_flags;
    s32 previous_direction;
    s32 direction_tiles;
    s32 slot_index;
    u8 *actor_slot;
    void *actor_node;
    S_8016F2E0_2 *actor_record;

    if ((*(s32 *)((u8 *)entity + (0x14))) & 0x00800000) {
        (*(s32 *)((u8 *)entity + (0x14))) &= 0xFF7FFFFF;
        func_800353F4(&D_800F8BBC);
        (*(u8 *)((u8 *)entity + (0x6D))) = 0;
        (*(u8 *)((u8 *)entity + (0x9B))) = 0;
        (*(u8 *)((u8 *)entity + (0x71))) &= 0x7F;
    }

    if (D_80013714 & 8) {
        slot_index = 1;
        actor_slot = D_800E3D7C + 4;
        do {
            actor_node = ((S_8016F2E0_0 *)actor_slot)->unk_AC;
            if (actor_node != 0) {
                actor_record = ((S_8016F2E0_1_pre *)actor_node)[-1].unk_00;
                actor_record->unk_14 &= 0xFFBF;
            }
            slot_index--;
            actor_slot -= 4;
        } while (slot_index >= 0);
    }

    if (D_80083462 & 0x2000) {
        paused_callback = (*(Callback *)((u8 *)entity + (0x8C)));
        if (paused_callback == (Callback)&D_8016F78C) {
            paused_callback(entity, motion, sprite, actor);
            return;
        }
        ((S_8016F2E0_3 *)actor)->unk_71 &= 0x7F;
        return;
    }

    old_direction = ((S_8016F2E0_3 *)actor)->unk_6D.v;
    old_direction = (old_direction << 24) >> 24;
    if (func_800A9E70(entity, motion, sprite, actor) != 0) {
        return;
    }

    {
        Callback update_callback = (*(Callback *)((u8 *)entity + (0x8C)));
        if (update_callback != 0) {
            update_callback(entity, motion, sprite, actor);
        }
    }
    D_80174AD4[(*(u8 *)((u8 *)entity + (0x9A)))](entity, motion, sprite, actor);

    direction_check = (s16)old_direction;
    if (direction_check != ((S_8016F2E0_3 *)actor)->unk_6D.n) {
        func_800AA36C(entity, motion, sprite, actor);
    }

    sprite_flags = ((S_8016F2E0_4 *)sprite)->unk_14.n;
    updated_flags = sprite_flags & 0x8000;
    if (updated_flags == 0) {
        old_direction = ((D_80083228 + ((S_8016F2E0_3 *)actor)->unk_2A + 0x100) >> 9) & 7;
        previous_direction = (*(s16 *)((u8 *)entity + (0x94)));
        ASM_SCHED_BARRIER();
        direction_value = old_direction;
        ASM_KEEP(old_direction);
        direction_copy = old_direction;
        if (previous_direction != direction_value) {
            direction_tiles = ((S_8016F2E0_4 *)sprite)->unk_2C;
            if (direction_tiles != 0) {
                tile_slot = (u8 *)direction_tiles + direction_value;
                func_80047738(sprite,
                    *tile_slot,
                    ((S_8016F2E0_4 *)sprite)->unk_04);
            }
            (*(s16 *)((u8 *)entity + (0x94))) = old_direction;
        }

        direction_slot = D_8006CCF8 + direction_copy;
        ASM_KEEP(direction_slot);
        if (*direction_slot != 0) {
            facing_flags = ((S_8016F2E0_4 *)sprite)->unk_14.n;
            facing_flags |= 1;
        } else {
            facing_flags = ((S_8016F2E0_4 *)sprite)->unk_14.v & 0xFFFE;
        }
        ((S_8016F2E0_4 *)sprite)->unk_14.v = facing_flags;
        if (!(((S_8016F2E0_3 *)actor)->unk_1C & 0x20)) {
            if (!(((S_8016F2E0_4 *)sprite)->unk_14.v & 0x40)) {
                func_800478B8(sprite);
            }
        } else {
            ((S_8016F2E0_4 *)sprite)->unk_14.v |= 0x7000;
        }

        func_800A020C(((S_8016F2E0_3 *)actor)->unk_1C, (u8 *)sprite + 0xC);
    } else {
        updated_flags = sprite_flags & 0x0800;
        if (updated_flags != 0) {
            updated_flags = sprite_flags & 0x8FFF;
        } else {
            updated_flags = sprite_flags | 0x7000;
        }
        ((S_8016F2E0_4 *)sprite)->unk_14.n = updated_flags;
    }

    ((S_8016F2E0_5 *)motion)->unk_00.at00.v += ((S_8016F2E0_5 *)motion)->unk_0C;
    ((S_8016F2E0_5 *)motion)->unk_04.at00.v += ((S_8016F2E0_5 *)motion)->unk_10;

    if ((*(u16 *)((u8 *)entity + (0x98))) & 8) {
        (*(u8 *)((u8 *)entity + (0x9D))) = 0;
    } else {
        ((S_8016F2E0_5 *)motion)->unk_14 += (*(s8 *)((u8 *)entity + (0x9D))) * 0x14000;
        (*(volatile u8 *)((u8 *)entity + (0x9D)))++;
    }
    (*(s32 *)((u8 *)entity + (0x90))) += ((S_8016F2E0_5 *)motion)->unk_14;

    if (!((*(volatile u16 *)((u8 *)entity + (0x98))) & 4)) {
        floor_height = func_800BCB04(((S_8016F2E0_5 *)motion)->unk_00.at02.v,
                              ((S_8016F2E0_5 *)motion)->unk_04.at02.v,
                              (s16)(((S_8016F2E0_3 *)actor)->unk_88.u - 0x20));
        if ((s16)floor_height < 0x200) {
            actor_height = ((S_8016F2E0_3 *)actor)->unk_88.s;
            actor_height_u = (*(volatile u16 *)((u8 *)actor + 0x88));
            if ((*(s16 *)((u8 *)entity + (0x92))) + actor_height < (s16)floor_height) {
                ((S_8016F2E0_3 *)actor)->unk_1C &= 0xF7FFFFFF;
            } else {
                if ((s16)floor_height >= actor_height) {
                    (*(s32 *)((u8 *)entity + (0x90))) = 0;
                } else {
                    (*(s16 *)((u8 *)entity + (0x92))) = floor_height - actor_height_u;
                    ASM_KEEP(actor_height_u);
                }
                ((S_8016F2E0_5 *)motion)->unk_14 = 0;
                ((S_8016F2E0_3 *)actor)->unk_1C |= 0x08000000;
                (*(u8 *)((u8 *)entity + (0x9D))) = 0;
            }

            if (((S_8016F2E0_3 *)actor)->unk_1C & 0x40000000) {
                ((S_8016F2E0_3 *)actor)->unk_1C &= 0xBFFFFFFF;
                floor_height = func_800BCB04((((S_8016F2E0_4 *)sprite)->unk_24 << 6) | 0x20,
                                      (((S_8016F2E0_4 *)sprite)->unk_25 << 6) | 0x20,
                                      (s16)(((S_8016F2E0_3 *)actor)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity + (0x92))) += ((S_8016F2E0_3 *)actor)->unk_88.u - floor_height;
                ((S_8016F2E0_3 *)actor)->unk_88.u = floor_height;
            }
            goto finish;
        }
    }

    ((S_8016F2E0_3 *)actor)->unk_1C &= 0xF7FFFFFF;

finish:
    ((S_8016F2E0_5 *)motion)->unk_0A = ((S_8016F2E0_3 *)actor)->unk_88.u + (*(u16 *)((u8 *)entity + (0x92)));
    ((S_8016F2E0_4 *)sprite)->unk_14.n |= 0x40;
}

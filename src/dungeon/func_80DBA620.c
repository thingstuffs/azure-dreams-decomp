#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80171E20_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80171E20_0;   /* arg0 in func_80171E20 */

typedef struct S_80171E20_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80171E20_1;   /* arg3 in func_80171E20 */

typedef struct S_80171E20_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_80171E20_2;   /* arg2 in func_80171E20 */


typedef struct S_80171E20_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80171E20_4;   /* actor in func_80171E20 */

typedef struct S_80171E20_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171E20_5;   /* origin in func_80171E20 */



typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0818(u8, u8, u8, u8, s16 *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);

extern void func_80172384(void *, void *, void *, void *);
extern void func_801725C8(void *, void *, void *, void *);
extern s32 func_80172D74(void *, void *, void *, void *);
extern void func_80172F38(void *, void *, void *, void *);
extern s32 func_80173050(void *, void *, void *, s32);
extern void func_80174890(void *, void *, void *, void *);
extern void func_80174A9C(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_801753BC[];
extern u8 D_801753C4[];
extern u8 D_801753F4[];
extern u8 D_801753FC[];
extern u8 D_80175404[];

/* Updates an actor's dungeon behavior, facing, and animation. */
void func_80171E20(void *actor_in, void *actor_data_in, void *sprite_in, void *status_in)
{
    static void *const action_labels[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12
    };
    void *actor = actor_in;
    void *actor_data = actor_data_in;
    void *sprite = sprite_in;
    register void *status ASM_REG("$18") = status_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u32 initial_flags = D_80083462;
    s16 distance;
    s32 status_flags;
    s32 action_index;
    s8 tile_id;
    s16 facing;
    u16 action_flags;
    u8 *anim_table;
    void *target;
    void *player;

    if (initial_flags & 0x1000) {
        ((S_80171E20_0 *)actor)->unk_9A = 14;
        func_80172384(actor_in, actor_data_in, sprite_in, status_in);
        return;
    }

    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(actor_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(sprite);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(status);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    if (((S_80171E20_1 *)status)->unk_25 == 0) {
        func_800AA79C(actor, actor_data, sprite, status);
        if (((S_80171E20_2 *)sprite)->unk_2C == D_80175404) {
            return;
        }
        {
            u8 *early_anim_table = D_801753FC;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = early_anim_table;
            func_80047784(
                sprite,
                early_anim_table[((D_80083228 + ((S_80171E20_1 *)status)->unk_2A + 0x100) >> 9) & 7],
                0);
            return;
        }
    }

    if (((S_80171E20_1 *)status)->unk_1C & 0x200) {
        if (((S_80171E20_2 *)sprite)->unk_2C == D_80175404) {
            ((S_80171E20_0 *)actor)->unk_9A = 13;
            ((S_80171E20_0 *)actor)->unk_9B = 1;
            ((S_80171E20_0 *)actor)->unk_8C = 0;
            ((S_80171E20_1 *)status)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, actor_data, sprite, D_801753FC) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (((S_80171E20_1 *)status)->unk_1C & 0x100) {
            func_800AA258(actor, actor_data, sprite, status);
            return;
        }

        {
            u8 current_state = ((S_80171E20_0 *)actor)->unk_9A;
            u32 next_state = 14;

            if (current_state != next_state) {
                anim_table = D_801753BC;
                if (((S_80171E20_2 *)sprite)->unk_2C != anim_table) {
                    (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
                    func_80047784(
                        sprite,
                        anim_table[((D_80083228 + ((S_80171E20_1 *)status)->unk_2A + 0x100) >> 9) & 7],
                        0);
                }
                ((S_80171E20_0 *)actor)->unk_9A = next_state;
            }
        }

        ((S_80171E20_0 *)actor)->unk_98 &= 0xFFF3;

        if (((S_80171E20_1 *)status)->unk_64 != 0) {
            if (func_800AA6B4(actor, actor_data, sprite, D_801753C4) != 0) {
                return;
            }
        }

        if (((S_80171E20_1 *)status)->unk_1C & 0x80000) {
            func_800AA888(actor, actor_data, sprite, status);
            func_80174890(actor, actor_data, sprite, status);
            return;
        }

        if ((s16)func_800A1C58(status) != 0) {
            func_800AAB10(actor, actor_data, sprite, status);
        }
    }

    tile_id = func_8009FB34(((S_80171E20_2 *)sprite)->unk_24.at00.v, ((S_80171E20_2 *)sprite)->unk_24.at01.v);
    ((S_80171E20_2 *)sprite)->unk_26 = tile_id;

    if (((S_80171E20_1 *)status)->unk_6D > 0) {
        if (((S_80171E20_1 *)status)->unk_1C & 0x20) {
            goto jt_c12;
        }
        if (((S_80171E20_2 *)sprite)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto jt_default;
        }
        action_flags = ((S_80171E20_1 *)status)->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(
                        status, (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80173050(actor, actor_data, sprite, 0) == 0) {
                return;
            }
            action_flags = ((S_80171E20_1 *)status)->unk_46 | 0x4000;
            ((S_80171E20_1 *)status)->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                goto jt_default;
            }
        }

        action_index = (((S_80171E20_1 *)status)->unk_46 & 0x3FFF) - 1;
        if ((u32)action_index >= 12U) {
            goto jt_default;
        }
        (void)action_labels;
        goto *D_80170808[action_index];

jt_c9:
        if ((s16)func_80172D74(actor, actor_data, sprite, status) != 0) {
            return;
        }
        func_80172F38(actor, actor_data, sprite, status);
        return;

jt_c8:
        func_80174A9C(actor, actor_data, sprite, status);
        return;

jt_c5:
jt_c6:
jt_c7:
        facing = func_800A0818(
            ((S_80171E20_2 *)sprite)->unk_24.at00.v, ((S_80171E20_2 *)sprite)->unk_24.at01.v,
            D_80082E80[0x24], D_80082E80[0x25], &distance);
        player = D_800814A8;
        ((S_80171E20_1 *)status)->unk_2A = facing;
        if (((S_80171E20_4 *)player)->unk_9A == 0x11) {
            goto jt_call;
        }

jt_c12:
        func_800A9A0C(status);
        return;

jt_c1:
jt_c2:
jt_c3:
jt_call:
        func_800AAF00(actor, actor_data, sprite, D_801753F4, func_80171E20);
        return;

jt_c4:
jt_c10:
jt_c11:
jt_default:
        func_801725C8(actor, actor_data, sprite, status);
        return;
    }

    status_flags = ((S_80171E20_1 *)status)->unk_1C;
    if (!(status_flags & 0x2000)) {
        if ((tile_id < 0) ||
            !(((DungeonRecord *)D_800E2970)[tile_id].flags & 2)) {
            if (!(status_flags & 0x430)) {
                target = D_80082E80;
                if ((s16)func_8009FD7C(
                        ((S_80171E20_2 *)sprite)->unk_24.at00.v, ((S_80171E20_2 *)sprite)->unk_24.at01.v,
                        ((S_80171E20_5 *)target)->unk_24, ((S_80171E20_5 *)target)->unk_25) != 0) {
                    ((S_80171E20_1 *)status)->unk_2A = func_800A0818(
                        ((S_80171E20_2 *)sprite)->unk_24.at00.v, ((S_80171E20_2 *)sprite)->unk_24.at01.v,
                        ((S_80171E20_5 *)target)->unk_24, ((S_80171E20_5 *)target)->unk_25, &distance);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_80171E20_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_801753BC;
    if (((S_80171E20_2 *)sprite)->unk_2C == anim_table) {
        return;
    }

assign_table:
    (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
    func_80047784(
        sprite,
        anim_table[((D_80083228 + ((S_80171E20_1 *)status)->unk_2A + 0x100) >> 9) & 7],
        0);
}

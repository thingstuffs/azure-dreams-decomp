#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800814A8.h"


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171510(void *, void *, void *, void *);
extern void func_80171768(void *, void *, void *, void *);
extern s32 func_80171F24(void *, void *, void *, void *);
extern void func_80172110(void *, void *, void *, void *);
extern s32 func_80172228(void *, void *, void *, s32);
extern void func_80173900(void *, void *, void *, void *);
extern void func_80173AD4(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern s32 D_80170F68;
extern u8 D_80173FB8[];
extern u8 D_80173FC0[];
extern u8 D_80173FF0[];
extern u8 D_80173FF8[];
extern u8 D_80174000[];



typedef struct S_80170F68_1 {
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
} S_80170F68_1;   /* arg3 in func_80170F68 */

typedef struct S_80170F68_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80170F68_2;   /* arg2 in func_80170F68 */


typedef struct S_80170F68_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80170F68_4;   /* origin in func_80170F68 */

typedef struct S_80170F68_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170F68_5;   /* global in func_80170F68 */

/* Updates a dungeon actor's behavior, facing, and animation from its current state. */
void func_80170F68(void *actor_arg, void *context_arg, void *map_object_arg, void *actor_state_arg)
{
    void *actor;
    void *context;
    void *map_object;
    register void *actor_state ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *anim_table;
    s32 tile_id;
    s32 distance;
    u32 initial_flags = D_80083462;

    actor = actor_arg;
    context = context_arg;
    map_object = map_object_arg;
    actor_state = actor_state_arg;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        func_80171510(actor, context, map_object, actor_state);
        return;
    }

    ASM_KEEP(context);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(map_object);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(actor_state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    if (((S_80170F68_1 *)actor_state)->unk_25 == 0) {
        u8 *inactive_anims;

        func_800AA79C(actor, context, map_object, actor_state);
        if (((S_80170F68_2 *)map_object)->unk_2C != D_80174000) {
            inactive_anims = D_80173FF8;
            (*(void * *)((u8 *)map_object + (0x2C))) = inactive_anims;
            func_80047784(map_object,
                inactive_anims[((D_80083228 + ((S_80170F68_1 *)actor_state)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        ((Rec_func_800A9E70_arg0 *)actor)->unk_AE = 0;
        func_80042B68(actor_state, 0x1A);
        return;
    }

    if (((S_80170F68_1 *)actor_state)->unk_1C & 0x200) {
        if (((S_80170F68_2 *)map_object)->unk_2C == D_80174000) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            ((S_80170F68_1 *)actor_state)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, context, map_object, D_80173FF8)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((S_80170F68_1 *)actor_state)->unk_1C & 0x100) {
            func_800AA258(actor, context, map_object, actor_state);
            return;
        }

        ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
            u8 next_state = 0xE;

            anim_table = D_80173FB8;
            if (((S_80170F68_2 *)map_object)->unk_2C != anim_table) {
                (*(void * *)((u8 *)map_object + (0x2C))) = anim_table;
                func_80047784(map_object,
                    anim_table[((D_80083228 + ((S_80170F68_1 *)actor_state)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = next_state;
        }

        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF3;
        if (((S_80170F68_1 *)actor_state)->unk_64 != 0) {
            if (func_800AA6B4(actor, context, map_object, D_80173FC0)) {
                return;
            }
        }

        if (((S_80170F68_1 *)actor_state)->unk_1C & 0x80000) {
            func_800AA888(actor, context, map_object, actor_state);
            func_80173900(actor, context, map_object, actor_state);
            return;
        }

        if ((s16)func_800A1C58(actor_state) != 0) {
            func_800AAB10(actor, context, map_object, actor_state);
        }
    }

    tile_id = func_8009FB34(((S_80170F68_2 *)map_object)->unk_24.at00.v, ((S_80170F68_2 *)map_object)->unk_24.at01.v);
    ((S_80170F68_2 *)map_object)->unk_26 = tile_id;

    if (((S_80170F68_1 *)actor_state)->unk_6D > 0) {
        if (((S_80170F68_1 *)actor_state)->unk_1C & 0x20) {
            goto special_cleanup;
        }
        if (((S_80170F68_2 *)map_object)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto ordinary_cleanup;
        }
        if (!(((S_80170F68_1 *)actor_state)->unk_46 & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(actor_state,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172228(actor, context, map_object, 0) == 0) {
                return;
            }
            ((S_80170F68_1 *)actor_state)->unk_46 |= 0x4000;
            if (!(((S_80170F68_1 *)actor_state)->unk_46 & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

#ifdef __mips__
        {
            static void *volatile dispatch_labels[] = {
                &&aaf_cleanup, &&aaf_cleanup, &&aaf_cleanup,
                &&extra_cleanup,
                &&coords_case, &&coords_case, &&coords_case,
                &&handler_case, &&handler_case,
                &&ordinary_cleanup, &&ordinary_cleanup,
                &&special_cleanup,
            };
            s32 dispatch_index;

            dispatch_index = (((S_80170F68_1 *)actor_state)->unk_46 & 0x3FFF) - 1;
            if ((u32)dispatch_index >= 12) {
                goto ordinary_cleanup;
            }
            goto *D_80170808[dispatch_index];
        }
handler_case:
#else
        switch (((S_80170F68_1 *)actor_state)->unk_46 & 0x3FFF) {
        case 8:
        case 9:
#endif
            if ((s16)func_80171F24(actor, context, map_object, actor_state) == 0) {
                func_80172110(actor, context, map_object, actor_state);
                return;
            }
            return;

#ifdef __mips__
extra_cleanup:
#else
        case 4:
#endif
            func_80173AD4(actor, context, map_object, actor_state);
            return;

#ifdef __mips__
coords_case:
#else
        case 5:
        case 6:
        case 7:
#endif
        {
            u8 *player_pos = D_80082E80;
            void *player;
            s32 direction;

            direction = func_800A0818(
                ((S_80170F68_2 *)map_object)->unk_24.at00.v, ((S_80170F68_2 *)map_object)->unk_24.at01.v,
                ((S_80170F68_4 *)player_pos)->unk_24, ((S_80170F68_4 *)player_pos)->unk_25,
                &distance);
            player = D_800814A8;
            ((S_80170F68_1 *)actor_state)->unk_2A = direction;
            if (((S_80170F68_5 *)player)->unk_9A == 0x11) {
                goto aaf_cleanup;
            }
            goto special_cleanup;
        }
#ifndef __mips__
        case 1:
        case 2:
        case 3:
            goto aaf_cleanup;

        case 12:
            goto special_cleanup;

        case 10:
        case 11:
        default:
            goto ordinary_cleanup;
        }
#endif

special_cleanup:
        func_800A9A0C(actor_state);
        return;

aaf_cleanup:
        func_800AAF00(actor, context, map_object, D_80173FF0, &D_80170F68);
        return;

ordinary_cleanup:
        func_80171768(actor, context, map_object, actor_state);
        return;
    } else if (!(((S_80170F68_1 *)actor_state)->unk_1C & 0x2000)) {
        s32 record_index = (s8)tile_id;

        if ((record_index < 0) || !(((DungeonRecord *)D_800E2970)[record_index].flags & 2)) {
            if (!(((S_80170F68_1 *)actor_state)->unk_1C & 0x430)) {
                u8 *player_pos = D_80082E80;

                if ((s16)func_8009FD7C(((S_80170F68_2 *)map_object)->unk_24.at00.v,
                        ((S_80170F68_2 *)map_object)->unk_24.at01.v, ((S_80170F68_4 *)player_pos)->unk_24,
                        ((S_80170F68_4 *)player_pos)->unk_25) != 0) {
                    ((S_80170F68_1 *)actor_state)->unk_2A = func_800A0818(
                        ((S_80170F68_2 *)map_object)->unk_24.at00.v, ((S_80170F68_2 *)map_object)->unk_24.at01.v,
                        ((S_80170F68_4 *)player_pos)->unk_24, ((S_80170F68_4 *)player_pos)->unk_25,
                        &distance);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_80170F68_2 *)map_object)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80173FB8;
    if (((S_80170F68_2 *)map_object)->unk_2C == anim_table) {
        return;
    }
    (*(void * *)((u8 *)map_object + (0x2C))) = anim_table;
    func_80047784(map_object,
        ((((D_80083228 + ((S_80170F68_1 *)actor_state)->unk_2A + 0x100) >> 9) & 7) + anim_table)[0],
        0);
}

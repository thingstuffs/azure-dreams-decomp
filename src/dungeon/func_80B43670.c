#include "common.h"
#include "records/Rec_D_800814A8.h"


typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0818();
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern s32 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);

extern void func_801713D4(void *);
extern void func_8017162C(void *, void *, void *, void *);
extern s32 func_80171DD8(void *, void *, void *, void *);
extern void func_80171F9C(void *, void *, void *, void *);
extern s32 func_801720B4(void *, void *, void *, s32);
extern void func_80173D64(void *, void *, void *, void *);
extern void func_8017526C(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80170E70[];
extern u8 D_80175A54[];
extern u8 D_80175A5C[];
extern u8 D_80175A8C[];
extern u8 D_80175A94[];
extern u8 D_80175A9C[];


typedef struct S_80170E70_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x66];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80170E70_0;   /* arg0 in func_80170E70 */

typedef struct S_80170E70_1 {
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
} S_80170E70_1;   /* arg3 in func_80170E70 */

typedef struct S_80170E70_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80170E70_2;   /* arg2 in func_80170E70 */


typedef struct S_80170E70_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170E70_4;   /* owner in func_80170E70 */

typedef struct S_80170E70_5 {
    u8 pad_00[0x10];
    s16 * unk_10;
} S_80170E70_5;   /* stack_base in func_80170E70 */

/* Update the actor's dungeon behavior, facing, and animation for its current state. */
void func_80170E70(void *entity_in, void *context_in, void *sprite_in, void *actor_in)
{
    u8 *effect_table;
    static void *const action_labels[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12
    };
    void *entity = entity_in;
    void *context = context_in;
    void *sprite = sprite_in;
    register void *actor ASM_REG("$18") = actor_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 next_state;
#ifdef __mips__
    register u8 *stack_base ASM_REG("$29");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
#endif
    s16 path_distance;
    s16 target_angle;
    s32 actor_flags;
    s32 action_index;
    s8 tile_id;
    s32 tile_x;
    s32 tile_y;
    s32 current_state;
    u16 action_flags;
    void *continuation;
    void *owner;

    if (D_80083462 & 0x1000) {
        ((S_80170E70_0 *)entity)->unk_9A = 14;
        func_801713D4(entity);
        return;
    }

    ASM_KEEP(context);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    if (((S_80170E70_1 *)actor)->unk_25 == 0) {
        func_800AA79C(entity, context, sprite, actor);
        if (((S_80170E70_2 *)sprite)->unk_2C == D_80175A9C) {
            return;
        }
        {
            u8 *effects = D_80175A94;
            (*(void * *)((u8 *)sprite + (0x2C))) = effects;
            func_80047784(
                sprite,
                effects[((D_80083228 + ((S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        return;
    }

    if (((S_80170E70_1 *)actor)->unk_1C & 0x200) {
        if (((S_80170E70_2 *)sprite)->unk_2C == D_80175A9C) {
            ((S_80170E70_0 *)entity)->unk_9A = 13;
            ((S_80170E70_0 *)entity)->unk_9B = 1;
            ((S_80170E70_0 *)entity)->unk_8C = 0;
            ((S_80170E70_1 *)actor)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(entity, context, sprite, D_80175A94) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (((S_80170E70_1 *)actor)->unk_1C & 0x100) {
            func_800AA258(entity, context, sprite, actor);
            return;
        }

        current_state = ((S_80170E70_0 *)entity)->unk_9A;
        next_state = 14;
        if (current_state != next_state) {
            u8 *effect = D_80175A54;

            if (((S_80170E70_2 *)sprite)->unk_2C != effect) {
                (*(void * *)((u8 *)sprite + (0x2C))) = effect;
                func_80047784(
                    sprite,
                    effect[((D_80083228 + ((S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
            ((S_80170E70_0 *)entity)->unk_9A = next_state;
        }

        ((S_80170E70_0 *)entity)->unk_98 &= 0xFFF3;
        if (((S_80170E70_1 *)actor)->unk_64 != 0) {
            if (func_800AA6B4(entity, context, sprite, D_80175A5C) != 0) {
                return;
            }
        }

        if (((S_80170E70_1 *)actor)->unk_1C & 0x80000) {
            func_800AA888(entity, context, sprite, actor);
            func_80173D64(entity, context, sprite, actor);
            return;
        }

        if ((s16)func_800A1C58(actor) != 0) {
            if ((s16)func_800AAB10(entity, context, sprite, actor) != 0) {
                func_8017526C(entity, context, sprite, actor);
            }
        }
    }

    tile_id = func_8009FB34(((S_80170E70_2 *)sprite)->unk_24.at00.v, ((S_80170E70_2 *)sprite)->unk_24.at01.v);
    ((S_80170E70_2 *)sprite)->unk_26 = tile_id;

    if (((S_80170E70_1 *)actor)->unk_6D > 0) {
        if (((S_80170E70_1 *)actor)->unk_1C & 0x20) {
            goto jt_c12;
        }
        if (((S_80170E70_2 *)sprite)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto jt_default;
        }

        action_flags = ((S_80170E70_1 *)actor)->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(
                        actor, (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_801720B4(entity, context, sprite, 0) == 0) {
                return;
            }
            action_flags = ((S_80170E70_1 *)actor)->unk_46 | 0x4000;
            ((S_80170E70_1 *)actor)->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                goto jt_default;
            }
        }

        action_index = (((S_80170E70_1 *)actor)->unk_46 & 0x3FFF) - 1;
        if ((u32)action_index >= 12U) {
            goto jt_default;
        }
        (void)action_labels;
        goto *D_80170808[action_index];

jt_c8:
jt_c9:
        if ((s16)func_80171DD8(entity, context, sprite, actor) != 0) {
            return;
        }
        func_80171F9C(entity, context, sprite, actor);
        return;

jt_c5:
jt_c6:
jt_c7:
        target_angle = func_800A0818(
            ((S_80170E70_2 *)sprite)->unk_24.at00.v, ((S_80170E70_2 *)sprite)->unk_24.at01.v,
            D_80082E80[0x24], D_80082E80[0x25], &path_distance);
        owner = D_800814A8;
        ((S_80170E70_1 *)actor)->unk_2A = target_angle;
        if (((S_80170E70_4 *)owner)->unk_9A == 0x11) {
            continuation = D_80170E70;
            goto jt_call;
        }

jt_c12:
        func_800A9A0C(actor);
        return;

jt_c1:
jt_c2:
jt_c3:
        continuation = D_80170E70;

jt_call:
        func_800AAF00(entity, context, sprite, D_80175A8C, continuation);
        return;

jt_c4:
jt_c10:
jt_c11:
jt_default:
        func_8017162C(entity, context, sprite, actor);
        return;
    }

    actor_flags = ((S_80170E70_1 *)actor)->unk_1C;
    if ((actor_flags & 0x2000) == 0) {
        if ((tile_id < 0) ||
            ((((DungeonRecord *)D_800E2970)[tile_id].flags & 2) == 0)) {
            if ((actor_flags & 0x430) == 0) {
                entity = (void *)((u32)&D_80082E80);
                if ((s16)func_8009FD7C(
                        ((S_80170E70_2 *)sprite)->unk_24.at00.v, ((S_80170E70_2 *)sprite)->unk_24.at01.v,
                        ((S_80170E70_0 *)entity)->unk_24, ((S_80170E70_0 *)entity)->unk_25) != 0) {
#ifdef __mips__
                    tile_x = ((S_80170E70_2 *)sprite)->unk_24.at00.v;
                    tile_y = ((S_80170E70_2 *)sprite)->unk_24.at01.v;
                    ((S_80170E70_5 *)stack_base)->unk_10 = &path_distance;
                    ((S_80170E70_1 *)actor)->unk_2A = func_800A0818(
                        tile_x, tile_y,
                        ((S_80170E70_0 *)entity)->unk_24, ((S_80170E70_0 *)entity)->unk_25);
#else
                    ((S_80170E70_1 *)actor)->unk_2A = func_800A0818(
                        ((S_80170E70_2 *)sprite)->unk_24.at00.v, ((S_80170E70_2 *)sprite)->unk_24.at01.v,
                        ((S_80170E70_0 *)entity)->unk_24, ((S_80170E70_0 *)entity)->unk_25, &path_distance);
#endif
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_80170E70_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    effect_table = D_80175A54;
    if (((S_80170E70_2 *)sprite)->unk_2C == effect_table) {
        return;
    }
    ASM_KEEP(sprite);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    {
        u8 *effects = effect_table;
        (*(void * *)((u8 *)sprite + (0x2C))) = effects;
        func_80047784(
            sprite,
            effects[((D_80083228 + ((S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
    }
}

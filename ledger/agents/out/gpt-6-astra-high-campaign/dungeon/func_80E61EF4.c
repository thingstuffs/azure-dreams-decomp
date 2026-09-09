#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, s32, s32);
extern s32 rand(void);
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
extern void func_80171CA8(void *, void *, void *);
extern void func_80171EEC(void *, void *, void *, void *);
extern s32 func_801726B0(void *, void *, void *, void *);
extern void func_80172874(void *, void *, void *, void *);
extern s32 func_8017298C(void *, void *, void *, s32);
extern void func_8017430C(void *, void *, void *, void *);
extern void func_80174FE4(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_801716F4[];
extern u8 D_80175554[];
extern u8 D_8017555C[];
extern u8 D_80175564[];
extern u8 D_80175594[];
extern u8 D_8017559C[];
extern u8 D_801755A4[];




typedef struct S_801716F4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_801716F4_2;   /* arg2 in func_801716F4 */


typedef struct S_801716F4_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801716F4_4;   /* origin in func_801716F4 */

typedef struct S_801716F4_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_801716F4_5;   /* player in func_801716F4 */

/* Updates a dungeon actor's behavior, facing, and directional animation. */
void func_801716F4(void *actor_arg, void *context_arg, void *sprite_arg, void *entity_arg)
{
    static void *const dispatch_labels[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    void *actor;
    void *context;
    void *sprite;
    register void *entity ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *anim_table;
    register u8 *next_table ASM_REG("$5"); /* MATCH: both paths merge their table pointer in a1. */
    s32 room_id;
    s32 distance;
    u32 initial_flags = D_80083462;

    actor = actor_arg;
    context = context_arg;
    sprite = sprite_arg;
    entity = entity_arg;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        func_80171CA8(actor, context, sprite);
        return;
    }

    ASM_KEEP(context);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    if (((Rec_D_800E3D7C *)entity)->unk_24.at01_u8.v == 0) {
        func_800AA79C(actor, context, sprite, entity);
        if (((S_801716F4_2 *)sprite)->unk_2C != D_801755A4) {
            next_table = D_8017559C;
            goto set_table;
        }
        return;
    }

    if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x200) {
        if (((S_801716F4_2 *)sprite)->unk_2C == D_801755A4) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_8017559C)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x100) {
            func_800AA258(actor, context, sprite, entity);
            return;
        }

        ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
            u8 idle_state = 0xE;

            anim_table = D_80175554;
            if (((S_801716F4_2 *)sprite)->unk_2C != anim_table) {
                (*(void * *)((u8 *)sprite + (0x2C))) = anim_table;
                func_80047784(sprite,
                    anim_table[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_s16 = 0;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v = (rand() & 0x1F) + 0xF;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = idle_state;
        }

        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF3;
        if (((Rec_D_800E3D7C *)entity)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80175564)) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x80000) {
            u8 *event_table;
            u8 *anim_entry;
            void *anim_sprite;
            s32 direction_index;

            func_800AA888(actor, context, sprite, entity);
            func_8017430C(actor, context, sprite, entity);
            event_table = D_8017555C;
            (*(void * *)((u8 *)sprite + (0x2C))) = event_table;
            direction_index = ((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7;
            anim_sprite = sprite;
#ifdef __mips__
            anim_entry = (u8 *)((u32)direction_index + (u32)event_table);
#else
            anim_entry = event_table + direction_index;
#endif
            func_80047784(anim_sprite, anim_entry[0], 0);
            ((Rec_func_800A9E70_arg0 *)actor)->unk_90.at00_s32.v = 0;
            return;
        }

        if ((func_800A1C58(entity) << 16) != 0) {
            func_800AAB10(actor, context, sprite, entity);
        }
    }

    room_id = func_8009FB34(((S_801716F4_2 *)sprite)->unk_24.at00.v, ((S_801716F4_2 *)sprite)->unk_24.at01.v);
    ((S_801716F4_2 *)sprite)->unk_26 = room_id;

    if (((Rec_D_800E3D7C *)entity)->unk_6D.as_s8 > 0) {
        u16 action_flags;

        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x20) {
            goto case_12;
        }
        if (((S_801716F4_2 *)sprite)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(entity,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8017298C(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v | 0x4000;
            ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v = action_flags;
            if (!(action_flags & 0x8000)) {
                goto generic;
            }
        }

        action_flags = ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x3FFF;
        if ((u32)(action_flags - 1) >= 12) {
            goto generic;
        }
        (void)dispatch_labels;
        goto *D_80170808[(u32)(action_flags - 1)];

jt_c8:
        if ((func_801726B0(actor, context, sprite, entity) << 16) != 0) {
            return;
        }
        func_80172874(actor, context, sprite, entity);
        return;

jt_c9:
        func_80174FE4(actor, context, sprite, entity);
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 heading;

            heading = func_800A0818(
                ((S_801716F4_2 *)sprite)->unk_24.at00.v, ((S_801716F4_2 *)sprite)->unk_24.at01.v,
                ((S_801716F4_4 *)origin)->unk_24, ((S_801716F4_4 *)origin)->unk_25,
                &distance);
            player = D_800814A8;
            ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = heading;
            if (((S_801716F4_5 *)player)->unk_9A == 0x11) {
                goto case_123;
            }
        }

jt_c12:
case_12:
        func_800A9A0C(entity);
        return;

jt_c1:
jt_c2:
jt_c3:
case_123:
        func_800AAF00(actor, context, sprite, D_80175594, D_801716F4);
        return;

jt_c4:
jt_c10:
jt_c11:
generic:
        func_80171EEC(actor, context, sprite, entity);
        return;
    } else if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) ||
            !(((DungeonRecord *)D_800E2970)[room_index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_801716F4_2 *)sprite)->unk_24.at00.v, ((S_801716F4_2 *)sprite)->unk_24.at01.v,
                        ((S_801716F4_4 *)origin)->unk_24, ((S_801716F4_4 *)origin)->unk_25) << 16) != 0) {
                    ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = func_800A0818(
                        ((S_801716F4_2 *)sprite)->unk_24.at00.v, ((S_801716F4_2 *)sprite)->unk_24.at01.v,
                        ((S_801716F4_4 *)origin)->unk_24, ((S_801716F4_4 *)origin)->unk_25,
                        &distance);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_801716F4_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80175554;
    if (((S_801716F4_2 *)sprite)->unk_2C == anim_table) {
        return;
    }
    ASM_KEEP(sprite);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    next_table = anim_table;
set_table:
    (*(void * *)((u8 *)sprite + (0x2C))) = next_table;
    {
        s32 direction_index = ((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7;
        u8 *anim_entry;
#ifdef __mips__
        anim_entry = (u8 *)((u32)direction_index + (u32)next_table);
#else
        anim_entry = next_table + direction_index;
#endif
        func_80047784(sprite, anim_entry[0], 0);
    }
}

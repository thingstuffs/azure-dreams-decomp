#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800814A8.h"


typedef struct S_80171400_1 {
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
} S_80171400_1;   /* arg3 in func_80171400 */

typedef struct S_80171400_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171400_2;   /* arg2 in func_80171400 */


typedef struct S_80171400_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171400_4;   /* origin in func_80171400 */

typedef struct S_80171400_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80171400_5;   /* player in func_80171400 */



typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern s16 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171960(void *, void *);
extern void func_80171B28(void *, void *, void *, void *);
extern s16 func_80172270(void *, void *, void *, void *);
extern void func_80172434(void *, void *, void *, void *);
extern s16 func_80172554(void *, void *, void *, s32);
extern void func_80174218(void *, void *, void *, void *);
extern void func_80174948(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern DungeonRecord D_800E2970[];
extern void *D_80170808[];
extern u8 D_80175140[];
extern u8 D_80175148[];
extern u8 D_80175150[];
extern u8 D_80175170[];
extern u8 D_80175178[];
extern u8 D_80175180[];
extern u8 D_80175188[];
extern u8 D_80175190[];

/* Updates a dungeon actor's state, animation, and facing direction. */
void func_80171400(void *actor, void *context, void *sprite_in, void *entity_in)
{
    register void *sprite ASM_REG("$18") = sprite_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *entity ASM_REG("$17") = entity_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 direction_aux;
    s8 room_id;
    u16 action_state;
    u32 dungeon_flags = D_80083462;

    if (dungeon_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        func_80171960(actor, context);
        return;
    }

    ASM_CLOBBER("$6");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_CLOBBER("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (((S_80171400_1 *)entity)->unk_25 == 0) {
        u8 *anim_table;

        func_800AA79C(actor, context, sprite, entity);
        if (((S_80171400_2 *)sprite)->unk_2C == D_80175188) {
            return;
        }
        anim_table = D_80175180;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
            anim_table[((D_80083228 + ((S_80171400_1 *)entity)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_80171400_1 *)entity)->unk_1C & 0x200) {
        if (((S_80171400_2 *)sprite)->unk_2C == D_80175190) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            ((S_80171400_1 *)entity)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_80175180) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((S_80171400_1 *)entity)->unk_1C & 0x100) {
            func_800AA258(actor, context, sprite, entity);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        }

        if ((((S_80171400_2 *)sprite)->unk_2C != D_80175140) &&
            (((S_80171400_2 *)sprite)->unk_2C != D_80175148)) {
            u8 *anim_table = D_80175140;

            ((Rec_func_800A9E70_arg0 *)actor)->unk_A8 = 0;
            (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
            func_80047784(sprite,
                anim_table[((D_80083228 + ((S_80171400_1 *)entity)->unk_2A + 0x100) >> 9) & 7],
                ((Rec_func_800A9E70_arg0 *)actor)->unk_A8);
        }

        ((S_80171400_1 *)entity)->unk_1C |= 0x40000;
        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF7;

        if (((S_80171400_1 *)entity)->unk_64 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80175150) != 0) {
                return;
            }
        }

        if (((S_80171400_1 *)entity)->unk_1C & 0x80000) {
            func_800AA888(actor, context, sprite, entity);
            ((Rec_func_800A9E70_arg0 *)actor)->unk_A8 = 0;
            func_80174218(actor, context, sprite, entity);
            return;
        }

        if ((func_800A1C58(entity) << 16) != 0) {
            if ((func_800AAB10(actor, context, sprite, entity) << 16) != 0) {
                func_80174948(actor, context, sprite, entity);
            }
        }
    }

    room_id = func_8009FB34(((S_80171400_2 *)sprite)->unk_24.at00.v, ((S_80171400_2 *)sprite)->unk_24.at01.v);
    ((S_80171400_2 *)sprite)->unk_26 = room_id;

    if (((S_80171400_1 *)entity)->unk_6D > 0) {
        if (((S_80171400_1 *)entity)->unk_1C & 0x20) {
            goto case_12;
        }
        if (((S_80171400_2 *)sprite)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((S_80171400_1 *)entity)->unk_46 & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(entity,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172554(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_state = ((S_80171400_1 *)entity)->unk_46 | 0x4000;
            ((S_80171400_1 *)entity)->unk_46 = action_state;
            if (!(action_state & 0x8000)) {
                goto generic;
            }
        }

        {
            static void *const case_labels[] = {
                &&case_123, &&generic, &&sw_case89, &&sw_case567, &&case_12
            };
            u32 action_index = (u32)((((S_80171400_1 *)entity)->unk_46 & 0x3FFF) - 1);

            if (action_index >= 12) {
                goto generic;
            }
            (void)case_labels;
            goto *D_80170808[action_index];
        }

sw_case89:
        if ((func_80172270(actor, context, sprite, entity) << 16) != 0) {
            return;
        }
        func_80172434(actor, context, sprite, entity);
        return;

sw_case567:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 direction;

            direction = func_800A0818(
                ((S_80171400_2 *)sprite)->unk_24.at00.v, ((S_80171400_2 *)sprite)->unk_24.at01.v,
                ((S_80171400_4 *)origin)->unk_24, ((S_80171400_4 *)origin)->unk_25, &direction_aux);
            player = D_800814A8;
            ((S_80171400_1 *)entity)->unk_2A = direction;
            if (((S_80171400_5 *)player)->unk_9A == 0x11) {
                goto case_123;
            }
        }
        /* fallthrough */

case_12:
        func_800A9A0C(entity);
        return;

case_123:
        {
            void *anim_table;

            if (((S_80171400_2 *)sprite)->unk_2C == D_80175140) {
                anim_table = D_80175170;
            } else {
                anim_table = D_80175178;
            }
            func_800AAF00(actor, context, sprite, anim_table, func_80171400);
            return;
        }

generic:
        func_80171B28(actor, context, sprite, entity);
        return;
    }

    if (!(((S_80171400_1 *)entity)->unk_1C & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) || !(D_800E2970[room_index].flags & 2)) {
            if (!(((S_80171400_1 *)entity)->unk_1C & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_80171400_2 *)sprite)->unk_24.at00.v, ((S_80171400_2 *)sprite)->unk_24.at01.v,
                        ((S_80171400_4 *)origin)->unk_24, ((S_80171400_4 *)origin)->unk_25) << 16) != 0) {
                    ((S_80171400_1 *)entity)->unk_2A = func_800A0818(
                        ((S_80171400_2 *)sprite)->unk_24.at00.v, ((S_80171400_2 *)sprite)->unk_24.at01.v,
                        ((S_80171400_4 *)origin)->unk_24, ((S_80171400_4 *)origin)->unk_25, &direction_aux);
                }
            }
        }
    }
}

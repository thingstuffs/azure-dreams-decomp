#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"


typedef struct S_80170E54_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    union { void * p; u8 * p2; } unk_2C;   /* accessed as both */
    u8 pad_30[0x8B];
    u8 unk_BB;
} S_80170E54_2;   /* object in func_80170E54 */


typedef struct S_80170E54_7 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    void * unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80170E54_7;   /* sub in func_80170E54 */

typedef struct S_80170E54_8 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80170E54_8;   /* base in func_80170E54 */

typedef struct S_80170E54_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170E54_9;   /* ((S_80170E54_2 *)object)->unk_08 in func_80170E54 */


extern s32 func_8003DE58(void *, void *, void *, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s16 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_80171570(void *, void *);
extern void func_801717B4(void *, void *, void *, void *);
extern s32 func_80171FC0(void *, void *, void *, void *);
extern void func_80172184(void *, void *, void *, void *);
extern s32 func_8017229C(void *, void *, void *, s32);
extern void func_80173EF4(void *, void *, void *, void *);

extern u8 D_800D79B0[];
extern u8 D_800DEA68[];
extern u8 D_80170E54;
extern u8 D_80174140[];
extern u8 D_80174148[];
extern u8 D_80174150[];
extern u8 D_80174188[];
extern u8 D_80174190[];

void func_80170E54(void *record, EntityRec *entity, void *object, EntityRec *other_entity)
{
    s32 scratch;
    s16 offset[3];
    s8 result;
    u16 state;
    u8 *table;
    u8 *high_table; /* MATCH: both table-selection paths feed the shared tail in a1. */

    if (dungeonStatus.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)record)->unk_9A.as_u8 = 0xE;
        func_80171570(record, entity);
        return;
    }

    if (other_entity->tileY == 0) {
        func_800AA79C(record, entity, object, other_entity);
        if (((S_80170E54_2 *)object)->unk_2C.p == D_80174190) {
            return;
        }
        {
            void *next_state;

            next_state = D_80174188;
            high_table = next_state;
        }
        (*(void * *)((u8 *)object + 0x2C)) = high_table;
        func_80047784(object,
            *((u8 *)(((gameWork.view.viewAngle + other_entity->facing + 0x100) >> 9) & 7) + (u32)high_table),
            0);
        return;
    }

    if (((u32)other_entity->flags1C) & 0x200) {
        if (((S_80170E54_2 *)object)->unk_2C.p == D_80174190) {
            ((Rec_func_800A9E70_arg0 *)record)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)record)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)record)->unk_8C = 0;
            other_entity->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(record, entity, object, D_80174188) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)other_entity->flags1C) & 0x100) {
            func_800AA258(record, entity, object, other_entity);
            return;
        }

normal_state:
        if (((Rec_func_800A9E70_arg0 *)record)->unk_9A.as_u8 != 0xE) {
            table = D_80174148;
            if (((S_80170E54_2 *)object)->unk_2C.p != table) {
                (*(void * *)((u8 *)object + 0x2C)) = table;
                func_80047784(object,
                    table[((gameWork.view.viewAngle + other_entity->facing + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)record)->unk_9A.as_u8 = 0xE;
        }

        ((Rec_func_800A9E70_arg0 *)record)->unk_98 &= 0xFFF3;
        if (other_entity->unk_64 != 0) {
            if (func_800AA6B4(record, entity, object, D_80174150) != 0) {
                return;
            }
        }

        if (((u32)other_entity->flags1C) & 0x80000) {
            func_800AA888(record, entity, object, other_entity);
            func_80173EF4(record, entity, object, other_entity);
            (*(void * *)((u8 *)object + 0x2C)) = D_80174140;
            func_80047784(object,
                *((u8 *)(((gameWork.view.viewAngle + other_entity->facing + 0x100) >> 9) & 7) + (u32)D_80174140),
                0);
            return;
        }

        if ((func_800A1C58(other_entity) << 16) != 0) {
            func_800AAB10(record, entity, object, other_entity);
        }
    }

    result = func_8009FB34(((S_80170E54_2 *)object)->unk_24.at00.v, ((S_80170E54_2 *)object)->unk_24.at01.v);
    ((S_80170E54_2 *)object)->unk_26 = result;

    if (other_entity->unk_6D > 0) {
        if (((u32)other_entity->flags1C) & 0x20) {
            goto case_12;
        }
        if (((S_80170E54_2 *)object)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            goto generic;
        }
        if (!(other_entity->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((func_8009A180(other_entity,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8017229C(record, entity, object, 0) << 16) == 0) {
                return;
            }
            state = other_entity->unk_46 | 0x4000;
            other_entity->unk_46 = state;
            if (!(state & 0x8000)) {
                goto generic;
            }
        }

        state = other_entity->unk_46 & 0x3FFF;
        switch (state) {
        case 8:
        case 9:
            if ((func_80171FC0(record, entity, object, other_entity) << 16) != 0) {
                return;
            }
            func_80172184(record, entity, object, other_entity);
            return;

        case 5:
        case 6:
        case 7:
        {
            EntityRec *player;
            s16 coordinate;

            coordinate = func_800A0818(
                ((S_80170E54_2 *)object)->unk_24.at00.v, ((S_80170E54_2 *)object)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY,
                &scratch);
            player = D_800814A8;
            other_entity->facing = coordinate;
            if (player->unk_9A == 0x11) {
                goto case_123;
            }
        }

        case 12:
case_12:
            func_800A9A0C(other_entity);
            return;

        case 1:
        case 2:
        case 3:
case_123:
            func_800AAF00(record, entity, object, D_80174140, &D_80170E54);
            return;

        case 11:
        default:
generic:
            func_801717B4(record, entity, object, other_entity);
            return;
        }
    }

    if (!(((u32)other_entity->flags1C) & 0x2000)) {
        s32 index = result;

        if ((index < 0) || !(D_800E2970[index].flags & 2)) {
            if (!(((u32)other_entity->flags1C) & 0x430)) {

                if ((func_8009FD7C(
                        ((S_80170E54_2 *)object)->unk_24.at00.v, ((S_80170E54_2 *)object)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    other_entity->facing = func_800A0818(
                        ((S_80170E54_2 *)object)->unk_24.at00.v, ((S_80170E54_2 *)object)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &scratch);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((S_80170E54_2 *)object)->unk_14 & 0x40) {
        return;
    }

    table = D_80174148;
    if ((((S_80170E54_2 *)object)->unk_2C.p != table) &&
        (((S_80170E54_2 *)object)->unk_2C.p != D_80174140)) {
        (*(void * *)((u8 *)object + 0x2C)) = table;
        func_80047784(object,
            table[((gameWork.view.viewAngle + other_entity->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_func_800A9E70_arg0 *)record)->unk_AA = 1;
    } else if (((S_80170E54_2 *)object)->unk_14 & 0x6000) {
        s16 timer = ((Rec_func_800A9E70_arg0 *)record)->unk_AA - 1;

        ((Rec_func_800A9E70_arg0 *)record)->unk_AA = timer;
        if (timer < 0) {
            ((Rec_func_800A9E70_arg0 *)record)->unk_AA = (func_80069EF8() & 0x1F) + 0x20;
        }
        if (((Rec_func_800A9E70_arg0 *)record)->unk_AA < 2) {
            ((S_80170E54_2 *)object)->unk_2C.p = D_80174148;
        } else {
            ((S_80170E54_2 *)object)->unk_2C.p = D_80174140;
        }
        func_80047784(object,
            ((S_80170E54_2 *)object)->unk_2C.p2[
                ((gameWork.view.viewAngle + other_entity->facing + 0x100) >> 9) & 7],
            0);
    }

    if (!func_8003DE58(((S_80170E54_2 *)object)->unk_08, object, offset, 1)) {
        return;
    }
    if (((S_80170E54_2 *)object)->unk_2C.p != D_80174148) {
        return;
    }

    {
        void *created;
        void *sub;
        void *color;
        u8 *base;
        s32 base_word;

        created = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
        ((Rec_func_800A9E70_arg0 *)record)->unk_A0.at00_pv.v = created;
        object = created;
        if (object == 0) {
            return;
        }
        func_8004491C(object, func_80045340);
        color = (void *)0x00808080;
        ((S_80170E54_2 *)object)->unk_10 = D_800D79B0;
        ((S_80170E54_9 *)(((S_80170E54_2 *)object)->unk_08))->unk_02 =
            ((u16)entity->x.w.i) + offset[0];
        ((S_80170E54_9 *)(((S_80170E54_2 *)object)->unk_08))->unk_06 =
            ((u16)entity->y.w.i) + offset[1];
        ((S_80170E54_9 *)(((S_80170E54_2 *)object)->unk_08))->unk_0A =
            ((u16)entity->z.w.i) + offset[2];
        sub = ((S_80170E54_2 *)object)->unk_0C;
        base = D_800DEA68;
        ((S_80170E54_2 *)object)->unk_BB = 0;
        ((S_80170E54_7 *)sub)->unk_1E = 0xC00;
        ((S_80170E54_7 *)sub)->unk_1C = 0xC00;
        ((S_80170E54_7 *)sub)->unk_0C = color;
        ((S_80170E54_7 *)sub)->unk_00 = base;
        ((S_80170E54_7 *)sub)->unk_14 |= 0xC;
        base_word = ((S_80170E54_8 *)base)->unk_04;
        ((S_80170E54_7 *)sub)->unk_04 = 0;
        ((S_80170E54_7 *)sub)->unk_05 = 0;
        ((S_80170E54_7 *)sub)->unk_08 = base_word;
    }
}


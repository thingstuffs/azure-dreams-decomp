#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"



typedef struct S_801711A4_2 {
    u8 pad_00[0x5];
    s8 unk_05;
    u8 pad_06[0x1E];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    M2C_UNK * unk_2C;
} S_801711A4_2;   /* arg2 in func_801711A4 */

typedef struct S_801711A4_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    s8 unk_9B;
} S_801711A4_3;   /* saved0 in func_801711A4 */



typedef struct EmptyArg {
} EmptyArg;

#define M2C_BREAK() 0
#define M2C_SYNC() 0

void func_80047784();
s32 func_8009A180();
s8 func_8009FB34();
s32 func_8009FD7C();
s16 func_800A0818();
s32 func_800A1C58();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AA258();
s32 func_800AA6B4();
M2C_UNK func_800AA79C();
M2C_UNK func_800AA888();
s32 func_800AA924();
M2C_UNK func_800AAB10();
M2C_UNK func_800AAF00();
M2C_UNK func_801716CC();
M2C_UNK func_80171884();
s32 func_80171FCC();
M2C_UNK func_80172190();
s32 func_801722B8();
M2C_UNK func_80173D10();
extern M2C_UNK D_801711A4;
extern M2C_UNK D_8017418C;
extern M2C_UNK D_80174194;
extern M2C_UNK D_801741AC;
extern M2C_UNK D_801741C4;
extern M2C_UNK D_801741CC;

/* Updates the actor animation and dispatches dungeon actions based on status and position. */
void func_801711A4(void *actor, M2C_UNK context, void *sprite, EntityRec *status) {
    M2C_UNK direction_aux;
    M2C_UNK *next_handler;
    s32 status_flags;
    s32 action_id;
    s8 room_id;
    s16 angle;
    u16 action_flags;
    EntityRec *active_actor;
    M2C_UNK *direction_aux_ptr;
    EmptyArg empty_arg;

    if (dungeonStatus.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
        func_801716CC(actor, context, sprite, status);
        return;
    }
    if (status->tileY == 0) {
        func_800AA79C(actor, context, sprite, status);
        if (((S_801711A4_2 *)sprite)->unk_2C == &D_801741CC) {
            return;
        }
        (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_801741C4;
        func_80047784(sprite, *(((u8 *)&D_801741C4) + (((s32) (gameWork.view.viewAngle + status->facing + 0x100) >> 9) & 7)), 0);
        return;
    }
    if (status->flags1C & 0x200) {
        {
            void *action_actor = actor;
            if (((S_801711A4_2 *)sprite)->unk_2C == &D_801741CC) {
                {
                    void *reset_actor = actor;
                    EntityRec *reset_status = status;
                    s32 clear_mask = (s32)0xFFFB0000;
                    s32 flags;
                    ((S_801711A4_3 *)reset_actor)->unk_9A = 0xDU;
                    ((S_801711A4_3 *)reset_actor)->unk_9B = 1;
                    ((S_801711A4_3 *)reset_actor)->unk_8C = 0;
                    flags = reset_status->flags1C;
                    clear_mask |= 0xFFFF;
                    flags &= clear_mask;
                    reset_status->flags1C = flags;
                    return;
                }
            }
            if (func_800AA924(action_actor, context, sprite, &D_801741C4) != 0) {
                return;
            }
        }
    }
    if (!(dungeonStatus.flags & 0x2000)) {
        if (status->flags1C & 0x100) {
            func_800AA258(actor, context, sprite, status);
            return;
        }
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
        }
        if (((S_801711A4_2 *)sprite)->unk_2C != &D_8017418C) {
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_8017418C;
            func_80047784(sprite, *(((u8 *)&D_8017418C) + (((s32) (gameWork.view.viewAngle + status->facing + 0x100) >> 9) & 7)), 0);
            ((S_801711A4_2 *)sprite)->unk_05 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_AE = 0;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_A8 = 0;
        }
        status->flags1C = (s32) (status->flags1C | 0x40000);
        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)actor)->unk_98 & 0xFFF7);
        if (status->unk_64 != 0) {
            if (func_800AA6B4(actor, context, sprite, &D_80174194) != 0) {
                return;
            }
        }
        if (status->flags1C & 0x80000) {
            func_800AA888(actor, context, sprite, status);
            ((Rec_func_800A9E70_arg0 *)actor)->unk_A8 = 0;
            func_80173D10(actor, context, sprite, status);
            return;
        }
        if ((func_800A1C58(status) << 0x10) != 0) {
            func_800AAB10(actor, context, sprite, status);
        }
    }
    room_id = func_8009FB34(((S_801711A4_2 *)sprite)->unk_24.at00.v, ((S_801711A4_2 *)sprite)->unk_24.at01.v);
    ((S_801711A4_2 *)sprite)->unk_26 = room_id;
    if (status->unk_6D <= 0) {
        goto block_49;
    }
    if (status->flags1C & 0x20) {
        goto block_41;
    }
    if (((S_801711A4_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
        goto block_47;
    }
    if (!(status->unk_46 & 0x8000)) {
        if (dungeonStatus.flags & 0x2000) {
            if ((func_8009A180(status, ((s32)D_800814A8->unk_58) + 0x20) << 0x10) != 0) {
                return;
            }
        }
        if ((func_801722B8(actor, context, sprite, 0) << 0x10) == 0) {
            return;
        }
        action_flags = status->unk_46 | 0x4000;
        status->unk_46 = action_flags;
        if (!(action_flags & 0x8000)) {
            goto block_47;
        }
    }
    action_id = status->unk_46 & 0x3FFF;
    switch (action_id) {
    case 8:
    case 9:
    if ((func_80171FCC(actor, context, sprite, status) << 0x10) != 0) {
        return;
    }
    func_80172190(actor, context, sprite, status);
    return;
    case 5:
    case 6:
    case 7:
    angle = func_800A0818(((S_801711A4_2 *)sprite)->unk_24.at00.v, ((S_801711A4_2 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY, &direction_aux);
    active_actor = D_800814A8;
    status->facing = angle;
    if (active_actor->unk_9A == 0x11) {
        next_handler = &D_801711A4;
        goto block_44;
    }
    case 12:
block_41:
    func_800A9A0C(status);
    return;
    case 1:
    case 2:
    case 3:
    next_handler = &D_801711A4;
block_44:
    func_800AAF00(actor, context, sprite, &D_801741AC, next_handler);
    return;
    case 4:
    case 10:
    case 11:
    default:
block_47:
    func_80171884(actor, context, sprite, status);
    return;
    }
block_49:
    status_flags = status->flags1C;
    if (status_flags & 0x2000) {
        return;
    }
    if (room_id >= 0) {
        if (D_800E2970[room_id].flags & 2) {
            return;
        }
    }
    if (status_flags & 0x430) {
        return;
    }
    if ((func_8009FD7C(((S_801711A4_2 *)sprite)->unk_24.at00.v, ((S_801711A4_2 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY) << 0x10) == 0) {
        return;
    }
    direction_aux_ptr = &direction_aux;
    angle = func_800A0818(((S_801711A4_2 *)sprite)->unk_24.at00.v, ((S_801711A4_2 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY, direction_aux_ptr, ({  empty_arg; }));
    status->facing = angle;
    return;
}

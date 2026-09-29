#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef s32 M2C_UNK;

typedef struct S_80170E9C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    s8 unk_9B;
} S_80170E9C_0;   /* arg0 in func_80170E9C */

typedef struct S_80170E9C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
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
} S_80170E9C_1;   /* arg3 in func_80170E9C */

typedef struct S_80170E9C_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    M2C_UNK * unk_2C;
} S_80170E9C_2;   /* arg2 in func_80170E9C */



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

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
s32 func_800AAB10();
M2C_UNK func_800AAF00();
M2C_UNK func_80171410();
M2C_UNK func_80171B58();
s32 func_80171E00();
M2C_UNK func_80171FC4();
M2C_UNK func_801737C4();
s32 func_80173A08();
M2C_UNK func_801747D0();
extern u8 D_80174EE0[];
extern M2C_UNK D_80174EF8;
extern M2C_UNK D_80174F00;
extern M2C_UNK D_80174F08;
extern M2C_UNK D_80174F10;

/* Updates entity actions, facing, and animation from state and terrain. */
void func_80170E9C(void *entity, M2C_UNK context, void *sprite, void *state) {
    M2C_UNK direction_aux;
    M2C_UNK *resume_handler;
    EntityRec *reference_entity;
    s16 target_angle;
    s32 idle_flags;
    s32 action_id;
    s32 state_flags;
    s8 terrain_index;
    u8 current_mode;
    u16 action_flags;
    u32 idle_mode;

    if (dungeonStatus.flags & 0x1000) {
        ((S_80170E9C_0 *)entity)->unk_9A = 0xEU;
        func_80171B58(entity);
        return;
    }
    if (((S_80170E9C_1 *)state)->unk_25 == 0) {
        func_800AA79C(entity, context, sprite, state);
        if (((S_80170E9C_2 *)sprite)->unk_2C == &D_80174F00) {
            return;
        }
        (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80174EF8;
        func_80047784(sprite, *(u8 *)((((s32)(gameWork.view.viewAngle + ((S_80170E9C_1 *)state)->unk_2A + 0x100) >> 9) & 7) + (u32)&D_80174EF8), 0);
        return;
    }
    state_flags = ((S_80170E9C_1 *)state)->unk_1C;
    if (state_flags & 0x200) {
        if (((S_80170E9C_2 *)sprite)->unk_2C == &D_80174F00) {
            ((S_80170E9C_0 *)entity)->unk_9A = 0xDU;
            ((S_80170E9C_0 *)entity)->unk_9B = 1;
            ((S_80170E9C_0 *)entity)->unk_8C = 0;
            ((S_80170E9C_1 *)state)->unk_1C = (s32)(((S_80170E9C_1 *)state)->unk_1C & 0xFFFBFFFF);
            ((S_80170E9C_2 *)sprite)->unk_0E = 0x40;
            ((S_80170E9C_2 *)sprite)->unk_0D = 0x40;
            ((S_80170E9C_2 *)sprite)->unk_0C = 0x40;
            return;
        }
        if (func_800AA924(entity, context, sprite, &D_80174EF8) == 0) {
            return;
        }
        ((S_80170E9C_1 *)state)->unk_1C |= 0x10000000;
        return;
    }
    if (!(dungeonStatus.flags & 0x2000)) {
        if (state_flags & 0x100) {
            func_800AA258(entity, context, sprite, state);
            return;
        }
        current_mode = ((S_80170E9C_0 *)entity)->unk_9A;
        idle_mode = 0xE;
        if (current_mode != idle_mode) {
            if (((S_80170E9C_2 *)sprite)->unk_2C != D_80174EE0) {
                (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = D_80174EE0;
                func_80047784(sprite, D_80174EE0[((s32)(gameWork.view.viewAngle + ((S_80170E9C_1 *)state)->unk_2A + 0x100) >> 9) & 7], 0);
            }
            ((S_80170E9C_0 *)entity)->unk_9A = idle_mode;
        }
        ((S_80170E9C_0 *)entity)->unk_98 = (u16)(((S_80170E9C_0 *)entity)->unk_98 & 0xFFF3);
        if (((S_80170E9C_1 *)state)->unk_64 != 0) {
            if (func_800AA6B4(entity, context, sprite, &D_80174F10) != 0) {
                return;
            }
        }
        if (((S_80170E9C_1 *)state)->unk_1C & 0x80000) {
            func_800AA888(entity, context, sprite, state);
            func_801737C4(entity, context, sprite, state);
            return;
        }
        if ((func_800A1C58(state) << 0x10) != 0) {
            if ((func_800AAB10(entity, context, sprite, state) << 0x10) != 0) {
                func_801747D0(entity, context, sprite, state);
            }
        }
    }
    terrain_index = func_8009FB34(((S_80170E9C_2 *)sprite)->unk_24.at00.v, ((S_80170E9C_2 *)sprite)->unk_24.at01.v);
    ((S_80170E9C_2 *)sprite)->unk_26 = terrain_index;
    if (((S_80170E9C_1 *)state)->unk_6D <= 0) {
        goto block_52;
    }
    if (((S_80170E9C_1 *)state)->unk_1C & 0x20) {
        goto block_44;
    }
    if (((S_80170E9C_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
        goto block_50;
    }
    if (!(((S_80170E9C_1 *)state)->unk_46 & 0x8000)) {
        if (dungeonStatus.flags & 0x2000) {
            if ((func_8009A180(state, ((s32)D_800814A8->unk_58) + 0x20) << 0x10) != 0) {
                return;
            }
        }
        if ((func_80173A08(entity, context, sprite, 0) << 0x10) == 0) {
            return;
        }
        action_flags = ((S_80170E9C_1 *)state)->unk_46 | 0x4000;
        ((S_80170E9C_1 *)state)->unk_46 = action_flags;
        if (!(action_flags & 0x8000)) {
            goto block_50;
        }
    }
    action_id = ((S_80170E9C_1 *)state)->unk_46 & 0x3FFF;
    switch (action_id) {
    case 8:
    case 9:
    if ((func_80171E00(entity, context, sprite, state) << 0x10) != 0) {
        return;
    }
    func_80171FC4(entity, context, sprite, state);
    return;
    case 5:
    case 6:
    case 7:
    target_angle = func_800A0818(((S_80170E9C_2 *)sprite)->unk_24.at00.v, ((S_80170E9C_2 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY, &direction_aux);
    reference_entity = D_800814A8;
    ((S_80170E9C_1 *)state)->unk_2A = target_angle;
    if (reference_entity->unk_9A == 0x11) {
        goto block_46;
    }
    case 12:
block_44:
    func_800A9A0C(state);
    return;
    case 1:
    case 2:
    case 3:
block_46:
    resume_handler = (M2C_UNK *)func_80170E9C;
block_47:
    func_800AAF00(entity, context, sprite, &D_80174F08, resume_handler);
    return;
    case 11:
    default:
block_49:
block_50:
    func_80171410(entity, context, sprite, state);
    return;
    }
block_52:
    idle_flags = ((S_80170E9C_1 *)state)->unk_1C;
    if (!(idle_flags & 0x2000)) {
        if (terrain_index >= 0) {
            if (D_800E2970[terrain_index].flags & 2) {
                goto block_59;
            }
        }
        if (!(idle_flags & 0x430)) {
            if ((func_8009FD7C(((S_80170E9C_2 *)sprite)->unk_24.at00.v, ((S_80170E9C_2 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY) << 0x10) != 0) {
                ((S_80170E9C_1 *)state)->unk_2A = func_800A0818(((S_80170E9C_2 *)sprite)->unk_24.at00.v, ((S_80170E9C_2 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY, &direction_aux);
            }
        }
    }
block_59:
    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((S_80170E9C_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    if (((S_80170E9C_2 *)sprite)->unk_2C == (M2C_UNK *)D_80174EE0) {
        return;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = (M2C_UNK *)D_80174EE0;
    func_80047784(sprite, D_80174EE0[((s32)(gameWork.view.viewAngle + ((S_80170E9C_1 *)state)->unk_2A + 0x100) >> 9) & 7], 0);
    return;
}

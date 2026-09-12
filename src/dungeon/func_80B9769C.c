#include "common.h"
#include "records/Rec_D_800814A8.h"

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


typedef struct S_80170E9C_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170E9C_4;   /* case_entity in func_80170E9C */


typedef struct {
    u8 pad_00[0x24];
    u8 x;
    u8 y;
} RefPosition;

typedef struct {
    u8 pad_00[0xC];
    u16 flags;
    u8 pad_0E[6];
} TerrainEntry;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80170808[];
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
extern void *D_800814A8;
extern RefPosition D_80082E80;
extern u16 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern TerrainEntry D_800E2970[];
extern u8 D_80174EE0[];
extern M2C_UNK D_80174EF8;
extern M2C_UNK D_80174F00;
extern M2C_UNK D_80174F08;
extern M2C_UNK D_80174F10;

/* Updates entity actions, facing, and animation from state and terrain. */
void func_80170E9C(void *entity_arg, M2C_UNK context_arg, void *sprite_arg, void *state_arg) {
    static void *const action_labels[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    void *entity = entity_arg;
    M2C_UNK context = context_arg;
    void *sprite = sprite_arg;
    M2C_UNK direction_aux;
    M2C_UNK *resume_handler;
    void *reference_entity;
    RefPosition *action_target;
    RefPosition *idle_target;
    s16 target_angle;
    s32 idle_flags;
    s32 action_id;
    s32 state_flags;
    s8 terrain_index;
    u8 current_mode;
    u16 action_flags;
    register void *state ASM_REG("$18") = state_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u32 idle_mode;

    if (!(D_80083462 & 0x1000)) {
        goto block_3;
    }
    ((S_80170E9C_0 *)entity)->unk_9A = 0xEU;
    func_80171B58(entity);
    return;
block_3:
    ASM_CLOBBER("$7");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    if (((S_80170E9C_1 *)state)->unk_25 != 0) {
        goto block_7;
    }
    func_800AA79C(entity, context, sprite, state);
    if (((S_80170E9C_2 *)sprite)->unk_2C == &D_80174F00) {
        goto block_63;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80174EF8;
    func_80047784(sprite, *(u8 *)((((s32)(D_80083228 + ((S_80170E9C_1 *)state)->unk_2A + 0x100) >> 9) & 7) + (u32)&D_80174EF8), 0);
    return;
block_7:
    state_flags = ((S_80170E9C_1 *)state)->unk_1C;
    if (!(state_flags & 0x200)) {
        goto block_14;
    }
    if (((S_80170E9C_2 *)sprite)->unk_2C != &D_80174F00) {
        goto block_11;
    }
    ((S_80170E9C_0 *)entity)->unk_9A = 0xDU;
    ((S_80170E9C_0 *)entity)->unk_9B = 1;
    ((S_80170E9C_0 *)entity)->unk_8C = 0;
    ((S_80170E9C_1 *)state)->unk_1C = (s32)(((S_80170E9C_1 *)state)->unk_1C & 0xFFFBFFFF);
    ((S_80170E9C_2 *)sprite)->unk_0E = 0x40;
    ((S_80170E9C_2 *)sprite)->unk_0D = 0x40;
    ((S_80170E9C_2 *)sprite)->unk_0C = 0x40;
    return;
block_11:
    if (func_800AA924(entity, context, sprite, &D_80174EF8) == 0) {
        goto block_63;
    }
    ((S_80170E9C_1 *)state)->unk_1C |= 0x10000000;
    return;
block_14:
    if (D_80083462 & 0x2000) {
        goto block_30;
    }
    if (!(state_flags & 0x100)) {
        goto block_18;
    }
    func_800AA258(entity, context, sprite, state);
    return;
block_18:
    current_mode = ((S_80170E9C_0 *)entity)->unk_9A;
    idle_mode = 0xE;
    if (current_mode == idle_mode) {
        goto block_22;
    }
    if (((S_80170E9C_2 *)sprite)->unk_2C == D_80174EE0) {
        goto block_21;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = D_80174EE0;
    func_80047784(sprite, D_80174EE0[((s32)(D_80083228 + ((S_80170E9C_1 *)state)->unk_2A + 0x100) >> 9) & 7], 0);
block_21:
    ((S_80170E9C_0 *)entity)->unk_9A = idle_mode;
block_22:
    ((S_80170E9C_0 *)entity)->unk_98 = (u16)(((S_80170E9C_0 *)entity)->unk_98 & 0xFFF3);
    if (((S_80170E9C_1 *)state)->unk_64 == 0) {
        goto block_24;
    }
    if (func_800AA6B4(entity, context, sprite, &D_80174F10) != 0) {
        goto block_63;
    }
block_24:
    if (!(((S_80170E9C_1 *)state)->unk_1C & 0x80000)) {
        goto block_27;
    }
    func_800AA888(entity, context, sprite, state);
    func_801737C4(entity, context, sprite, state);
    return;
block_27:
    if ((func_800A1C58(state) << 0x10) == 0) {
        goto block_30;
    }
    if ((func_800AAB10(entity, context, sprite, state) << 0x10) == 0) {
        goto block_30;
    }
    func_801747D0(entity, context, sprite, state);
block_30:
    terrain_index = func_8009FB34(((S_80170E9C_2 *)sprite)->unk_24.at00.v, ((S_80170E9C_2 *)sprite)->unk_24.at01.v);
    ((S_80170E9C_2 *)sprite)->unk_26 = terrain_index;
    if (((S_80170E9C_1 *)state)->unk_6D <= 0) {
        goto block_52;
    }
    if (((S_80170E9C_1 *)state)->unk_1C & 0x20) {
        goto block_44;
    }
    if (((S_80170E9C_2 *)sprite)->unk_24.at00u.v == D_80082EA4) {
        goto block_50;
    }
    if (((S_80170E9C_1 *)state)->unk_46 & 0x8000) {
        goto block_38;
    }
    if (!(D_80083462 & 0x2000)) {
        goto block_36;
    }
    if ((func_8009A180(state, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 0x10) != 0) {
        goto block_63;
    }
block_36:
    if ((func_80173A08(entity, context, sprite, 0) << 0x10) == 0) {
        goto block_63;
    }
    action_flags = ((S_80170E9C_1 *)state)->unk_46 | 0x4000;
    ((S_80170E9C_1 *)state)->unk_46 = action_flags;
    if (!(action_flags & 0x8000)) {
        goto block_50;
    }
block_38:
    action_id = ((S_80170E9C_1 *)state)->unk_46 & 0x3FFF;
    if ((u32)(action_id - 1) >= 0xCU) {
        goto block_49;
    }
    (void)action_labels;
    goto *D_80170808[(u32)(action_id - 1)];
jt_c8:
jt_c9:
    if ((func_80171E00(entity, context, sprite, state) << 0x10) != 0) {
        goto block_63;
    }
    func_80171FC4(entity, context, sprite, state);
    return;
jt_c5:
jt_c6:
jt_c7:
    action_target = &D_80082E80;
    target_angle = func_800A0818(((S_80170E9C_2 *)sprite)->unk_24.at00.v, ((S_80170E9C_2 *)sprite)->unk_24.at01.v, action_target->x, action_target->y, &direction_aux);
    reference_entity = D_800814A8;
    ((S_80170E9C_1 *)state)->unk_2A = target_angle;
    if (((S_80170E9C_4 *)reference_entity)->unk_9A == 0x11) {
        goto jt_c1;
    }
jt_c12:
block_44:
    func_800A9A0C(state);
    return;
jt_c1:
jt_c2:
jt_c3:
    resume_handler = (M2C_UNK *)func_80170E9C;
block_47:
    func_800AAF00(entity, context, sprite, &D_80174F08, resume_handler);
    return;
jt_c4:
jt_c10:
jt_c11:
block_49:
block_50:
    func_80171410(entity, context, sprite, state);
    return;
block_52:
    idle_flags = ((S_80170E9C_1 *)state)->unk_1C;
    if (idle_flags & 0x2000) {
        goto block_59;
    }
    if (terrain_index < 0) {
        goto block_55;
    }
    if (D_800E2970[terrain_index].flags & 2) {
        goto block_59;
    }
block_55:
    if (idle_flags & 0x430) {
        goto block_59;
    }
    idle_target = &D_80082E80;
    if ((func_8009FD7C(((S_80170E9C_2 *)sprite)->unk_24.at00.v, ((S_80170E9C_2 *)sprite)->unk_24.at01.v, idle_target->x, idle_target->y) << 0x10) == 0) {
        goto block_58;
    }
    ((S_80170E9C_1 *)state)->unk_2A = func_800A0818(((S_80170E9C_2 *)sprite)->unk_24.at00.v, ((S_80170E9C_2 *)sprite)->unk_24.at01.v, idle_target->x, idle_target->y, &direction_aux);
block_58:
block_59:
    if (D_80083462 & 0x2000) {
        goto block_63;
    }
    if (((S_80170E9C_2 *)sprite)->unk_14 & 0x40) {
        goto block_63;
    }
    if (((S_80170E9C_2 *)sprite)->unk_2C == (M2C_UNK *)D_80174EE0) {
        goto block_63;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = (M2C_UNK *)D_80174EE0;
    func_80047784(sprite, D_80174EE0[((s32)(D_80083228 + ((S_80170E9C_1 *)state)->unk_2A + 0x100) >> 9) & 7], 0);
block_63:
    return;
}

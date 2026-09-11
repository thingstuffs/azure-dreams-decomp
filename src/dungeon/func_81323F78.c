#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"



typedef struct S_8016B778_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    union { u8 * p; void * p2; } unk_2C;   /* accessed as both */
} S_8016B778_2;   /* arg2 in func_8016B778 */

typedef struct S_8016B778_3 {
    u8 pad_00[0x58];
    s32 unk_58;
} S_8016B778_3;   /* *D_800814A8 in func_8016B778 */

typedef struct S_8016B778_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_8016B778_4;   /* global_814A8 in func_8016B778 */

typedef struct S_8016B778_5 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_8016B778_5;   /* entry in func_8016B778 */


extern u16 D_80083462[5];
extern u8 D_801746A4[];
extern u8 D_80174684[];
extern s16 D_80083228[5];
extern volatile s16 D_80013714[8];
extern u8 D_801746C4[];
extern s32 D_80083460[3];
extern u8 D_8017467C[];
extern s32 D_8008346C[];
extern u16 D_80082EA4[8];
extern int D_800814A8[4];
extern u8 D_80082E80[];
extern u8 D_8016B778[];
extern s8 D_800E2970[];
extern void *D_8016A828[];
s8 func_8009FB34();
s32 func_8009FD7C();
s32 func_800A1C58();
M2C_UNK func_800A9A0C();
extern void func_800AA258(void *, void *, void *, void *);
s32 func_800AA6B4();
M2C_UNK func_800AA888();
s32 func_800AA924();
M2C_UNK func_800AAF00();
M2C_UNK func_8016BD14();
M2C_UNK func_8016BF74();
s32 func_8016C720();
M2C_UNK func_8016C8AC();
s32 func_8016C98C();
M2C_UNK func_8016DAA4();
M2C_UNK func_8016EF10();
extern M2C_UNK D_8017469C;
extern M2C_UNK D_801746BC;

/* Update the actor's dungeon action, animation, and facing direction. */
void func_8016B778(Rec_func_800A9E70_arg0 *actor, M2C_UNK context, S_8016B778_2 *map_actor, void *entity) {
    static void *const action_labels[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&state_store };
    M2C_UNK target_distance;
    s32 entity_flags;
    s32 state_flags;
    s32 override_flag;
    s16 target_angle;
    s32 action_id;
    s8 tile_index;
    u16 action_flags;
    u8 *action_data;
    register void *current_anim;
    u8 *idle_anim;
    void *action_actor;
    s32 flag_mask_hi;
    u8 *target_actor;
    u8 *tile_table;
    u8 *tile_entry;
    u8 *active_actor;
    s32 *dungeon_state;
    if (!(*D_80083462 & 0x1000)) {
        goto block_3;
    }
    actor->unk_9A.as_u8 = 0xEU;
    func_8016BD14(actor, context, map_actor, entity);
    return;
block_3:
    if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x200)) {
        goto block_8;
    }
    if (map_actor->unk_2C.p != D_801746A4) {
        goto block_7;
    }
    flag_mask_hi = (s32)0xFFFB0000;
    actor->unk_9A.as_u8 = 0xDU;
    actor->unk_9B.as_s8 = 1;
    actor->unk_8C = 0;
    ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 &= flag_mask_hi | 0xFFFF;
    return;
block_7:
    if (func_800AA924(actor, context, map_actor, &D_8017469C) != 0) {
        goto block_65;
    }
block_8:
    if (*D_80083462 & 0x2000) {
        goto block_33;
    }
    state_flags = ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32;
    override_flag = state_flags & 0x100;
    action_actor = actor;
    if (!override_flag) {
        goto block_12;
    }
    func_800AA258(action_actor, context, map_actor, entity);
    return;
block_12:
    if (actor->unk_9A.as_u8 != 0xE) {
        if (actor->unk_B3 == 0) {
            current_anim = map_actor->unk_2C.p2;
            idle_anim = (u8 *)&D_8017467C;
        } else {
            current_anim = map_actor->unk_2C.p2;
            idle_anim = D_80174684;
        }
        if (current_anim != idle_anim) {
            map_actor->unk_2C.p = idle_anim;
            action_data = (u8 *)(((s32) (*D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7);
            action_data += (u32)idle_anim;
            func_80047784(map_actor, *action_data, 0);
        }
state_store:
        actor->unk_9A.as_u8 = 0xEU;
    }
    actor->unk_98 = (u16) (actor->unk_98 & 0xFFF3);
    if (actor->unk_B4 != 0) {
        goto block_25;
    }
    if ((u16) *D_80013714 & 8) {
        goto block_25;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_64.as_s16 == 0) {
        goto block_28;
    }
    if (func_800AA6B4(actor, context, map_actor, D_801746C4) == 0) {
        goto block_28;
    }
    return;
block_25:
    if (((Rec_D_800E3D7C *)entity)->unk_64.as_s16 == 0) {
        goto block_28;
    }
    dungeon_state = D_80083460;
    if (dungeon_state[4] != (entity - 0x20)) {
        goto block_28;
    }
    dungeon_state[4] &= 0x7FFFFFFF;
block_28:
    if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x80000)) {
        goto block_31;
    }
    func_800AA888(actor, context, map_actor, entity);
    func_8016DAA4(actor, context, map_actor, entity);
    map_actor->unk_2C.p = D_8017467C;
    func_80047784(map_actor, D_8017467C[((s32) (*D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    actor->unk_90.at00_s32.v = 0;
    return;
block_31:
    if ((func_800A1C58(entity) << 0x10) == 0) {
        goto block_33;
    }
    ((Rec_D_800E3D7C *)entity)->unk_18 = 0;
    *D_8008346C = 0;
block_33:
    tile_index = func_8009FB34(map_actor->unk_24.at00.v, map_actor->unk_24.at01.v);
    map_actor->unk_26 = tile_index;
    if (((Rec_D_800E3D7C *)entity)->unk_6D.as_s8 <= 0) {
        goto block_58;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x20) {
        goto block_50;
    }
    if (map_actor->unk_24.at00u.v == *D_80082EA4) {
        goto block_56;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x8000) {
        goto block_44;
    }
    if (!(*D_80083462 & 0x2000)) {
        goto block_39;
    }
    if ((func_8009A180(entity, ((S_8016B778_3 *)(*D_800814A8))->unk_58 + 0x20) << 0x10) != 0) {
        goto block_65;
    }
block_39:
    if (!((u16) *D_80013714 & 8)) {
        goto block_42;
    }
    func_8016EF10(actor, context, map_actor);
    ((Rec_D_800E3D7C *)entity)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)entity)->unk_71.as_u8 & 0x7F);
    func_800A9A0C(entity);
    ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v &= 0x7FFF;
    return;
block_42:
    if ((func_8016C98C(actor, context, map_actor, 0) << 0x10) == 0) {
        goto block_65;
    }
    action_flags = ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v | 0x4000;
    ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v = action_flags;
    if (!(action_flags & 0x8000)) {
        goto block_56;
    }
block_44:
    action_id = ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x3FFF;
    if ((u32) (action_id - 1) >= 0xCU) {
        goto block_55;
    }
    (void)action_labels; goto *D_8016A828[(u32)((action_id) - 1)];
jt_c8:
jt_c9:
    if ((func_8016C720(actor, context, map_actor, entity) << 0x10) != 0) {
        goto block_65;
    }
    func_8016C8AC(actor, context, map_actor, entity);
    return;
jt_c5:
jt_c6:
jt_c7:
    target_angle = func_800A0818(map_actor->unk_24.at00.v, map_actor->unk_24.at01.v, D_80082E80[0x24], D_80082E80[0x25], &target_distance);
    active_actor = (u8 *)*D_800814A8;
    ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = target_angle;
    if (((S_8016B778_4 *)active_actor)->unk_9A == 0x11) {
        action_data = (u8 *)0x80170000;
        goto block_53_low;
    }
jt_c12:
block_50:
    func_800A9A0C(entity);
    return;
jt_c1:
jt_c2:
jt_c3:
    action_data = (u8 *)0x80170000;
block_53_low:
    action_data -= 0x4888;
block_53:
    func_800AAF00(actor, context, map_actor, &D_801746BC, action_data);
    return;
jt_c4:
jt_c10:
jt_c11:
block_55:
block_56:
    func_8016BF74(actor, context, map_actor, entity);
    return;
block_58:
    entity_flags = ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32;
    if (entity_flags & 0x2000) {
        goto block_65;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    if ((u16) *D_80013714 & 8) {
        goto block_65;
    }
    if (tile_index < 0) {
        goto block_62;
    }
    tile_table = D_800E2970;
    tile_entry = (tile_index * 0x14) + tile_table;
    if (((S_8016B778_5 *)tile_entry)->unk_0C & 2) {
        goto block_65;
    }
block_62:
    if (entity_flags & 0x430) {
        goto block_65;
    }
    target_actor = D_80082E80;
    if ((func_8009FD7C(map_actor->unk_24.at00.v, map_actor->unk_24.at01.v, target_actor[0x24], target_actor[0x25]) << 0x10) == 0) {
        goto block_65;
    }
    ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = func_800A0818(map_actor->unk_24.at00.v, map_actor->unk_24.at01.v, target_actor[0x24], target_actor[0x25], &target_distance);
block_65:
    return;
}

#ifndef DUNGEON_OVL_7CE800_H
#define DUNGEON_OVL_7CE800_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "modules/dungeon_native_abi.h"
extern void *D_800FBE1C;
typedef union { u8 first; s8 bytes[9]; } DungeonFlagBuffer9;
extern DungeonFlagBuffer9 D_800DCF5B;
ObjectNodeHeader *func_8003FC64(s32);
void func_8003DB94(void *,void *,s32);
struct ColorPart;
struct DungeonObject;
struct Position3;
struct S807AF9A4;
struct S_807AFB48_0;
struct S_807AFB48_2;
struct S_807AFC9C_2;
struct S_807AFC9C_4;
struct S_807B09A0_0;
struct UnkStruct807B11B8;
typedef struct DirectionOffsets {
    u16 x0;
    u16 y0;
    u16 x1;
    u16 y1;
    u16 x2;
    u16 y2;
    u16 x3;
    u16 y3;
    u16 x4;
    u16 y4;
    u16 x5;
    u16 y5;
    u16 x6;
    u16 y6;
    u16 x7;
    u16 y7;
} __attribute__((packed)) DirectionOffsets;
extern const DirectionOffsets dungeon_7ce800_directions;
void func_800F6070(M2C_UNK unused_first, M2C_UNK unused_second, M2C_UNK value);
void func_800F6090(s16 x, s16 y);
void func_800F6160(u8 *state, u8 *actor, u8 *target);
void func_800F643C(s16 x, s16 y, s32 slot);
void func_800F6544(void *data);
void func_800F65CC(void);
void func_800F6738(void);
void func_800F678C(void *owner);
void func_800F6ACC(void);
void func_800F6AF4(void);
s32 func_800F6D28(s16 *target_pos);
void *func_800F6DFC(void *entity);
s32 func_800F6E48(struct DungeonObject *object, u16 *origin);
void func_800F71A4(struct S807AF9A4 *data);
void func_800F72E4(void *sourceData);
void func_800F7348(void *transition, struct S_807AFB48_0 *position, struct S_807AFB48_2 *color);
void func_800F749C(s32 spawn_arg, struct S_807AFC9C_2 *origin, struct S_807AFC9C_4 *source);
void func_800F75EC(void *effect, struct Position3 *position, struct ColorPart *tint);
void func_800F784C(void *parent_data);
void func_800F7910(void *motion_data, s16 *position);
void func_800F7A38(EntityRec *source, s16 state_value, s32 render_value);
void func_800F7B5C(void);
void func_800F7BA0(void);
void func_800F7BC0(void);
s32 func_800F7C0C(void);
void func_800F80D4(void);
void func_800F80F0(s16 tile_x, s16 tile_y, s16 initial_value);
void func_800F81A0(struct S_807B09A0_0 *emitter);
s32 func_800F833C(void *object, s32 caller_a1, void *caller_a2);
void func_800F89B8(u16 *object_data, struct UnkStruct807B11B8 *motion, u16 *update_state);
#endif

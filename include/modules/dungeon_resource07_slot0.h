#ifndef DUNGEON_RESOURCE07_SLOT0_H
#define DUNGEON_RESOURCE07_SLOT0_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/def_table.h"
#include "records/Rec_func_80172CC0_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_func_801736F4_arg0.h"

typedef s32 R07_80170854_M2C_UNK;
typedef struct R07_80170854_S_8016A854_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} R07_80170854_S_8016A854_0;
typedef struct R07_80170854_S_8016A854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} R07_80170854_S_8016A854_1;
typedef struct R07_80170854_S_8016A854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} R07_80170854_S_8016A854_2;
typedef struct R07_80170854_S_8016A854_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} R07_80170854_S_8016A854_3;
typedef struct R07_80170854_S_8016A854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} R07_80170854_S_8016A854_4;
typedef void (*R07_80170A28_EntityCallback)(void *, void *, void *, void *);
typedef struct R07_80170A28_S_80170A28_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} R07_80170A28_S_80170A28_0;
typedef struct R07_80170A28_S_80170A28_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} R07_80170A28_S_80170A28_1;
typedef struct R07_80170A28_S_80170A28_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R07_80170A28_S_80170A28_2;
typedef struct R07_80170E54_S_80170E54_2 {
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
    } unk_24;   
    u8 unk_26;
    u8 pad_27[0x5];
    union { void * p; u8 * p2; } unk_2C;   
    u8 pad_30[0x8B];
    u8 unk_BB;
} R07_80170E54_S_80170E54_2;
typedef struct R07_80170E54_S_80170E54_7 {
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
} R07_80170E54_S_80170E54_7;
typedef struct R07_80170E54_S_80170E54_8 {
    u8 pad_00[0x4];
    s32 unk_04;
} R07_80170E54_S_80170E54_8;
typedef struct R07_80170E54_S_80170E54_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} R07_80170E54_S_80170E54_9;
typedef struct R07_80171570_S_80171570_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x18];
    s16 unk_8A;
} R07_80171570_S_80171570_0;
typedef struct R07_80171570_S_80171570_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} R07_80171570_S_80171570_2;
typedef struct R07_80171570_S_80171570_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R07_80171570_S_80171570_3;
typedef struct R07_801717B4_S_80171C34_1 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x1];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { s16 s; u16 u; } unk_2A;   
    u8 pad_2C[0x19];
    u8 unk_45;
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   
    u8 pad_6E[0x3];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x16];
    union { u16 u; s16 s; } unk_88;   
} R07_801717B4_S_80171C34_1;
typedef struct R07_801717B4_S_80171C34_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   
    union { s8 s; u8 u; } unk_26;   
} R07_801717B4_S_80171C34_2;
typedef struct R07_801717B4_S_80171C34_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R07_801717B4_S_80171C34_3_pre;
typedef struct R07_801717B4_S_80171C34_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} R07_801717B4_S_80171C34_3;
typedef struct R07_801717B4_S_80171C34_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   
} R07_801717B4_S_80171C34_5;
typedef struct R07_801717B4_S_80171C34_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R07_801717B4_S_80171C34_7;
typedef struct R07_801717B4_S_80171C34_8 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R07_801717B4_S_80171C34_8;
typedef struct R07_801717B4_DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} R07_801717B4_DungeonRecord;
typedef struct R07_80172184_Ent R07_80172184_Ent;
typedef struct R07_8017229C_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} R07_8017229C_S_80172628_0;
typedef struct R07_801723E0_S_801724A8_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   
} R07_801723E0_S_801724A8_0;
typedef struct R07_80172478_S_80172478_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    union { s16 s; u16 u; } unk_A8;   
} R07_80172478_S_80172478_0;
typedef struct R07_80172478_S_80172478_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} R07_80172478_S_80172478_2;
typedef struct {
    u8 pad0[0x8C];
    void (*callback)(void *, void *, void *, void *);
} Resource07CallbackState;
typedef struct R07_8017284C_S_8017284C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} R07_8017284C_S_8017284C_0;
typedef struct R07_80172CC0_S_80172CC0_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} R07_80172CC0_S_80172CC0_1_pre;
typedef struct R07_80172CC0_S_80172CC0_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R07_80172CC0_S_80172CC0_2;
typedef struct R07_80173238_S_80173238_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   
    u8 pad_98[0x3];
    u8 unk_9B;
} R07_80173238_S_80173238_1;
typedef struct R07_80173238_S_80173238_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R07_80173238_S_80173238_2;
typedef struct {
    s8 pad_00[0x8C];
    void *unk_8C;
} R07_80173EF4_Actor;
typedef struct {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} R07_80173EF4_Entity;
typedef struct {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} R07_80173EF4_MapObject;
s32 func_8003FD64();
s32 func_8004491C();
s32 func_800A6D30();
s32 func_800A48F0();
void func_800A9C18();
s32 func_800AA36C();
void func_80047738();
void func_800478B8();
void func_800A020C();
s32 func_800A9E70();
s16 func_800BCB04();
s32 func_8003DE58();
void func_80047784();
s32 func_80069EF8();
s32 func_8009A180();
s32 func_8009FB34();
s32 func_8009FD7C();
s32 func_800A0818();
s32 func_800A1C58();
void func_800A9A0C();
void func_800AA258();
s32 func_800AA6B4();
s32 func_800AA79C();
void func_800AA888();
s32 func_800AA924();
s32 func_800AAB10();
void func_800AAF00();
void func_8009A21C();
void func_8009A3D0();
s32 func_8009A66C();
s32 func_800A19E4();
s32 func_800A02AC();
s32 func_800A04F0();
s32 func_800A0134();
s32 func_8009A540();
s32 func_800A0E6C();
s32 func_8009C93C();
s32 func_800A2B5C();
u32 func_800A2CB8();
s32 func_800C7930();
s32 func_800A2BDC();
s32 func_800ADDA0();
s32 func_800A4ACC();
s32 func_800AB1C0();
void func_800AD594();
s32 func_800AD9B4();
s32 func_800644B8();
void func_800A2B04();
void func_800A9A04();
s32 func_800AB378();
s32 func_8009C12C();
s32 func_800A56E0();
s32 func_8003F270();
s32 func_800A05A4();
s32 func_800A94A0();
void func_800DA840();
void func_800AAA54();
void func_800AD4D0();
s32 func_800AD058();
s32 func_800AB538();
s32 func_800AB778();
s32 func_800ABDBC();
s32 func_80042900();
void func_80042B68();
s32 func_8009FD40();
s32 func_800A2C34();
s32 func_800AC82C();
s32 func_800AC010();
s32 func_800AC480();
s32 func_800AC5C8();
s32 func_800ACE34();
s32 func_800AB464();
s32 func_800AC7EC();
extern u8 D_80174148[];
extern u8 D_80174190[];
extern u8 D_80174198[];
extern u8 D_800D79B0[];
extern u8 D_800DEA68[];
extern u8 D_80174140[];
extern u8 D_80174150[];
extern u8 D_80174188[];
extern u8 D_80174138[];
extern u8 D_8006CD00[];
extern u8 D_80174158[];
extern u8 D_80174160[];
extern u8 D_80174168[];
extern u8 D_800E3DE8[];
extern u8 D_80174170[];
extern u8 D_80174180[];
extern u8 D_80174178[];
void *func_80170854(s16 kind_flags, s16 byte_24, s16 byte_25, s16 value_0a);
void func_80170A28(void *entity, R07_80170A28_S_80170A28_2 *motion, void *part);
void func_80170E54(void *record, EntityRec *entity, void *object, EntityRec *other_entity);
void func_80171570(void *action, s32 action_id, void *entity, void *move_state);
void func_801717B4(void *move_data, void *context, void *position_data, void *actor_data);
void func_80171EFC(void *effect, s32 *position, void *sprite, void *source);
s32 func_80171FC0(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, EntityRec *actor);
void func_80172184(void *action_state, void *action_context, void *sprite, EntityRec *actor);
s32 func_8017229C(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void func_801723E0(R07_801723E0_S_801724A8_0 *state, s32 context, s32 source, s32 target);
void func_80172478(void *action, void *motion, void *sprite, void *actor);
void func_801727E8(Resource07CallbackState *state, void *entity, void *position, void *graphic);
void func_8017284C(R07_8017284C_S_8017284C_0 *action, EntityRec *motion, Rec_D_80082E80 *sprite, EntityRec *actor);
void func_80172CC0(void *action, EntityRec *motion, void *sprite, void *actor);
void func_80173238(void *motion_state, void *motion, void *sprite, void *entity);
void func_8017365C(void *state, void *motion, void *position, void *actor);
void func_8017367C(void *state, void *motion, void *position, void *actor);
void func_8017369C(void *state, void *motion, void *position, void *actor);
void func_801736BC(Resource07CallbackState *state, void *motion, void *position, void *actor);
void func_801736F4(void *controller, s32 actor_index, void *sprite, EntityRec *actor);
void func_80173BB8(void *controller, void *context, void *sprite, EntityRec *entity);
void func_80173EF4(R07_80173EF4_Actor *actor, s32 action, R07_80173EF4_Entity *entity, R07_80173EF4_MapObject *map_object);
void func_80173FBC(Resource07CallbackState *state, void *entity, void *position, void *graphic);
void func_80174020(Resource07CallbackState *state, void *motion, void *position, void *actor);
void func_80174058(Resource07CallbackState *state, void *motion, void *position, void *actor);
void func_80174090(Resource07CallbackState *state, void *motion, void *position, void *actor);
void func_801740C8(Resource07CallbackState *state, void *motion, void *position, void *actor);
void func_80174100(Resource07CallbackState *state, void *motion, void *position, void *actor);
#endif

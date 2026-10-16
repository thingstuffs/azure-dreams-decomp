#ifndef DUNGEON_RESOURCE16_SLOT0_H
#define DUNGEON_RESOURCE16_SLOT0_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "m2c_compat.h"
#include "shared/def_table.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_func_8017360C_arg0.h"
#include "shared/object_flags.h"
#include "records/Rec_func_801732A4_arg0.h"

#define NULL 0
typedef struct R16_80170878_S_80170878_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} R16_80170878_S_80170878_0;
typedef struct R16_80170878_S_80170878_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} R16_80170878_S_80170878_1;
typedef struct R16_80170878_S_80170878_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} R16_80170878_S_80170878_2;
typedef struct R16_80170878_S_80170878_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} R16_80170878_S_80170878_3;
typedef struct R16_80170878_S_80170878_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} R16_80170878_S_80170878_4;
typedef void (*R16_80170A58_Callback)(void *, void *, void *, void *);
typedef struct R16_80170A58_S_80170A58_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} R16_80170A58_S_80170A58_2;
typedef struct R16_80171014_S_80171014_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   
} R16_80171014_S_80171014_0;
typedef struct R16_80171014_S_80171014_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x1E];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} R16_80171014_S_80171014_2;
typedef struct R16_80171574_S_80171FC8_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x16];
    u16 unk_88;
    union { s16 s; u16 u; } unk_8A;   
} R16_80171574_S_80171FC8_0;
typedef struct R16_80171574_S_80171FC8_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} R16_80171574_S_80171FC8_1;
typedef struct R16_80171574_S_80171FC8_2 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R16_80171574_S_80171FC8_2;
typedef struct R16_80171574_S_80171FC8_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x2];
    u16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
} R16_80171574_S_80171FC8_3;
typedef struct R16_80171574_S_80171FC8_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R16_80171574_S_80171FC8_4;
typedef struct R16_80171784_S_80171C34_1 {
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
} R16_80171784_S_80171C34_1;
typedef struct R16_80171784_S_80171C34_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   
    union { s8 s; u8 u; } unk_26;   
} R16_80171784_S_80171C34_2;
typedef struct R16_80171784_S_80171C34_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R16_80171784_S_80171C34_3_pre;
typedef struct R16_80171784_S_80171C34_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} R16_80171784_S_80171C34_3;
typedef struct R16_80171784_S_80171C34_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   
} R16_80171784_S_80171C34_5;
typedef struct R16_80171784_S_80171C34_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R16_80171784_S_80171C34_7;
typedef struct R16_80171784_S_80171C34_8 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R16_80171784_S_80171C34_8;
typedef struct R16_80171784_DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} R16_80171784_DungeonRecord;
typedef struct R16_80171ECC_S_80171ECC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R16_80171ECC_S_80171ECC_1;
typedef struct R16_801721B4_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} R16_801721B4_S_80172628_0;
typedef struct {
    u8 pad0[0x8C];
    void (*callback)(void *, void *, void *, void *);
} Resource16CallbackState;
typedef struct R16_801723F0_S_801723F0_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} R16_801723F0_S_801723F0_0;
typedef struct R16_801723F0_S_801723F0_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R16_801723F0_S_801723F0_3;
typedef struct R16_801725A4_S_801725A4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} R16_801725A4_S_801725A4_0;
typedef struct R16_801725A4_S_801725A4_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   
    union { u8 s; s8 u; } unk_73;   
} R16_801725A4_S_801725A4_1;
typedef struct R16_801725A4_S_801725A4_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} R16_801725A4_S_801725A4_2;
typedef struct R16_801725A4_S_801725A4_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R16_801725A4_S_801725A4_3;
typedef struct R16_801729D8_S_80173294_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; s16 p; } unk_96;   
    u8 pad_98[0x3];
    u8 unk_9B;
} R16_801729D8_S_80173294_0;
typedef struct R16_80172CCC_S_80173588_0 {
    u8 pad_00[0xA2];
    s16 unk_A2;
} R16_80172CCC_S_80173588_0;
typedef struct R16_80172D50_S_80173E50_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} R16_80172D50_S_80173E50_0;
typedef struct {
    s8 pad_00[0x8C];
    void *unk_8C;
} R16_80173468_Actor;
typedef struct {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} R16_80173468_Entity;
typedef struct {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} R16_80173468_MapObject;
typedef struct R16_801736AC_Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct R16_801736AC_Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} R16_801736AC_Entry;
typedef struct {
    u8 pad[0x13C];
    s32 value;
} R16_801736AC_Scratchpad;
typedef struct {
    u8 pad[0x5218];
    s16 value;
} R16_801736AC_GlobalPage;
typedef struct R16_80173738_S_80173738_0_pre {
    u16 unk_00;
} R16_80173738_S_80173738_0_pre;
typedef struct R16_80173738_S_80173738_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x2];
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x1E];
    s32 unk_40;
    s32 unk_44;
} R16_80173738_S_80173738_0;
typedef struct R16_80173738_S_80173738_2 {
    s32 unk_00;
} R16_80173738_S_80173738_2;
typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
} R16_80173738_FuncArg1;
typedef struct R16_80173904_S_80173904_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x2];
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0x1E];
    s32 unk_40;
    s32 unk_44;
} R16_80173904_S_80173904_0;
typedef struct R16_80173904_S_80173904_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} R16_80173904_S_80173904_1;
typedef struct R16_80173904_S_80173904_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} R16_80173904_S_80173904_2;
typedef struct R16_80173904_S_80173904_3 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} R16_80173904_S_80173904_3;
typedef struct R16_80173904_S_80173904_4 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} R16_80173904_S_80173904_4;
typedef struct {
    u8 pad0[2];
    u16 flags;
    u8 pad4[6];
    u16 count;
} R16_80173AE8_DungeonState;
typedef struct R16_80173CEC_S_80173CEC_11 {
    u8 pad_00[0x8];
    void * unk_08;
} R16_80173CEC_S_80173CEC_11;
typedef struct R16_80173CEC_S_80173CEC_12 {
    s32 unk_00;
    s32 unk_04;
} R16_80173CEC_S_80173CEC_12;
typedef struct R16_80173CEC_S_80173CEC_2 {
    u8 unk_00;
} R16_80173CEC_S_80173CEC_2;
typedef struct R16_80173CEC_S_80173CEC_3 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} R16_80173CEC_S_80173CEC_3;
typedef struct R16_80173CEC_S_80173CEC_4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} R16_80173CEC_S_80173CEC_4;
typedef struct R16_80173CEC_S_80173CEC_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} R16_80173CEC_S_80173CEC_5;
typedef struct R16_80173CEC_S_80173CEC_8 {
    u8 pad_00[0x8];
    s32 unk_08;
} R16_80173CEC_S_80173CEC_8;
typedef struct R16_80173CEC_S_80173CEC_9 {
    u8 pad_00[0xC];
    union { s32 s; void * u; } unk_0C;   
    s32 unk_10;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} R16_80173CEC_S_80173CEC_9;
extern s32 abs(s32);
extern s32 rand(void);
s32 Control_CD();
s32 func_8003FD64();
s32 func_8004491C();
s32 func_800A48F0();
s32 func_800A6D30();
void func_800A9C18();
s32 func_800AA36C();
void func_80047738();
s32 func_800478B8();
s32 func_800644B8();
void func_800A020C();
s32 func_800A9E70();
s16 func_800BCB04();
s32 func_80047784();
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
s32 func_8009A21C();
s32 func_8009A3D0();
s32 func_800A19E4();
s32 func_800A02AC();
s32 func_800A04F0();
s32 func_800A0134();
s32 func_8009A540();
s32 func_800A0E6C();
s32 func_8009A8C0();
s32 func_8009C93C();
s32 func_800A2B5C();
u32 func_800A2CB8();
s32 func_800C7930();
s32 func_800A2BDC();
s32 func_800ADDA0();
s32 func_800A4ACC();
s32 func_800AB1C0();
s32 func_800AD594();
s32 func_800AD9B4();
s32 func_800AB378();
s32 func_8009C12C();
s32 func_800A56E0();
s32 func_8003F270();
s32 func_800A05A4();
void func_800A2B04();
s32 func_800A94A0();
void func_800BB044();
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
void func_800A9A04();
s32 func_80175060();
s32 func_800AC82C();
s32 func_800AC010();
s32 func_800AC480();
s32 func_800AC5C8();
s32 func_800AC7EC();
s32 func_800ACE34();
s32 func_800AB464();
void func_800453E0();
s32 func_8003DB94();
s32 func_80064584();
void func_80044A50();
void func_8003F540();
void func_80041588();
int func_800445E0();
s32 func_800498A0();
s32 func_80069EF8();
void func_8009A028();
void func_800A18E8();
s32 func_800A504C();
s32 func_800ADC4C();
s32 func_800C77D0();
extern u8 D_8017420C[];
extern u8 D_8017425C[];
extern u8 D_8017426C[];
extern u8 D_8017421C[];
extern u8 D_8017424C[];
extern u8 D_80174254[];
extern u8 D_8006CD00[];
extern u8 D_80174214[];
extern u8 D_8017423C[];
extern u8 D_80174244[];
extern u8 D_80174264[];
extern u8 D_801742E0[];
extern u8 D_800DEC70[];
extern u8 D_800DCF5E[];
extern u8 D_801742E8[];
extern u8 D_8003E140[];
extern u8 D_8006CD58[];
extern u8 D_800DCEEC[];
extern u8 D_800DCF5C[];
extern u8 D_8014A000[];
extern u8 D_801742CC[];
extern u8 D_801742D4[];
extern u8 D_801742E4[];
extern u8 D_801742E5[];
void *func_80170878(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c);
void func_80170A58(void *entity, EntityRec *motion, void *sprite);
void func_80171014(void *actor, void *actor_context, void *map_object, EntityRec *creature);
void func_80171574(void *motion_state, s32 unused, void *entity, void *path_state);
void func_80171784(void *move_data, void *context, void *position_data, void *actor_data);
s32 func_80171ECC(void *action_state, s32 action_id, void *source_obj, EntityRec *actor);
void func_80172090(Rec_func_800A9E70_arg0 *action_state, M2C_UNK context, Rec_D_80082E80 *animation, EntityRec *actor);
s32 func_801721B4(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void func_801722F8(void *state, s32 unused, s32 source, s32 target);
void func_8017238C(Resource16CallbackState *state, void *entity, void *position, void *graphic);
void func_801723F0(void *action, void *motion, void *anim, void *actor);
void func_801725A4(void *owner, void *motion, void *actor, void *object_in);
void func_801729D8(R16_801729D8_S_80173294_0 *motion_state, EntityRec *motion, Rec_D_80082E80 *tile_state, void *entity);
void func_80172CAC(void *state, void *motion, void *position, void *actor);
void func_80172CCC(R16_80172CCC_S_80173588_0 *state, void *context, void *data);
void func_80172CF8(void *state, void *motion, void *position, void *actor);
void func_80172D18(Resource16CallbackState *state, void *motion, void *position, void *actor);
void func_80172D50(void *actor, void *context, void *render_record, EntityRec *actor_state);
void func_80173114(void *actor, void *context, void *animation, EntityRec *entity);
void func_80173468(R16_80173468_Actor *actor, s32 action, R16_80173468_Entity *entity, R16_80173468_MapObject *map_object);
void func_80173530(Resource16CallbackState *state, void *entity, void *position, void *graphic);
void func_80173594(Resource16CallbackState *state, void *motion, void *position, void *actor);
void func_801735CC(Resource16CallbackState *state, void *motion, void *position, void *actor);
void func_80173604(Resource16CallbackState *state, void *motion, void *position, void *actor);
void func_8017363C(Resource16CallbackState *state, void *motion, void *position, void *actor);
void func_80173674(Resource16CallbackState *state, void *motion, void *position, void *actor);
s32 func_801736AC(void *initial_payload, s32 entry_data, R16_801736AC_Entry *entry, s32 unused);
void func_80173738(void *effect, R16_80173738_FuncArg1 *position, Rec_D_80082E80 *primitive);
void func_80173904(
    s32 unused_0, R16_80173904_S_80173904_3 *origin, s32 unused_2, s32 unused_3, s16 angle, u16 depth_offset);
void func_80173AE8(void *entity_data, s32 unused_1, s32 unused_2, void *other_data);
void func_80173B94(void *entity_data, void *unused, void *source_data);
void func_80173CEC(Rec_func_801732A4_arg0 *state, EntityRec *position, Rec_D_80082E80 *actor, void *model);
#endif

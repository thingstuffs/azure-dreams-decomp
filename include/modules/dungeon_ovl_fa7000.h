#ifndef DUNGEON_OVL_FA7000_H
#define DUNGEON_OVL_FA7000_H
#include "common.h"
#include "shared/entity.h"
#include "shared/tile_object.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"
typedef struct BankFA_fa8b9c_BankActorState BankFA_fa8b9c_BankActorState;
typedef struct BankFA_fa8c30_BankActorState BankFA_fa8c30_BankActorState;
typedef struct BankFA_fa9d44_BankActorState BankFA_fa9d44_BankActorState;
typedef struct BankFA_faa538_BankActorState BankFA_faa538_BankActorState;
typedef struct BankFA_faa600_BankActorState BankFA_faa600_BankActorState;
typedef struct BankFA_faa664_BankActorState BankFA_faa664_BankActorState;
typedef struct BankFA_faa69c_BankActorState BankFA_faa69c_BankActorState;
typedef struct BankFA_faa6d4_BankActorState BankFA_faa6d4_BankActorState;
typedef void (*BankActorCallback)(void *,s32,SpriteFrameState *,EntityRec *);
extern u8 D_80174AD4[];
void func_80047784();
s32 func_8009FD7C();
void func_8009A3D0();
void func_8009A21C();
s32 func_8009A180();
s16 func_800BCB04();
s16 func_800A0134();
s32 func_800A04F0();
s32 func_800C7930();
s32 func_800A4ACC();
void func_800AD594();
s32 func_800AA6B4();
s32 func_800A0818();
void * func_8003FD64();
s32 func_8004491C();
s32 func_800A56E0();
void *func_80170880(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);
void func_80170A70(void *entity, void *motion_arg, void *sprite_arg);
void func_80171138(void *actor_in, void *context_in, void *sprite_in, void *stats_in);
void func_80171670();
void func_8017182C(Rec_func_800A9E70_arg0 *move_data, void *context, TileObject *position_data, EntityRec *actor_data);
s32 func_80171F74(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, EntityRec *actor);
void func_80172138(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, EntityRec *entity);
s32 func_80172258(EntityRec *actor, void *primary_context, void *secondary_context, s32 force_move);
void func_8017239C(BankFA_fa8b9c_BankActorState *state, s32 unused, SpriteFrameState *source, EntityRec *target);
void func_80172430(BankFA_fa8c30_BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target);
void func_80172494(void *action, void *motion, void *map_actor, void *actor_arg);
void func_80172A40(void *owner_input, EntityRec *motion_input, void *actor_input, EntityRec *object);
void func_80172F00(void *action, EntityRec *motion, void *sprite, EntityRec *entity);
void func_80173294(void *effect_data, void *motion_data, void *sprite_data, void *object_data);
void func_80173504(void *state, s32 action, SpriteFrameState *source, EntityRec *target);
void func_80173524(void *state, s32 action, SpriteFrameState *source, EntityRec *target);
void func_80173544(BankFA_fa9d44_BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target);
void func_8017357C(void *controller, EntityRec *motion, void *sprite, EntityRec *actor);
void func_801739F8(void *controller, void *context, void *sprite, void *entity);
void func_80173D38(BankFA_faa538_BankActorState *actor, s32 action, SpriteFrameState *sprite, EntityRec *target);
void func_80173E00(BankFA_faa600_BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target);
void func_80173E64(BankFA_faa664_BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target);
void func_80173E9C(BankFA_faa69c_BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target);
void func_80173ED4(BankFA_faa6d4_BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target);
void func_80173F0C(void *effect, void *position, void *visual);
void func_801740F4(void *work, void *part_a, void *part_b, EntityRec *actor);
void func_80174260(void *state_input, void *motion_input, void *animation_input, void *actor_input);
void func_801745E0(void *state);
#endif

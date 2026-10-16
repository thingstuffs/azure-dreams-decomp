#ifndef DUNGEON_OVL_19CC800_H
#define DUNGEON_OVL_19CC800_H
#include "shared/dungeon_effect_views.h"
#include "modules/dungeon_native_abi.h"
#include "shared/animation_views.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "records/Rec_func_800249DC_arg0.h"
typedef struct MotionRecord {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x28];
    s16 speed;          /* 0x30 */
    u8 pad_32[4];
    s16 direction;      /* 0x36 */
} MotionRecord;
typedef struct FollowerRecord {
    u8 pad_00[8];
    ObjectNodeHeader *owner;
    u8 pad_0C[42];
    s16 angle;
} FollowerRecord;
typedef struct EffectSprite {
    u8 pad_00[6]; s16 unk_06; void *unk_08;
    union { s32 color; s32 unk_0C; } shade;
    u8 pad_10[10]; s16 angle; s16 size; s16 size_max;
} EffectSprite;
extern u16 D_80027452[8];
extern s16 D_80027450;
extern u8 D_80027460[12];

struct EffectColor;
struct Entry;
struct EventState;
struct FrameState;
struct Motion;
struct Position;
struct RenderData;
struct S_8002593C_1;
struct S_8002593C_2;
struct S_80025B78_2;
struct S_80025B78_4;
struct S_819ACB28_4;

void func_80024020(struct EventState *event);
void dungeonAdvanceEffectPhases(void *object, Rec_func_800249DC_arg0 *record, struct S_819ACB28_4 *packed_value);
void *dungeonAllocateInitializedEffectObject(EntityRec *source_pos, s32 offset_base);
void dungeonRunWarpCutscene(struct Motion *motion, struct Position *position, u8 *color);
void *func_800249DC(void *src);
void dungeonAdvanceEffectMotionAndSpeed(MotionRecord *motion, EntityRec *position);
void dungeonUpdateEffectPositionAndColor(ObjectNodeHeader *source, s16 effect_param, s32 render_param);
void dungeonCopyFollowerOwnerPositionAndColor(FollowerRecord *record, EntityRec *position, struct RenderData *render);
void func_80024EF8(ObjectNodeHeader *owner, s16 angle);
void dungeonUpdateWarpCameraAndEffects(void *entity, void *motion, void *gfx);
void *dungeonCreateLinkedSpritePieces(s16 x, s16 y, s16 z, s16 heading);
void func_800257D0(struct FrameState *dst, struct AnimEntry *src);
void dungeonAdvanceAnimationIndexWithinBounds(AnimPlayer *player, s16 *index_step, s32 min_index, s32 max_index);
void dungeonSetAnimationEntryAddress(AnimPlayer *player, s16 entry_index);
void func_8002593C(void *base_matrix, struct S_8002593C_1 *position, struct S_8002593C_2 *rotation);
void dungeonFadeColorToBlack(void *owner, s32 unused, void *color_data);
s32 dungeonProcessEffectBufferChain(void *initial_state, s32 initial_value, struct Entry *initial_entry);
void *dungeonCreateCopiedEffectObject(void *source_data, struct S_80025B78_2 *source_triplet, struct S_80025B78_4 *source_state);
void func_80025D28(void *state, void *points, void *appearance);
void *func_80025FCC(s16 x, s16 y, s16 z, s16 effect_param);
void dungeonFadeEffectColorToBlack(void *record, s32 unused, struct EffectColor *color);
void *func_8002614C(s16 x, s16 y, s16 z, s16 angle, s16 spawn_actor);
s32 resolveRecordOrientationOrFallback(void *, void *, void *, s32);
s32 rand(void);
s32 func_800C9034(void *, s32, void *);
s32 dungeonProcessLinkedMeshStatesMode0(void *, s32, void *);
#endif

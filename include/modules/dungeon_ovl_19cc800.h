#ifndef DUNGEON_OVL_19CC800_H
#define DUNGEON_OVL_19CC800_H
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "records/Rec_func_800249DC_arg0.h"
typedef struct EffectPosition {
    u8 pad_00[2];
    u16 x;
    u8 pad_04[2];
    u16 y;
    u8 pad_08[2];
    u16 z;
} EffectPosition;
typedef union FixedCoord {
    s32 fixed;
    struct {
        u16 frac;
        s16 whole;
    } part;
} FixedCoord;
typedef struct FixedEffectPosition {
    FixedCoord x;
    FixedCoord y;
    FixedCoord z;
} FixedEffectPosition;
typedef struct SignedEffectPosition {
    s16 pad_00;
    s16 x;
    s16 pad_04;
    s16 y;
    s16 pad_08;
    s16 z;
} SignedEffectPosition;
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
typedef struct AnimPlayer {
    s32 entry;
    u8 index;           /* current entry number, signed when compared */
    u8 pad_05[0x3];
    void *owner;
    u8 pad_0C[0x8];
    u16 flags;          /* 0x4000 set while the index is clamped to a bound */
} AnimPlayer;
typedef struct AnimOwner {
    u8 pad_00[0xC];
    s32 table;
} AnimOwner;
typedef struct EffectSprite {
    u8 pad_00[6]; s16 unk_06; void *unk_08;
    union { s32 color; s32 unk_0C; } shade;
    u8 pad_10[10]; s16 angle; s16 size; s16 size_max;
} EffectSprite;
extern u16 D_80027452[8];
extern s16 D_80027450;
extern u8 D_80027460[12];
struct AnimEntry;
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
void func_80024328(void *object, Rec_func_800249DC_arg0 *record, struct S_819ACB28_4 *packed_value);
void *func_800244C4(EffectPosition *source_pos, s32 offset_base);
void func_800245A0(struct Motion *motion, struct Position *position, u8 *color);
void *func_800249DC(void *src);
void func_80024B00(MotionRecord *motion, FixedEffectPosition *position);
void func_80024C38(ObjectNodeHeader *source, s16 effect_param, s32 render_param);
void func_80024E60(FollowerRecord *record, EffectPosition *position, struct RenderData *render);
void func_80024EF8(ObjectNodeHeader *owner, s16 angle);
void func_8002501C(void *entity, void *motion, void *gfx);
void *func_800255B8(s16 x, s16 y, s16 z, s16 heading);
void func_800257D0(struct FrameState *dst, struct AnimEntry *src);
void func_80025840(AnimPlayer *player, s16 *index_step, s32 min_index, s32 max_index);
void func_8002590C(AnimPlayer *player, s16 entry_index);
void func_8002593C(void *base_matrix, struct S_8002593C_1 *position, struct S_8002593C_2 *rotation);
void func_80025A34(void *owner, s32 unused, void *color_data);
s32 func_80025AAC(void *initial_state, s32 initial_value, struct Entry *initial_entry);
void *func_80025B78(void *source_data, struct S_80025B78_2 *source_triplet, struct S_80025B78_4 *source_state);
void func_80025D28(void *state, void *points, void *appearance);
void *func_80025FCC(s16 x, s16 y, s16 z, s16 effect_param);
void func_800260D4(void *record, s32 unused, struct EffectColor *color);
void *func_8002614C(s16 x, s16 y, s16 z, s16 angle, s16 spawn_actor);
s32 func_8003DE58(void *, void *, void *, s32);
ObjectNodeHeader *func_8003FC64(s32);
s32 rand(void);
s32 func_800C9034(void *, s32, void *);
s32 func_800CEEFC(void *, s32, void *);
#endif

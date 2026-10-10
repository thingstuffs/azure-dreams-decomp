#ifndef DUNGEON_OVL_198A800_H
#define DUNGEON_OVL_198A800_H
#include "modules/dungeon_native_abi.h"

/* Promoted Layer-2 record names and layouts are shared without changing the bodies. */
/* Position the point is projected from: three 4-byte slots, only the second halfword of each is used. */
typedef struct PointPosition {
    u16 pad_00;
    u16 x;
    u16 pad_04;
    u16 y;
    u16 pad_08;
    u16 z;
} PointPosition;

/* The effect point's record (the object header precedes it). */
typedef struct PointRecord {
    u8 pad_00[8];
    u32 color;          /* r/g/b/code word copied into the tile */
    u8 pad_0C[0x26];
    s16 brightness;     /* 0x80 = full */
} PointRecord;

/* GPU scratchpad (0x1F800000) workspace used while projecting. */
typedef struct Scratch80024124 {
    u16 x;
    u16 y;
    u16 z;
    u8 pad06[0x12];
    u8 *cursor;
    u8 pad1C[4];
    u32 *ot;
    u8 pad24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad98[0x28];
    u32 index;
} Scratch80024124;

/* Shaded tile (code 0x6A, 3 words) or draw-mode packet (3 words). */
typedef struct Packet80024124 {
    u32 tag;
    u8 r;
    u8 g;
    u8 b;
    u8 code;
    u32 data;
} Packet80024124;

/* Three 4-byte slots; only the second halfword of each is used. */
typedef struct EffectPosition {
    u16 pad_00;
    u16 x;
    u16 pad_04;
    u16 y;
    u16 pad_08;
    u16 z;
} EffectPosition;

/* The spawned effect's record (the object header precedes it). */
typedef struct SpawnedRecord {
    u8 pad_00[8];
    s32 unk_08;
    u8 pad_0C[8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} SpawnedRecord;
#include "shared/tile_object.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/slus_callbacks.h"
typedef struct S_8196B4A4_0 {
    u8 pad_00[0x2C];
    s16 unk_2C;
    u8 pad_2E[0x5E];
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    u8 pad_98[0x8];
    s32 unk_A0;
} S_8196B4A4_0;
typedef struct S_8196B4A4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8196B4A4_1;
typedef struct S_8196B4A4_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_8196B4A4_2;
typedef struct S_8196B4A4_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8196B4A4_3;
typedef struct S_8196B4A4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8196B4A4_4;
typedef struct S_8196B4A4_5 {
    u8 pad_00[0x26];
    s16 unk_26;
} S_8196B4A4_5;
typedef struct {
    u8 bytes[0x20];
} LocalPoints;
typedef struct {
    s16 x;
    u16 y;
} LocalPoint;
typedef struct S_8196BF24_0_pre {
    u16 unk_00;
} S_8196BF24_0_pre;
typedef struct S_8196BF24_0 {
    u8 pad_00[0x2C];
    union { u16 s; s16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x12];
    u8 unk_40;
    u8 unk_41;
} S_8196BF24_0;
typedef struct S_8196BF24_1 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_8196BF24_1;
typedef struct S_8196BFB0_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
        struct { u8 pad[0x2]; u16 v; } at02p;
    } unk_08;   /* overlapping accesses */
} S_8196BFB0_0;
typedef struct S_8196BFB0_1 {
    u8 pad_00[0x2C];
    s16 unk_2C;
    u8 pad_2E[0x22];
    s16 unk_50;
    u8 pad_52[0x3A];
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
    s32 unk_9C;
    s32 unk_A0;
} S_8196BFB0_1;
typedef struct S_8196BFB0_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    union { u16 u; s16 s; } unk_1C;   /* accessed as both */
    union { u16 u; s16 s; } unk_1E;   /* accessed as both */
} S_8196BFB0_2;
typedef struct S_8196BFB0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8196BFB0_3;
typedef struct S_8196BE48_0_pre {
    u16 unk_00;
} S_8196BE48_0_pre;
typedef struct S_8196BE48_0 {
    u8 pad_00[0x2C];
    u16 unk_2C;
    u8 pad_2E[0x6];
    u16 unk_34;
    u8 pad_36[0xA];
    u8 unk_40;
    u8 unk_41;
    u8 pad_42[0xE];
    u16 unk_50;
} S_8196BE48_0;
typedef struct S_8196BE48_1 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_8196BE48_1;
typedef struct S_8196B074_0 {
    u8 pad_00[0x2C];
    u16 unk_2C;
    u8 pad_2E[0x5E];
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
    s32 unk_9C;
    s32 unk_A0;
} S_8196B074_0;
typedef struct S_8196B074_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
} S_8196B074_1;
typedef struct S_8196BD3C_0 {
    u8 pad_00[0x2C];
    s16 unk_2C;
    u8 pad_2E[0x4E];
    void * unk_7C;
} S_8196BD3C_0;
typedef struct S_8196BD3C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8196BD3C_1;
typedef struct S_8196BD3C_2_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_8196BD3C_2_pre;
typedef struct {
    u32 word[3];
} __attribute__((packed)) PackedVec3;
typedef struct {
    u8 pad0[6];
    s16 field6;
    void *vector;
    u8 red;
    u8 green;
    u8 blue;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 flags;
    u8 pad16[6];
    s16 scaleY;
    s16 scaleX;
} Display;
typedef struct S_8196BA5C_0 {
    u8 pad_00[0x2C];
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x10];
    u8 unk_40;
    u8 unk_41;
    u8 pad_42[0xE];
    s16 unk_50;
    u8 pad_52[0x2A];
    void * unk_7C;
} S_8196BA5C_0;
typedef struct S_8196BA5C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8196BA5C_1;
typedef struct S_8196BA5C_2_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_8196BA5C_2_pre;
typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} Rect16;
typedef struct {
    Rect16 rect[8];
} RectTable;
typedef struct {
    u32 word[4];
} __attribute__((packed)) PackedBlock;
typedef struct {
    u32 word[4];
} AlignedBlock;
typedef struct {
    s16 x;
    s16 y;
} OffsetPair;
typedef struct {
    OffsetPair p[8];
} OffsetTable;
typedef struct {
    u8 bytes[12];
} Template12 __attribute__((packed));
typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Position;
typedef struct {
    u8 pad0[6];
    s16 unk6;
    void *image;
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
    s16 unk10;
    u8 pad12[2];
    u16 flags;
    u8 pad16[6];
    s16 scale_x;
    s16 scale_y;
} Sprite;
typedef struct {
    u8 pad0[0x8C];
    s32 vel_x;
    s32 vel_y;
    s32 vel_z;
    u8 pad98[8];
    s32 accel_z;
} Motion;
typedef struct {
    u8 pad0[4];
    void *object;
    u8 kind;
    u8 pad9;
    s16 state;
    s16 x;
    s16 y;
    s16 z;
    s16 old_x;
    s16 old_y;
    s16 old_z;
    s16 mid_x;
    s16 mid_y;
    s16 mid_z;
    u8 pad1E[2];
    s16 timer;
    u8 pad22[4];
    s16 table_index;
    u8 pad28[4];
    u16 counter;
} Work;
typedef struct {
    u8 pad0[8];
    void *field8;
} SearchContext;
typedef struct {
    u8 pad0[0x60];
    void *field60;
} DungeonState;
typedef struct {
    s16 value;
    u8 pad2[10];
} S16Global;
typedef struct S_8196ACE4_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_08;   /* overlapping accesses */
} S_8196ACE4_0;
typedef struct S_8196ACE4_1_pre {
    u16 unk_00;
} S_8196ACE4_1_pre;
typedef struct S_8196ACE4_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x4];
    u16 unk_34;
    u8 pad_36[0x56];
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
    s32 unk_9C;
    s32 unk_A0;
} S_8196ACE4_1;
typedef struct S_8196ACE4_2 {
    u8 pad_00[0x69B4];
    s16 unk_69B4;
} S_8196ACE4_2;
typedef struct S_8196ACE4_4 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_8196ACE4_4;
typedef struct S_8196B780_0 {
    u8 pad_00[0x2C];
    s16 unk_2C;
    u8 pad_2E[0x5E];
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    u8 pad_98[0x8];
    s32 unk_A0;
} S_8196B780_0;
typedef struct S_8196B780_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8196B780_1;
typedef struct S_8196B780_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_8196B780_2;
typedef struct S_8196B780_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8196B780_3;
typedef struct S_8196B780_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8196B780_4;
typedef struct S_8196B780_5 {
    u8 pad_00[0x26];
    s16 unk_26;
} S_8196B780_5;
typedef struct S_8196C280_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_08;   /* overlapping accesses */
} S_8196C280_0;
typedef struct S_8196C280_1 {
    u8 pad_00[0x2C];
    u16 unk_2C;
    u8 pad_2E[0x22];
    u16 unk_50;
    u8 pad_52[0x3A];
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
    s32 unk_9C;
    s32 unk_A0;
} S_8196C280_1;
typedef struct S_8196C280_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8196C280_2;
typedef struct PositionRef {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} PositionRef;
typedef struct Data {
    u16 pad0;
    u16 x;
    u16 pad4;
    u16 y;
    u16 pad8;
    u16 z;
} Data;
typedef struct Object {
    u8 pad0[8];
    Data *data;
    u8 padC[4];
    void (*callback)(void *);
} Object;
typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;
typedef struct S_80024124_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024124_1;
typedef struct S_80024124_2 {
    u8 pad_00[0x3];
    u8 unk_03;
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_80024124_2;
typedef struct S_80024124_3_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_80024124_3_pre;
typedef struct S_80024124_3 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
} S_80024124_3;
typedef struct S_80024124_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80024124_4;


typedef struct EffectState {
    u8 pad_00[0x2C];
    s16 size_x;
    s16 size_y;
    u8 pad_30[0x64];
    s32 seed;
    u8 pad_98[0x8];
    s32 scale;
} EffectState;
typedef struct Vec3u16 {
    u8 pad_00[0x2];
    u16 x;
    u8 pad_04[0x2];
    u16 y;
    u8 pad_08[0x2];
    u16 z;
} Vec3u16;
typedef struct RenderState {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 flags;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} RenderState;
typedef struct Effect {
 u8 pad0[8];
 union { Vec3u16 *position; Position *pos; } coordinates;
 union { RenderState *render; Sprite *sprite; } visual;
 union { void *handler; void (*update)(); } callback;
 u8 pad14[0xC];
 union { EffectState state; Motion motion; } payload;
} Effect;
typedef union NativeOffsets58 { s16 pairs[8][2]; LocalPoints raw; OffsetTable signed_pairs; } NativeOffsets58;
extern const NativeOffsets58 D_80024004;
extern const RectTable D_80024024;
extern s16 D_800269B4;
extern PackedVec3 D_80026978;
ObjectNodeHeader *func_8003FC64(s32);
s32 rand(void);
void func_8003DB94(void *, void *, s32);
s32 func_800A45D8(s32, s32, s16);
void func_80024CA4(S_8196B4A4_5 *source, s32 unused_1, s32 unused_2, s16 offset_x, s16 offset_y, s16 offset_z);
void func_80025724(void *effect, s32 unused, S_8196BF24_1 *transform);
void func_800257B0(void *object, void *position, void *render_state);
void func_80025648(void *effect_data, s32 unused, void *sprite);
void func_80024374(void *object);
void func_80024874(void *motion, void *position, s32 update_id);
void func_8002553C(void *source, s32 unused_position, s32 unused_render);
void func_8002525C(void *owner);
void func_80025D68(Work *work, s32 position_arg, s32 sprite_arg);
void func_800244E4(void *effect, S_8196ACE4_0 *position, Rec_D_80082E80 *sprite);
void func_80024F80(S_8196B780_5 *source, s32 unused_1, s32 unused_2, s16 x, s16 y, s16 z);
void func_80025A80(void *effect, void *position, void *sprite);
void func_80024A5C(void *effect, s32 unused, u8 *primitive);
void func_8002407C(void *state, void *unused, void *visual);
void func_800243C4(ObjectNodeHeader *source, s32 state_14_value, s32 state_08_value, s32 state_32_value, s16 x_offset, s16 y_offset, s16 z_offset);
s32 func_80024124(PointRecord *first_point, PointPosition *first_position);
void func_80024AF8(s32 unused_0, s32 unused_1, s32 unused_2, s16 x, s16 y, s16 z);
#endif

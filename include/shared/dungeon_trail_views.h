#ifndef SHARED_DUNGEON_TRAIL_VIEWS_H
#define SHARED_DUNGEON_TRAIL_VIEWS_H
#include "common.h"
#include "shared/gpu_packets.h"
/* Partial trail-effect and GPU views; offsets and access widths bind to retail. */
typedef struct TrailEffectState {
    void *unk_00;
    u16 *unk_04;
    u8 pad_08[1];
    u8 unk_09;
    s16 unk_0A;
    u8 pad_0C[0x44];
    u16 unk_50;
    s16 unk_52;
} TrailEffectState;

typedef struct TrailMotion {
    union {
        s32 unk_00;
        struct {
            u8 pad_00[2];
            u16 unk_02;
        } unk_02;
    } unk_00;
    union {
        s32 unk_04;
        struct {
            u8 pad_04[2];
            u16 unk_06;
        } unk_06;
    } unk_04;
    u8 pad_08[2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} TrailMotion;

typedef struct TrailActor {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void *unk_60;
    u8 pad_64[0xE];
    u8 unk_72;
    u8 unk_73;
} TrailActor;

typedef struct TrailObject {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
} TrailObject;

typedef struct TrailSprite {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} TrailSprite;

typedef struct TrailSpawnedObject {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0xC];
    void *unk_20;
} TrailSpawnedObject;

typedef struct TrailParticleData {
    u8 pad_00[4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0x24];
    s16 unk_4C;
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
    s16 unk_54;
    s16 unk_56;
} TrailParticleData;

typedef struct TrailHeightView {
    u8 pad_00[0xA];
    u16 unk_0A;
} TrailHeightView;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} DungeonVertex;

typedef struct {
    u8 pad[0x10];
    DungeonVertex v[4];
} DungeonVertexBlock;

typedef struct {
    u8 pad[0x18];
    DungeonVertexBlock block;
} DungeonFinalView;

typedef struct DungeonObj DungeonObj;

struct DungeonObj {
    DungeonObj *parent;
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
    u8 pad1C[0x0C];
    u16 vx0;
    u16 vy0;
    u16 vr0;
    u16 pad2E;
    u16 vx1;
    u16 vy1;
    u16 vr1;
    u16 pad36;
    u16 vx2;
    u16 vy2;
    u16 vr2;
    u16 pad3E;
    u16 vx3;
    u16 vy3;
    u16 vr3;
    u16 pad46;
    u8 red;
    u8 green;
    u8 blue;
    u8 pad4B;
    u16 angle;
    u16 angle2;
    u16 height;
    u16 timer;
    s16 aux;
    s16 state;
};

typedef struct {
    void *p0;
    void *p4;
    s16 h8;
    s16 hA;
    u16 angle;
    s16 padE;
    s16 x;
    s16 y;
    u16 height;
    s16 pad16;
    s16 type;
    s16 pad1A;
} LocalPacket;

typedef struct TrailTriangle {
    u32 unk_00;
    s32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} TrailTriangle;   /* packet1 in func_80024A1C */

typedef struct TrailRenderItem {
    u8 pad_00[0x48];
    s32 unk_48;
    u8 pad_4C[0x8];
    s16 unk_54;
} TrailRenderItem;   /* item in func_80024A1C */

typedef struct TrailOrderEntry {
    u8 pad_00[0xB0];
    u32 unk_B0;
} TrailOrderEntry;   /* entry in func_80024A1C */

typedef struct TrailDrawMode {
    u32 unk_00;
} TrailDrawMode;   /* packet0 in func_80024A1C */

typedef struct TrailChainPrefix {
    s32 unk_00;
    u8 pad_04[0x4];
} TrailChainPrefix;   /* the 0x8 bytes before outer in func_80024A1C, addressed as outer[-1] */




#endif

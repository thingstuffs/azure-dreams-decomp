#ifndef DUNGEON_OVL_1924800_H
#define DUNGEON_OVL_1924800_H
#include "shared/dungeon_effect_views.h"
#include "common.h"
#include "m2c_compat.h"
#include "modules/dungeon_native_abi.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/entity_height_offsets.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

/* Same three position slots, with the signed spawn and unsigned raise views
 * visible together. Retail loads at +2,+6,+10; raise also updates the z word. */

typedef u8 *(*FnPtr)(void *, s32, void *, void *, u8 *);

typedef struct { s32 w0, w1, w2, w3; } Blk16;

typedef struct { s32 w0, w1; } Blk8;

typedef struct { s32 a0,a1,a2,a3,a4,a5,a6,a7,a8,a9; } Blk40;

typedef struct S_func_81904990_1 {
    s32 unk_00;
    void * unk_04;
    u8 pad_08[0x72];
    u16 unk_7A;
    u16 unk_7C;
} S_func_81904990_1;

typedef struct S_func_81904990_2 {
    u8 pad_00[0x8];
    void * unk_08;
    union {
        s32 as_s32_0C;
        struct {
            u8 pad_0C[0x3];
            u8 unk_0F;
        } as_u8_0F;
    } unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
} S_func_81904990_2;

typedef struct S_func_81904990_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u16 unk_04;
    u16 unk_06;
    union {
        FnPtr as_FnPtr_08;
        u8 as_u8_08;
        struct {
            u8 pad_08[0x1];
            u8 unk_09;
        } as_u8_09;
        struct {
            u8 pad_08[0x2];
            u8 unk_0A;
        } as_u8_0A;
        struct {
            u8 pad_08[0x3];
            u8 unk_0B;
        } as_u8_0B;
    } unk_08;
} S_func_81904990_3;

typedef struct S_func_81904990_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    union {
        s32 as_s32_10;
        u16 as_u16_10;
    } unk_10;
    union {
        s32 as_s32_14;
        u16 as_u16_14;
    } unk_14;
    u8 pad_18[0x8];
    s32 * unk_20;
    u16 unk_24;
    u8 pad_26[0xA];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x34];
    u16 unk_70;
    u16 unk_72;
    u16 unk_74;
    u8 pad_76[0x2];
    u16 unk_78;
    u16 unk_7A;
    u16 unk_7C;
    u8 pad_7E[0x2];
    u16 unk_80;
    u16 unk_82;
    u16 unk_84;
    u8 pad_86[0x2];
    u16 unk_88;
    u16 unk_8A;
    u16 unk_8C;
    u8 pad_8E[0x2A];
    u16 unk_B8;
    u16 unk_BA;
    u8 pad_BC[0x4];
    s32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u16 unk_F0;
    u16 unk_F2;
    u16 unk_F4;
    u16 unk_F6;
    u16 unk_F8;
    u16 unk_FA;
    u16 unk_FC;
    u16 unk_FE;
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
    u8 pad_106[0x2];
    u16 unk_108;
    u16 unk_10A;
} S_func_81904990_4;

typedef struct S_func_81904990_6 {
    u16 unk_00;
    u16 unk_02;
} S_func_81904990_6;

typedef struct S_func_81904990_7 {
    union {
        s32 as_s32_00;
        struct {
            u8 pad_00[0x3];
            s8 unk_03;
        } as_s8_03;
    } unk_00;
    s32 unk_04;
    union {
        s16 as_s16_08;
        u16 as_u16_08;
    } unk_08;
    s16 unk_0A;
    union {
        s16 as_s16_0C;
        struct {
            u8 pad_0C[0x1];
            u8 unk_0D;
        } as_u8_0D;
    } unk_0C;
    u16 unk_0E;
    union {
        s16 as_s16_10;
        u16 as_u16_10;
    } unk_10;
    s16 unk_12;
    union {
        s16 as_s16_14;
        u8 as_u8_14;
        struct {
            u8 pad_14[0x1];
            u8 unk_15;
        } as_u8_15;
    } unk_14;
    u16 unk_16;
    union {
        s16 as_s16_18;
        u16 as_u16_18;
    } unk_18;
    s16 unk_1A;
    union {
        s16 as_s16_1C;
        struct {
            u8 pad_1C[0x1];
            u8 unk_1D;
        } as_u8_1D;
    } unk_1C;
    u8 pad_1E[0x2];
    union {
        s16 as_s16_20;
        u16 as_u16_20;
    } unk_20;
    s16 unk_22;
    union {
        s16 as_s16_24;
        u8 as_u8_24;
        struct {
            u8 pad_24[0x1];
            u8 unk_25;
        } as_u8_25;
    } unk_24;
} S_func_81904990_7;

typedef struct S_func_81904990_8 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_func_81904990_8;

typedef struct ScreenPos {
    u16 x;
    s16 y;
} ScreenPos;

typedef struct ScreenRect {
    u16 x;
    s16 y;
    s32 size;
} ScreenRect;

typedef struct FillPacket {
    u32 tag;       /* low 24 bits next address; byte 3 = word count (3) */
    u32 command;   /* 0x60000000: monochrome rectangle, black */
    u16 x;
    s16 y;
    s32 size;
} FillPacket;

typedef struct Scratch80024D64 {
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
} Scratch80024D64;

typedef struct EffectRecord {
    u8 pad_00[0x32];
    s16 timer;
} EffectRecord;

typedef struct S_800251A0_0_pre {
    u16 unk_00;
} S_800251A0_0_pre;

typedef struct S_800251A0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800251A0_0;

typedef struct DungeonAnimSlot {
    u8 pad_00[0x50];
    s16 field_50;
    u8 pad_52[0x10];
    u16 field_62;
} DungeonAnimSlot;

typedef struct CountdownRecord {
    u16 pad_00;
    u16 counter;
} CountdownRecord;

typedef struct {
    u8 bytes[0x20];
} LocalPoints;

typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} Box __attribute__((packed));

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} PackedVector __attribute__((packed));

typedef struct {
    u16 x;
    u16 y;
} Point __attribute__((packed));

typedef struct {
    u8 bytes[8];
} Copy8;

typedef struct {
    u8 bytes[12];
} Copy12;

typedef struct {
    u8 bytes[32];
} Copy32;

typedef struct {
    s16 a;
    s16 b;
    s16 c;
} Vec3;

typedef struct S_func_81905FD0_1 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union {
        s16 s16;
        u16 u16;
    } unk_0A;
    u8 pad_0C[0x6C];
    union {
        s16 s16;
        u16 u16;
    } unk_78;
    u8 unk_7A;
    u8 unk_7B;
    u8 pad_7C[0x2];
    union {
        s16 s16;
        u16 u16;
    } unk_7E;
    u8 pad_80[0x2];
    union {
        s16 s16;
        u16 u16;
    } unk_82;
    u8 pad_84[0x4];
    u16 unk_88;
    u16 unk_8A;
    u8 pad_8C[0x4];
    union {
        s16 s16;
        u16 u16;
    } unk_90;
    u16 unk_92;
    union {
        s16 s16;
        u16 u16;
    } unk_94;
    u16 unk_96;
    u8 pad_98[0x4];
    union {
        s16 s16;
        u16 u16;
    } unk_9C;
    u8 pad_9E[0x1C];
    u8 unk_BA;
    u8 unk_BB;
} S_func_81905FD0_1;

typedef struct S_func_81905FD0_2 {
    union {
        u32 u32;
        struct {
            u8 pad_00[0x2];
            u16 unk_02;
        } u16_02;
    } unk_00;
    union {
        u32 u32;
        struct {
            u8 pad_04[0x2];
            u16 unk_06;
        } u16_06;
    } unk_04;
    union {
        s32 s32;
        u32 u32;
        struct {
            u8 pad_08[0x2];
            s16 unk_0A;
        } s16_0A;
        struct {
            u8 pad_08[0x2];
            u16 unk_0A;
        } u16_0A;
    } unk_08;
    u32 unk_0C;
    u32 unk_10;
    union {
        s32 s32;
        u32 u32;
    } unk_14;
} S_func_81905FD0_2;

typedef struct S_func_81905FD0_3 {
    u8 pad_00[0x6];
    u16 unk_06;
    void * unk_08;
    union {
        u32 u32;
        u8 u8;
        struct {
            u8 pad_0C[0x1];
            u8 unk_0D;
        } u8_0D;
        struct {
            u8 pad_0C[0x2];
            u8 unk_0E;
        } u8_0E;
    } unk_0C;
    union {
        s16 s16;
        u16 u16;
    } unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    union {
        s16 s16;
        u16 u16;
    } unk_1C;
    union {
        s16 s16;
        u16 u16;
    } unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
    u8 unk_24;
    u8 unk_25;
} S_func_81905FD0_3;

typedef struct S_func_81905FD0_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} S_func_81905FD0_4;

typedef struct S_func_81905FD0_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_func_81905FD0_5;

typedef struct S_func_81905FD0_6 {
    u8 pad_00[0x13];
    u8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_func_81905FD0_6;

typedef struct S_func_81905FD0_7 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x2A];
    void * unk_38;
    void * unk_3C;
    void * unk_40;
    void * unk_44;
    void * unk_48;
    void * unk_4C;
} S_func_81905FD0_7;

typedef struct S_func_81905FD0_8 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} S_func_81905FD0_8;

typedef struct S_func_81905FD0_9 {
    s16 unk_00;
    u16 unk_02;
} S_func_81905FD0_9;

typedef struct S_func_81905FD0_10 {
    union {
        s16 s16;
        u16 u16;
    } unk_00;
} S_func_81905FD0_10;

typedef struct S_func_81905FD0_11 {
    u8 unk_00;
} S_func_81905FD0_11;

typedef struct S_func_81905FD0_12 {
    u16 unk_00;
} S_func_81905FD0_12;

typedef struct S_func_81905FD0_13 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_func_81905FD0_13;

extern const u16 D_80024004[4];
extern const u16 D_8002400C[4];
extern const s16 D_80024014[8][2];
extern s32 func_800990FC(s32, s32);
extern s32 func_80099194(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 dungeonWriteTextByteAndAdvance(s8 value, s8 *dest);
extern s32 func_80099734(void *record, u8 *out);
extern void dungeonAdjustSourceValueAndFinalize(u8 *, u8 *);
extern s32 dungeonTryTriggerTargetRecordEffect(u8 *, s32);
extern void func_800A5720(s8 *text);
extern s32 func_800A6D30(void);
extern void createActorValuePopup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
extern u8 D_800E20D6[];
extern u8 D_800E20FC[];
extern void func_80064840(void *, void *, void *);
extern void func_800649A0(s32, s32);
extern void func_80064A40(s32);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern void func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_80067EF4();
extern u8 D_8006CD10[3];
extern u8 D_801C9E40[16];
extern void func_80067E2C(void *, void *);
extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern s16 D_800267B8[5];
extern s32 rand(void);
extern s32 func_800644B8(s32);
extern s32 func_80067014(s32);
extern void func_800672D8(Box *, u8 *);
extern void func_8006733C(Box *, u8 *);
extern void func_800B8FC8(void *, void *, void *, s32, s32);
extern u8 D_80026820[];
extern u8 D_80026760[12];
extern u8 D_8002676C[12];
extern u8 D_80026778[12];
extern u8 D_80026784[24];
extern u8 D_800267A8[12];
extern u8 D_800E3D68[1];
extern s32 func_8003DF74(void *, void *, Vec3 *, s32);
extern s32 func_80069EF8(void);
extern s32 func_800A4778(u16, u16, s16, void *);
void func_8002405C(u8 *entity, s32 chance, void *unused_context);
void dungeonBuildTexturedSpriteStrips(void *screen_pos, void *sprite, s32 *ordering_table, s32 draw_mode);
void func_80024B6C(s32 draw_data, ScreenRect *clip_rect, void *screen_pos, u16 clear_rect, s16 draw_param);
s32 dungeonDrawBrightnessScaledLinkedTiles(PointRecord *first_point, EntityRec *first_position);
void dungeonRaiseEffectToHeightLimit(EffectRecord *object, EntityRec *source);
void func_80025080(ObjectNodeHeader *parent, s16 field_34, s32 field_28, s16 field_52, s16 offset_x, s16 offset_y, s16 offset_z);
void dungeonUpdateEffectAnimationSlots(void *anim_state);
void dungeonTickEffectRecord(CountdownRecord *record);
void dungeonUpdateEffectBrightnessPulse(u8 *effect, void *unused, u8 *target);
void func_80025408(void *context, void *unused, void *effect_data);
void func_800257D0(S_func_81905FD0_1 *effect, S_func_81905FD0_2 *motion, S_func_81905FD0_3 *render);
#endif

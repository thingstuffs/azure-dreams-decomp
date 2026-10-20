#ifndef DUNGEON_OVL_19A332C_H
#define DUNGEON_OVL_19A332C_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/slus_callbacks.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
typedef struct ovl_19a332c_81982864_S_80024064_0_pre {
    u16 unk_00;
} ovl_19a332c_81982864_S_80024064_0_pre;
typedef struct ovl_19a332c_81982864_S_80024064_0 {
    void * unk_00;
    u16 * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; u16 p; } unk_0A;   
    s32 unk_0C;
    u8 pad_10[0xA];
    s16 unk_1A;
    u8 pad_1C[0x4];
    s16 unk_20;
    s16 unk_22;
} ovl_19a332c_81982864_S_80024064_0;
typedef struct ovl_19a332c_81982864_S_80024064_2 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 pad_A9[0x4B];
    s32 unk_F4;
} ovl_19a332c_81982864_S_80024064_2;
typedef struct ovl_19a332c_81982864_S_80024064_3_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} ovl_19a332c_81982864_S_80024064_3_pre;
typedef struct ovl_19a332c_81982864_S_80024064_4 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 unk_A9;
} ovl_19a332c_81982864_S_80024064_4;
typedef struct ovl_19a332c_81982864_S_80024064_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} ovl_19a332c_81982864_S_80024064_5;
typedef struct ovl_19a332c_81982864_S_80024064_6 {
    u8 pad_00[0x96];
    s16 unk_96;
} ovl_19a332c_81982864_S_80024064_6;
typedef struct ovl_19a332c_81982864_S_80024064_7 {
    u8 pad_00[0x102];
    s8 unk_102;
} ovl_19a332c_81982864_S_80024064_7;
typedef struct ovl_19a332c_81982864_StackPair {
    s32 first;
    s32 second;
} ovl_19a332c_81982864_StackPair;
typedef struct ovl_19a332c_81982B2C_EntityInner {
    u8 pad0[8];
    void *coords;
    void *actor;
} ovl_19a332c_81982B2C_EntityInner;
typedef struct ovl_19a332c_81982B2C_Entity {
    u8 pad0[8];
    ovl_19a332c_81982B2C_EntityInner *inner;
    u8 padC[0x18];
    u16 x;
    u16 y;
    s16 z;
    u16 pad2A;
    s16 state;
    s16 active;
} ovl_19a332c_81982B2C_Entity;
typedef struct ovl_19a332c_81982B2C_Position {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} ovl_19a332c_81982B2C_Position;
typedef struct ovl_19a332c_81982B2C_Motion {
    u8 pad0[12];
    u32 value;
} ovl_19a332c_81982B2C_Motion;
typedef struct ovl_19a332c_81982CEC_S_800244EC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x14];
    s32 unk_28;
} ovl_19a332c_81982CEC_S_800244EC_0;
typedef struct ovl_19a332c_81982CEC_S_800244EC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { void * v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} ovl_19a332c_81982CEC_S_800244EC_1;
typedef struct ovl_19a332c_81982CEC_S_800244EC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} ovl_19a332c_81982CEC_S_800244EC_2;
#define NULL 0
typedef struct
{
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fc;
    s32 f10;
    s32 f14;
}
ovl_19a332c_81982DF8_Arg1;
typedef struct
{
    u8 pad0[0xC];
    u8 c;
    u8 d;
    u8 e;
    u8 padF[0xD];
    u16 f1c;
    u16 f1e;
}
ovl_19a332c_81982DF8_Arg2;
typedef struct ovl_19a332c_81982F0C_S_8002470C_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} ovl_19a332c_81982F0C_S_8002470C_0;
typedef struct ovl_19a332c_81982F0C_S_8002470C_2 {
    u8 pad_00[0x30];
    s16 unk_30;
    u8 pad_32[0x4];
    s16 unk_36;
} ovl_19a332c_81982F0C_S_8002470C_2;
typedef struct {
    u8 pad0[8];
    void *dst;
    void *sprite;
    void (*callback)(void);
} ovl_19a332c_81982F0C_Object;
typedef struct ovl_19a332c_81983088_S_80024888_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} ovl_19a332c_81983088_S_80024888_0;
typedef struct ovl_19a332c_81983088_S_80024888_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} ovl_19a332c_81983088_S_80024888_1;
typedef struct ovl_19a332c_81983088_S_80024888_2_pre {
    u16 unk_00;
} ovl_19a332c_81983088_S_80024888_2_pre;
typedef struct ovl_19a332c_81983088_S_80024888_2 {
    u8 pad_00[0x30];
    u16 unk_30;
} ovl_19a332c_81983088_S_80024888_2;
typedef struct ovl_19a332c_81983138_S_80024938_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} ovl_19a332c_81983138_S_80024938_0;
typedef struct ovl_19a332c_81983138_S_80024938_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} ovl_19a332c_81983138_S_80024938_1;
typedef struct ovl_19a332c_81983138_S_80024938_3 {
    u8 pad_00[0x30];
    s16 unk_30;
    u8 pad_32[0x4];
    u16 unk_36;
} ovl_19a332c_81983138_S_80024938_3;
typedef struct {
    u8 pad[12];
    u8 red;
    u8 green;
    u8 blue;
} ovl_19a332c_819832B4_EffectColor;
typedef struct ovl_19a332c_8198332C_Coord {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    s16 z;
} ovl_19a332c_8198332C_Coord;
typedef struct ovl_19a332c_8198332C_Prim {
    s32 unk0;
    s32 unk4;
    void *unk8;
    u32 color;
    s16 unk10;
    s16 unk12;
    u16 unk14;
    s16 unk16;
    s32 unk18;
    s16 unk1C;
    s16 unk1E;
} ovl_19a332c_8198332C_Prim;
typedef struct ovl_19a332c_8198332C_Actor {
    s32 unk0;
    s32 unk4;
    ovl_19a332c_8198332C_Coord *pos;
    ovl_19a332c_8198332C_Prim *prim;
    void *update;
    u8 pad14[0x50 - 0x14];
    s16 unk50;
} ovl_19a332c_8198332C_Actor;
typedef struct { s32 a, b; } __attribute__((packed)) ovl_19a332c_819835AC_M2C_PACKED_PAIR;
typedef struct { s16 x, y, z; } ovl_19a332c_819835AC_M2C_VEC3S;
typedef struct { s32 sf; } ovl_19a332c_819835AC_M2C_S32F;
typedef struct ovl_19a332c_819835AC_S_819835AC_1 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    union {
        s16 s16;
        u16 u16;
    } unk_28;
    union {
        s16 s16;
        u16 u16;
    } unk_2A;
    union {
        s16 s16;
        u16 u16;
    } unk_2C;
    u8 pad_2E[0x2];
    s16 unk_30;
    u8 pad_32[0x2];
    union {
        s16 s16;
        u16 u16;
    } unk_34;
    s16 unk_36;
    u16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
    s16 unk_42;
    u16 unk_44;
    u16 unk_46;
    u16 unk_48;
    u16 unk_4A;
    u16 unk_4C;
    u8 pad_4E[0x3A];
    s16 unk_88;
    u16 unk_8A;
    u8 pad_8C[0x8];
    u16 unk_94;
    s16 unk_96;
    u8 unk_98;
    u8 unk_99;
    u16 unk_9A;
    void * unk_9C;
} ovl_19a332c_819835AC_S_819835AC_1;
typedef struct ovl_19a332c_819835AC_S_819835AC_2 {
    union {
        s32 word;
        struct {
            u8 pad_00[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_02;
        } half;
    } unk_00;
    union {
        s32 word;
        struct {
            u8 pad_04[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_06;
        } half;
    } unk_04;
    union {
        s32 word;
        struct {
            u8 pad_08[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_0A;
        } half;
    } unk_08;
    union {
        s32 word;
        struct {
            u8 pad_0C[0x2];
            s16 unk_0E;
        } half;
    } unk_0C;
    union {
        s32 word;
        struct {
            u8 pad_10[0x2];
            s16 unk_12;
        } half;
    } unk_10;
    union {
        s32 word;
        struct {
            u8 pad_14[0x2];
            s16 unk_16;
        } half;
    } unk_14;
} ovl_19a332c_819835AC_S_819835AC_2;
typedef struct ovl_19a332c_819835AC_S_819835AC_3 {
    s32 unk_00;
    u8 unk_04;
    u8 pad_05[0x7];
    union {
        s32 word;
        struct {
            u8 unk_0C;
            u8 unk_0D;
            u8 unk_0E;
        } half;
    } unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} ovl_19a332c_819835AC_S_819835AC_3;
typedef struct ovl_19a332c_819835AC_S_819835AC_4 {
    u8 pad_00[0x48];
    ovl_19a332c_819835AC_M2C_PACKED_PAIR unk_48;
    ovl_19a332c_819835AC_M2C_PACKED_PAIR unk_50;
} ovl_19a332c_819835AC_S_819835AC_4;
typedef struct ovl_19a332c_819835AC_S_819835AC_5 {
    u8 pad_00[0x2A];
    union {
        s16 s16;
        u16 u16;
    } unk_2A;
    u8 pad_2C[0x5C];
    union {
        s16 s16;
        u16 u16;
    } unk_88;
} ovl_19a332c_819835AC_S_819835AC_5;
typedef struct ovl_19a332c_819835AC_S_819835AC_6 {
    u8 pad_00[0x5C];
    s32 unk_5C;
    u8 pad_60[0x28];
    s16 unk_88;
    u8 pad_8A[0xC];
    s16 unk_96;
    u8 pad_98[0xE];
    u16 unk_A6;
} ovl_19a332c_819835AC_S_819835AC_6;
typedef struct ovl_19a332c_819835AC_S_819835AC_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x3];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x2];
    u8 unk_24;
    u8 unk_25;
} ovl_19a332c_819835AC_S_819835AC_7;
typedef struct ovl_19a332c_819835AC_S_819835AC_8 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} ovl_19a332c_819835AC_S_819835AC_8;
typedef struct ovl_19a332c_819835AC_S_819835AC_9 {
    u8 pad_00[0x50];
    u16 unk_50;
    u16 unk_52;
    u16 unk_54;
} ovl_19a332c_819835AC_S_819835AC_9;
typedef struct ovl_19a332c_819835AC_S_819835AC_10 {
    u16 unk_00;
} ovl_19a332c_819835AC_S_819835AC_10;
typedef struct ovl_19a332c_819835AC_S_819835AC_11 {
    void * unk_00;
} ovl_19a332c_819835AC_S_819835AC_11;
#define M2C_SFIELD(expr, offset) (((ovl_19a332c_819835AC_M2C_S32F *)((s8 *)(expr) + (offset)))->sf)
typedef struct ovl_19a332c_81984754_Pos {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} ovl_19a332c_81984754_Pos;
typedef struct ovl_19a332c_81984754_Part {
    void *unk0;
    u8 pad4[4];
    void *table;
    u8 padC[4];
    u16 f10;
    u8 pad12[2];
    u16 flags;
    s16 f16;
    u8 pad18[2];
    s16 f1A;
} ovl_19a332c_81984754_Part;
typedef struct ovl_19a332c_81984754_History {
    u16 x;
    u16 y;
    u16 z;
    u16 pad6;
} ovl_19a332c_81984754_History;
typedef struct ovl_19a332c_81984754_Entity {
    u8 pad0[0x20];
    void *parent;
    void *next;
    u8 pad28[0x34 - 0x28];
    s16 f34;
    s16 f36;
    s16 angle;
    s16 f3A;
    s16 f3C;
    u8 pad3E[0x44 - 0x3E];
    s16 f44;
    u8 pad46[2];
    ovl_19a332c_81984754_History history[8];
    s16 index;
    u8 pad8A[0x96 - 0x8A];
    s16 direction;
} ovl_19a332c_81984754_Entity;
typedef struct ovl_19a332c_81984754_Object {
    u8 pad0[8];
    ovl_19a332c_81984754_Pos *pos;
    ovl_19a332c_81984754_Part *part;
    void (*state)(void *);
    u8 pad14[0x20 - 0x14];
    ovl_19a332c_81984754_Entity entity;
} ovl_19a332c_81984754_Object;
typedef struct {
    s32 words[4];
} __attribute__((packed)) ovl_19a332c_81984A40_PackedWords4;
typedef struct {
    ovl_19a332c_81984A40_PackedWords4 words;
    s16 field_10;
    s8 field_12;
    s8 field_13;
    s8 field_14;
} ovl_19a332c_81984A40_Source81984A40;
typedef struct {
    ovl_19a332c_81984A40_PackedWords4 words;
    s16 field_10;
    s16 pad_12;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
} ovl_19a332c_81984A40_Dest81984A40;
typedef struct ovl_19a332c_81984AB0_S_81984AB0_1 {
    u8 pad_00[0x8];
    void * unk_08;
} ovl_19a332c_81984AB0_S_81984AB0_1;
typedef struct ovl_19a332c_81984AB0_S_81984AB0_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} ovl_19a332c_81984AB0_S_81984AB0_2;
typedef struct ovl_19a332c_81984AB0_S_81984AB0_0 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
} ovl_19a332c_81984AB0_S_81984AB0_0;
typedef struct ovl_19a332c_81984AF4_S_81984AF4_0 {
    s32 unk_00;
    union { s8 s; u8 u; } unk_04;   
    u8 pad_05[0x3];
    void * unk_08;
    u8 pad_0C[0x8];
    union { u16 s; u16 u; } unk_14;   
} ovl_19a332c_81984AF4_S_81984AF4_0;
typedef struct ovl_19a332c_81984AF4_S_81984AF4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
} ovl_19a332c_81984AF4_S_81984AF4_1;
typedef struct ovl_19a332c_81984BC0_S_81984BC0_1 {
    u8 pad_00[0x8];
    void * unk_08;
} ovl_19a332c_81984BC0_S_81984BC0_1;
typedef struct ovl_19a332c_81984BC0_S_81984BC0_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} ovl_19a332c_81984BC0_S_81984BC0_2;
typedef struct ovl_19a332c_81984BC0_S_81984BC0_0 {
    s32 unk_00;
} ovl_19a332c_81984BC0_S_81984BC0_0;
typedef struct ovl_19a332c_81984BF0_S_81984BF0_0 {
    u8 pad_00[0x5C];
    s32 unk_5C;
} ovl_19a332c_81984BF0_S_81984BF0_0;
typedef struct ovl_19a332c_81984BF0_S_81984BF0_1 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} ovl_19a332c_81984BF0_S_81984BF0_1;
typedef struct ovl_19a332c_81984C44_S_81984C44_1 {
    u8 pad_00[0x26];
    s8 unk_26;
} ovl_19a332c_81984C44_S_81984C44_1;
typedef struct ovl_19a332c_81984C44_S_81984C44_2_pre {
    void * unk_00;
    u8 pad_04[0xE];
    u16 unk_12;
} ovl_19a332c_81984C44_S_81984C44_2_pre;
typedef struct ovl_19a332c_81984C44_S_81984C44_2 {
    u8 pad_00[0x5C];
    void * unk_5C;
} ovl_19a332c_81984C44_S_81984C44_2;
typedef struct ovl_19a332c_81984C44_S_81984C44_4 {
    u8 pad_00[0x26];
    s8 unk_26;
} ovl_19a332c_81984C44_S_81984C44_4;
typedef struct ovl_19a332c_81984D4C_S_81984D4C_1 {
    union { u8 u; s8 s; } unk_00;   
} ovl_19a332c_81984D4C_S_81984D4C_1;
typedef struct ovl_19a332c_81984D4C_S_81984D4C_2 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} ovl_19a332c_81984D4C_S_81984D4C_2;
typedef struct ovl_19a332c_81984D4C_S_81984D4C_3 {
    union { u8 u; s8 s; } unk_00;   
} ovl_19a332c_81984D4C_S_81984D4C_3;
typedef struct ovl_19a332c_81984D4C_S_81984D4C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} ovl_19a332c_81984D4C_S_81984D4C_4;
typedef struct {
    void *field_B8;
    s32 unkBC;
    char padC0[4];
    s32 unkC4;
    char padC8[4];
    s32 unkCC;
    s32 unkD0;
    char padD4[4];
    void *ptr;
    s16 unkDC;
    s16 unkDE;
    s32 unkE0;
} ovl_19a332c_81984E94_S_8191696C_state;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
extern u16 D_800269F8;
s32 play_sound_if_enabled();
extern s32 D_800269D0;
extern M2C_UNK D_80027750;
extern M2C_UNK D_80027C74;
extern s16 D_80027C94;
extern u8 D_80027C96;
extern void *D_80027C98;
extern s32 resolve_record_orientation_or_fallback(s32, void *, u16 *, s32);
extern void register_node(void *, void *);
extern void func_8004491C(void *, void *);
extern s32 draw_textured_ellipse(void *, void *, s32, s32);
extern s32 D_800269D4;
extern s32 D_800269FC;
extern s32 D_800DF31C;
extern s32 rand(void);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern void func_8003DB94(void *, void *, s32);
extern u8 D_80026AB0[];
extern u8 D_800269EC[];
extern s16 D_80026B28;
extern ovl_19a332c_8198332C_Coord D_80027CA4;
s32 func_80069EF8();
void apply_attack_power_and_element_effects();
s32 forward_monster_coordinate_delta();
void spawn_blinking_sprite_flash();
extern u8 D_80026BC8[];
extern u8 D_80026BD4[];
extern s32 D_800E3D18;
extern u8 D_80026B2C[];
extern u8 D_80026BBC[];
extern u8 D_80080010[];
extern void draw_linked_model_chain(void);
extern s32 has_enough_available_runtime_nodes(s32);
extern ovl_19a332c_81984754_Object *allocate_list_node(s32, void *);
extern ovl_19a332c_81984754_Object *func_8003FD64(s32, void *);
extern s16 get_tile_chebyshev_distance(void *, void *);
extern s32 check_entity_interaction_compatibility(void *, void *);
extern s32 check_entity_eligibility(void *);
extern u8 D_80026BE4[16];
extern u8 D_800E3D20[16];
void func_80024064(void *transition);
void initialize_entity_position_and_motion(ovl_19a332c_81982B2C_Entity *entity, ovl_19a332c_81982B2C_Position *position, ovl_19a332c_81982B2C_Motion *motion);
void *allocate_two_part_object(ovl_19a332c_81982CEC_S_800244EC_2 *source_part, s32 offset);
void move_fade_and_expand_effect(void *effect_data, void *motion_data, void *sprite_data);
void *spawn_random_motion_particles(s16 x, s16 y, s16 z, s16 heading, s16 count);
void advance_effect_motion_and_color_fade(void *effect, ovl_19a332c_81983088_S_80024888_0 *motion, ovl_19a332c_81983088_S_80024888_1 *color);
void *spawn_thirty_two_angled_particles(s16 x, s16 y, s16 z, s16 angle, s32 unused_context);
void fade_effect_color_by_quarter(u16 *effect_data, s32 unused, ovl_19a332c_819832B4_EffectColor *color);
void *spawn_effect_actor_or_curved_trail(s16 x, s16 y, s16 z, s16 angle, s16 spawn_actor);
void update_homing_effect_and_attached_copies(ovl_19a332c_819835AC_S_819835AC_1 *effect, ovl_19a332c_819835AC_S_819835AC_2 *motion, ovl_19a332c_819835AC_S_819835AC_3 *visual);
void *create_nine_linked_effects(s32 x, s32 y, s32 z, s32 angle);
void inventory_copy_and_sign_extend_record_fields(ovl_19a332c_81984A40_Dest81984A40 *dst, ovl_19a332c_81984A40_Source81984A40 *src);
void inventory_select_entry_and_reset_object(ovl_19a332c_81984AB0_S_81984AB0_0 *object, s16 entry_index);
void step_and_clamp_entry_index(void *object, s16 *index_step, s32 min_index, s32 max_index);
void inventory_set_object_entry_address(ovl_19a332c_81984BC0_S_81984BC0_0 *object, s16 entry_index);
void inventory_clear_circular_list_flag_2000(void *unused_actor);
void *find_eligible_nearby_entity(void *source_entity);
void clear_object_buffer_and_state(void *tracker);
s32 inventory_reset_shared_state_mode_13(s32 unused, s32 state_key, s32 value, s16 secondary_value);
#endif

#ifndef DUNGEON_OVL_DD9000_P03_H
#define DUNGEON_OVL_DD9000_P03_H
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#ifndef NULL
#define NULL 0
#endif
#include "shared/game_work.h"


typedef struct T_80170874_S_80DB9000_1 {
    u8 pad_00[0x4E];
    union {
        s16 s16;
        u16 u16;
    } unk_4E;
    u16 unk_50;
} T_80170874_S_80DB9000_1;

typedef struct T_80170874_S_80DB9000_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} T_80170874_S_80DB9000_2;

typedef struct T_80170874_S_80DB9000_3 {
    u8 pad_00[0x8];
    void * unk_08;
    union {
        s32 s32;
        struct {
            u8 pad_0C[0x3];
            u8 unk_0F;
        } u8;
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
} T_80170874_S_80DB9000_3;

typedef struct T_80170874_S_80DB9000_4 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x2];
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u8 pad_1C[0x8];
    u32 unk_24;
    u16 unk_28;
    u8 pad_2A[0xA];
    u32 unk_34;
    union {
        u16 u16;
        u32 u32;
    } unk_38;
    union {
        u16 u16;
        u32 u32;
    } unk_3C;
    u8 pad_40[0x48];
    u32 unk_88;
    u32 unk_8C;
    u32 unk_90;
    union {
        s32 word;
        struct { u16 x; u16 y; } parts;
    } screen[4];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x2];
    u16 unk_AC;
    u16 unk_AE;
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    u8 pad_B6[0x2];
    u16 unk_B8;
    u16 unk_BA;
    u16 unk_BC;
    u8 pad_BE[0x2];
    u16 unk_C0;
    u16 unk_C2;
    u16 unk_C4;
    u8 pad_C6[0x2];
    u16 unk_C8;
    u16 unk_CA;
    u16 unk_CC;
    u8 pad_CE[2];
    s32 transform_p;
    s32 transform_flags;
    u8 pad_D8[0x20];
    union {
        s32 word;
        struct { u16 x; u16 y; } parts;
    } origin;
    u8 pad_FC[0x4];
    u32 unk_100;
} T_80170874_S_80DB9000_4;

typedef struct T_80170874_S_80DB9000_6 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} T_80170874_S_80DB9000_6;

typedef struct T_80170874_S_80DB9000_7 {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[0x2];
    u16 unk_04;
    u16 unk_06;
    union {
        struct {
            u8 unk_00;
            u8 unk_01;
            u8 unk_02;
            u8 unk_03;
        } u8;
        void * void_ptr;
    } unk_08;
    u8 pad_0C[0x10];
    s32 unk_1C;
} T_80170874_S_80DB9000_7;

typedef struct T_80170874_S_80DB9000_9 {
    union {
        s32 s32;
        struct {
            u8 pad_00[0x3];
            s8 unk_03;
        } s8;
    } unk_00;
    s32 unk_04;
    u16 unk_08;
    u16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    union {
        s16 s16;
        u8 u8;
    } unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    union {
        s16 s16;
        struct {
            u8 pad_1C[0x1];
            u8 unk_1D;
        } u8;
    } unk_1C;
    u8 pad_1E[0x2];
    u16 unk_20;
    s16 unk_22;
    union {
        s16 s16;
        struct {
            u8 unk_24;
            u8 unk_25;
        } u8;
    } unk_24;
} T_80170874_S_80DB9000_9;

typedef struct {
    unsigned addr: 24;
    unsigned len: 8;
    u8 r0, g0, b0, code;
} T_80170874_P_TAG;
#define setaddr(p, _addr) (((T_80170874_P_TAG *)(p))->addr = (u32)(_addr))
#define getaddr(p) (u32)(((T_80170874_P_TAG *)(p))->addr)

void * CompMatrix(void *, void *, void *);
void PushMatrix(void);
void PopMatrix(void);
void * ScaleMatrix(void *, void *);
void SetRotMatrix(void *);
void SetTransMatrix(void *);
extern s32 RotTransPers(void *vertex, s32 *screen, s32 *p, s32 *flag);
extern s32 RotTransPers4(void *v0, void *v1, void *v2, void *v3, s32 *s0, s32 *s1, s32 *s2, s32 *s3, s32 *p, s32 *flag);
extern void RotMatrix();
extern s32 sprite_projection_matrix[];
#endif

#ifndef SHARED_SPU_VOICE_H
#define SHARED_SPU_VOICE_H

#include "common.h"

/* Existing setter layout and observed eight-halfword voice registers. */
typedef struct SpuVolume_ {
    s16 left;
    s16 right;
} SpuVolume_;

typedef struct SpuVoiceAttr_ {
    u32 voice;          /* 0x00 */
    u32 mask;           /* 0x04 */
    SpuVolume_ volume;  /* 0x08 */
    SpuVolume_ volmode; /* 0x0C */
    SpuVolume_ volumex; /* 0x10 */
    u16 pitch;          /* 0x14 */
    u16 note;           /* 0x16 */
    u16 sample_note;    /* 0x18 */
    s16 envx;           /* 0x1A */
    u32 addr;           /* 0x1C */
    u32 loop_addr;      /* 0x20 */
    s32 a_mode;         /* 0x24 */
    s32 s_mode;         /* 0x28 */
    s32 r_mode;         /* 0x2C */
    u16 ar;             /* 0x30 */
    u16 dr;             /* 0x32 */
    u16 sr;             /* 0x34 */
    u16 rr;             /* 0x36 */
    u16 sl;             /* 0x38 */
    u16 adsr1;          /* 0x3A */
    u16 adsr2;          /* 0x3C */
} SpuVoiceAttr_;

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u16 unkE;
} S_8005FA34_ent;


#endif

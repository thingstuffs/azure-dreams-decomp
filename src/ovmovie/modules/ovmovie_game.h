#ifndef OVMOVIE_GAME_H
#define OVMOVIE_GAME_H
#include "common.h"
#include "shared/game_work.h"
#include "shared/runtime_dispatch.h"

typedef struct { s16 x, y, w, h; } MovieRect;
/* Playback work block. The buffer view below starts at byte 4. */
typedef struct {
    s32 tag;
    void *frame_buffers[2];
    s32 frame_buffer_index;
    void *output;
    MovieRect screen[2];
    s32 screen_index;
    MovieRect strip;
    s32 ready;
    s32 done;
    s32 width, height;
} MovieState;
/* Initializer's 0x30-byte view of MovieState + 4. */
typedef struct {
    void *unk00;
    void *unk04;
    s32 unk08;
    void *unk0C;
    s16 unk10, unk12, unk14, unk16;
    s16 unk18, unk1A, unk1C, unk1E;
    s32 unk20;
    s16 unk24, unk26, unk28, unk2A;
    s32 unk2C;
} MovieBuffer;
/* Waiter's unsigned halfword copy view of the same buffer subobject. */
typedef struct {
    u8 pad00[0x10];
    u16 unk10, unk12;
    u8 pad14[0x0C];
    s32 unk20;
    u16 unk24, unk26;
    u8 pad28[0x04];
    s32 unk2C;
} MovieEntity;
typedef struct { u8 pad00[8]; u32 frame; u8 pad0C[4]; u16 width, height; } FrameInfo;
typedef struct { u8 pad00[0x14]; s16 w0, h0; u8 pad18[4]; s16 w1, h1; u8 pad20[10]; s16 rounded_height; } FrameDisplay;
typedef struct { MovieRect viewport, screen; u8 interlaced, rgb24, pad[6]; } MovieDisplayEnv;
typedef struct { u8 bytes[96]; } MovieDrawEnv;

extern s8 D_80080A88;
extern u8 D_80082E6B;
extern s32 D_80086D8C;
extern s32 D_801781D0, D_801781D4, D_801781D8, D_801781DC, D_801781E0, D_801781E4;
extern u8 D_80189388[8];
extern MovieState *D_80189390;
extern s32 D_80189394;
extern u8 D_80189398[];
extern s32 D_801B8EB8, D_801B8EBC;
extern u8 D_801C9E40[];

extern s32 Control_CD(s32, s32, s32);
extern void func_8003F320(void);
extern s32 func_8003E240(s32);
extern void SD_Call(s32);
extern void func_800542BC(void);
extern void func_8005A4E8(s32, s32, s32);
extern void func_8005A56C(s32, s16, s16);
extern void func_8005FE18(s32);
extern void func_80060B04(void *, s32);
extern void func_80060D90(s32, u8 *);
extern void func_80060DE8(s32);
extern void func_80061208(s32);
extern void func_8006124C(s32, void *);
extern s32 func_80061350(void);
extern s32 func_80063424(s32);
extern void func_80063538(void);
extern void func_800636AC(s32, s32, s32, s32, s32);
extern s32 func_80063734(s32);
extern s32 func_80063828(s32 *, FrameInfo **);
extern void func_8006390C(void);
extern void func_8006636C(void *, s32, s32, s32, s32);
extern void func_80066424(void *, s32, s32, s32, s32);
extern void func_80066F78(s32);
extern void func_80067014(s32);
extern void func_800671A8(s16 *, s32, s32, s32);
extern void func_800672D8(MovieRect *, void *);
extern void func_8006751C(void *, s32);
extern void func_80067688(void *);
extern void func_800678E0(void *);
/* LIBPRESS public entries; signatures agree with its shared header. */
extern void func_801776D8(s32);
extern void func_80177844(s32 *, s32);
extern void func_801778C0(s32, u32);
extern s32 func_8017797C(void (*)(void));
/* The unregistered VLC routine is an external platform boundary. */
extern s32 func_80177E6C(s32, void *);

void func_801768AC(void);
void func_80176AD8(s32);
void func_80176B3C(s16, s16);
void func_80176B60(void *, void (*)(void));
void func_80176BEC(MovieBuffer *, s32, s32, s32, s32);
void func_80176CA8(void);
s32 func_80176E90(void *);
s32 func_80176F2C(u8 *);
void func_801770BC(MovieEntity *, s32);
void func_80177154(void *);
s32 func_8017719C(s32, s32, s32, s32);
#endif

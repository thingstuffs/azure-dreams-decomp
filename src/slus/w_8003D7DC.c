#include "common.h"

/* Initialise the double-buffered draw/display environments for the 320x224
 * (0x140 x 0xE0) NTSC screen, then patch each DISPENV's screen RECT (y, h) to
 * the standard 12/224 offsets and force isbg=1 on both DRAWENVs. */
#include "common.h"

/* GsWORK-like graphics-environment block: DRAWENV-shaped header (0x00-0x5B,
 * padded to 0x5C in this build) + DISPENV-shaped header (0x5C-0x6F), followed
 * by a huge OT/primitive packet buffer (not modelled -- accessed only via raw
 * pointer offsets from the base in this function). Two full copies exist for
 * double buffering: D_801C9E40 (buffer 0) and D_801DA714 (buffer 1), exactly
 * 0x108D4 bytes apart (see func_8003D5A4's `p + 0x108D4` toggle). */
typedef struct {
    /* DRAWENV portion */
    s16 clip_x, clip_y, clip_w, clip_h; /* 0x00 RECT clip */
    s16 ofs0, ofs1;                     /* 0x08 draw offset */
    s16 tw_x, tw_y, tw_w, tw_h;         /* 0x0C RECT tw */
    u16 tpage;                          /* 0x14 */
    u8  dtd, dfe;                       /* 0x16, 0x17 */
    s32 isbg;                           /* 0x18: packs isbg + r0,g0,b0 (LE) in one store */
    u8  dr_env[0x40];                   /* 0x1C reserved GPU env packet, pads to 0x5C */
    /* DISPENV portion */
    s16 disp_x, disp_y, disp_w, disp_h;         /* 0x5C RECT disp */
    s16 screen_x, screen_y, screen_w, screen_h; /* 0x64 RECT screen */
    u8  isinter, isrgb24, disp_pad0, disp_pad1; /* 0x6C */
} S_801C9E40;

extern S_801C9E40 D_801C9E40;      /* GsWORK buffer 0 */
extern S_801C9E40 D_801DA714;      /* GsWORK buffer 1, == &D_801C9E40 + 0x108D4 */
extern s32 D_801DA72C[3];          /* buffer-1-adjacent flag; >8B decl forces hi/lo */

extern void *SetDefDrawEnv(void *env, s32 x, s32 y, s32 w, s32 h);
extern void *SetDefDispEnv(void *env, s32 x, s32 y, s32 w, s32 h);

void func_8003D7DC(void)
{
    u8 *base = (u8 *)&D_801C9E40;
    s32 x = 0;
    s32 h1 = 0xE0;
    s32 h2 = 0xF0;

    SetDefDrawEnv(base, x, x, 0x140, h1);
    SetDefDrawEnv(&D_801DA714, x, h1, 0x140, h1);
    SetDefDispEnv(base + 0x5C, x, h1, 0x140, h2);
    SetDefDispEnv((u8 *)&D_801DA714 + 0x5C, x, x, 0x140, h2);

    *(s16 *)(base + 0x1093A) = 0xC;
    *(s16 *)(base + 0x66) = 0xC;
    *(s16 *)(base + 0x1093E) = h1;
    *(s16 *)(base + 0x6A) = h1;

    D_801DA72C[0] = 1;
    *(s32 *)(base + 0x18) = 1;
}

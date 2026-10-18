#ifndef DUNGEON_OVL_190C800_H
#define DUNGEON_OVL_190C800_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/scratchpad.h"
#include "shared/game_work.h"
/* cfail-repair: tf7-phase1-cache-v3 */

typedef struct { s32 w[10]; } Blk40;
typedef struct { s32 w[4]; } Blk16;
typedef struct { s32 w[2]; } Blk8;

#define M2C_BREAK() 0
#define M2C_SYNC() 0
#define SP8(offset) M2C_FIELD(scratch, u8 *, (offset))
#define SP16(offset) (scratch->h[(offset) / 2])
#define SP32(offset) (scratch->sw[(offset) / 4])
#define SP5D M2C_FIELD(quad_copies, u8 *, 53)

typedef struct Row_818EC800_QuadTail {
    u8 pad0[50];
    u16 y;
    u8 pad1;
    u8 flag;
} Row_818EC800_QuadTail;

#ifdef __mips__






#endif

/* Draws a transformed sprite as horizontally displaced scanline quads. */
typedef struct Row_818ED25C_S_80024A5C_0 {
    u8 pad_00[0x8B0];
    u32 unk_8B0;
    u8 pad_8B4[0x1C];
    u8 * unk_8D0;
} Row_818ED25C_S_80024A5C_0;   /* ctx in func_80024A5C */

typedef struct Row_818ED25C_S_80024A5C_1 {
    u32 unk_00;
} Row_818ED25C_S_80024A5C_1;   /* packet in func_80024A5C */

typedef struct Row_818ED25C_S_80024A5C_2 {
    u16 unk_00;
    s16 unk_02;
} Row_818ED25C_S_80024A5C_2;   /* work in func_80024A5C */

typedef struct Row_818ED25C_S_80024A5C_3 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} Row_818ED25C_S_80024A5C_3;   /* ctx2 in func_80024A5C */

typedef struct Row_818ED25C_S_80024A5C_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    u32 unk_04;
    u16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
} Row_818ED25C_S_80024A5C_4;   /* packet2 in func_80024A5C */

typedef struct Row_818ED25C_S_80024A5C_5 {
    u16 unk_00;
    s16 unk_02;
    s32 unk_04;
} Row_818ED25C_S_80024A5C_5;   /* arg1 in func_80024A5C */

typedef struct Row_818ED25C_S_80024A5C_6 {
    u32 unk_00;
} Row_818ED25C_S_80024A5C_6;   /* ot in func_80024A5C */

typedef struct Row_818ED25C_S_80024A5C_7 {
    void * unk_00;
} Row_818ED25C_S_80024A5C_7;   /* pbase in func_80024A5C */

/* Draws at a page-adjusted position with clipping commands and an optional black rectangle.
 * Keeping the page pointer live across setup and spelling the sign extension as one expression
 * reproduce the retail allocation and call-argument order. */
s32 func_800644B8();
void func_80064840();
void func_800649A0();
void func_80064A40();
void func_80064BC0();
void func_80064CF0();
void func_80064D80();
void func_800654B0();
void func_80065820();
void func_80067EF4();
void func_80067E2C(void *, void *);
extern u8 D_8006CD10[3];
extern u8 D_801C9E40[16];
void render_rotated_effect_quads(void *screen_pos, void *effect, s32 *ordering_tag, u32 draw_mode);
void draw_effect_and_restore_clip(s32 draw_data, Row_818ED25C_S_80024A5C_5 *clip_rect, void *screen_pos, u16 clear_rect, s16 draw_param);
#endif

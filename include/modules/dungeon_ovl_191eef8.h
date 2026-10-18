#ifndef DUNGEON_OVL_191EEF8_H
#define DUNGEON_OVL_191EEF8_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
/* Decrement the countdown, reset scale, and flag completion when it expires. */
/* Sets the object and global flags and marks the update. */
typedef struct Row_818FEF80_S_818FEF80_0_pre {
    u16 unk_00;
} Row_818FEF80_S_818FEF80_0_pre;   /* the 0x2 bytes before arg0 in func_80024780, addressed as arg0[-1] */

typedef struct Row_818FEF80_S_818FEF80_0 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x6];
    union { s16 s; s16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x24];
    void * unk_30;
} Row_818FEF80_S_818FEF80_0;   /* arg0 in func_80024780 */

typedef struct Row_818FEF80_S_818FEF80_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} Row_818FEF80_S_818FEF80_1_pre;   /* the 0x14 bytes before object in func_80024780, addressed as object[-1] */

typedef struct Row_818FEF80_S_818FEF80_1 {
    u8 pad_00[0x13];
    u8 unk_13;
} Row_818FEF80_S_818FEF80_1;   /* object in func_80024780 */

typedef struct Row_818FEF80_S_818FEF80_2 {
    u8 pad_00[0x8];
    union { s32 s; s32 u; } unk_08;   /* accessed as both */
} Row_818FEF80_S_818FEF80_2;   /* arg1 in func_80024780 */

typedef struct Row_818FEF80_S_818FEF80_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} Row_818FEF80_S_818FEF80_3;   /* arg2 in func_80024780 */

typedef struct Row_818FEF80_S_818FEF80_4 {
    u8 pad_00[0x14];
    u16 unk_14;
} Row_818FEF80_S_818FEF80_4;   /* linked in func_80024780 */

/* Advance a timed visual effect, updating position, shading, and linked display flags. */
typedef struct Row_818FF19C_S_818FF19C_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    s16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
    u8 pad_0C[0x24];
    void * unk_30;
    void * unk_34;
    void * unk_38;
    void * unk_3C;
} Row_818FF19C_S_818FF19C_0;   /* arg0 in func_8002499C */

typedef struct Row_818FF19C_S_818FF19C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} Row_818FF19C_S_818FF19C_1;   /* arg1 in func_8002499C */

typedef struct Row_818FF19C_S_818FF19C_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} Row_818FF19C_S_818FF19C_2;   /* arg2 in func_8002499C */

typedef struct Row_818FF19C_S_818FF19C_3 {
    u8 pad_00[0x90];
    s16 unk_90;
} Row_818FF19C_S_818FF19C_3;   /* ((Row_818FF19C_S_818FF19C_0 *)arg0)->unk_34 in func_8002499C */

typedef struct Row_818FF19C_S_818FF19C_4 {
    u8 pad_00[0x13];
    u8 unk_13;
} Row_818FF19C_S_818FF19C_4;   /* ((Row_818FF19C_S_818FF19C_0 *)arg0)->unk_30 in func_8002499C */

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} __attribute__((packed)) Row_818FF19C_Rect8;

/* Updates the tiled texture and draws a moving, fading effect until completion. */
#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Row_818FF5B8_Copy12;

typedef struct Row_818FF5B8_S_818FF5B8_0 {
    u8 pad_00[0x2C];
    void * unk_2C;
    s32 unk_30;
    void ** unk_34;
} Row_818FF5B8_S_818FF5B8_0;   /* temp_v1 in func_80024DB8 */

typedef struct Row_818FF5B8_S_818FF5B8_1 {
    u8 pad_00[0x60];
    s32 unk_60;
} Row_818FF5B8_S_818FF5B8_1;   /* *arg0 in func_80024DB8 */

typedef struct Row_818FF5B8_S_818FF5B8_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} Row_818FF5B8_S_818FF5B8_2;   /* temp_a3 in func_80024DB8 */

typedef struct Row_818FF5B8_S_818FF5B8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} Row_818FF5B8_S_818FF5B8_3;   /* temp_v1_2 in func_80024DB8 */

typedef struct Row_818FF5B8_S_818FF5B8_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} Row_818FF5B8_S_818FF5B8_4;   /* arg1 in func_80024DB8 */

typedef struct Row_818FF5B8_S_818FF5B8_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} Row_818FF5B8_S_818FF5B8_5;   /* arg2 in func_80024DB8 */

/* Creates an owner-linked object with the supplied position and appearance. */
s32 func_80067014(s32);
void func_800672D8(void *, void *);
void func_8006733C(void *, void *);
void draw_transformed_sprite_with_clip_rect(void *, void *, void *, s32, s32);
s32 func_8004491C();

extern Row_818FF19C_Rect8 D_80024028;
extern Row_818FF19C_Rect8 D_80024030;
extern M2C_UNK D_80024750;
extern Row_818FF5B8_Copy12 D_80025E64;
void func_800246F8(void *state_data, s32 unused, void *scale_data);
void func_80024750(void *object);
void advance_timed_visual_effect(void *state, void *position, void *visual);
void update_tiled_fade_effect(void *effect, void *offset_state, void *render_state);
void func_80024DB8(void **owner_ref, Row_818FF5B8_S_818FF5B8_4 *spawn_pos, Row_818FF5B8_S_818FF5B8_5 *appearance);
extern u8 D_80025E80[];
#endif

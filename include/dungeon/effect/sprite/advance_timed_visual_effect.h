#ifndef DUNGEON_OVL_191EEF8_H
#define DUNGEON_OVL_191EEF8_H
#include "common.h"
#include "dungeon/effect/particle.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"
struct ObjectNodeHeader;
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

typedef struct {
    ActorRecord *actor;
} MirroredSpriteOwner;
typedef struct {
    u8 pad_00[0x20];
    Row_818FF5B8_Copy12 texture;
    ActorRecord *actor;
    void *target;
    MirroredSpriteOwner *owner;
} MirroredSpriteBody;
typedef struct {
    ObjectNodeHeader header;
    MirroredSpriteBody body;
} MirroredSpriteNode;

/* Creates an owner-linked object with the supplied position and appearance. */
s32 DrawSync(s32);
void LoadImage(void *, void *);
void StoreImage(void *, void *);
void draw_transformed_sprite_with_clip_rect(void *, void *, void *, s32, s32);
s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);

extern Row_818FF19C_Rect8 D_80024028;
extern Row_818FF19C_Rect8 D_80024030;
extern M2C_UNK D_80024750;
extern Row_818FF5B8_Copy12 D_80025E64;
void expire_effect_at_unit_scale(void *state_data, s32 unused, void *scale_data);
void finish_timed_visual_effect(void *object);
void advance_timed_visual_effect(void *state, void *position, void *visual);
void update_tiled_fade_effect(void *effect, void *offset_state, void *render_state);
extern u8 particle_update_flag[];
#endif

#ifndef DUNGEON_OVL_190D6A4_H
#define DUNGEON_OVL_190D6A4_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
#include "sdk/libc.h"
#include "dungeon/level.h"
/* extern */

/* Return a random sign of either -1 or 1. */
typedef struct { u8 pad[0x32]; s16 lifetime; } ParticleWork;
typedef union { s32 word; struct { u16 low; s16 high; } half; } ParticleFixed;
typedef struct { u16 pad0, x, pad4, y; ParticleFixed z; } ParticlePosition;

/* Raise a particle below terrain, then retire it when its lifetime expires. */
typedef struct { u16 pad0, x, pad4, y, pad8, z; } ParticleVector;
typedef struct { s32 x, y, z; } ParticleOffsets;
typedef struct Row_818ED7A0_ParticleNode { u8 pad0[8]; ParticleVector *position; void *sprite; void *update; } Row_818ED7A0_ParticleNode;
typedef struct { u8 pad0[8]; s32 color; u8 padC[8]; u16 age; u8 pad16[0x1C]; u16 lifetime; } NewParticleWork;

/* Attach a particle with randomized offsets and a finite lifetime to its owner. */
typedef struct Row_818ED8C0_S_800250C0_0 {
    u16 unk_00;
    u8 pad_02[0x2];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x4];
    s16 unk_0C;
    u8 pad_0E[0x12];
    s16 unk_20;
    u8 pad_22[0x8];
    u8 unk_2A;
    u8 unk_2B;
} Row_818ED8C0_S_800250C0_0;   /* arg0 in func_800250C0; pointer addresses record offset 0x2 */

typedef struct Row_818ED8C0_S_800250C0_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} Row_818ED8C0_S_800250C0_1;   /* arg2 in func_800250C0 */

/* Updates an effect's grayscale intensity and animation frame, marking it finished at the end of its lifetime. */
typedef struct Row_818ED9F0_S_800251F0_0 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x6];
    u16 unk_0A;
    union { u16 s; s16 u; } unk_0C;   /* accessed as both */
    u8 pad_0E[0x10];
    u16 unk_1E;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 unk_29;
    u8 pad_2A[0x62];
    u16 unk_8C;
} Row_818ED9F0_S_800251F0_0;   /* arg1 in func_800251F0 */

typedef struct Row_818ED9F0_S_800251F0_1 {
    u8 pad_00[0x6428];
    s16 unk_6428;
} Row_818ED9F0_S_800251F0_1;   /* page in func_800251F0 */

/* Advance object counters and animation values, and flag expiration. */
typedef struct Row_818EDB60_S_80025360_0_pre {
    u16 unk_00;
} Row_818EDB60_S_80025360_0_pre;   /* the 0x2 bytes before obj in func_80025360, addressed as obj[-1] */

typedef struct Row_818EDB60_S_80025360_0 {
    s16 unk_00;
    s16 unk_02;
    u8 pad_04[0x3C];
    void * unk_40;
    u8 pad_44[0x4];
    s32 unk_48;
} Row_818EDB60_S_80025360_0;   /* obj in func_80025360 */

typedef struct Row_818EDB60_S_80025360_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} Row_818EDB60_S_80025360_1;   /* dest in func_80025360 */

typedef struct Row_818EDB60_S_80025360_2 {
    u8 pad_00[0x9C];
    s16 unk_9C;
} Row_818EDB60_S_80025360_2;   /* ((Row_818EDB60_S_80025360_0 *)obj)->unk_40 in func_80025360 */

typedef struct Row_818EDB60_Rect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Row_818EDB60_Rect;

typedef struct Row_818EDB60_Work {
    Row_818EDB60_Rect rect;
    s16 x;
    s16 y;
} Row_818EDB60_Work;

/* Updates a timed rectangle effect, fading its color in and out and marking completion. */
void *allocate_list_node(s32, void *);
void *func_8003FD64(s32, void *);
void register_node(void *, void *);
void func_8004491C(void *, void *);
void func_80024C54(void);
s32 draw_effect_and_restore_clip();

extern u8 D_80020000[];
extern Row_818EDB60_Rect D_80024048;
s32 get_a_random_sign_either_n_1_n_1(void);
void create_linked_effect_segments(ParticleWork *work, ParticlePosition *position);
void spawn_linked_effect_particle(Row_818ED7A0_ParticleNode *owner, s32 age, s32 color, s32 lifetime, s16 dx, s16 dy, s16 dz);
void update_an_effect_s_grayscale_intensity_animation_frame_marking_finished_end(void *effect, s32 age, Row_818ED8C0_S_800250C0_1 *color, s32 fade_ticks);
void advance_object_counters_animation_values_flag_expiration(void *object_ptr);
void update_a_timed_rectangle_effect_fading_color_in_out_marking_completion(void *effect_arg, void *unused, void *sprite_arg);
extern u8 rectangle_effect_updated[];
#endif

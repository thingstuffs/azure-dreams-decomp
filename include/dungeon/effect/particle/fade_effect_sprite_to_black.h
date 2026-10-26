#ifndef DUNGEON_OVL_184C800_H
#define DUNGEON_OVL_184C800_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "modules/dungeon_native_abi.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor.h"

typedef struct S_8182C800_1 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    s32 unk_60;
    u8 pad_64[0xE];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_8182C800_1;   /* temp_s7 in func_8002401C */

typedef struct S_8182C800_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_8182C800_2;   /* sp68 in func_8002401C */

typedef struct S_8182C800_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8182C800_3;   /* temp_a1_2 in func_8002401C */

typedef struct S_8182C800_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8182C800_5;   /* arg1 in func_8002401C */

typedef struct S_8182C800_6 {
    u8 * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8182C800_6;   /* work_s5 in func_8002401C */

typedef struct S_8182C800_7 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_7;   /* page_a in func_8002401C */

typedef struct S_8182C800_8 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8182C800_8;   /* temp_s4 in func_8002401C */

typedef struct S_8182C800_10 {
    s32 unk_00;
} S_8182C800_10;   /* temp_a1_3 in func_8002401C */

typedef struct S_8182C800_11 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_11;   /* temp_a1_4 in func_8002401C */

typedef struct S_8182C800_12 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8182C800_12;   /* temp_a0_7 in func_8002401C */

typedef struct S_8182C800_14 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_14;   /* state1_tex in func_8002401C */

typedef struct S_8182C800_15 {
    void * unk_00;
    u8 pad_04[0x44];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_8182C800_15;   /* temp_s3 in func_8002401C */

typedef struct S_8182C800_16 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_16;   /* page_e in func_8002401C */

typedef struct S_8182C800_17 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_17;   /* page_b in func_8002401C */

typedef struct S_8182C800_18 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_8182C800_18;   /* temp_a0_11 in func_8002401C */

typedef struct S_8182C800_19 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_8182C800_19;   /* temp_a0_12 in func_8002401C */

typedef struct S_8182C800_21 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_21;   /* page_d in func_8002401C */

typedef struct S_8182C800_22 {
    s32 unk_00;
} S_8182C800_22;   /* D_800814A0 in func_8002401C */

typedef struct Func80024000Frame {
    s16 pad20;
    s16 sp22;
    s16 pad24;
    s16 sp26;
    union {
        s32 sp28;
        struct { s16 pad28; s16 sp2A; } half;
    } u28;
    u8 pad2C[12];
    s16 sp38;
    s16 sp3A;
    s16 sp3C;
    s16 pad3E;
    s16 *sp40;
    s16 *sp44;
    s16 sp48;
    s16 pad4A;
    s16 sp4C;
    s16 pad4E;
    s16 sp50;
    s16 sp52;
    s16 sp54;
    s16 pad56;
    s16 sp58;
    s16 sp5A;
    u8 pad5C[4];
    s16 sp60;
    s16 sp62;
    s16 sp64;
    s16 pad66;
} Func80024000Frame;

typedef struct S_8182D544_0_pre {
    u16 unk_00;
} S_8182D544_0_pre;   /* the 0x2 bytes before arg0 in func_80024D44, addressed as arg0[-1] */

typedef struct S_8182D544_0 {
    void * unk_00;
    u8 pad_04[0x44];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_8182D544_0;   /* arg0 in func_80024D44 */

typedef struct S_8182D544_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_8182D544_1;   /* object in func_80024D44 */

typedef struct S_8182D544_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8182D544_2;   /* arg1 in func_80024D44 */

typedef struct S_8182D544_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x6];
    union {
        struct { u8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x4];
    u16 unk_14;
} S_8182D544_3;   /* arg2 in func_80024D44 */

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct {
    void *child;
    u8 pad[0x44];
    u16 count;
    u16 pad4a;
    s16 kind;
} Object;

typedef struct {
    u8 pad[0x0C];
    u8 limit;
    u8 value_d;
    u8 value_e;
    u8 pad_f[5];
    u16 flags;
} Effect;

extern u8 directional_effect_entries[];
extern u8 directional_sprite_entries[];
extern s32 D_800DEB70;
s32 resolve_record_orientation_or_fallback();
s32 rand(void);
void apply_attack_power_and_element_effects();
void *scan_actor_along_heading();
s32 get_definition_entry_byte_13();
extern u8 D_800DEBD8;
extern s32 rand(void);
void update_directional_actor_effect(void *effect, void *motion, void *sprite);
void move_the_effect_count_down_timer_fade_sprite_black(void *effect, S_8182D544_2 *motion, SpriteFrameState *sprite);
void advance_motion_damping_downward_acceleration_count_down_fade_effect(Object *object, Motion *motion, SpriteFrameState *effect);
#endif

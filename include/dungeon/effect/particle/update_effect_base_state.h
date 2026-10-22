#ifndef DUNGEON_OVL_1864800_H
#define DUNGEON_OVL_1864800_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_native_abi.h"
#include "shared/dungeon_status.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/sprite_source.h"

typedef struct S_81844800_0_pre {
    u16 unk_00;
} S_81844800_0_pre;   /* the 0x2 bytes before arg0 in func_80024020, addressed as arg0[-1] */

typedef struct S_81844800_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x44];
    union { u16 s; s16 u; } unk_50;   /* accessed as both */
    union { u16 s; s16 u; } unk_52;   /* accessed as both */
} S_81844800_0;   /* arg0 in func_80024020 */

typedef struct S_81844800_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_81844800_1_pre;   /* the 0x14 bytes before root in func_80024020, addressed as root[-1] */

typedef struct S_81844800_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_81844800_1;   /* root in func_80024020 */

typedef struct S_81844800_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_81844800_2;   /* object in func_80024020 */

typedef struct S_81844800_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_10;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_81844800_3;   /* arg1_reg in func_80024020 */

typedef struct S_81844800_5 {
    u8 pad_00[0x4];
    u32 unk_04;
} S_81844800_5;   /* s8_page in func_80024020 */

typedef struct S_81844800_6 {
    u8 pad_00[0x48];
    u16 unk_48;
    u16 unk_4A;
    u16 unk_4C;
} S_81844800_6;   /* part in func_80024020 */

typedef struct S_81844800_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_81844800_7;   /* info in func_80024020 */

typedef struct S_81844800_8_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_81844800_8_pre;   /* the 0x14 bytes before created in func_80024020, addressed as created[-1] */

typedef struct S_81844800_9 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81844800_9;   /* arg2_reg in func_80024020 */

typedef struct S_81844800_10 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_81844800_10;   /* base_before in func_80024020 */

typedef struct S_81844800_11 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81844800_11;   /* base_after in func_80024020 */

typedef struct S_81844800_12 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x20];
    u16 unk_2A;
    u16 unk_2C;
} S_81844800_12;   /* initial_part in func_80024020 */

typedef struct S_81844800_14 {
    union { s32 * s; s32 u; } unk_00;   /* accessed as both */
    union { s32 * s; s32 u; } unk_04;   /* accessed as both */
    union { struct { s32 * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_81844800_14;   /* ((S_81844800_2 *)object)->unk_08 in func_80024020 */

typedef struct S_81844800_15 {
    u16 unk_00;
} S_81844800_15;   /* ((S_81844800_0 *)arg0)->unk_04 in func_80024020 */

typedef struct S_81844800_16 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81844800_16;   /* ((S_81844800_10 *)base_before)->unk_0C in func_80024020 */

typedef struct S_81844800_17 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81844800_17;   /* ((S_81844800_11 *)base_after)->unk_08 in func_80024020 */

typedef struct Vec3 {
    s16 x;
    s16 y;
    s16 z;
} Vec3;

typedef struct S_81844F2C_0_pre {
    u16 unk_00;
} S_81844F2C_0_pre;   /* the 0x2 bytes before base in func_8002472C, addressed as base[-1] */

typedef struct S_81844F2C_0 {
    void * unk_00;
    u16 unk_04;
    union { u16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x4];
    u16 unk_0C;
    u16 unk_0E;
    u8 pad_10[0x1A];
    union { u16 s; u16 u; s16 p; } unk_2A;   /* accessed as both */
    union { u16 s; s16 u; u16 p; } unk_2C;   /* accessed as both */
} S_81844F2C_0;   /* base in func_8002472C */

typedef struct S_81844F2C_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_81844F2C_1;   /* entity in func_8002472C */

typedef struct S_81844F2C_4 {
    u8 pad_00[0x14A0];
    u32 unk_14A0;
} S_81844F2C_4;   /* page in func_8002472C */

typedef struct Packed8 {
    u32 word0;
    u32 word1;
} __attribute__((packed)) Packed8;

typedef struct Coord {
    s16 x;
    s16 y;
} Coord;

typedef union Scratch {
    s32 word;
    u16 half;
    u8 byte;
} Scratch;

typedef struct {
    unsigned addr: 24;
    unsigned len: 8;
    u8 r0, g0, b0, code;
} P_TAG;

typedef struct {
    s32 x, y, z;
    s32 vx, vy, vz;
} VecState;

extern u8 secondary_sprite[];
extern u8 D_800DECF8[];
extern s32 func_80069EF8(void);
extern s32 get_definition_entry_byte_13(s16 entry_index);
extern void *scan_actor_along_heading(void *, u8, u8, s16, s16);
extern void apply_attack_power_and_element_effects(void *, s32, s32, s32, s32, void *, s32);
extern void *resolve_record_orientation_or_fallback(void *, void *, Vec3 *, s32);
extern s32 func_80065420(Packed8 *, Coord *, Coord *, Coord *);
extern s32 func_80066460(s32, s32, s32, s32);
extern s32 func_8006649C(s32, s32);
extern void func_80066640(void *, s32);
extern void func_800666F4(void *);
void func_80024020(void *effect, void *motion, void *source_render);
void update_effect_base_state(s32 effect_or_count);
s32 draw_layered_vertical_sprite_chain(u8 *first_node);
void fade_effect_sprite_to_black(void *effect, VecState *motion, SpriteFrameState *sprite);
#endif

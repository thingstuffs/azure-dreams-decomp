#ifndef DUNGEON_OVL_18C4828_H
#define DUNGEON_OVL_18C4828_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"


/* Applies a flag-adjusted stat increase to an eligible target and updates its state. */
typedef struct {
    u8 pad14[0x14];
    u16 flags;
    u8 pad1a[4];
    s16 value;
} Row_818A48C4_Func818A48C4Object;

/* Increment the source flags and update the target with a random value. */
typedef struct Row_818A4948_S_func_818A4948_0 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} Row_818A4948_S_func_818A4948_0;

typedef struct Row_818A4948_S_func_818A4948_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} Row_818A4948_S_func_818A4948_1;

typedef struct Row_818A4948_S_func_818A4948_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} Row_818A4948_S_func_818A4948_2;

/* Creates and initializes an object with the supplied data and coordinates. */
/* Increment the object counter and pass the low 32 bits of the value to the helper. */
#ifndef NULL
#define NULL 0
#endif

typedef struct Row_818A4A64_S_818A4A64_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} Row_818A4A64_S_818A4A64_0;   /* temp_v0 in func_80024264 */

typedef struct Row_818A4A64_S_818A4A64_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} Row_818A4A64_S_818A4A64_1;   /* temp_s0 in func_80024264 */

typedef struct Row_818A4A64_S_818A4A64_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} Row_818A4A64_S_818A4A64_2;   /* arg1 in func_80024264 */

typedef struct Row_818A4A64_S_818A4A64_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} Row_818A4A64_S_818A4A64_3;   /* temp_v1 in func_80024264 */

/* Creates an object, initializes its rendering state, and copies its position. */
/* extern */
                      /* extern */
                             /* extern */
                             /* extern */
                                /* extern */

typedef struct Row_818A4B40_S_818A4B40_0 {
    void * unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
} Row_818A4B40_S_818A4B40_0;   /* arg0 in func_80024340 */

typedef struct Row_818A4B40_S_818A4B40_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} Row_818A4B40_S_818A4B40_1;   /* temp_v1 in func_80024340 */

typedef struct Row_818A4B40_S_818A4B40_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} Row_818A4B40_S_818A4B40_2;   /* arg1 in func_80024340 */

/* Advance the height offset, randomize position on wrap, and update the object. */
/* extern */
           /* extern */
                             /* extern */
                             /* extern */
                                /* extern */

typedef struct Row_818A4CA0_S_818A4CA0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} Row_818A4CA0_S_818A4CA0_0;   /* temp_v0 in func_800244A0 */

typedef struct Row_818A4CA0_S_818A4CA0_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
} Row_818A4CA0_S_818A4CA0_1;   /* arg0 in func_800244A0 */

typedef struct Row_818A4CA0_S_818A4CA0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} Row_818A4CA0_S_818A4CA0_2;   /* arg1 in func_800244A0 */

typedef struct Row_818A4CA0_S_818A4CA0_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} Row_818A4CA0_S_818A4CA0_3;   /* temp_s0 in func_800244A0 */

typedef struct Row_818A4CA0_S_818A4CA0_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} Row_818A4CA0_S_818A4CA0_4;   /* temp_s3 in func_800244A0 */

/* Create a sprite effect at a random offset from the supplied position. */
typedef struct Row_818A4E74_S_func_818A4E74_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} Row_818A4E74_S_func_818A4E74_0;

typedef struct Row_818A4E74_S_func_818A4E74_1 {
    u8 pad_00[0x1A];
    s16 unk_1A;
} Row_818A4E74_S_func_818A4E74_1;

/* Increment the object counter and store a random remainder modulo 4096 in the target. */
/* extern */
                                /* extern */

typedef struct Row_818A4ED0_S_818A4ED0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} Row_818A4ED0_S_818A4ED0_0;   /* temp_v0 in func_800246D0 */

typedef struct Row_818A4ED0_S_818A4ED0_1 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} Row_818A4ED0_S_818A4ED0_1;   /* temp_s0 in func_800246D0 */

typedef struct Row_818A4ED0_S_818A4ED0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} Row_818A4ED0_S_818A4ED0_2;   /* temp_s0_2 in func_800246D0 */

typedef struct Row_818A4ED0_S_818A4ED0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} Row_818A4ED0_S_818A4ED0_3;   /* arg1 in func_800246D0 */

/* Creates an object at the supplied position with a randomized rotation. */
s32 func_8009D218(void *, s32);
s32 func_800A6870(s16 input_value);
void func_800AD4D0(void *);
void func_800AD568(void *);
void func_800B4C7C(s32 flags, void *source_data, s16 value, u16 callback_mode);
void func_8003DB94(void *, void *, s32);
void func_800478B8(void *);
s32 rand(void);
s32 func_8004491C(void *, s32);
s32 func_800644B8();
s32 func_80064584();
extern u8 D_80025238[];
extern u8 D_800DEAE0[];
extern M2C_UNK D_800DECF8;
extern u8 D_80025214[];
void func_80024028(void *target, s32 effect_param);
void func_800240C4(Row_818A48C4_Func818A48C4Object **source_ref, s32 unused,
                   Row_818A48C4_Func818A48C4Object *target);
void *func_80024148(s32 user_data, Row_818A4948_S_func_818A4948_2 *source_coords);
void func_80024230(void **object_ref, long long value);
void *func_80024264(s32 context_value, Row_818A4A64_S_818A4A64_2 *initial_position);
void func_80024340(Row_818A4B40_S_818A4B40_0 *motion, Row_818A4B40_S_818A4B40_2 *position, Rec_D_80082E80 *object);
s32 func_800244A0(Row_818A4CA0_S_818A4CA0_1 *effect_data, Row_818A4CA0_S_818A4CA0_2 *origin, s16 effect_param, s16 frame_index);
void func_80024674(void **object_ref, s32 unused, Row_818A4E74_S_func_818A4E74_1 *target);
s32 func_800246D0(s32 object_param, Row_818A4ED0_S_818A4ED0_3 *spawn_position);
#endif

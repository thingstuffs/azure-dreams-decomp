#ifndef DUNGEON_OVL_7E705800_H
#define DUNGEON_OVL_7E705800_H
#include "common.h"
#include "m2c_compat.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Row_818FECCC_S_818FECCC_0 {
    u8 pad_00[0x8];
    union { void * s; s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x4];
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} Row_818FECCC_S_818FECCC_0;   /* temp_s0 in func_800244CC */

typedef struct Row_818FECCC_S_818FECCC_1 {
    u8 pad_00[0x8];
    void * unk_08;
} Row_818FECCC_S_818FECCC_1;   /* held_arg0 in func_800244CC */

typedef struct Row_818FECCC_S_818FECCC_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} Row_818FECCC_S_818FECCC_2;   /* dest1 in func_800244CC */

typedef struct Row_818FECCC_S_818FECCC_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} Row_818FECCC_S_818FECCC_3;   /* dest2 in func_800244CC */

typedef struct Row_818FECCC_S_818FECCC_4 {
    u8 pad_00[0x8];
    void * unk_08;
} Row_818FECCC_S_818FECCC_4;   /* call_obj in func_800244CC */

typedef struct Row_818FECCC_S_818FECCC_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} Row_818FECCC_S_818FECCC_5;   /* dest3 in func_800244CC */

typedef struct Row_818FECCC_S_818FECCC_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} Row_818FECCC_S_818FECCC_6;   /* ((Row_818FECCC_S_818FECCC_1 *)held_arg0)->unk_08 in func_800244CC */

/* Creates an effect at randomized offsets from the source object's position. */
void *allocate_list_node(s32, void *);
void *func_8003FD64(s32, void *);
s32 func_80069EF8(void);
void register_node(void *, void *);
void func_8004491C(void *, void *);
extern u8 D_800241B0[];
extern u8 D_80024400[];
void spawn_jittered_child_effect(
    void *source,
    s16 field_34,
    s32 field_28,
    s16 field_52,
    s16 offset_x,
    s16 offset_y,
    s16 offset_z);
#endif

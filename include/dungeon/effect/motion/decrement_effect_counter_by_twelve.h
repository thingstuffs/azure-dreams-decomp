#ifndef DUNGEON_OVL_7E711800_H
#define DUNGEON_OVL_7E711800_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
/* Subtracts 12 from the object counter and sets flags when it reaches zero. */
#ifndef NULL
#define NULL 0
#endif

typedef struct Row_818F33BC_S_80024BBC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} Row_818F33BC_S_80024BBC_0;   /* object in func_80024BBC */

typedef struct Row_818F33BC_S_80024BBC_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} Row_818F33BC_S_80024BBC_2;   /* dest1 in func_80024BBC */

typedef struct Row_818F33BC_S_80024BBC_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} Row_818F33BC_S_80024BBC_3;   /* dest2 in func_80024BBC */

typedef struct Row_818F33BC_S_80024BBC_4 {
    u8 pad_00[0xA];
    s16 unk_0A;
} Row_818F33BC_S_80024BBC_4;   /* dest3 in func_80024BBC */

typedef struct Row_818F33BC_S_80024BBC_5 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    u8 pad_34[0x1C];
    s32 unk_50;
} Row_818F33BC_S_80024BBC_5;   /* base in func_80024BBC */

typedef struct Row_818F33BC_S_80024BBC_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} Row_818F33BC_S_80024BBC_6;   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_80024BBC */

/* Creates an object with randomized position offsets and initializes its state and callbacks. */
void *allocate_list_node(s32, void *);
void *func_8003FD64(s32, void *);
s32 rand(void);
void register_node(void *, void *);
void func_8004491C(void *, void *);
void draw_linked_shaded_tiles(void);
extern s16 D_800259AC;
void decrement_effect_counter_by_twelve(void *object);
void create_random_offset_effect_object(
    EntityRec *source, s16 field_14_value, void *payload, s16 field_32_value,
    s16 x_offset, s16 y_offset, s16 z_offset);
#endif

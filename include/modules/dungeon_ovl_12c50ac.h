#ifndef MODULE_DUNGEON_OVL_12C50AC_H
#define MODULE_DUNGEON_OVL_12C50AC_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct {
    u8 pad0[2];
    s16 field2;
    u8 pad4[2];
    s16 field6;
    u8 pad8[2];
    u16 fieldA;
    u8 padC[0x18];
    u8 field24;
    u8 field25;
    u8 pad26[6];
    void *field2C;
} Func812A5000Child;

typedef struct {
    u8 pad0[8];
    Func812A5000Child *child1;
    Func812A5000Child *child0;
    void *field10;
} Func812A5000Parent;

typedef struct {
    u8 pad0[0x13];
    u8 field13;
    u32 field14;
    u8 pad18[4];
    u32 field1C;
    u8 pad20[0xA];
    s16 field2A;
    u8 pad2C[0x60];
    void *field8C;
    u8 pad90[2];
    s16 field92;
    u8 pad94[6];
    u8 field9A;
    u8 pad9B;
    s8 field9C;
} Func812A5000Entity;



void *func_8003FD64();                 /* extern */
s32 func_8004491C();                /* extern */
void initialize_actor_sprite_and_animation(); /* extern */
s32 try_move_actor_to_valid_position(); /* extern */
s32 get_direction_toward_target_position();                          /* extern */
extern void *D_800FBE1C[];
void func_80170A4C(void *, void *, void *);

/* Creates and initializes an entity at the center of the specified tile. */

#include "shared/dir_step.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
extern int abs(int);

typedef struct S_812A524C_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
} S_812A524C_0;   /* &D_800FBE22 in func_80170A4C */

typedef struct S_812A524C_1 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
} S_812A524C_1;   /* &D_800FBE20 in func_80170A4C */


typedef struct S_812A524C_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x60];
    void (*unk_8C)(void *, void *, void *, void *);
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_90;   /* overlapping accesses */
    s16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x1];
    union { s8 s; u8 u; } unk_9D;   /* accessed as both */
    u16 unk_9E;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0xC];
    s32 unk_B0;
    u8 pad_B4[0x4];
    u8 unk_B8;
    u8 unk_B9;
} S_812A524C_3;   /* arg0 in func_80170A4C */

typedef struct S_812A524C_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
} S_812A524C_4;   /* arg3 in func_80170A4C */

typedef struct S_812A524C_5 {
    void * unk_00;
} S_812A524C_5;   /* &D_800FBE54 in func_80170A4C */

typedef struct S_812A524C_6 {
    u16 unk_00;
} S_812A524C_6;   /* &D_80013714 in func_80170A4C */

typedef struct S_812A524C_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_7;   /* ev0 in func_80170A4C */

typedef struct S_812A524C_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_8;   /* pos0 in func_80170A4C */

typedef struct S_812A524C_9 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x6E];
    u8 unk_9A;
} S_812A524C_9;   /* temp_actor in func_80170A4C */

typedef struct S_812A524C_10 {
    u8 pad_00[0x24];
    union {
        struct { u16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
} S_812A524C_10;   /* ev1 in func_80170A4C */

typedef struct S_812A524C_12 {
    u8 pad_00[0x24];
    union {
        struct { u16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
} S_812A524C_12;   /* ev2 in func_80170A4C */

typedef struct S_812A524C_14 {
    u8 pad_00[0x24];
    union {
        struct { u16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
} S_812A524C_14;   /* ev3 in func_80170A4C */

typedef struct S_812A524C_15 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_15;   /* pos3 in func_80170A4C */

typedef struct S_812A524C_16 {
    u8 pad_00[0x24];
    union {
        struct { u16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
} S_812A524C_16;   /* ev4 in func_80170A4C */

typedef struct S_812A524C_17 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_17;   /* pos4 in func_80170A4C */

typedef struct S_812A524C_18 {
    u8 pad_00[0x24];
    union {
        struct { u16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
} S_812A524C_18;   /* ev5 in func_80170A4C */

typedef struct S_812A524C_21 {
    u8 pad_00[0x24];
    union {
        struct { u16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
} S_812A524C_21;   /* ev6 in func_80170A4C */

typedef struct S_812A524C_23 {
    u8 pad_00[0x24];
    union {
        struct { u16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
} S_812A524C_23;   /* ev7 in func_80170A4C */

typedef struct S_812A524C_24 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_24;   /* pos7 in func_80170A4C */

typedef struct S_812A524C_25 {
    u8 pad_00[0x24];
    union {
        struct { u16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
} S_812A524C_25;   /* ev8 in func_80170A4C */

typedef struct S_812A524C_26 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_26;   /* pos8 in func_80170A4C */

typedef struct S_812A524C_27 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_27;   /* ev9 in func_80170A4C */

typedef struct S_812A524C_28 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_28;   /* pos9 in func_80170A4C */

typedef struct S_812A524C_29 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_29;   /* ev10 in func_80170A4C */

typedef struct S_812A524C_31 {
    u8 pad_00[0x24];
    union {
        struct { u16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
} S_812A524C_31;   /* ev11 in func_80170A4C */

typedef struct S_812A524C_32 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_32;   /* pos11 in func_80170A4C */

typedef struct S_812A524C_34 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_34;   /* temp_v1_3 in func_80170A4C */

typedef struct S_812A524C_36 {
    union { s32 n; s32 v; } unk_00;   /* accessed as both */
} S_812A524C_36;   /* &D_800E296C in func_80170A4C */

typedef struct S_812A524C_37 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_812A524C_37;   /* arg1 in func_80170A4C */

typedef struct S_812A524C_38 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    union { u16 n; u16 v; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { u8 * p; s32 i; } unk_2C;   /* accessed as both */
} S_812A524C_38;   /* arg2 in func_80170A4C */

typedef struct S_812A524C_39 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x6E];
    u8 unk_9A;
} S_812A524C_39;   /* ((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v in func_80170A4C */

typedef struct S_812A524C_40 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_812A524C_40;   /* ((S_812A524C_5 *)(&D_800FBE54))->unk_00 in func_80170A4C */


s32 func_800353F4(); /* extern */
void func_80042B68();                /* extern */
void select_indirect_table_entry();              /* extern */
void func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
void apply_monster_koyaw_data();                 /* extern */
s32 has_pending_actor_or_turn_action();                          /* extern */
s16 set_or_clear_actor_status_slot();       /* extern */
void update_actor_status_and_food();                      /* extern */
s32 refresh_actor_facing_and_lifecycle();  /* extern */
s32 sample_terrain_surface_height();                   /* extern */
void *find_linked_entity_of_type_21();                /* extern */
extern u16 D_80013714[8];
extern u8 D_8006EE9C[16];
extern u8 D_8006F47A[16];
extern u8 D_8006F50D[16];
extern u8 D_8006F6B9[16];
extern u8 D_8006F9D0[16];
extern u8 D_8006FD01[16];
extern u8 D_8006FFB7[16];
extern u8 D_800703D9[16];
extern u8 D_80070684[16];
extern u8 D_80070AF8[16];
extern u8 D_80070C11[16];
extern u8 D_80070E63[16];
extern u8 D_800E296C[16];
extern u8 D_800E3D7C[16];
extern u8 D_800FB3C8[16];
extern u8 D_800FB8DF[16];
extern u8 D_800FBAD7[16];
extern u8 D_800FBD96[16];
extern u8 D_800FBE20[16];
extern u8 D_800FBE22[16];
extern u8 D_800FBE54[16];
typedef struct {
    u8 bytes[16];
} __attribute__((packed)) Packed16;
extern Packed16 D_80170804;
extern u8 D_80171FA4[16];
extern u8 D_80175C30[16];
extern void (*D_80175CC8[])(void *, void *, void *, void *);

#define event_base ((u8 *)((u8 *)(&D_80082E80)))
#define position_base ((u8 *)((u8 *)(&D_80083780)))

/* Updates actor events, behavior, movement, and sprite height and facing. */

#endif

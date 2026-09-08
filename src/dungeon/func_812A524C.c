#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_812A524C_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
} S_812A524C_0;   /* &D_800FBE22 in func_812A524C */

typedef struct S_812A524C_1 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
} S_812A524C_1;   /* &D_800FBE20 in func_812A524C */


typedef struct S_812A524C_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x60];
    M2C_UNK (*unk_8C)(void *, void *, void *, void *);
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_90;   /* overlapping accesses */
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
} S_812A524C_3;   /* arg0 in func_812A524C */

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
} S_812A524C_4;   /* arg3 in func_812A524C */

typedef struct S_812A524C_5 {
    void * unk_00;
} S_812A524C_5;   /* &D_800FBE54 in func_812A524C */

typedef struct S_812A524C_6 {
    u16 unk_00;
} S_812A524C_6;   /* &D_80013714 in func_812A524C */

typedef struct S_812A524C_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_7;   /* ev0 in func_812A524C */

typedef struct S_812A524C_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_8;   /* pos0 in func_812A524C */

typedef struct S_812A524C_9 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x6E];
    u8 unk_9A;
} S_812A524C_9;   /* temp_actor in func_812A524C */

typedef struct S_812A524C_10 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_10;   /* ev1 in func_812A524C */

typedef struct S_812A524C_11 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_11;   /* pos1 in func_812A524C */

typedef struct S_812A524C_12 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_12;   /* ev2 in func_812A524C */

typedef struct S_812A524C_13 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_13;   /* pos2 in func_812A524C */

typedef struct S_812A524C_14 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_14;   /* ev3 in func_812A524C */

typedef struct S_812A524C_15 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_15;   /* pos3 in func_812A524C */

typedef struct S_812A524C_16 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_16;   /* ev4 in func_812A524C */

typedef struct S_812A524C_17 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_17;   /* pos4 in func_812A524C */

typedef struct S_812A524C_18 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_18;   /* ev5 in func_812A524C */

typedef struct S_812A524C_19 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_19;   /* pos5 in func_812A524C */

typedef struct S_812A524C_20 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_812A524C_20;   /* flag_base in func_812A524C */

typedef struct S_812A524C_21 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_21;   /* ev6 in func_812A524C */

typedef struct S_812A524C_22 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_22;   /* pos6 in func_812A524C */

typedef struct S_812A524C_23 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_23;   /* ev7 in func_812A524C */

typedef struct S_812A524C_24 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_24;   /* pos7 in func_812A524C */

typedef struct S_812A524C_25 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_25;   /* ev8 in func_812A524C */

typedef struct S_812A524C_26 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_26;   /* pos8 in func_812A524C */

typedef struct S_812A524C_27 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_27;   /* ev9 in func_812A524C */

typedef struct S_812A524C_28 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_28;   /* pos9 in func_812A524C */

typedef struct S_812A524C_29 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_29;   /* ev10 in func_812A524C */

typedef struct S_812A524C_30 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_30;   /* pos10 in func_812A524C */

typedef struct S_812A524C_31 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_31;   /* ev11 in func_812A524C */

typedef struct S_812A524C_32 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_32;   /* pos11 in func_812A524C */

typedef struct S_812A524C_33 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_33;   /* var_v0_7 in func_812A524C */

typedef struct S_812A524C_34 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_34;   /* temp_v1_3 in func_812A524C */

typedef struct S_812A524C_35 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_35;   /* pos12 in func_812A524C */

typedef struct S_812A524C_36 {
    union { s32 n; volatile s32 v; } unk_00;   /* accessed as both */
} S_812A524C_36;   /* &D_800E296C in func_812A524C */

typedef struct S_812A524C_37 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_812A524C_37;   /* arg1 in func_812A524C */

typedef struct S_812A524C_38 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    union { u16 n; volatile u16 v; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { u8 * p; s32 i; } unk_2C;   /* accessed as both */
} S_812A524C_38;   /* arg2 in func_812A524C */

typedef struct S_812A524C_39 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x6E];
    u8 unk_9A;
} S_812A524C_39;   /* ((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v in func_812A524C */

typedef struct S_812A524C_40 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_812A524C_40;   /* ((S_812A524C_5 *)(&D_800FBE54))->unk_00 in func_812A524C */


M2C_UNK func_800353F4(); /* extern */
M2C_UNK func_80042B68();                /* extern */
M2C_UNK func_80047738();              /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
M2C_UNK func_800A020C();                 /* extern */
s32 func_800A2C34();                          /* extern */
M2C_UNK func_800A48F0();       /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
s32 func_800A9E70();  /* extern */
M2C_UNK func_800AA36C(); /* extern */
s32 func_800BCB04();                   /* extern */
s32 func_800F6D28();    /* extern */
void *func_800F6DFC();                /* extern */
void func_80170CE8() __attribute__((noreturn));     /* extern */
void func_801713EC() __attribute__((noreturn));     /* extern */
void func_80171468() __attribute__((noreturn));     /* extern */
void func_801714E4() __attribute__((noreturn));     /* extern */
void func_80171968() __attribute__((noreturn));     /* extern */
void func_80171AD8() __attribute__((noreturn));     /* extern */
void func_80171B6C() __attribute__((noreturn));     /* extern */
void func_80171BEC() __attribute__((noreturn));     /* extern */
void func_80171CD4() __attribute__((noreturn));     /* extern */
void func_80171E8C() __attribute__((noreturn));     /* extern */
void func_80171ECC() __attribute__((noreturn));     /* extern */
void func_80171ED0() __attribute__((noreturn));     /* extern */
void func_80171F74() __attribute__((noreturn));     /* extern */
extern u8 D_80010248[];
extern u16 D_80013714[8];
extern u8 D_8006CCF8[16];
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
extern u8 D_80082E80[64];
extern u16 D_80082EA4[8];
extern u8 D_80083160[16];
extern s16 D_80083228[8];
extern u16 D_80083462[8];
extern u8 D_80083780[16];
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

#define event_base ((u8 *)&D_80082E80)
#define position_base ((u8 *)&D_80083780)

/* Updates actor events, behavior, movement, and sprite height and facing. */
void func_812A524C(void *actor_in, void *motion_in, void *sprite_in) {
    Packed16 facing_map;
    Packed16 *facing_map_src;
    void *actor = actor_in;
    void *motion = motion_in;
    void *sprite = sprite_in;
    void *entity;
    register u16 *facing_lookup ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 tail_value;
    s32 tail_acc;
    register u32 early_page ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *flag_base;
    u8 *event_0;
    u8 *position_0;
    u8 *event_1;
    u8 *position_1;
    u8 *event_2;
    u8 *position_2;
    u8 *event_3;
    u8 *position_3;
    u8 *event_4;
    u8 *position_4;
    u8 *event_5;
    u8 *position_5;
    u8 *event_6;
    u8 *position_6;
    u8 *event_7;
    u8 *position_7;
    u8 *event_8;
    u8 *position_8;
    u8 *event_9;
    u8 *position_9;
    u8 *event_10;
    u8 *position_10;
    u8 *event_11;
    u8 *position_11;
    u8 *position_12;
    M2C_UNK (*update_actor)(void *, void *, void *, void *);
    M2C_UNK (*update_special)(void *, void *, void *, void *);
    M2C_UNK *nearby_event;
    u8 *scan_10;
    u8 *scan_80;
    u8 *scan_100;
    s32 height;
    s32 ground_delta;
    s16 facing;
    s16 ground_height;
    s32 event_x;
    s32 object_addr;
    s32 velocity_x;
    s32 event_y;
    s32 velocity_y;
    s32 direction;
    s32 start_direction;
    s32 bob_offset;
    s32 entity_flags;
    s32 moving_flags;
    s32 fixed_entity_flags;
    s32 scan_index_10;
    s32 scan_index_80;
    s32 scan_index_100;
    s32 scan_kind;
    s32 scan_group;
    s32 clear_flags;
    s32 motion_x;
    register s32 motion_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 distance_x;
    s32 distance_y;
    s32 scaled_x;
    register s32 event_x_1 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 event_x_2 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 event_x_3 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 event_x_4 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 event_x_5 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 event_x_6 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 event_x_7 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 event_x_8 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 event_x_11 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 final_tail_value;
    s32 fixed_flags;
    s16 previous_state;
    s16 sprite_facing;
    u16 fixed_bob_phase;
    u16 fixed_bob_phase_wide;
    register s32 sprite_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 first_flags;
    u16 bob_phase;
    u16 bob_phase_wide;
    u8 action_state;
    register u8 scan_type ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u8 actor_kind;
    u8 current_kind;
    void *nearby_object;
    S_812A524C_34 *nearby_tile;
    S_812A524C_9 *facing_actor;

    facing_map_src = &D_80170804;
    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    facing_map = *facing_map_src;
    entity = actor;
    flag_base = D_80083160;
    facing_lookup = (u16 *)&facing_map;
    if (((S_812A524C_0 *)(&D_800FBE22))->unk_00.s != ((S_812A524C_1 *)(&D_800FBE20))->unk_00.s) {
        ((S_812A524C_0 *)(&D_800FBE22))->unk_00.u = (u16) ((S_812A524C_1 *)(&D_800FBE20))->unk_00.u;
    }
    if (((S_812A524C_1 *)(&D_800FBE20))->unk_00.s != ((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A) {
        ((S_812A524C_1 *)(&D_800FBE20))->unk_00.u = (u16) ((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A;
    }
    action_state = ((S_812A524C_3 *)actor)->unk_B8;
    if (action_state == 2) {
        direction = func_800F6D28(motion);
        ((S_812A524C_3 *)actor)->unk_2A = (s16) (direction << 9);
        if ((((S_812A524C_3 *)actor)->unk_B8 == action_state) && (((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A == 0xE)) {
            ((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_2A = (s16) (facing_lookup[direction & 7] << 9);
        }
    }
    if (((S_812A524C_3 *)actor)->unk_B8 == 3) {
        ((S_812A524C_3 *)actor)->unk_B8 = 0U;
        func_800AA36C(actor, motion, sprite, entity);
    }
    if (((S_812A524C_3 *)actor)->unk_B8 != 0) {
        func_800A9A0C(entity);
        if (D_80083462[0] & 0x2000) {
            ((S_812A524C_4 *)entity)->unk_71 = (u8) (((S_812A524C_4 *)entity)->unk_71 & 0x7F);
        }
    }
    if ((u32) (D_80082EA4[0] - 0x2536) < 2U) {
        ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 0x20000);
    }
    if (!(((S_812A524C_3 *)actor)->unk_B0 & 0x20000)) {
        if (((S_812A524C_5 *)(&D_800FBE54))->unk_00 == NULL) goto block_27;
        func_800A48F0(((S_812A524C_5 *)(&D_800FBE54))->unk_00 + 0x20, 1, 0xA);
        early_page = 0x80010000;
        ASM_PAGEBASE_PIN(early_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80170CE8();
    }
    goto block_26;
action_10:
    func_800353F4(&D_8006F6B9);
    ((S_812A524C_4 *)entity)->unk_6D = 0U;
    ((S_812A524C_3 *)actor)->unk_9B = 0;
    ((S_812A524C_3 *)actor)->unk_B8 = 1U;
    ((S_812A524C_3 *)actor)->unk_B0 |= 0x10;
    func_801713EC();
action_80:
    func_800353F4(&D_8006FFB7);
    ((S_812A524C_4 *)entity)->unk_6D = 0U;
    ((S_812A524C_3 *)actor)->unk_9B = 0;
    ((S_812A524C_3 *)actor)->unk_B8 = 1U;
    ((S_812A524C_3 *)actor)->unk_B0 |= 0x80;
    func_80171468();
action_100:
    func_800353F4(&D_800703D9);
    ((S_812A524C_4 *)entity)->unk_6D = 0U;
    ((S_812A524C_3 *)actor)->unk_9B = 0;
    ((S_812A524C_3 *)actor)->unk_B8 = scan_type;
    ((S_812A524C_3 *)actor)->unk_B0 |= 0x100;
    func_801714E4();
block_26:
    object_addr = (s32) ((S_812A524C_5 *)(&D_800FBE54))->unk_00;
    if (object_addr != 0) {
        func_80042B68(object_addr + 0x20, 1);
        ((S_812A524C_5 *)(&D_800FBE54))->unk_00 = NULL;
    }
block_27:
    ASM_CLOBBER("$18");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    if (!(((S_812A524C_6 *)(&D_80013714))->unk_00 & 1)) {
        if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
            if (!(D_80083462[0] & 0x2000) && ((func_800A2C34(entity) << 0x10) == 0) && (event_0 = (u8 *)&D_80082E80, position_0 = (u8 *)&D_80083780, (((((S_812A524C_7 *)event_0)->unk_24 << 6) + 0x20) == ((S_812A524C_8 *)position_0)->unk_02)) && (((((S_812A524C_7 *)event_0)->unk_25 << 6) + 0x20) == ((S_812A524C_8 *)position_0)->unk_06)) {
                actor_kind = ((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A;
                if ((actor_kind != 0x19) && (actor_kind != 0x1B) && !(((S_812A524C_4 *)entity)->unk_1C & 0x80000)) {
                    if ((((S_812A524C_3 *)actor)->unk_B9 == 0) && !(D_80013714[0] & 1)) {
                        ((S_812A524C_3 *)actor)->unk_B9 = 1U;
                        func_800353F4(&D_8006EE9C);
                        ((S_812A524C_4 *)entity)->unk_6D = 0U;
                        ((S_812A524C_3 *)actor)->unk_9B = 0;
                        ((S_812A524C_3 *)actor)->unk_B8 = 2U;
                        start_direction = func_800F6D28(motion);
                        facing_actor = ((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v;
                        ((S_812A524C_4 *)entity)->unk_2A = (s16) (start_direction << 9);
                        if (facing_actor->unk_9A == 0xE) {
                            facing_actor->unk_2A = (s16) (((u16 *)&facing_map)[start_direction & 7] << 9);
                        }
                        ((S_812A524C_5 *)(&D_800FBE54))->unk_00 = func_800F6DFC(entity);
                    }
                    if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                        if (!(((S_812A524C_3 *)actor)->unk_B0 & 0x20)) {
                            event_1 = (u8 *)&D_80082E80;
                            if ((((S_812A524C_10 *)event_1)->unk_24.at00.v == 0x519) || (((S_812A524C_10 *)event_1)->unk_24.at00.v == 0x619)) {
                                position_1 = (u8 *)&D_80083780;
                                event_x_1 = ((S_812A524C_10 *)event_1)->unk_24.at00u.v;
                                if (((event_x_1 << 6) + 0x20) == ((S_812A524C_11 *)position_1)->unk_02) {
                                    if (((((S_812A524C_10 *)event_1)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_11 *)position_1)->unk_06) {
                                        func_800353F4(&D_8006F9D0);
                                        ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                        ((S_812A524C_3 *)actor)->unk_9B = 0;
                                        ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                        ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 0x20);
                                    }
                                }
                            }
                            current_kind = ((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A;
                            if ((current_kind != 0x19) && (current_kind != 0x1B) && ((((S_812A524C_0 *)(&D_800FBE22))->unk_00.s == 0x1B) || (((S_812A524C_0 *)(&D_800FBE22))->unk_00.s == 0x1F) || (((S_812A524C_0 *)(&D_800FBE22))->unk_00.s == 0x20) || (((S_812A524C_1 *)(&D_800FBE20))->unk_00.s == 0x1B) || (((S_812A524C_1 *)(&D_800FBE20))->unk_00.s == 0x1F) || (((S_812A524C_1 *)(&D_800FBE20))->unk_00.s == 0x20))) {
                                func_800353F4(&D_8006F9D0);
                                ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                ((S_812A524C_3 *)actor)->unk_9B = 0;
                                ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 0x20);
                            }
                        }
                        if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                            if (!(((S_812A524C_3 *)actor)->unk_B0 & 0x4000)) {
                                event_2 = (u8 *)&D_80082E80;
                                if ((((S_812A524C_12 *)event_2)->unk_24.at00.v == 0x2B2D) || (((S_812A524C_12 *)event_2)->unk_24.at00.v == 0x2C2D)) {
                                    position_2 = (u8 *)&D_80083780;
                                    event_x_2 = ((S_812A524C_12 *)event_2)->unk_24.at00u.v;
                                    if (((event_x_2 << 6) + 0x20) == ((S_812A524C_13 *)position_2)->unk_02) {
                                        if (((((S_812A524C_12 *)event_2)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_13 *)position_2)->unk_06) {
                                            func_800353F4(&D_800FB8DF);
                                            ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                            ((S_812A524C_3 *)actor)->unk_9B = 0;
                                            ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                            ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 0x4000);
                                        }
                                    }
                                }
                                if (((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A == 0x1C) {
                                    func_800353F4(&D_800FB8DF);
                                    ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                    ((S_812A524C_3 *)actor)->unk_9B = 0;
                                    ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                    ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 0x4000);
                                }
                            }
                            if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                                if (!(((S_812A524C_3 *)actor)->unk_B0 & 0x200) && (event_3 = (u8 *)&D_80082E80, ((u32) (((S_812A524C_14 *)event_3)->unk_24.at00.v - 0xB36) < 2U)) && (position_3 = (u8 *)&D_80083780, event_x_3 = ((S_812A524C_14 *)event_3)->unk_24.at00u.v, (((event_x_3 << 6) + 0x20) == ((S_812A524C_15 *)position_3)->unk_02)) && (((((S_812A524C_14 *)event_3)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_15 *)position_3)->unk_06)) {
                                    func_800353F4(&D_80070684);
                                    ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                    ((S_812A524C_3 *)actor)->unk_9B = 0;
                                    ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                    ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 0x200);
                                }
                                if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                                    if (!(((S_812A524C_3 *)actor)->unk_B0 & 0x8000) && (event_4 = (u8 *)&D_80082E80, ((u32) (((S_812A524C_16 *)event_4)->unk_24.at00.v - 0x1236) < 2U)) && (position_4 = (u8 *)&D_80083780, event_x_4 = ((S_812A524C_16 *)event_4)->unk_24.at00u.v, (((event_x_4 << 6) + 0x20) == ((S_812A524C_17 *)position_4)->unk_02)) && (((((S_812A524C_16 *)event_4)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_17 *)position_4)->unk_06)) {
                                        func_800353F4(&D_800FBAD7);
                                        ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                        ((S_812A524C_3 *)actor)->unk_9B = 0;
                                        ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                        ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 0x8000);
                                    }
                                    if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                                        if (!(((S_812A524C_3 *)actor)->unk_B0 & 2)) {
                                            event_5 = (u8 *)&D_80082E80;
                                            if ((u32) (((S_812A524C_18 *)event_5)->unk_24.at00.v - 0x1D07) < 2U) {
                                                position_5 = (u8 *)&D_80083780;
                                                event_x_5 = ((S_812A524C_18 *)event_5)->unk_24.at00u.v;
                                                if (((event_x_5 << 6) + 0x20) == ((S_812A524C_19 *)position_5)->unk_02) {
                                                    if (((((S_812A524C_18 *)event_5)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_19 *)position_5)->unk_06) {
                                                        func_800353F4(&D_8006F47A);
                                                        ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                        ((S_812A524C_3 *)actor)->unk_9B = 0;
                                                        ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                                        ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 2);
                                                    }
                                                }
                                            }
                                            if ((((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A != 0x19) && (((S_812A524C_20 *)flag_base)->unk_10 & 0x20)) {
                                                func_800353F4(&D_8006F47A);
                                                ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                ((S_812A524C_3 *)actor)->unk_9B = 0;
                                                ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                                ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 2);
                                            }
                                        }
                                        if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                                            if (!(((S_812A524C_3 *)actor)->unk_B0 & 4)) {
                                                event_6 = (u8 *)&D_80082E80;
                                                if ((u32) (((S_812A524C_21 *)event_6)->unk_24.at00.v - 0x291E) < 3U) {
                                                    position_6 = (u8 *)&D_80083780;
                                                    event_x_6 = ((S_812A524C_21 *)event_6)->unk_24.at00u.v;
                                                    if (((event_x_6 << 6) + 0x20) == ((S_812A524C_22 *)position_6)->unk_02) {
                                                        if (((((S_812A524C_21 *)event_6)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_22 *)position_6)->unk_06) {
                                                            func_800353F4(&D_8006F50D);
                                                            ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                            ((S_812A524C_3 *)actor)->unk_9B = 0;
                                                            ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                                            ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 4);
                                                        }
                                                    }
                                                }
                                                if ((((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A != 0x19) && (((S_812A524C_20 *)flag_base)->unk_08 & 0x10)) {
                                                    func_800353F4(&D_8006F50D);
                                                    ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                    ((S_812A524C_3 *)actor)->unk_9B = 0;
                                                    ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                                    ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 4);
                                                }
                                            }
                                            if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                                                if (!(((S_812A524C_3 *)actor)->unk_B0 & 0x10) && (((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A != 0x23)) {
                                                    scan_index_10 = 0;
                                                    scan_kind = 0xF;
                                                    scan_group = 2;
                                                    scan_10 = (u8 *)0x80010000;
loop_102:
                                                    if ((scan_10[0x249] != scan_kind) || (scan_10[0x248] != scan_group)) {
                                                        scan_index_10 += 1;
                                                        scan_10 += 4;
                                                        if (scan_index_10 >= 0x14) {
                                                            goto block_105;
                                                        }
                                                        goto loop_102;
                                                    }
                                                    goto action_10;
                                                }
block_105:
                                                if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                                                    if (!(((S_812A524C_3 *)actor)->unk_B0 & 0x80) && (((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A != 0x23)) {
                                                        scan_index_80 = 0;
                                                        scan_kind = 0x12;
                                                        scan_group = 0x15;
                                                        scan_80 = (u8 *)0x80010000;
loop_109:
                                                        if ((scan_80[0x249] != scan_kind) || (scan_80[0x248] != scan_group)) {
                                                            scan_index_80 += 1;
                                                            scan_80 += 4;
                                                            if (scan_index_80 >= 0x14) {
                                                                goto block_112;
                                                            }
                                                            goto loop_109;
                                                        }
                                                        goto action_80;
                                                    }
block_112:
                                                    if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                                                        if (!(((S_812A524C_3 *)actor)->unk_B0 & 0x100) && (((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A != 0x23)) {
                                                            scan_index_100 = 0;
                                                            scan_kind = 4;
                                                            scan_group = 1;
                                                            scan_100 = (u8 *)0x80010000;
loop_116:
                                                            if ((scan_100[0x249] != scan_kind) || (scan_type = scan_100[0x248], (scan_type != scan_group))) {
                                                                scan_index_100 += 1;
                                                                scan_100 += 4;
                                                                if (scan_index_100 >= 0x14) {
                                                                    goto block_119;
                                                                }
                                                                goto loop_116;
                                                            }
                                                            goto action_100;
                                                        }
block_119:
                                                        if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                                                            if (!(((S_812A524C_3 *)actor)->unk_B0 & 0x40) && (event_7 = (u8 *)&D_80082E80, ((u32) (((S_812A524C_23 *)event_7)->unk_24.at00.v - 0x161C) < 7U)) && (position_7 = (u8 *)&D_80083780, event_x_7 = ((S_812A524C_23 *)event_7)->unk_24.at00u.v, (((event_x_7 << 6) + 0x20) == ((S_812A524C_24 *)position_7)->unk_02)) && (((((S_812A524C_23 *)event_7)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_24 *)position_7)->unk_06)) {
                                                                func_800353F4(&D_8006FD01);
                                                                ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                                ((S_812A524C_3 *)actor)->unk_9B = 0;
                                                                ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                                                ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 0x40);
                                                            }
                                                            if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                                                                if (!(((S_812A524C_3 *)actor)->unk_B0 & 0x400) && (event_8 = (u8 *)&D_80082E80, ((u32) (((S_812A524C_25 *)event_8)->unk_24.at00.v - 0x2036) < 2U)) && (position_8 = (u8 *)&D_80083780, event_x_8 = ((S_812A524C_25 *)event_8)->unk_24.at00u.v, (((event_x_8 << 6) + 0x20) == ((S_812A524C_26 *)position_8)->unk_02)) && (((((S_812A524C_25 *)event_8)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_26 *)position_8)->unk_06)) {
                                                                    func_800353F4(&D_80070AF8);
                                                                    ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                                    ((S_812A524C_3 *)actor)->unk_9B = 0;
                                                                    ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                                                    ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 0x400);
                                                                }
                                                                if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                                                                    if (!(((S_812A524C_3 *)actor)->unk_B0 & 0x800) && ((D_80082EA4[0] == 0x31E) || (D_80082EA4[0] == 0x41E) || (D_80082EA4[0] == 0x51E) || (D_80082EA4[0] == 0x61E) || (D_80082EA4[0] == 0x71E) || (D_80082EA4[0] == 0x81E)) && (event_9 = (u8 *)&D_80082E80, position_9 = (u8 *)&D_80083780, (((((S_812A524C_27 *)event_9)->unk_24 << 6) + 0x20) == ((S_812A524C_28 *)position_9)->unk_02)) && (((((S_812A524C_27 *)event_9)->unk_25 << 6) + 0x20) == ((S_812A524C_28 *)position_9)->unk_06)) {
                                                                        func_800353F4(&D_80070C11);
                                                                        ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                                        ((S_812A524C_3 *)actor)->unk_9B = 0;
                                                                        ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                                                        ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 0x800);
                                                                    }
                                                                    if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                                                                        if (!(((S_812A524C_3 *)actor)->unk_B0 & 0x1000)) {
                                                                            if (((u32) (D_80082EA4[0] - 0x2C1E) < 3U) || (D_80082EA4[0] == 0x2D1E) || (D_80082EA4[0] == 0x2D1F) || (D_80082EA4[0] == 0x2D20)) {
                                                                                event_10 = (u8 *)&D_80082E80;
                                                                                position_10 = (u8 *)&D_80083780;
                                                                                if ((((((S_812A524C_29 *)event_10)->unk_24 << 6) + 0x20) == ((S_812A524C_30 *)position_10)->unk_02) && (((((S_812A524C_29 *)event_10)->unk_25 << 6) + 0x20) == ((S_812A524C_30 *)position_10)->unk_06)) {
                                                                                    func_800353F4(&D_80070E63);
                                                                                    ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                                                    ((S_812A524C_3 *)actor)->unk_9B = 0;
                                                                                    ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                                                                    ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 0x1000);
                                                                                }
                                                                            }
                                                                        }
                                                                        if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                                                                            if (!(((S_812A524C_3 *)actor)->unk_B0 & 0x2000) && (event_11 = (u8 *)&D_80082E80, ((u32) (((S_812A524C_31 *)event_11)->unk_24.at00.v - 0x121C) < 7U)) && (position_11 = (u8 *)&D_80083780, event_x_11 = ((S_812A524C_31 *)event_11)->unk_24.at00u.v, (((event_x_11 << 6) + 0x20) == ((S_812A524C_32 *)position_11)->unk_02)) && (((((S_812A524C_31 *)event_11)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_32 *)position_11)->unk_06)) {
                                                                                func_800353F4(&D_800FB3C8);
                                                                                ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                                                ((S_812A524C_3 *)actor)->unk_9B = 0;
                                                                                ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                                                                ((S_812A524C_3 *)actor)->unk_B0 = (s32) (((S_812A524C_3 *)actor)->unk_B0 | 0x2000);
                                                                            }
                                                                            if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
                                                                                if (!(((S_812A524C_3 *)actor)->unk_B0 & 0x10000)) {
                                                                                    if (((S_812A524C_5 *)(&D_800FBE54))->unk_00 == NULL) {
                                                                                        nearby_object = func_800F6DFC(entity);
                                                                                        ((S_812A524C_5 *)(&D_800FBE54))->unk_00 = nearby_object;
                                                                                        if (nearby_object != NULL) {
                                                                                            goto block_163;
                                                                                        }
                                                                                    } else {
block_163:
                                                                                        nearby_tile = ((S_812A524C_40 *)(((S_812A524C_5 *)(&D_800FBE54))->unk_00))->unk_0C;
                                                                                        nearby_event = &D_80082E80;
                                                                                        event_x = ((S_812A524C_33 *)nearby_event)->unk_24;
                                                                                        distance_x = event_x - nearby_tile->unk_24;
                                                                                        if (distance_x < 0) {
                                                                                            distance_x = 0 - distance_x;
                                                                                        }
                                                                                        if (distance_x < 4) {
                                                                                            event_y = ((S_812A524C_33 *)nearby_event)->unk_25;
                                                                                            distance_y = event_y - nearby_tile->unk_25;
                                                                                            if (distance_y < 0) {
                                                                                                distance_y = 0 - distance_y;
                                                                                            }
                                                                                            if (distance_y < 4) {
                                                                                                scaled_x = event_x << 6;
                                                                                                position_12 = (u8 *)&D_80083780;
                                                                                                if (((scaled_x + 0x20) == ((S_812A524C_35 *)position_12)->unk_02) && (((event_y << 6) + 0x20) == ((S_812A524C_35 *)position_12)->unk_06)) {
                                                                                                    func_800353F4(&D_800FBD96);
                                                                                                    ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                                                                    ((S_812A524C_3 *)actor)->unk_9B = 0;
                                                                                                    ((S_812A524C_3 *)actor)->unk_B8 = 1U;
                                                                                                    ((S_812A524C_3 *)actor)->unk_B0 |= 0x10000;
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                goto block_172;
                                                                            }
                                                                            goto active_return;
                                                                        }
                                                                        goto active_return;
                                                                    }
                                                                    goto active_return;
                                                                }
                                                                goto active_return;
                                                            }
                                                            goto active_return;
                                                        }
                                                        goto active_return;
                                                    }
                                                    goto active_return;
                                                }
                                                goto active_return;
                                            }
                                            goto active_return;
                                        }
                                        goto active_return;
                                    }
                                    goto active_return;
                                }
                                goto active_return;
                            }
                            goto active_return;
                        }
                        goto active_return;
                    }
                    goto active_return;
                }
            }
            goto block_172;
        }
        goto active_return;
    }
block_172:
    if (((S_812A524C_3 *)actor)->unk_B8 == 0) {
        goto inactive;
    }
active_return:
    ((S_812A524C_36 *)(&D_800E296C))->unk_00.n |= 0x200000;
    func_80171968();
inactive:
    clear_flags = ((S_812A524C_36 *)(&D_800E296C))->unk_00.v;
    clear_flags &= 0xFFDFFFFF;
    ((S_812A524C_36 *)(&D_800E296C))->unk_00.v = clear_flags;
    ASM_KEEP(clear_flags);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    if (D_80083462[0] & 0x2000) {
        update_special = ((S_812A524C_3 *)actor)->unk_8C;
        if (update_special == &D_80171FA4) {
            update_special(actor, motion, sprite, entity);
            func_80171F74();
            return;
        }
        ((S_812A524C_4 *)entity)->unk_71 &= 0x7F;
        func_80171F74(actor);
        return;
    }
    previous_state = (s8) ((S_812A524C_4 *)entity)->unk_6D;
    if (func_800A9E70(actor, motion, sprite, entity) == 0) {
        update_actor = ((S_812A524C_3 *)actor)->unk_8C;
        if (update_actor != NULL) {
            update_actor(actor, motion, sprite, entity);
        }
        D_80175CC8[((S_812A524C_3 *)actor)->unk_9A](actor, motion, sprite, entity);
        if ((s16) previous_state != (s8) ((S_812A524C_4 *)entity)->unk_6D) {
            func_800AA36C(actor, motion, sprite, entity);
        }
        motion_x = ((S_812A524C_37 *)motion)->unk_00.at00.v;
        velocity_x = ((S_812A524C_37 *)motion)->unk_0C;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        motion_y = ((S_812A524C_37 *)motion)->unk_04.at00.v;
        velocity_y = ((S_812A524C_37 *)motion)->unk_10;
        ((S_812A524C_37 *)motion)->unk_00.at00.v = motion_x + velocity_x;
        ((S_812A524C_37 *)motion)->unk_04.at00.v = motion_y + velocity_y;
        if (!(((S_812A524C_4 *)entity)->unk_1C & 0x40000) && !(((S_812A524C_3 *)actor)->unk_98 & 8)) {
            ((S_812A524C_37 *)motion)->unk_14 = (s32) (((S_812A524C_37 *)motion)->unk_14 + (((S_812A524C_3 *)actor)->unk_9D.s * 0x14000));
            ((S_812A524C_3 *)actor)->unk_9D.u += 1;
            func_80171AD8(velocity_x, velocity_y);
            return;
        }
        ((S_812A524C_3 *)actor)->unk_9D.s = 0;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_812A524C_3 *)actor)->unk_90.at00.v = (s32) (((S_812A524C_3 *)actor)->unk_90.at00.v + ((S_812A524C_37 *)motion)->unk_14);
        facing = ((s32) (D_80083228[0] + ((S_812A524C_4 *)entity)->unk_2A + 0x100) >> 9) & 7;
        sprite_facing = facing;
        if (((S_812A524C_3 *)actor)->unk_94 != sprite_facing) {
            func_80047738(sprite, ((S_812A524C_38 *)sprite)->unk_2C.p[sprite_facing], ((S_812A524C_38 *)sprite)->unk_04.s8);
            ((S_812A524C_3 *)actor)->unk_94 = facing;
        }
        if (D_8006CCF8[sprite_facing] != 0) {
            tail_value = ((S_812A524C_38 *)sprite)->unk_14.n;
            tail_value |= 1;
            ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            func_80171B6C();
            return;
        }
        first_flags = ((S_812A524C_38 *)sprite)->unk_14.v;
        ((S_812A524C_38 *)sprite)->unk_14.v = first_flags & 0xFFFE;
        sprite_flags = ((S_812A524C_38 *)sprite)->unk_14.v;
        fixed_flags = sprite_flags & 0x8000;
        if (fixed_flags == 0) {
            func_800A020C(((S_812A524C_4 *)entity)->unk_1C, sprite + 0xC);
            if (!(((S_812A524C_4 *)entity)->unk_1C & 0x20)) {
                if (!(((S_812A524C_38 *)sprite)->unk_14.n & 0x40)) {
                    func_800478B8(sprite);
                    tail_value = 0xF7FF0000;
                    ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                    func_80171BEC();
                    return;
                }
                goto block_201;
            }
            ((S_812A524C_38 *)sprite)->unk_14.n = (u16) (((S_812A524C_38 *)sprite)->unk_14.n | 0x7000);
            ((S_812A524C_4 *)entity)->unk_1C = (s32) (((S_812A524C_4 *)entity)->unk_1C & 0xFFFBFFFF);
block_201:
            moving_flags = ((S_812A524C_4 *)entity)->unk_1C & 0xF7FFFFFF;
            ((S_812A524C_4 *)entity)->unk_1C = moving_flags;
            if (moving_flags & 0x40000) {
                if (!(((S_812A524C_38 *)sprite)->unk_14.n & 0x40) && (((S_812A524C_38 *)sprite)->unk_2C.i == &D_80175C30)) {
                    if (((S_812A524C_38 *)sprite)->unk_04.u16 == 0x100) {
                        ((S_812A524C_3 *)actor)->unk_9E = 0U;
                        ((S_812A524C_3 *)actor)->unk_A0.at00.v = 0;
                    }
                    if ((u32) ((u8) ((S_812A524C_38 *)sprite)->unk_04.s8 - 1) < 4U) {
                        bob_phase = ((S_812A524C_3 *)actor)->unk_9E;
                        ((S_812A524C_3 *)actor)->unk_9E = (u16) (bob_phase + 1);
                        tail_value = func_800644B8((s16) bob_phase * 0xAA);
                        tail_acc = ((S_812A524C_3 *)actor)->unk_A0.at00.v;
                        tail_value <<= 5;
                        ASM_KEEP(tail_acc);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                        ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                        func_80171CD4();
                        return;
                    }
                    bob_phase_wide = ((S_812A524C_3 *)actor)->unk_9E;
                    ((S_812A524C_3 *)actor)->unk_9E = (u16) (bob_phase_wide + 1);
                    ((S_812A524C_3 *)actor)->unk_A0.at00.v = (s32) (((S_812A524C_3 *)actor)->unk_A0.at00.v + (func_800644B8((s16) bob_phase_wide * 0xAA) << 6));
                    goto block_210;
                }
block_210:
                if (!(((S_812A524C_3 *)actor)->unk_98 & 8)) {
                    height = ((S_812A524C_3 *)actor)->unk_90.at02.v;
                    tail_acc = ((S_812A524C_3 *)actor)->unk_90.at02u.v;
                    if (height >= -0x1F) {
                        tail_value = height < -0x28;
                        ASM_KEEP(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                        tail_value = tail_acc - 8;
                        ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                        func_80171ECC(height);
                        return;
                    }
                    goto block_233;
                }
                goto block_235;
            }
            goto block_217;
        }
        fixed_flags = sprite_flags & 0x800;
        if (fixed_flags != 0) {
            fixed_flags = sprite_flags & 0x8FFF;
            goto flags_ready;
        }
        fixed_flags = sprite_flags | 0x7000;
flags_ready:
        ((S_812A524C_38 *)sprite)->unk_14.n = (u16) fixed_flags;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        fixed_entity_flags = ((S_812A524C_4 *)entity)->unk_1C & 0xF7FFFFFF;
        ((S_812A524C_4 *)entity)->unk_1C = fixed_entity_flags;
        if (!(fixed_entity_flags & 0x40000)) {
block_217:
            bob_offset = ((S_812A524C_3 *)actor)->unk_A0.at00.v;
            ((S_812A524C_3 *)actor)->unk_9E = 0U;
            ((S_812A524C_3 *)actor)->unk_A0.at00.v = 0;
            ((S_812A524C_3 *)actor)->unk_90.at00.v = (s32) (((S_812A524C_3 *)actor)->unk_90.at00.v - bob_offset);
            if (!(((S_812A524C_3 *)actor)->unk_98 & 8)) {
                ground_delta = func_800BCB04(((S_812A524C_37 *)motion)->unk_00.at02.v, ((S_812A524C_37 *)motion)->unk_04.at02.v, (s16) (((S_812A524C_4 *)entity)->unk_88 - 0x20)) - ((S_812A524C_4 *)entity)->unk_88;
                if ((s16) ground_delta < ((S_812A524C_3 *)actor)->unk_90.at02.v) {
                    ((S_812A524C_3 *)actor)->unk_90.at02.v = (s16) ground_delta;
                    ((S_812A524C_3 *)actor)->unk_9D.s = 0;
                    ((S_812A524C_37 *)motion)->unk_14 = 0;
                    ((S_812A524C_4 *)entity)->unk_1C |= 0x08000000;
                    func_80171ED0(ground_delta);
                    return;
                }
            }
            goto block_235;
        }
        if (!(((S_812A524C_38 *)sprite)->unk_14.n & 0x40) && (((S_812A524C_38 *)sprite)->unk_2C.i == &D_80175C30)) {
            if (((S_812A524C_38 *)sprite)->unk_04.u16 == 0x100) {
                ((S_812A524C_3 *)actor)->unk_9E = 0U;
                ((S_812A524C_3 *)actor)->unk_A0.at00.v = 0;
            }
            if ((u32) ((u8) ((S_812A524C_38 *)sprite)->unk_04.s8 - 1) < 4U) {
                fixed_bob_phase = ((S_812A524C_3 *)actor)->unk_9E;
                ((S_812A524C_3 *)actor)->unk_9E = (u16) (fixed_bob_phase + 1);
                tail_value = func_800644B8((s16) fixed_bob_phase * 0xAA);
                tail_acc = ((S_812A524C_3 *)actor)->unk_A0.at00.v;
                tail_value <<= 5;
                ASM_KEEP(tail_acc);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                func_80171E8C();
                return;
            }
            fixed_bob_phase_wide = ((S_812A524C_3 *)actor)->unk_9E;
            ((S_812A524C_3 *)actor)->unk_9E = (u16) (fixed_bob_phase_wide + 1);
            ((S_812A524C_3 *)actor)->unk_A0.at00.v = (s32) (((S_812A524C_3 *)actor)->unk_A0.at00.v + (func_800644B8((s16) fixed_bob_phase_wide * 0xAA) << 6));
            goto block_229;
        }
block_229:
        if (!(((S_812A524C_3 *)actor)->unk_98 & 8)) {
            height = ((S_812A524C_3 *)actor)->unk_90.at02.v;
            tail_acc = ((S_812A524C_3 *)actor)->unk_90.at02u.v;
            if (height >= -0x1F) {
                tail_value = tail_acc - 8;
                ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                func_80171ECC(height);
                return;
            }
block_233:
            if (height < -0x28) {
                final_tail_value = tail_acc + 8;
                ((S_812A524C_3 *)actor)->unk_90.at02.v = (s16) final_tail_value;
            }
            goto block_235;
        }
block_235:
        entity_flags = ((S_812A524C_4 *)entity)->unk_1C;
        if (entity_flags & 0x40000000) {
            ((S_812A524C_4 *)entity)->unk_1C = (s32) (entity_flags & 0xBFFFFFFF);
            ground_height = func_800BCB04((((S_812A524C_38 *)sprite)->unk_24 << 6) | 0x20, (((S_812A524C_38 *)sprite)->unk_25 << 6) | 0x20, (s16) (((S_812A524C_4 *)entity)->unk_88 - 0x20));
            if (ground_height < 0x200) {
                ((S_812A524C_3 *)actor)->unk_90.at02.v = (s16) ((u16) ((S_812A524C_3 *)actor)->unk_90.at02.v + (((S_812A524C_4 *)entity)->unk_88 - ground_height));
                ((S_812A524C_4 *)entity)->unk_88 = (u16) ground_height;
            }
        }
        ((S_812A524C_37 *)motion)->unk_0A = (s16) ((((S_812A524C_4 *)entity)->unk_88 + (u16) ((S_812A524C_3 *)actor)->unk_90.at02.v) - ((S_812A524C_3 *)actor)->unk_A0.at02.v);
        ((S_812A524C_38 *)sprite)->unk_14.n = (u16) (((S_812A524C_38 *)sprite)->unk_14.n | 0x40);
    }
    return;
}

/* Set alternate menu entry coordinates. */
#include "common.h"
#include "m2c_compat.h"
typedef struct MenuDisplay {
    void *unk_00;
    u8 pad04[0x58];
    struct { void *as_pv; } unk_A8;
} MenuDisplay;


typedef struct S_800AF36C_2 {
    u8 pad_00[0x10];
    void * unk_10;
    void * unk_14;
} S_800AF36C_2;

typedef struct S_800AF36C_3 {
    u8 pad_00[0x10];
    void * unk_10;
    void * unk_14;
} S_800AF36C_3;

typedef struct S_800AF36C_4 {
    u8 pad_00[0x34];
    s32 unk_18;
} S_800AF36C_4;   

typedef struct S_800AF36C_5 {
    u8 pad_00[0x10];
    void * unk_10;
} S_800AF36C_5;   

typedef struct S_800AF36C_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AF36C_6;

typedef struct S_800AF36C_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AF36C_7;

typedef struct S_800AF36C_8 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AF36C_8;

typedef struct S_800AF36C_9 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AF36C_9;

typedef struct S_800AF36C_10 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AF36C_10;   

typedef struct S_800AF36C_11 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800AF36C_11;

typedef struct S_800AF36C_12 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_800AF36C_12;

typedef struct S_800AF36C_13 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800AF36C_13;

typedef struct S_800AF36C_14 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AF36C_14;

typedef struct S_800AF36C_15 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800AF36C_15;   



/* Positions a menu entry from the last decimal digit of its index and places its companion beside it. */
void set_alternate_menu_entry_coordinates(MenuDisplay *object) {
    s32 digit;
    s32 row;
    S_800AF36C_2 *x_parts;
    S_800AF36C_3 *y_parts;

    digit = ((S_800AF36C_4 *)(((MenuDisplay *)object)->unk_00))->unk_18 % 10;
    row = digit / 5;
    ((S_800AF36C_15 *)(((S_800AF36C_10 *)(((S_800AF36C_5 *)(((MenuDisplay *)object)->unk_A8.as_pv))->unk_10))->unk_04))->unk_08 =
        (s16) ((row << 7) - 0x38);
    ((S_800AF36C_15 *)(((S_800AF36C_10 *)(((S_800AF36C_5 *)(((MenuDisplay *)object)->unk_A8.as_pv))->unk_10))->unk_04))->unk_0A =
        (s16) (((digit - (row * 5)) << 4) + 8);
    x_parts = object->unk_A8.as_pv;
    ((S_800AF36C_11 *)(((S_800AF36C_6 *)(x_parts->unk_14))->unk_04))->unk_08 =
        (s16) (((S_800AF36C_12 *)(((S_800AF36C_7 *)(x_parts->unk_10))->unk_04))->unk_08 + 0x38);
    y_parts = object->unk_A8.as_pv;
    ((S_800AF36C_13 *)(((S_800AF36C_8 *)(y_parts->unk_14))->unk_04))->unk_0A =
        (s16) (((S_800AF36C_14 *)(((S_800AF36C_9 *)(y_parts->unk_10))->unk_04))->unk_0A - 9);
}

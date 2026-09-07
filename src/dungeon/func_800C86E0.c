#include "common.h"

typedef struct {
    u8 pad0;
    u8 active;
    u8 pad2[2];
} ActiveEntry;

typedef struct {
    u8 x;
    u8 y;
    u8 pad2[2];
    u16 value;
    u8 pad6[6];
} FirstEntry;

typedef struct {
    u8 pad0[6];
    u8 x;
    u8 y;
    u8 pad8[10];
    u16 value;
    u8 pad14[4];
} SecondEntry;

extern ActiveEntry D_800E3548[64];
extern ActiveEntry D_800E3648[32];
extern FirstEntry D_800E36C8[64];
extern SecondEntry D_800E39C8[32];

void func_800CDE40(s16 x, s16 y, s32 amount)
{
    s32 i;
    s32 first_x;
    s32 first_y;
    s32 second_x;
    s32 second_y;
    ActiveEntry *first_active;
    ActiveEntry *second_active;
    FirstEntry *first;
    SecondEntry *second;

    i = 0;
    first_x = x;
    first_y = y;
    first = D_800E36C8;
    first_active = D_800E3548;
    do {
        if (first_active->active != 0 &&
            first->x == first_x &&
            first->y == first_y) {
            first->value += amount;
        }
        first++;
        i++;
        first_active++;
    } while (i < 64);

    i = 0;
    second_x = x;
    second_y = y;
    second = D_800E39C8;
    second_active = D_800E3648;
    do {
        if (second_active->active != 0 &&
            second->x == second_x &&
            second->y == second_y) {
            second->value += amount;
        }
        second++;
        i++;
        second_active++;
    } while (i < 32);
}

/* MECHANISM: Frameless leaf with two explicit pointer-induction scans.
   Per-scan signed coordinate locals place each sign-extension before its bases.
   Distinct coordinate and active-pointer lifetimes produce retail's second-scan recoloring. */

#include "common.h"

typedef struct SpriteFields {
    u32 pad0;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
} SpriteFields;

typedef struct DisplayPair {
    u32 pad0;
    SpriteFields *src;
} DisplayPair;

typedef struct TownSlots {
    void **slots[97];
    DisplayPair *display;
} TownSlots;

typedef struct TownObject {
    u8 pad0[0xF];
    u8 digit;
    u8 row;
    u8 index;
    u8 pad12[0x46];
    TownSlots *town;
} TownObject;

extern u8 func_80123200(u32);
extern void func_80123A60(TownObject *);

extern void *D_80126988[4];
extern void *D_80126998[4];
extern void *D_801269A8[10];
extern void *D_801269D0[10];
extern u16 D_80126B20[2];
extern u16 D_80126B24[8];
extern u8 D_80127B64[16];
extern u8 D_80127B70[16];
extern u8 D_80127E4C[16];
extern u8 D_80127F48[16];
extern u8 D_80128038[16];
extern u8 D_801289EC[16];

/* Updates the numbered menu entries and selection sprite. */
void func_80124188(TownObject *menu)
{
    register s32 sprite_slot ASM_REG("$16");   /* MATCH pin: retail immediate-load split depends on it */
    TownObject *obj = menu;
    s16 entry_number;
    s32 entry_index;
    s32 entry_id;
    void **normal_digits;
    void **selected_digits;
    register s32 digit_base ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 table_page;
    s32 blank_count;
    SpriteFields *display_sprite;

    func_80123A60(menu);
    *obj->town->slots[28] = D_80127E4C;
    *obj->town->slots[29] = D_80127F48;
    *obj->town->slots[30] = D_80126988[obj->digit];
    *obj->town->slots[31] = D_80126998[obj->digit];
    *obj->town->slots[32] = D_801289EC;

    if (obj->digit == 3) {
        sprite_slot = 33;
        entry_index = 0;
        digit_base = 0x80120000;
        ASM_KEEP(digit_base);   /* MATCH pin: load-bearing for the whole function shape */
        selected_digits = (void **)(digit_base + 0x69A8);
        digit_base = *(volatile u8 *)&obj->digit;
        table_page = 0x80120000;
        ASM_KEEP(table_page);   /* MATCH pin: retail immediate-load split depends on it */
        normal_digits = (void **)(table_page + 0x69D0);
        digit_base <<= 4;
        entry_id = digit_base;
        entry_number = digit_base | 1;
        ASM_KEEP(digit_base);   /* MATCH pin: load-bearing for the whole function shape */
        do {
            if (func_80123200((u8)entry_id) != 0) {
                *obj->town->slots[sprite_slot++] = D_80127B64;
                if (entry_index == obj->row) {
                    *obj->town->slots[sprite_slot] = selected_digits[entry_number / 10];
                    sprite_slot++;
                    *obj->town->slots[sprite_slot++] = selected_digits[entry_number % 10];
                } else {
                    *obj->town->slots[sprite_slot] = normal_digits[entry_number / 10];
                    sprite_slot++;
                    *obj->town->slots[sprite_slot++] = normal_digits[entry_number % 10];
                }
            } else {
                *obj->town->slots[sprite_slot++] = D_80127B70;
                *obj->town->slots[sprite_slot++] = 0;
                *obj->town->slots[sprite_slot++] = 0;
            }

            blank_count = 0;
            do {
                *obj->town->slots[sprite_slot++] = 0;
                blank_count++;
            } while (blank_count < 21);
            entry_index++;
            entry_id++;
            entry_number++;
        } while (entry_index < 2);

        obj->town->display->src->f8 = D_80126B20[obj->row];
        obj->town->display->src->fA = D_80126B24[0];
        if (obj->row != 0) {
            *obj->town->slots[30] = D_80128038;
        }
    } else {
        sprite_slot = 33;
        entry_index = 0;
        digit_base = 0x80120000;
        ASM_KEEP(digit_base);   /* MATCH pin: load-bearing for the whole function shape */
        selected_digits = (void **)(digit_base + 0x69A8);
        digit_base = *(volatile u8 *)&obj->digit;
        table_page = 0x80120000;
        ASM_KEEP(table_page);   /* MATCH pin: retail immediate-load split depends on it */
        normal_digits = (void **)(table_page + 0x69D0);
        digit_base <<= 4;
        entry_id = digit_base;
        entry_number = digit_base | 1;
        ASM_KEEP(digit_base);   /* MATCH pin: load-bearing for the whole function shape */
        do {
            if (func_80123200((u8)entry_id) != 0) {
                *obj->town->slots[sprite_slot++] = D_80127B64;
                if (entry_index == (obj->row << 3) + obj->index) {
                    *obj->town->slots[sprite_slot] = selected_digits[entry_number / 10];
                    sprite_slot++;
                    *obj->town->slots[sprite_slot++] = selected_digits[entry_number % 10];
                } else {
                    *obj->town->slots[sprite_slot] = normal_digits[entry_number / 10];
                    sprite_slot++;
                    *obj->town->slots[sprite_slot++] = normal_digits[entry_number % 10];
                }
            } else {
                *obj->town->slots[sprite_slot++] = D_80127B70;
                *obj->town->slots[sprite_slot++] = 0;
                *obj->town->slots[sprite_slot++] = 0;
            }

            entry_index++;
            entry_id++;
            entry_number++;
        } while (entry_index < 16);

        obj->town->display->src->f8 = D_80126B20[obj->row];
        obj->town->display->src->fA = D_80126B24[obj->index];
    }

    display_sprite = obj->town->display->src;
    display_sprite->f6 = 0x1000;
    display_sprite->f4 = 0x1000;
}

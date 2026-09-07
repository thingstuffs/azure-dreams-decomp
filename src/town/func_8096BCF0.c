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
extern void func_80123A60(void);

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

void func_80124188(TownObject *arg0)
{
    register s32 slot ASM_REG("$16");   /* MATCH pin: retail immediate-load split depends on it */
    TownObject *obj = arg0;
    s16 value;
    s32 iteration;
    s32 input;
    void **lo_digits;
    void **hi_digits;
    register s32 initial ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 page;
    s32 clear;
    SpriteFields *source;

    func_80123A60();
    *obj->town->slots[28] = D_80127E4C;
    *obj->town->slots[29] = D_80127F48;
    *obj->town->slots[30] = D_80126988[obj->digit];
    *obj->town->slots[31] = D_80126998[obj->digit];
    *obj->town->slots[32] = D_801289EC;

    if (obj->digit == 3) {
        slot = 33;
        iteration = 0;
        initial = 0x80120000;
        ASM_KEEP(initial);   /* MATCH pin: load-bearing for the whole function shape */
        hi_digits = (void **)(initial + 0x69A8);
        initial = *(volatile u8 *)&obj->digit;
        page = 0x80120000;
        ASM_KEEP(page);   /* MATCH pin: retail immediate-load split depends on it */
        lo_digits = (void **)(page + 0x69D0);
        initial <<= 4;
        input = initial;
        value = initial | 1;
        ASM_KEEP(initial);   /* MATCH pin: load-bearing for the whole function shape */
        do {
            if (func_80123200((u8)input) != 0) {
                *obj->town->slots[slot++] = D_80127B64;
                if (iteration == obj->row) {
                    *obj->town->slots[slot] = hi_digits[value / 10];
                    slot++;
                    *obj->town->slots[slot++] = hi_digits[value % 10];
                } else {
                    *obj->town->slots[slot] = lo_digits[value / 10];
                    slot++;
                    *obj->town->slots[slot++] = lo_digits[value % 10];
                }
            } else {
                *obj->town->slots[slot++] = D_80127B70;
                *obj->town->slots[slot++] = 0;
                *obj->town->slots[slot++] = 0;
            }

            clear = 0;
            do {
                *obj->town->slots[slot++] = 0;
                clear++;
            } while (clear < 21);
            iteration++;
            input++;
            value++;
        } while (iteration < 2);

        obj->town->display->src->f8 = D_80126B20[obj->row];
        obj->town->display->src->fA = D_80126B24[0];
        if (obj->row != 0) {
            *obj->town->slots[30] = D_80128038;
        }
    } else {
        slot = 33;
        iteration = 0;
        initial = 0x80120000;
        ASM_KEEP(initial);   /* MATCH pin: load-bearing for the whole function shape */
        hi_digits = (void **)(initial + 0x69A8);
        initial = *(volatile u8 *)&obj->digit;
        page = 0x80120000;
        ASM_KEEP(page);   /* MATCH pin: retail immediate-load split depends on it */
        lo_digits = (void **)(page + 0x69D0);
        initial <<= 4;
        input = initial;
        value = initial | 1;
        ASM_KEEP(initial);   /* MATCH pin: load-bearing for the whole function shape */
        do {
            if (func_80123200((u8)input) != 0) {
                *obj->town->slots[slot++] = D_80127B64;
                if (iteration == (obj->row << 3) + obj->index) {
                    *obj->town->slots[slot] = hi_digits[value / 10];
                    slot++;
                    *obj->town->slots[slot++] = hi_digits[value % 10];
                } else {
                    *obj->town->slots[slot] = lo_digits[value / 10];
                    slot++;
                    *obj->town->slots[slot++] = lo_digits[value % 10];
                }
            } else {
                *obj->town->slots[slot++] = D_80127B70;
                *obj->town->slots[slot++] = 0;
                *obj->town->slots[slot++] = 0;
            }

            iteration++;
            input++;
            value++;
        } while (iteration < 16);

        obj->town->display->src->f8 = D_80126B20[obj->row];
        obj->town->display->src->fA = D_80126B24[obj->index];
    }

    source = obj->town->display->src;
    source->f6 = 0x1000;
    source->f4 = 0x1000;
}

#include "common.h"

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} Point;

typedef struct {
    void *object;
    Point points[5];
    u8 pad2C[8];
    s32 value34;
    s16 field38;
    s16 field3A;
    s16 field3C;
    s16 field3E;
    s16 field40;
    s16 field42;
    s16 delta44;
    s16 pad46;
    u16 timer48;
    s16 state4A;
} Entity;

extern void func_80024E54(void) __attribute__((noreturn));
extern void func_80024EE0(void) __attribute__((noreturn));
extern void func_80024F20() __attribute__((noreturn));
extern void func_8004491C(void *, void *);
extern s16 func_80066460(s32, s32, s32, s32);
extern s16 func_8006649C(s32, s32);
extern s32 rand();
extern u8 D_800249BC[];
extern u32 D_800814A0;

void func_80024C40(Entity *entity)
{
    s32 i;
    s16 state;
    s32 coord;
    s16 result;

    *(u16 *)((u8 *)entity->object + 0x52) |= 0x8000;
    state = entity->state4A;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        func_80024F20();
    }
    if (state == 2) {
        goto state_two;
    }
    func_80024F20();

state_zero:
    entity->timer48--;
    if ((s16)entity->timer48 > 0) {
        return;
    }
    {
        void *call_arg;
        u8 *data_page;
        call_arg = (u8 *)entity - 0x20;
        ASM_KEEP(call_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        data_page = (u8 *)0x80020000;
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        func_8004491C(call_arg, data_page + 0x49BC);
    }
    entity->value34 = 0x00C0C0C0;
    entity->field40 = func_80066460(0, 1, 0x2C0, 0x100);
    result = func_8006649C(0xA0, 0x1F7);
    i = 1;
    {
        register u8 *cursor ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        cursor = (u8 *)entity + 8;
        entity->field42 = result;
        entity->field3E = 0x1F;
        entity->field3C = 0x1F;
        entity->field38 = 0x80;
        entity->timer48 = 0;
        entity->field3A = 0;
        entity->delta44 = -0x1C;
        do {
            *(u16 *)(cursor + 4) = entity->points[0].x;
            *(u16 *)(cursor + 6) = entity->points[0].y;
            *(u16 *)(cursor + 8) = entity->points[0].z + entity->delta44 * i;
            cursor += 8;
            i++;
        } while (i < 5);
    }
    state = (u16)entity->state4A + 1;
    ASM_TAILSLOT_PIN_TIED(state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_80024EE0();

state_one:
    i = 1;
    if ((s16)entity->timer48 < 6) {
        do {
            coord = entity->points[0].x + rand() % 95 - 0x30;
            entity->points[i].x = coord;
            coord = entity->points[0].y + rand(coord) % 95 - 0x30;
            entity->points[i].y = coord;
            i++;
        } while (i < 5);
        i = 1;
        ASM_TAILSLOT_PIN_TIED(i);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80024E54();
    }
    ASM_KEEP(i);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    i++;
    while (i < 5) {
        i++;
    }
    i = 1;
    do {
        entity->points[i].z = entity->points[0].z + entity->delta44 * i;
        i++;
    } while (i < 5);
    {
        s32 amount;
        register s32 delta ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 masked;
        amount = entity->timer48;
        delta = (u16)entity->delta44;
        amount++;
        entity->timer48 = amount;
        amount <<= 1;
        masked = entity->timer48;
        delta -= amount;
        entity->delta44 = delta;
        delta = entity->timer48;
        entity->field38 = ((masked & 3) << 5) + 0x80;
        entity->field3A = ((s16)delta >> 2) << 5;
        if ((s16)entity->timer48 >= 8) {
            entity->value34 = 0;
            entity->state4A++;
            func_80024F20(amount);
        }
        delta = 0xFFEFEFF0;
        entity->value34 += delta;
        func_80024F20(amount);
    }

state_two:
    {
        register u32 *page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        page = (u32 *)0x80080000;
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        *(u16 *)((u8 *)entity - 2) |= 0x8000;
        page[0x528] |= 0x8000;
    }
}

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

extern void func_8004491C(void *, void *);
extern s16 func_80066460(s32, s32, s32, s32);
extern s16 func_8006649C(s32, s32);
extern s32 rand();
extern u8 D_800249BC[];
extern u32 D_800814A0;

/* Initializes, animates, and retires a jittering five-point effect. */
void func_80024C40(Entity *entity)
{
    s32 point_index;
    s16 state;
    s32 jitter_coord;
    s16 random_value;

    *(u16 *)((u8 *)entity->object + 0x52) |= 0x8000;
    state = entity->state4A;
    if (state == 1) {
        goto animate;
    }
    if (state < 2) {
        if (state == 0) {
            goto initialize;
        }
        goto end;
    }
    if (state == 2) {
        goto finish;
    }
    goto end;

initialize:
    entity->timer48--;
    if ((s16)entity->timer48 > 0) {
        return;
    }
    {
        void *entity_base;
        u8 *data_page;
        entity_base = (u8 *)entity - 0x20;
        ASM_KEEP(entity_base);
        data_page = (u8 *)0x80020000;
        ASM_KEEP(data_page);
        func_8004491C(entity_base, data_page + 0x49BC);
    }
    entity->value34 = 0x00C0C0C0;
    entity->field40 = func_80066460(0, 1, 0x2C0, 0x100);
    random_value = func_8006649C(0xA0, 0x1F7);
    point_index = 1;
    {
        register u8 *point_cursor ASM_REG("$3");
        point_cursor = (u8 *)entity + 8;
        entity->field42 = random_value;
        entity->field3E = 0x1F;
        entity->field3C = 0x1F;
        entity->field38 = 0x80;
        entity->timer48 = 0;
        entity->field3A = 0;
        entity->delta44 = -0x1C;
        do {
            *(u16 *)(point_cursor + 4) = entity->points[0].x;
            *(u16 *)(point_cursor + 6) = entity->points[0].y;
            *(u16 *)(point_cursor + 8) = entity->points[0].z + entity->delta44 * point_index;
            point_cursor += 8;
            point_index++;
        } while (point_index < 5);
    }
    state = (u16)entity->state4A + 1;
    goto store_state;

animate:
    point_index = 1;
    if ((s16)entity->timer48 < 6) {
        do {
            jitter_coord = entity->points[0].x + rand() % 95 - 0x30;
            entity->points[point_index].x = jitter_coord;
            jitter_coord = entity->points[0].y + rand(jitter_coord) % 95 - 0x30;
            entity->points[point_index].y = jitter_coord;
            point_index++;
        } while (point_index < 5);
        point_index = 1;
    } else {
        ASM_KEEP(point_index);
        point_index++;
        while (point_index < 5) {
            point_index++;
        }
        point_index = 1;
    }
    point_index = 1;
    do {
        entity->points[point_index].z = entity->points[0].z + entity->delta44 * point_index;
        point_index++;
    } while (point_index < 5);
    {
        s32 update_value;
        s32 timer_bits;
        jitter_coord = entity->timer48;
        update_value = (u16)entity->delta44;
        jitter_coord++;
        entity->timer48 = jitter_coord;
        jitter_coord <<= 1;
        timer_bits = entity->timer48;
        update_value -= jitter_coord;
        entity->delta44 = update_value;
        entity->field38 = ((timer_bits & 3) << 5) + 0x80;
        entity->field3A = ((s16)entity->timer48 >> 2) << 5;
        if ((s16)entity->timer48 >= 8) {
            entity->value34 = 0;
            state = (u16)entity->state4A + 1;
store_state:
            entity->state4A = state;
            goto end;
        }
        update_value = 0xFFEFEFF0;
        entity->value34 += update_value;
        goto end;
    }

finish:
    {
        register u32 *flags_page ASM_REG("$3");
        flags_page = (u32 *)0x80080000;
        ASM_KEEP(flags_page);
        *(u16 *)((u8 *)entity - 2) |= 0x8000;
        flags_page[0x528] |= 0x8000;
    }
end:
    return;
}

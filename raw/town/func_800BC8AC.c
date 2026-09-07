#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(s32);
extern s32 rand(void);
extern void func_8008F104(void *, void *, void *);

typedef struct Palette {
    u8 pad[0xA8];
    u8 red;
    u8 green;
    u8 blue;
} Palette;

extern u8 D_80045C34[];
extern u8 D_80046398[];
extern Palette D_80083160[];
extern u8 D_800B9CB8[];
extern u8 D_800B9D64[];
extern u8 D_800B9EDC[];
extern u8 D_800B9F74[];
extern void *D_800D1BCC[];
extern u8 D_800F8A1C[];
extern u8 D_800F8A28[];

void func_800BA00C(void *arg0, void *arg1)
{
    register void *input ASM_REG("$22") = arg1;
    void *callback;
    register Palette *palette ASM_REG("$21");
    register u8 *obj ASM_REG("$17");
    register u8 *entity ASM_REG("$16");
    register void *callback2 ASM_REG("$23");
    register void *texture2 ASM_REG("$21");
    register s32 color ASM_REG("$20");
    register s32 initial_angle ASM_REG("$5");
    register s32 quotient ASM_REG("$3");
    register s32 remtemp ASM_REG("$2");
    register s32 parent_value ASM_REG("$2");
    register u32 page ASM_REG("$2");
    register s32 temp_v0 ASM_REG("$2");
    register s32 temp_v1 ASM_REG("$3");
    register void *init_data ASM_REG("$5");
    register void *temp_ptr ASM_REG("$2");
    register void *call_obj ASM_REG("$4");
    s32 rand1;
    s32 rand2;
    s32 angle;
    s32 blue;
    register s32 quadrant ASM_REG("$23");
    s32 i;
    void **params;
    u8 *sprite;
    void *origin;

    FIELD(arg0, void *, -0x10) = D_800B9CB8;
    rand1 = rand();
    FIELD(arg0, s16, 0x66) = rand1 % 0x1000;
    rand2 = rand();
    initial_angle = FIELD(arg0, s16, 0x66);
    FIELD(arg0, s8, 0x97) = (rand2 % 9) + 12;
    quotient = initial_angle / 0x200;
    remtemp = quotient;
    if (quotient < 0) {
        remtemp = quotient + 3;
    }
    remtemp >>= 2;
    remtemp <<= 2;
    quadrant = quotient - remtemp;

    i = 0;
    page = 0x800C0000;
    ASM_KEEP(page);
    callback = (void *)(page - 0x629C);
    page = 0x80080000;
    ASM_KEEP(page);
    palette = (Palette *)(page + 0x3160);
    page = 0x800D0000;
    ASM_KEEP(page);
    params = (void **)(page + 0x1BCC);
    do {
        obj = func_8003FD64(0x136, (u8 *)arg0 - 0x20);
        if (obj != 0) {
            FIELD(obj, void *, 0x10) = callback;
            func_8004491C(obj, D_80046398);
            parent_value = FIELD(arg0, s32, 0x98);
            ASM_KEEP(parent_value);
            entity = obj + 0x20;
            ASM_KEEP(entity);
            FIELD(entity, void *, 0x9C) = arg0;
            FIELD(entity, s16, 0x66) = 0;
            FIELD(entity, s8, 0x97) = i;
            FIELD(entity, s32, 0x98) = parent_value;
            sprite = FIELD(obj, u8 *, 0xC);
            FIELD(sprite, s16, 0x1C) = 0x1000;
            FIELD(sprite, s16, 0x1E) = 0x1000;
            FIELD(sprite, s16, 0x20) = 0xAAA;
            FIELD(sprite, u8, 0xC) = palette->red;
            FIELD(sprite, u8, 0xD) = palette->green;
            blue = palette->blue;
            FIELD(sprite, s32, 8) = i + 0x1A;
            FIELD(sprite, u8, 0xE) = blue;
            obj = FIELD(obj, u8 *, 8);
            FIELD(obj, s32, 0) = FIELD(input, s32, 0);
            FIELD(obj, s32, 4) = FIELD(input, s32, 4);
            if (FIELD(entity, s8, 0x97) == (s8)quadrant) {
                angle = FIELD(FIELD(entity, void *, 0x9C), s16, 0x66);
                FIELD(obj, s32, 8) = -((func_800644B8(((angle % 0x200) << 16) >> 15) >> 4) * 0x1E00);
                FIELD(entity, s16, 0x66) = 0x1E;
            } else {
                FIELD(obj, s32, 8) = 0;
            }
            func_8008F104(entity, obj, *params);
        }
        i++;
        params++;
    } while (i < 4);

    i = 0;
    page = 0x800C0000;
    ASM_KEEP(page);
    callback2 = (void *)(page - 0x6124);
    page = 0x80100000;
    ASM_KEEP(page);
    texture2 = (void *)(page - 0x75E4);
    color = 0x80;
    do {
        obj = func_8003FD64(0x36, (u8 *)arg0 - 0x20);
        if (obj != 0) {
            FIELD(obj, void *, 0x10) = callback2;
            func_8004491C(obj, D_80045C34);
            parent_value = FIELD(arg0, s32, 0x98);
            ASM_KEEP(parent_value);
            entity = obj + 0x20;
            ASM_KEEP(entity);
            FIELD(entity, void *, 0x9C) = arg0;
            FIELD(entity, s8, 0x97) = i;
            FIELD(entity, s32, 0x98) = parent_value;
            sprite = FIELD(obj, u8 *, 0xC);
            FIELD(sprite, void *, 8) = texture2;
            FIELD(sprite, s8, 0xE) = color;
            FIELD(sprite, s8, 0xD) = color;
            FIELD(sprite, s8, 0xC) = color;
            FIELD(sprite, s16, 0x16) = 0x370;
            FIELD(sprite, s16, 0x18) = 0;
            temp_v1 = FIELD(arg0, u16, 0x66);
            ASM_KEEP(temp_v1);
            temp_v0 = 0x1000;
            ASM_KEEP(temp_v0);
            FIELD(sprite, s16, 0x1E) = temp_v0;
            FIELD(sprite, s16, 0x1C) = temp_v0;
            temp_v0 = i << 10;
            ASM_KEEP(temp_v0);
            temp_v1 += temp_v0;
            FIELD(sprite, s16, 0x1A) = temp_v1;
            obj = FIELD(obj, u8 *, 8);
            FIELD(obj, s32, 0) = FIELD(input, s32, 0);
            temp_v1 = FIELD(input, s32, 4);
            ASM_KEEP(temp_v1);
            temp_v0 = 0xFF2C0000;
            ASM_KEEP(temp_v0);
            FIELD(obj, s32, 8) = temp_v0;
            temp_v0 = 0x200000;
            ASM_KEEP(temp_v0);
            temp_v1 += temp_v0;
            FIELD(obj, s32, 4) = temp_v1;
        }
        i++;
    } while (i < 4);

    origin = (u8 *)arg0 - 0x20;
    obj = func_8003FD64(0x36, origin);
    if (obj != 0) {
        call_obj = obj;
        init_data = D_80045C34;
        ASM_KEEP_NV(init_data);
        temp_ptr = D_800B9EDC;
        FIELD(obj, void *, 0x10) = temp_ptr;
        func_8004491C(call_obj, init_data);
        parent_value = FIELD(arg0, s32, 0x98);
        ASM_KEEP(parent_value);
        entity = obj + 0x20;
        ASM_KEEP(entity);
        FIELD(entity, void * volatile, 0x9C) = arg0;
        FIELD(entity, volatile s32, 0x98) = parent_value;
        page = 0x80100000;
        ASM_KEEP_NV(page);
        sprite = FIELD(obj, u8 *, 0xC);
        ASM_KEEP_NV(sprite);
        page -= 0x75D8;
        FIELD(sprite, void *, 8) = (void *)page;
        FIELD(sprite, u8, 0xE) = 0x80;
        FIELD(sprite, u8, 0xD) = 0x80;
        FIELD(sprite, u8, 0xC) = 0x80;
        FIELD(sprite, s16, 0x16) = 0x370;
        FIELD(sprite, s16, 0x18) = 0;
        temp_v1 = FIELD(arg0, u16, 0x66);
        ASM_KEEP(temp_v1);
        temp_v0 = 0x1000;
        ASM_KEEP(temp_v0);
        FIELD(sprite, s16, 0x1E) = temp_v0;
        FIELD(sprite, s16, 0x1C) = temp_v0;
        FIELD(sprite, u16, 0x1A) = temp_v1;
        obj = FIELD(obj, u8 *, 8);
        FIELD(obj, s32, 0) = FIELD(input, s32, 0);
        temp_v1 = FIELD(input, s32, 4);
        ASM_KEEP(temp_v1);
        temp_v0 = 0xFF2C0000;
        ASM_KEEP(temp_v0);
        FIELD(obj, s32, 8) = temp_v0;
        temp_v0 = 0x200000;
        ASM_KEEP(temp_v0);
        temp_v1 += temp_v0;
        FIELD(obj, s32, 4) = temp_v1;
    }

    obj = func_8003FD64(0x136, origin);
    if (obj != 0) {
        call_obj = obj;
        init_data = D_80046398;
        ASM_KEEP_NV(init_data);
        temp_ptr = D_800B9F74;
        FIELD(obj, void *, 0x10) = temp_ptr;
        func_8004491C(call_obj, init_data);
        parent_value = FIELD(arg0, s32, 0x98);
        ASM_KEEP(parent_value);
        entity = obj + 0x20;
        ASM_KEEP(entity);
        FIELD(entity, void *, 0x9C) = arg0;
        FIELD(entity, s32, 0x98) = parent_value;
        sprite = FIELD(obj, u8 *, 0xC);
        FIELD(sprite, s16, 0x1C) = 0x1000;
        FIELD(sprite, s16, 0x1E) = 0x1000;
        FIELD(sprite, s16, 0x20) = 0x1000;
        FIELD(sprite, u16, 0x1A) = FIELD(arg0, u16, 0x66);
        page = 0x80080000;
        ASM_KEEP(page);
        page += 0x3160;
        ASM_KEEP(page);
        temp_v1 = FIELD((u8 *)page, u8, 0xA8);
        ASM_KEEP(temp_v1);
        FIELD(sprite, u8, 0xC) = temp_v1;
        temp_v1 = FIELD((u8 *)page, u8, 0xA9);
        ASM_KEEP(temp_v1);
        FIELD(sprite, u8, 0xD) = temp_v1;
        temp_v0 = FIELD((u8 *)page, u8, 0xAA);
        ASM_KEEP(temp_v0);
        FIELD(sprite, u8, 0xE) = temp_v0;
        obj = FIELD(obj, u8 *, 8);
        FIELD(sprite, s32, 8) = 0x19;
        FIELD(obj, s32, 0) = FIELD(input, s32, 0);
        temp_v0 = FIELD(input, s32, 4);
        ASM_KEEP(temp_v0);
        FIELD(obj, s32, 8) = 0;
        FIELD(obj, s32, 4) = temp_v0;
    }
}

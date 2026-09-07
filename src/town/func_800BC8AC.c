#include "common.h"


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


typedef struct S_800BA00C_0_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_800BA00C_0_pre;   /* the 0x10 bytes before arg0 in func_800BA00C, addressed as arg0[-1] */

typedef struct S_800BA00C_0 {
    u8 pad_00[0x66];
    union { s16 s; u16 u; } unk_66;   /* accessed as both */
    u8 pad_68[0x2F];
    s8 unk_97;
    s32 unk_98;
} S_800BA00C_0;   /* arg0 in func_800BA00C */

typedef struct S_800BA00C_1 {
    s32 unk_00;
    s32 unk_04;
    union { u8 * p; s32 i; } unk_08;   /* accessed as both */
    u8 * unk_0C;
    void * unk_10;
} S_800BA00C_1;   /* obj in func_800BA00C */

typedef struct S_800BA00C_2 {
    u8 pad_00[0x8];
    union { s32 i; void * p; } unk_08;   /* accessed as both */
    union { u8 u; s8 s; } unk_0C;   /* accessed as both */
    union { u8 u; s8 s; } unk_0D;   /* accessed as both */
    union { u8 u; s8 s; } unk_0E;   /* accessed as both */
    u8 pad_0F[0x7];
    s16 unk_16;
    s16 unk_18;
    union { s16 s; u16 u; } unk_1A;   /* accessed as both */
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800BA00C_2;   /* sprite in func_800BA00C */

typedef struct S_800BA00C_3 {
    s32 unk_00;
    s32 unk_04;
} S_800BA00C_3;   /* input in func_800BA00C */

typedef struct S_800BA00C_4 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_800BA00C_4;   /* (u8 *)page in func_800BA00C */

typedef struct S_800BA00C_5 {
    u8 pad_00[0x66];
    s16 unk_66;
} S_800BA00C_5;   /* (*(void * *)((u8 *)entity + 0x9C)) in func_800BA00C */

void func_800BA00C(void *arg0, void *arg1)
{
    S_800BA00C_3 *input = arg1;
    void *callback;
    Palette *palette;
    u8 *obj;
    u8 *entity;
    void *callback2;
    void *texture2;
    s32 color;
    s32 initial_angle;
    register s32 quotient ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 remtemp;
    s32 parent_value;
    register u32 page ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 temp_v0;
    s32 temp_v1;
    void *init_data;
    void *temp_ptr;
    register void *call_obj ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 rand1;
    s32 rand2;
    s32 angle;
    s32 blue;
    register s32 quadrant ASM_REG("$23");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 i;
    void **params;
    u8 *sprite;
    void *origin;

    ((S_800BA00C_0_pre *)arg0)[-1].unk_00 = D_800B9CB8;
    rand1 = rand();
    ((S_800BA00C_0 *)arg0)->unk_66.s = rand1 % 0x1000;
    rand2 = rand();
    initial_angle = ((S_800BA00C_0 *)arg0)->unk_66.s;
    ((S_800BA00C_0 *)arg0)->unk_97 = (rand2 % 9) + 12;
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
    ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
    callback = (void *)(page - 0x629C);
    page = 0x80080000;
    ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
    palette = (Palette *)(page + 0x3160);
    page = 0x800D0000;
    ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
    params = (void **)(page + 0x1BCC);
    do {
        obj = func_8003FD64(0x136, (u8 *)arg0 - 0x20);
        if (obj != 0) {
            ((S_800BA00C_1 *)obj)->unk_10 = callback;
            func_8004491C(obj, D_80046398);
            parent_value = ((S_800BA00C_0 *)arg0)->unk_98;
            ASM_KEEP(parent_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
            entity = obj + 0x20;
            ASM_KEEP(entity);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            (*(void * *)((u8 *)entity + 0x9C)) = arg0;
            (*(s16 *)((u8 *)entity + 0x66)) = 0;
            (*(s8 *)((u8 *)entity + 0x97)) = i;
            (*(s32 *)((u8 *)entity + 0x98)) = parent_value;
            sprite = ((S_800BA00C_1 *)obj)->unk_0C;
            ((S_800BA00C_2 *)sprite)->unk_1C = 0x1000;
            ((S_800BA00C_2 *)sprite)->unk_1E = 0x1000;
            ((S_800BA00C_2 *)sprite)->unk_20 = 0xAAA;
            ((S_800BA00C_2 *)sprite)->unk_0C.u = palette->red;
            ((S_800BA00C_2 *)sprite)->unk_0D.u = palette->green;
            blue = palette->blue;
            ((S_800BA00C_2 *)sprite)->unk_08.i = i + 0x1A;
            ((S_800BA00C_2 *)sprite)->unk_0E.u = blue;
            obj = ((S_800BA00C_1 *)obj)->unk_08.p;
            ((S_800BA00C_1 *)obj)->unk_00 = input->unk_00;
            ((S_800BA00C_1 *)obj)->unk_04 = input->unk_04;
            if ((*(s8 *)((u8 *)entity + 0x97)) == (s8)quadrant) {
                angle = ((S_800BA00C_5 *)((*(void * *)((u8 *)entity + 0x9C))))->unk_66;
                ((S_800BA00C_1 *)obj)->unk_08.i = -((func_800644B8(((angle % 0x200) << 16) >> 15) >> 4) * 0x1E00);
                (*(s16 *)((u8 *)entity + 0x66)) = 0x1E;
            } else {
                ((S_800BA00C_1 *)obj)->unk_08.i = 0;
            }
            func_8008F104(entity, obj, *params);
        }
        i++;
        params++;
    } while (i < 4);

    i = 0;
    page = 0x800C0000;
    ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
    callback2 = (void *)(page - 0x6124);
    page = 0x80100000;
    ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
    texture2 = (void *)(page - 0x75E4);
    color = 0x80;
    do {
        obj = func_8003FD64(0x36, (u8 *)arg0 - 0x20);
        if (obj != 0) {
            ((S_800BA00C_1 *)obj)->unk_10 = callback2;
            func_8004491C(obj, D_80045C34);
            parent_value = ((S_800BA00C_0 *)arg0)->unk_98;
            ASM_KEEP(parent_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
            entity = obj + 0x20;
            ASM_KEEP(entity);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            (*(void * *)((u8 *)entity + 0x9C)) = arg0;
            (*(s8 *)((u8 *)entity + 0x97)) = i;
            (*(s32 *)((u8 *)entity + 0x98)) = parent_value;
            sprite = ((S_800BA00C_1 *)obj)->unk_0C;
            ((S_800BA00C_2 *)sprite)->unk_08.p = texture2;
            ((S_800BA00C_2 *)sprite)->unk_0E.s = color;
            ((S_800BA00C_2 *)sprite)->unk_0D.s = color;
            ((S_800BA00C_2 *)sprite)->unk_0C.s = color;
            ((S_800BA00C_2 *)sprite)->unk_16 = 0x370;
            ((S_800BA00C_2 *)sprite)->unk_18 = 0;
            temp_v1 = ((S_800BA00C_0 *)arg0)->unk_66.u;
            temp_v0 = 0x1000;
            ((S_800BA00C_2 *)sprite)->unk_1E = temp_v0;
            ((S_800BA00C_2 *)sprite)->unk_1C = temp_v0;
            temp_v0 = i << 10;
            temp_v1 += temp_v0;
            ((S_800BA00C_2 *)sprite)->unk_1A.s = temp_v1;
            obj = ((S_800BA00C_1 *)obj)->unk_08.p;
            ((S_800BA00C_1 *)obj)->unk_00 = input->unk_00;
            temp_v1 = input->unk_04;
            temp_v0 = 0xFF2C0000;
            ((S_800BA00C_1 *)obj)->unk_08.i = temp_v0;
            temp_v0 = 0x200000;
            temp_v1 += temp_v0;
            ((S_800BA00C_1 *)obj)->unk_04 = temp_v1;
        }
        i++;
    } while (i < 4);

    origin = (u8 *)arg0 - 0x20;
    obj = func_8003FD64(0x36, origin);
    if (obj != 0) {
        call_obj = obj;
        init_data = D_80045C34;
        ASM_KEEP_NV(init_data);   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_ptr = D_800B9EDC;
        ((S_800BA00C_1 *)obj)->unk_10 = temp_ptr;
        func_8004491C(call_obj, init_data);
        parent_value = ((S_800BA00C_0 *)arg0)->unk_98;
        ASM_KEEP(parent_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
        entity = obj + 0x20;
        ASM_KEEP(entity);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        (*(void * volatile *)((u8 *)entity + 0x9C)) = arg0;
        (*(volatile s32 *)((u8 *)entity + 0x98)) = parent_value;
        page = 0x80100000;
        ASM_KEEP_NV(page);   /* MATCH pin: retail immediate-load split depends on it */
        sprite = ((S_800BA00C_1 *)obj)->unk_0C;
        page -= 0x75D8;
        ((S_800BA00C_2 *)sprite)->unk_08.p = (void *)page;
        ((S_800BA00C_2 *)sprite)->unk_0E.u = 0x80;
        ((S_800BA00C_2 *)sprite)->unk_0D.u = 0x80;
        ((S_800BA00C_2 *)sprite)->unk_0C.u = 0x80;
        ((S_800BA00C_2 *)sprite)->unk_16 = 0x370;
        ((S_800BA00C_2 *)sprite)->unk_18 = 0;
        temp_v1 = ((S_800BA00C_0 *)arg0)->unk_66.u;
        temp_v0 = 0x1000;
        ((S_800BA00C_2 *)sprite)->unk_1E = temp_v0;
        ((S_800BA00C_2 *)sprite)->unk_1C = temp_v0;
        ((S_800BA00C_2 *)sprite)->unk_1A.u = temp_v1;
        obj = ((S_800BA00C_1 *)obj)->unk_08.p;
        ((S_800BA00C_1 *)obj)->unk_00 = input->unk_00;
        temp_v1 = input->unk_04;
        temp_v0 = 0xFF2C0000;
        ((S_800BA00C_1 *)obj)->unk_08.i = temp_v0;
        temp_v0 = 0x200000;
        temp_v1 += temp_v0;
        ((S_800BA00C_1 *)obj)->unk_04 = temp_v1;
    }

    obj = func_8003FD64(0x136, origin);
    if (obj != 0) {
        call_obj = obj;
        init_data = D_80046398;
        ASM_KEEP_NV(init_data);   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_ptr = D_800B9F74;
        ((S_800BA00C_1 *)obj)->unk_10 = temp_ptr;
        func_8004491C(call_obj, init_data);
        parent_value = ((S_800BA00C_0 *)arg0)->unk_98;
        ASM_KEEP(parent_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
        entity = obj + 0x20;
        ASM_KEEP(entity);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        (*(void * *)((u8 *)entity + 0x9C)) = arg0;
        (*(s32 *)((u8 *)entity + 0x98)) = parent_value;
        sprite = ((S_800BA00C_1 *)obj)->unk_0C;
        ((S_800BA00C_2 *)sprite)->unk_1C = 0x1000;
        ((S_800BA00C_2 *)sprite)->unk_1E = 0x1000;
        ((S_800BA00C_2 *)sprite)->unk_20 = 0x1000;
        ((S_800BA00C_2 *)sprite)->unk_1A.u = ((S_800BA00C_0 *)arg0)->unk_66.u;
        page = 0x80080000;
        ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
        page += 0x3160;
        temp_v1 = ((S_800BA00C_4 *)((u8 *)page))->unk_A8;
        ((S_800BA00C_2 *)sprite)->unk_0C.u = temp_v1;
        temp_v1 = ((S_800BA00C_4 *)((u8 *)page))->unk_A9;
        ((S_800BA00C_2 *)sprite)->unk_0D.u = temp_v1;
        temp_v0 = ((S_800BA00C_4 *)((u8 *)page))->unk_AA;
        ((S_800BA00C_2 *)sprite)->unk_0E.u = temp_v0;
        obj = ((S_800BA00C_1 *)obj)->unk_08.p;
        ((S_800BA00C_2 *)sprite)->unk_08.i = 0x19;
        ((S_800BA00C_1 *)obj)->unk_00 = input->unk_00;
        temp_v0 = input->unk_04;
        ((S_800BA00C_1 *)obj)->unk_08.i = 0;
        ((S_800BA00C_1 *)obj)->unk_04 = temp_v0;
    }
}

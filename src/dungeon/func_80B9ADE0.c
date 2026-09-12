#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;

typedef struct {
    u8 pad_00[0x0C];
    u8 field_0C;
    u8 field_0D;
    u8 field_0E;
    u8 pad_0F;
    u16 field_10;
    u8 pad_12[2];
    u16 field_14;
    u8 pad_16[6];
    s16 field_1C;
    s16 field_1E;
} Prim;

typedef struct {
    u8 pad_00[4];
    u8 field_04;
    u8 field_05;
    u8 field_06;
    u8 pad_07[0x13];
    s16 field_1A;
    u16 field_1C;
    u8 pad_1E[0x46];
    s16 field_64;
    s16 field_66;
    s16 field_68;
    s16 field_6A;
    s16 field_6C;
    s16 field_6E;
    s16 field_70;
    s16 field_72;
    s16 field_74;
    s16 field_76;
    s16 field_78;
    s16 field_7A;
} Sub;

typedef struct {
    u8 pad_00[8];
    Vec3i *vec;
    Prim *prim;
    void (*callback)(void);
    u8 pad_14[0x0C];
    Sub sub;
} Entity;

typedef struct {
    u8 pad_00[0x96];
    u16 field_96;
} Source;

extern Entity *func_8003FC64(s32);
extern void func_8004491C(Entity *, void *);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern u8 D_80045340;
extern void D_8017414C(void);

/* Creates a 16-segment cylindrical effect at the supplied position. */
void func_801745E0(Source *source, Vec3i *origin)
{
    s16 segment;
    void (*callback)(void);
    s32 base_color;

    segment = 0;
    callback = D_8017414C;
    base_color = 32;
    for (; segment < 16; segment++) {
        Entity *entity;
        Sub *sub;
        Vec3i *position;
        Prim *prim;
        s32 angle;
        s32 next_angle;
        s16 radial_offset;
        u16 flags;
        volatile u16 *prim_flags;
        Entity *init_entity;
        s32 lifetime;
        s32 unit_scale;
        u8 color_copy;
        s32 trig_angle;
        s32 trig_value;

        entity = func_8003FC64(18);
        if (entity == 0) {
            continue;
        }

        sub = &entity->sub;
        lifetime = 50;
        init_entity = entity;
        sub->field_1A = lifetime;
        sub->field_1C = source->field_96;
        entity->callback = callback;
        func_8004491C(init_entity, &D_80045340);

        angle = segment;
        prim = entity->prim;
        prim_flags = &prim->field_14;
        flags = *(u16 *)prim_flags;
        flags |= 0xC;
        prim->field_10 = base_color;
        *prim_flags = flags;
        flags |= 0x80;
        *prim_flags = flags;

        position = entity->vec;
        position->x = origin->x;
        next_angle = (angle + 1) << 8;
        position->y = origin->y;
        position->z = origin->z;

        sub->field_6E = -64;
        sub->field_68 = -64;
        sub->field_7A = 0;
        sub->field_74 = 0;

        trig_value = func_80064584(next_angle);
        do {
            angle <<= 8;
        } while (0);
        trig_angle = angle;
        ASM_KEEP(trig_value);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        radial_offset = (trig_value * 24) >> 12;
        sub->field_70 = radial_offset;
        sub->field_64 = radial_offset;

        trig_value = func_80064584(trig_angle);
        trig_angle = next_angle;
        radial_offset = (trig_value * 24) >> 12;
        sub->field_76 = radial_offset;
        sub->field_6A = radial_offset;

        trig_value = func_800644B8(trig_angle);
        trig_angle = angle;
        radial_offset = (trig_value * 24) >> 12;
        sub->field_72 = radial_offset;
        sub->field_66 = radial_offset;

        trig_value = func_800644B8(trig_angle);
        radial_offset = (trig_value * 24) >> 12;
        sub->field_78 = radial_offset;
        sub->field_6C = radial_offset;

        prim = entity->prim;
        prim->field_0C = base_color;
        color_copy = base_color;
        unit_scale = 4096;
        prim->field_1E = unit_scale;
        prim->field_1C = unit_scale;
        prim->field_0D = 128;
        prim->field_0E = base_color;
        sub->field_04 = prim->field_0C;
        sub->field_05 = prim->field_0D;
        sub->field_06 = prim->field_0E;
    }
}

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
extern void func_80174934(void);

void func_80174E78(Source *src, Vec3i *vec)
{
    s16 i;
    void (*callback)(void);
    s32 thirty_two;

    i = 0;
    callback = func_80174934;
    thirty_two = 32;
    for (; i < 16; i++) {
        Entity *entity;
        Sub *sub;
        Prim *prim;
        Vec3i *dst;
        s32 angle;
        s32 next;
        s32 value;
        u16 flags;
        volatile u16 *flag_ptr;
        Entity *call_arg;
        s32 fifty;
        s32 trig_arg;
        register s32 raw_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        register u8 intensity ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        u8 held_intensity;

        entity = func_8003FC64(18);
        if (entity == 0) {
            continue;
        }

        sub = &entity->sub;
        fifty = 50;
        call_arg = entity;
        ASM_KEEP(call_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        sub->field_1A = fifty;
        sub->field_1C = src->field_96;
        entity->callback = callback;
        func_8004491C(call_arg, &D_80045340);

        angle = i;
        prim = entity->prim;
        flag_ptr = &prim->field_14;
        flags = *(u16 *)flag_ptr;
        flags |= 0xC;
        prim->field_10 = thirty_two;
        *flag_ptr = flags;
        flags |= 0x80;
        *flag_ptr = flags;

        dst = entity->vec;
        dst->x = vec->x;
        next = (angle + 1) << 8;
        dst->y = vec->y;
        dst->z = vec->z;

        sub->field_6E = -64;
        sub->field_68 = -64;
        sub->field_7A = 0;
        sub->field_74 = 0;

        raw_value = func_80064584(next);
        angle <<= 8;
        trig_arg = angle;
        ASM_KEEP(trig_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        value = (raw_value * 24) >> 12;
        sub->field_70 = value;
        sub->field_64 = value;

        raw_value = func_80064584(trig_arg);
        trig_arg = next;
        ASM_KEEP(trig_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        value = (raw_value * 24) >> 12;
        sub->field_76 = value;
        sub->field_6A = value;

        raw_value = func_800644B8(trig_arg);
        trig_arg = angle;
        ASM_KEEP(trig_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        value = (raw_value * 24) >> 12;
        sub->field_72 = value;
        sub->field_66 = value;

        raw_value = func_800644B8(trig_arg);
        value = (raw_value * 24) >> 12;
        sub->field_78 = value;
        sub->field_6C = value;

        prim = entity->prim;
        intensity = 128;
        prim->field_0C = intensity;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        held_intensity = intensity;
        ASM_KEEP(held_intensity);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        prim->field_1E = 4096;
        prim->field_1C = 4096;
        prim->field_0D = thirty_two;
        prim->field_0E = thirty_two;
        sub->field_04 = held_intensity;
        sub->field_05 = prim->field_0D;
        sub->field_06 = prim->field_0E;
    }
}

/* MECHANISM: The 0x38 frame and s0-s7/fp roles fall from the natural loop lifetimes.
   Split call setup and trig returns into guarded a0/v0 ranges to reproduce retail's pipeline.
   A held u8 0x80 plus a store-seam ASM_SCHED_BARRIER closes the final one-word rotation. */

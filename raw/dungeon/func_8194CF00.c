#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} WordQuad;

extern M2C_UNK func_8003DB94();
extern void *func_8003FC64(s32);
extern M2C_UNK func_8004491C();
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern M2C_UNK func_800649A0();
extern M2C_UNK func_80064A40();
extern M2C_UNK func_80064B30();

extern M2C_UNK D_8002455C[];
extern s32 D_80045340;
extern u8 D_800DE938[];

void func_80024700(void *arg0)
{
    s16 rotation[3];
    u16 delta[3];
    s16 temp_s16;
    s32 value;
    u16 firstAngle;
    u16 secondAngle;
    u16 flags14;
    u16 flags10;
    M2C_UNK *link;
    void *source = arg0;
    register void *object ASM_REG("$18");
    register void *data ASM_REG("$17");
    register void *primitive ASM_REG("$16");
    register s32 allocType ASM_REG("$4") = 0x212;
    register u8 *texture ASM_REG("$5");
    register s32 zero ASM_REG("$6");
    register u32 linkPage ASM_REG("$2");

    object = func_8003FC64(allocType);
    ASM_KEEP(object);
    if (object != NULL) {
        linkPage = 0x80020000;
        ASM_KEEP(linkPage);
        link = (M2C_UNK *)(linkPage + 0x455C);
        texture = D_800DE938;
        FIELD(object, M2C_UNK *, 0x10) = link;
        value = FIELD(source, s32, 0);
        ASM_KEEP(value);
        data = (u8 *)object + 0x20;
        ASM_KEEP(data);
        FIELD(object, s32, 0x20) = value;
        FIELD(object, WordQuad, 0x24) = FIELD(source, WordQuad, 0x4C);
        FIELD(object, WordQuad, 0x34) = FIELD(source, WordQuad, 0x5C);

        firstAngle = FIELD(source, u16, 0x78);
        ASM_KEEP(firstAngle);
        zero = 0;
        ASM_KEEP(zero);
        FIELD(data, u16, 0x2C) = firstAngle;
        secondAngle = FIELD(source, u16, 0x76);
        FIELD(data, u8, 0x30) = 1;
        FIELD(data, u16, 0x2E) = secondAngle;

        primitive = FIELD(object, void *, 0xC);
        ASM_KEEP(primitive);
        FIELD(primitive, u8, 0xE) = 0x40;
        FIELD(primitive, u8, 0xD) = 0x40;
        FIELD(primitive, u8, 0xC) = 0x40;
        func_8003DB94(primitive, texture, zero);

        value = 0x2000;
        allocType = (s32)object;
        texture = (u8 *)0x80040000;
        ASM_KEEP(texture);
        FIELD(primitive, s16, 0x1E) = value;
        FIELD(primitive, s16, 0x1C) = value;
        temp_s16 = FIELD(data, u16, 0x24);
        ASM_KEEP(temp_s16);
        texture += 0x5340;
        ASM_KEEP(texture);
        FIELD(primitive, s16, 0x16) = temp_s16 >> 12;
        temp_s16 = FIELD(data, u16, 0x26);
        flags14 = FIELD(primitive, u16, 0x14);
        FIELD(primitive, s16, 0x18) = temp_s16 >> 12;
        zero = FIELD(data, u16, 0x2E);
        flags10 = FIELD(primitive, u16, 0x10);
        FIELD(primitive, u16, 0x14) = flags14 | 0xC;
        FIELD(primitive, u16, 0x10) = flags10 | 0x20;
        FIELD(primitive, u16, 0x1A) = zero;
        func_8004491C((void *)allocType, texture);

        primitive = FIELD(object, void *, 8);
        ASM_KEEP(primitive);
        value = FIELD(source, s32, 0x34);
        FIELD(primitive, s32, 0xC) = value;
        FIELD(primitive, s32, 0) = value;
        value = FIELD(source, s32, 0x38);
        FIELD(primitive, s32, 0x10) = value;
        FIELD(primitive, s32, 4) = value;
        value = FIELD(source, s32, 0x3C);
        FIELD(primitive, s32, 0x14) = value;
        FIELD(primitive, s32, 8) = value;

        rotation[0] = ((func_800644B8(FIELD(data, s16, 0x2E)) >> 4) *
            FIELD(data, s16, 0x2C)) >> 8;
        rotation[1] = ((func_80064584(FIELD(data, s16, 0x2E)) >> 4) *
            FIELD(data, s16, 0x2C)) >> 8;
        rotation[2] = 0;
        func_800649A0();
        ASM_KEEP(object);
        func_80064B30((u8 *)object + 0x24, rotation, delta);
        func_80064A40();

        FIELD(primitive, u16, 2) += delta[0];
        FIELD(primitive, u16, 6) += delta[1];
        FIELD(primitive, u16, 0xA) += delta[2];
    }
}

/* MECHANISM: The 0x38 frame holds source/object/data/primitive in s3/s2/s1/s0 and uses sibling
   rotation/delta stack arrays; caller-register locals plus page/fence seams reproduce split loads.
   A post-func_800649A0 object fence rematerializes object+0x24 without a fifth saved register. */

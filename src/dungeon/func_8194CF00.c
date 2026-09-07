#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif


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


typedef struct S_80024700_0 {
    u8 pad_00[0x24];
    u16 unk_24;
    u16 unk_26;
    u8 pad_28[0x4];
    union { u16 u; s16 s; } unk_2C;   /* accessed as both */
    union { u16 u; s16 s; } unk_2E;   /* accessed as both */
    u8 unk_30;
} S_80024700_0;   /* data in func_80024700 */

typedef struct S_80024700_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    union { u16 u16; s32 s32; } unk_10;   /* accessed as both */
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
    s16 unk_18;
    u16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024700_1;   /* primitive in func_80024700 */

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
    void *object;
    S_80024700_0 *data;
    register void *primitive ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
    register s32 allocType ASM_REG("$4") = 0x212;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u8 *texture ASM_REG("$5");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 zero;
    u32 linkPage;

    object = func_8003FC64(allocType);
    if (object != NULL) {
        linkPage = 0x80020000;
        ASM_KEEP(linkPage);   /* MATCH pin: load-bearing for the whole function shape */
        link = (M2C_UNK *)(linkPage + 0x455C);
        texture = D_800DE938;
        (*(M2C_UNK * *)((u8 *)object + 0x10)) = link;
        value = (*(s32 *)((u8 *)source + 0));
        ASM_KEEP(value);   /* MATCH pin: keeps a statement from moving across a call/branch */
        data = (u8 *)object + 0x20;
        ASM_KEEP(data);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        (*(s32 *)((u8 *)object + 0x20)) = value;
        (*(WordQuad *)((u8 *)object + 0x24)) = (*(WordQuad *)((u8 *)source + 0x4C));
        (*(WordQuad *)((u8 *)object + 0x34)) = (*(WordQuad *)((u8 *)source + 0x5C));

        firstAngle = (*(u16 *)((u8 *)source + 0x78));
        ASM_KEEP(firstAngle);   /* MATCH pin: retail basic-block layout depends on it */
        zero = 0;
        ASM_KEEP(zero);   /* MATCH pin: retail delay-slot fill depends on it */
        data->unk_2C.u = firstAngle;
        secondAngle = (*(u16 *)((u8 *)source + 0x76));
        data->unk_30 = 1;
        data->unk_2E.u = secondAngle;

        primitive = (*(void * *)((u8 *)object + 0xC));
        ((S_80024700_1 *)primitive)->unk_0C.at02.v = 0x40;
        ((S_80024700_1 *)primitive)->unk_0C.at01.v = 0x40;
        ((S_80024700_1 *)primitive)->unk_0C.at00.v = 0x40;
        func_8003DB94(primitive, texture, zero);

        value = 0x2000;
        allocType = (s32)object;
        texture = (u8 *)0x80040000;
        ASM_KEEP(texture);   /* MATCH pin: keeps a statement from moving across a call/branch */
        ((S_80024700_1 *)primitive)->unk_1E = value;
        ((S_80024700_1 *)primitive)->unk_1C = value;
        temp_s16 = data->unk_24;
        texture += 0x5340;
        ((S_80024700_1 *)primitive)->unk_14.at02.v = temp_s16 >> 12;
        temp_s16 = data->unk_26;
        flags14 = ((S_80024700_1 *)primitive)->unk_14.at00.v;
        ((S_80024700_1 *)primitive)->unk_18 = temp_s16 >> 12;
        zero = data->unk_2E.u;
        flags10 = ((S_80024700_1 *)primitive)->unk_10.u16;
        ((S_80024700_1 *)primitive)->unk_14.at00.v = flags14 | 0xC;
        ((S_80024700_1 *)primitive)->unk_10.u16 = flags10 | 0x20;
        ((S_80024700_1 *)primitive)->unk_1A = zero;
        func_8004491C((void *)allocType, texture);

        primitive = (*(void * *)((u8 *)object + 8));
        value = (*(s32 *)((u8 *)source + 0x34));
        ((S_80024700_1 *)primitive)->unk_0C.at00u.v = value;
        ((S_80024700_1 *)primitive)->unk_00.at00.v = value;
        value = (*(s32 *)((u8 *)source + 0x38));
        ((S_80024700_1 *)primitive)->unk_10.s32 = value;
        ((S_80024700_1 *)primitive)->unk_04.at00.v = value;
        value = (*(s32 *)((u8 *)source + 0x3C));
        ((S_80024700_1 *)primitive)->unk_14.at00u.v = value;
        ((S_80024700_1 *)primitive)->unk_08.at00.v = value;

        rotation[0] = ((func_800644B8(data->unk_2E.s) >> 4) *
            data->unk_2C.s) >> 8;
        rotation[1] = ((func_80064584(data->unk_2E.s) >> 4) *
            data->unk_2C.s) >> 8;
        rotation[2] = 0;
        func_800649A0();
        ASM_KEEP(object);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        func_80064B30((u8 *)object + 0x24, rotation, delta);
        func_80064A40();

        ((S_80024700_1 *)primitive)->unk_00.at02.v += delta[0];
        ((S_80024700_1 *)primitive)->unk_04.at02.v += delta[1];
        ((S_80024700_1 *)primitive)->unk_08.at02.v += delta[2];
    }
}

/* MECHANISM: The 0x38 frame holds source/object/data/primitive in s3/s2/s1/s0 and uses sibling
   rotation/delta stack arrays; caller-register locals plus page/fence seams reproduce split loads.
   A post-func_800649A0 object fence rematerializes object+0x24 without a fifth saved register. */

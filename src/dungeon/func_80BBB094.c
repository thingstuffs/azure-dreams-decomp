#include "common.h"

typedef struct {
    u8 pad0[10];
    s16 unkA;
} Func80BBB094PartA;

typedef struct {
    u8 pad0[0x24];
    u8 unk24;
    u8 unk25;
    u8 pad26[6];
    void *volatile unk2C;
} Func80BBB094PartB;

typedef struct {
    u8 pad0[0x13];
    u8 unk13;
    u32 unk14;
    u8 pad18[4];
    u32 unk1C;
    u8 pad20[0x6C];
    void *unk8C;
    u8 pad90[10];
    u8 unk9A;
    u8 unk9B;
    s8 unk9C;
} Func80BBB094PartC;

typedef struct {
    u8 pad0[8];
    Func80BBB094PartA *unk8;
    Func80BBB094PartB *unkC;
    void *unk10;
    u8 pad14[12];
    Func80BBB094PartC unk20;
} Func80BBB094Object;

extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_8014CE9C[];
extern u8 D_80150ED8[];
extern u8 D_80150F00[];
extern u8 D_8014CA98[];

extern Func80BBB094Object *func_8003FD64(s32, void *);
extern void func_8004491C(Func80BBB094Object *, void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(Func80BBB094PartC *, s32, s32);
extern void func_800A9C18(Func80BBB094Object *, Func80BBB094PartA *,
                          Func80BBB094PartB *, s32);
extern void func_800AA36C(Func80BBB094PartC *, Func80BBB094PartA *,
                          Func80BBB094PartB *, Func80BBB094PartC *);

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
Func80BBB094PartC *func_8014C894(s32 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c)
{
    Func80BBB094PartC *result = 0;
    register s32 arg1Reg ASM_REG("$21") = attr_a;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register unsigned long slot1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 arg2Reg;
    register Func80BBB094PartC *resultAlias;
    Func80BBB094Object *obj;
    Func80BBB094PartA *partA;
    s16 savedArg0;
    Func80BBB094PartB *partB;
    unsigned long slot2;
    s32 mode;
    s32 flag;
    s32 randomTest;
    slot1 = (unsigned long)attr_c;
    arg2Reg = attr_b;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        savedArg0 = spawn_flags;
        ASM_KEEP_NV(spawn_flags);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        result = &obj->unk20;
        result->unk13 = 14;
        func_8004491C(obj, D_80045340);

        partA = obj->unk8;
        partA->unkA = (s32)slot1;
        slot1 = (unsigned long)obj->unkC;
        partB = (Func80BBB094PartB *)slot1;
        partB->unk25 = arg2Reg;
        partB->unk24 = arg1Reg;
        resultAlias = result;

        mode = spawn_flags & 3;
        if (mode == 1) {
            result->unk8C = D_8014CE9C;
            result->unk14 |= 0x6000;
            result->unk1C |= 0x6000;
            partB->unk2C = D_80150ED8;
        } else if (mode >= 2) {
            result->unk8C = D_8014CE9C;
            result->unk14 |= 0x2000;
            result->unk1C |= 0x2000;
            partB->unk2C = D_80150ED8;
        } else {
            slot2 = spawn_flags & -4;
            slot2 = (u32)slot2 << 16;
            if (slot2 == 0) {
                flag = result->unk14 & 0x200;
                if (flag == 0) {
                    randomTest = func_800A6D30() & 1;
                    if (randomTest != 0) {
                        s32 random = func_800A6D30();

                        func_800A48F0(result, 1, (random & 0x3F) | 0x20);
                        partB->unk2C = D_80150F00;
                    }
                } else {
                }
                resultAlias->unk8C = (void *)D_8014CE9C;
            } else {
                result->unk8C = (void *)D_8014CE9C;
            }
            partB->unk2C = D_80150ED8;
        }

        obj->unk10 = D_8014CA98;
        func_800A9C18(obj, partA, partB, savedArg0);

        resultAlias->unk9A = 0xFF;
        resultAlias->unk9C = -1;
        func_800AA36C(resultAlias, partA, partB, result);
    }
    return result;
}

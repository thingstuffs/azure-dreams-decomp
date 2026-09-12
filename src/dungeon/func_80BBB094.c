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

Func80BBB094PartC *func_8014C894(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    Func80BBB094PartC *result = 0;
    register s32 arg1Reg ASM_REG("$21") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register unsigned long slot1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 arg2Reg ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register Func80BBB094PartC *resultAlias;
    Func80BBB094Object *obj;
    Func80BBB094PartA *partA;
    s16 savedArg0;
    Func80BBB094PartB *partB;
    unsigned long slot2;
    s32 mode;
    s32 flag;
    s32 randomTest;
    u32 word14;
    u32 word1C;
    slot1 = (unsigned long)arg3;
    arg2Reg = arg2;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        savedArg0 = arg0;
        ASM_KEEP_NV(arg0);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
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

        mode = arg0 & 3;
        if (mode == 1) {
            result->unk8C = D_8014CE9C;
            ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            word14 = result->unk14;
            word1C = result->unk1C;
            word14 |= 0x6000;
            word1C |= 0x6000;
            result->unk14 = word14;
            ASM_USE(word14);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            result->unk1C = word1C;
            slot2 = (unsigned long)D_80150ED8;
        } else if (mode >= 2) {
            result->unk8C = D_8014CE9C;
            ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            word14 = result->unk14;
            word1C = result->unk1C;
            word14 |= 0x2000;
            word1C |= 0x2000;
            result->unk14 = word14;
            ASM_USE2(word14, word1C);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            result->unk1C = word1C;
            slot2 = (unsigned long)D_80150ED8;
            ASM_KEEP_NV(slot2);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        } else {
            slot2 = arg0 & -4;
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
                    slot2 = 0x80150000UL;
                } else {
                    slot2 = 0x80150000UL;
                }
                slot2 -= 0x3164;
                resultAlias->unk8C = (void *)slot2;
            } else {
                slot2 = 0x80150000UL;
                ASM_KEEP_NV(slot2);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                slot2 -= 0x3164;
                result->unk8C = (void *)slot2;
            }
            slot2 = (unsigned long)D_80150ED8;
        }

        partB->unk2C = (void *)slot2;
        ASM_KEEP(partB);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        obj->unk10 = D_8014CA98;
        func_800A9C18(obj, partA, partB, savedArg0);

        resultAlias->unk9A = 0xFF;
        resultAlias->unk9C = -1;
        func_800AA36C(resultAlias, partA, partB, result);
    }
    return result;
}

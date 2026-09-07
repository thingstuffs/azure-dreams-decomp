#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_80069EF8(void);
extern u8 D_80045340[0x10];
extern s32 D_800814A0[3];
extern u8 D_80083498[];
extern s32 D_800DB164;
extern s32 D_800DEA68;

void func_800DAEF4(void *arg0, void *arg1)
{
    register void *owner ASM_REG("$22");
    register void *params ASM_REG("$20");
    register s32 count ASM_REG("$21");
    u8 *link;
    register void *object ASM_REG("$18");
    register void *node ASM_REG("$17");
    register u8 *work ASM_REG("$19");
    s32 random;
    s32 other2;
    s32 random2;
    s32 divisor;
    s32 x;
    s32 linkValue;
    u16 timer;
    u16 paramValue;
    register void *part ASM_REG("$6");

    owner = arg0;
    params = arg1;
    count = 12;
    link = (u8 *)&D_800DEA68;
    do {
        object = func_8003FD64(0x312, D_80083498);
        if (object != 0) {
            FIELD(object, void *, 0x10) = &D_800DB164;
            func_8004491C(object, D_80045340);
            node = FIELD(object, void *, 0xC);
            work = (u8 *)object + 0x20;

            random = func_80069EF8();
            do {
                register const s32 other ASM_REG("$3") = func_80069EF8();
                register s32 firstWork ASM_REG("$5");
                register s32 secondWork ASM_REG("$4");
                register s32 randomSum ASM_REG("$2");

                part = FIELD(object, void *, 8);
                firstWork = random;
                if (random < 0) {
                    firstWork = random + 63;
                }
                secondWork = other;
                ASM_KEEP_NV(secondWork);
                randomSum = (firstWork >> 6) << 6;
                firstWork = random - randomSum;
                if (other < 0) {
                    secondWork = other + 63;
                }
                randomSum = (secondWork >> 6) << 6;
                randomSum = firstWork + (other - randomSum) - 64;
                ASM_USE_NV(other);
                FIELD(part, u16, 2) = FIELD(params, u16, 2) + randomSum / 2;
            } while (0);

            random2 = func_80069EF8();
            other2 = func_80069EF8();
            FIELD(FIELD(object, void *, 8), u16, 6) = FIELD(params, u16, 6) + (random2 % 64 + other2 % 64 - 64) / 2;

            FIELD(FIELD(object, void *, 8), u16, 0xA) = FIELD(owner, u16, 0x10);
            FIELD(work, u16, 0x10) = FIELD(params, u16, 0xA);

            divisor = (func_80069EF8() & 3) + 4;
            x = FIELD(params, s32, 8);
            x -= FIELD(owner, s16, 0x10) << 16;
            FIELD(FIELD(object, void *, 8), s32, 0x14) = x / divisor;

            FIELD(node, u16, 0x14) |= 0xC;
            FIELD(node, u16, 0x1C) = 0x1000;
            FIELD(node, u16, 0x1E) = 0x200;
            if (func_80069EF8() & 1) {
                FIELD(node, u16, 0x14) |= 1;
            }
            FIELD(node, u16, 0x10) = 0x60;
            FIELD(node, s32, 0xC) = 0xC06060;
            FIELD(node, void *, 0) = link;
            linkValue = FIELD(link, s32, 4);
            FIELD(node, s8, 4) = 0;
            FIELD(node, s8, 5) = 0;
            FIELD(node, s32, 8) = linkValue;
            paramValue = FIELD(params, u16, 0xA);
            FIELD(work, u16, 0x48) = 4;
            FIELD(work, u16, 0x10) = paramValue;
        }
        count--;
    } while (count >= 0);

    timer = FIELD(owner, u16, 0x48) - 1;
    FIELD(owner, u16, 0x48) = timer;
    if ((timer << 16) <= 0) {
        FIELD(owner, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

    ASM_KEEP(owner);
    ASM_KEEP(params);
    ASM_KEEP(count);
    ASM_KEEP(link);
    ASM_KEEP(object);
    ASM_KEEP(node);
    ASM_KEEP(work);
}

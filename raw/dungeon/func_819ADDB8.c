#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct Obj Obj;

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern u8 D_80082E80[];
extern u8 D_80083498[];
extern u8 D_8002501C[];
extern u8 D_800274C0[];
extern u8 D_80027580[];
extern u8 D_800C9034[];

extern s32 func_8003FA44(s32);
extern Obj *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);

void *func_800255B8(s32 arg0, s32 arg1, s16 arg2, u16 arg3) {
    void *objects[12];
    register s32 xArg ASM_REG("$21");
    register s32 yArg ASM_REG("$22");
    register s16 zArg ASM_REG("$23");
    register u16 wArg ASM_REG("$18");
    s32 i;
    register void **base ASM_REG("$19");
    register void **cur ASM_REG("$16");
    s16 *xTable;
    register u8 *color;
    register u8 *tail ASM_REG("$4");
    register u8 *partA ASM_REG("$3");
    u8 *partB;
    u8 firstColor;
    u32 secondColor;
    register u32 tableOff ASM_REG("$4");
    s32 xDelta;
    s32 yDelta;
    u16 flags;

    xArg = arg0;
    yArg = arg1;
    zArg = arg2;
    wArg = arg3;
    ASM_KEEP4_NV(xArg, yArg, zArg, wArg);

    if (func_8003FA44(12) == 0) {
        return 0;
    }

    i = 0;
#ifdef NON_MATCHING
    xTable = D_8006CCD8;
    color = D_80082E80;
#else
    {
        register u8 *pageBase ASM_REG("$2");

        pageBase = (u8 *)0x80070000;
        ASM_KEEP_NV(pageBase);
        xTable = (s16 *)(pageBase - 0x3328);
        pageBase = (u8 *)0x80080000;
        ASM_KEEP_NV(pageBase);
        color = pageBase + 0x2E80;
    }
#endif
    base = objects;
    cur = base;

loop:
        {
            register void *source ASM_REG("$5");
            register u8 *defaultPage ASM_REG("$2");

            if (i != 0) {
                source = objects[0];
                ASM_KEEP_NV(source);
            } else {
#ifdef NON_MATCHING
                source = D_80083498;
#else
                defaultPage = (u8 *)0x80080000;
                ASM_KEEP_NV(defaultPage);
                source = defaultPage + 0x3498;
#endif
                ASM_KEEP_NV(source);
            }
            *cur = func_8003FD64(2, source);
        }

        {
            register u8 *resource ASM_REG("$5");

            partA = D_8002501C;
            ASM_KEEP_NV(partA);
#ifdef NON_MATCHING
            resource = D_800C9034 + 0x6FCC;
#else
            resource = (u8 *)0x800D0000;
#endif
            ASM_KEEP_NV(resource);
            FIELD(*cur, void *, 0x10) = partA;
            func_8004491C(*cur, resource - 0x6FCC);
        }

        tableOff = (wArg >> 8) & 0xE;
        partA = FIELD(*cur, u8 *, 8);
        xDelta = xTable[tableOff / 2] << 5;
        FIELD(partA, s16, 2) = xArg + xDelta;
        ASM_SCHED_BARRIER();
        {
            register s16 *yTable ASM_REG("$2");

#ifdef NON_MATCHING
            yTable = D_8006CCE8;
#else
            yTable = (s16 *)0x80070000;
            ASM_KEEP_NV(yTable);
            yTable = (s16 *)((u8 *)yTable - 0x3318);
#endif
            ASM_KEEP_NV(yTable);
            tableOff = tableOff + (u32)yTable;
            ASM_KEEP_NV(tableOff);
            yDelta = *(s16 *)tableOff << 5;
        }
        FIELD(partA, s16, 0xA) = zArg;
        FIELD(partA, s16, 6) = yArg + yDelta;

        partA = (u8 *)(i << 4);
        partB = FIELD(*cur, u8 *, 0xC);
        FIELD(partB, s16, 0x20) = 0x1000;
        FIELD(partB, s16, 0x1E) = 0x1000;
        FIELD(partB, s16, 0x1C) = 0x1000;
        ASM_SCHED_BARRIER();
        {
            register u8 *spriteTable ASM_REG("$2");

#ifdef NON_MATCHING
            spriteTable = D_800274C0;
#else
            spriteTable = (u8 *)0x80020000;
            ASM_KEEP_NV(spriteTable);
            spriteTable += 0x74C0;
#endif
            ASM_KEEP_NV(spriteTable);
            partA = (u8 *)((u32)partA + (u32)spriteTable);
            ASM_KEEP_NV(partA);
            FIELD(partB, void *, 8) = partA;
        }
        ASM_MEM_BARRIER();
        flags = FIELD(partB, u16, 0x14);
        ASM_SCHED_BARRIER();
        FIELD(partB, s16, 0x10) = 0x20;
        FIELD(partB, s16, 0x16) = 0x400;
        FIELD(partB, s16, 0x1A) = wArg - 0x400;
        FIELD(partB, u16, 0x14) = flags | 0xC;

        {
            register void *tailBase ASM_REG("$2");

            tailBase = *cur;
            ASM_KEEP_NV(tailBase);
            tail = (u8 *)tailBase + 0x20;
        }
        if (i != 0) {
            register u32 linkValue ASM_REG("$2");
            register u8 *linkAddress ASM_REG("$3");

            linkValue = (u32)D_80027580;
            ASM_KEEP_NV(linkValue);
            linkAddress = (u8 *)(i + linkValue);
            ASM_KEEP_NV(linkAddress);
            linkValue = *linkAddress;
            ASM_KEEP_NV(linkValue);
            if (linkValue != 0) {
                linkValue = (u32)base[linkValue - 1] & 0x7FFFFFFF;
            } else {
                linkValue = (u32)cur[-1];
            }
            FIELD(tail, void *, 0x20) = (void *)linkValue;
        }

        FIELD(tail, s16, 0x30) = 4;
        FIELD(tail, s16, 0x36) = 15;
        FIELD(tail, s16, 0x32) = 1;
        FIELD(tail, s16, 0x34) = wArg;
        FIELD(tail, s16, 0x48) = i;
        FIELD(tail, s16, 0x46) = 8;
        firstColor = color[0x24];
        FIELD(tail, s16, 0x3C) = firstColor;
        FIELD(tail, s16, 0x40) = firstColor;
        secondColor = color[0x25];
        ASM_MEM_BARRIER();
        i++;
        FIELD(tail, s16, 0x42) = secondColor;
        FIELD(tail, s16, 0x3E) = secondColor;
        cur++;
        if (i < 12) {
            goto loop;
        }

    return objects[0];
}

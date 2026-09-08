#include "common.h"


typedef struct Obj Obj;

typedef struct S_800255B8_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_800255B8_0;   /* *cur in func_800255B8 */

typedef struct S_800255B8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800255B8_1;   /* partA in func_800255B8 */

typedef struct S_800255B8_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    s16 unk_16;
    u8 pad_18[0x2];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800255B8_2;   /* partB in func_800255B8 */

typedef struct S_800255B8_3 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0xC];
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
    u8 pad_38[0x4];
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
    s16 unk_42;
    u8 pad_44[0x2];
    s16 unk_46;
    s16 unk_48;
} S_800255B8_3;   /* tail in func_800255B8 */


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
    register s32 xArg ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 yArg ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 zArg ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 wArg;
    s32 i;
    void **base;
    register void **cur ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 *xTable;
    register u8 *color;
    u8 *tail;
    register u8 *partA ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *partB;
    u8 firstColor;
    u32 secondColor;
    u32 tableOff;
    s32 xDelta;
    s32 yDelta;
    u16 flags;

    xArg = arg0;
    yArg = arg1;
    zArg = arg2;
    wArg = arg3;
    ASM_KEEP4_NV(xArg, yArg, zArg, wArg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    if (func_8003FA44(12) == 0) {
        return 0;
    }

    i = 0;
#ifdef NON_MATCHING
    xTable = D_8006CCD8;
    color = D_80082E80;
#else
    {
        u8 *pageBase;

        pageBase = (u8 *)0x80070000;
        ASM_KEEP_NV(pageBase);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        xTable = (s16 *)(pageBase - 0x3328);
        pageBase = (u8 *)0x80080000;
        ASM_KEEP_NV(pageBase);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        color = pageBase + 0x2E80;
    }
#endif
    base = objects;
    cur = base;

loop:
        {
            void *source;
            u8 *defaultPage;

            if (i != 0) {
                source = objects[0];
            } else {
#ifdef NON_MATCHING
                source = D_80083498;
#else
                defaultPage = (u8 *)0x80080000;
                ASM_KEEP_NV(defaultPage);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                source = defaultPage + 0x3498;
#endif
            }
            *cur = func_8003FD64(2, source);
        }

        {
            u8 *resource;

            partA = D_8002501C;
#ifdef NON_MATCHING
            resource = D_800C9034 + 0x6FCC;
#else
            resource = (u8 *)0x800D0000;
#endif
            ASM_KEEP_NV(resource);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            ((S_800255B8_0 *)(*cur))->unk_10 = partA;
            func_8004491C(*cur, resource - 0x6FCC);
        }

        tableOff = (wArg >> 8) & 0xE;
        partA = ((S_800255B8_0 *)(*cur))->unk_08;
        xDelta = xTable[tableOff / 2] << 5;
        ((S_800255B8_1 *)partA)->unk_02 = xArg + xDelta;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        {
            s16 *yTable;

#ifdef NON_MATCHING
            yTable = D_8006CCE8;
#else
            yTable = (s16 *)0x80070000;
            ASM_KEEP_NV(yTable);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            yTable = (s16 *)((u8 *)yTable - 0x3318);
#endif
            tableOff = tableOff + (u32)yTable;
            yDelta = *(s16 *)tableOff << 5;
        }
        ((S_800255B8_1 *)partA)->unk_0A = zArg;
        ((S_800255B8_1 *)partA)->unk_06 = yArg + yDelta;

        partA = (u8 *)(i << 4);
        partB = ((S_800255B8_0 *)(*cur))->unk_0C;
        ((S_800255B8_2 *)partB)->unk_20 = 0x1000;
        ((S_800255B8_2 *)partB)->unk_1E = 0x1000;
        ((S_800255B8_2 *)partB)->unk_1C = 0x1000;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        {
            u8 *spriteTable;

#ifdef NON_MATCHING
            spriteTable = D_800274C0;
#else
            spriteTable = (u8 *)0x80020000;
            ASM_KEEP_NV(spriteTable);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            spriteTable += 0x74C0;
#endif
            partA = (u8 *)((u32)partA + (u32)spriteTable);
            ((S_800255B8_2 *)partB)->unk_08 = partA;
        }
        flags = ((S_800255B8_2 *)partB)->unk_14;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        ((S_800255B8_2 *)partB)->unk_10 = 0x20;
        ((S_800255B8_2 *)partB)->unk_16 = 0x400;
        ((S_800255B8_2 *)partB)->unk_1A = wArg - 0x400;
        ((S_800255B8_2 *)partB)->unk_14 = flags | 0xC;

        {
            void *tailBase;

            tailBase = *cur;
            tail = (u8 *)tailBase + 0x20;
        }
        if (i != 0) {
            register u32 linkValue ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            register u8 *linkAddress ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            linkValue = (u32)D_80027580;
            linkAddress = (u8 *)(i + linkValue);
            ASM_KEEP_NV(linkAddress);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            linkValue = *linkAddress;
            ASM_KEEP_NV(linkValue);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if (linkValue != 0) {
                linkValue = (u32)base[linkValue - 1] & 0x7FFFFFFF;
            } else {
                linkValue = (u32)cur[-1];
            }
            ((S_800255B8_3 *)tail)->unk_20 = (void *)linkValue;
        }

        ((S_800255B8_3 *)tail)->unk_30 = 4;
        ((S_800255B8_3 *)tail)->unk_36 = 15;
        ((S_800255B8_3 *)tail)->unk_32 = 1;
        ((S_800255B8_3 *)tail)->unk_34 = wArg;
        ((S_800255B8_3 *)tail)->unk_48 = i;
        ((S_800255B8_3 *)tail)->unk_46 = 8;
        firstColor = color[0x24];
        ((S_800255B8_3 *)tail)->unk_3C = firstColor;
        ((S_800255B8_3 *)tail)->unk_40 = firstColor;
        secondColor = color[0x25];
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        i++;
        ((S_800255B8_3 *)tail)->unk_42 = secondColor;
        ((S_800255B8_3 *)tail)->unk_3E = secondColor;
        cur++;
        if (i < 12) {
            goto loop;
        }

    return objects[0];
}

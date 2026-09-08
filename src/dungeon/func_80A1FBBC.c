#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801733BC_0 {
    u8 pad_00[0xC];
    union { u32 u32; u8 u8; } unk_0C;   /* accessed as both */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    u32 unk_28;
} S_801733BC_0;   /* arg2 in func_801733BC */

typedef struct S_801733BC_1 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xC];
    union { u16 u; s16 s; } unk_A8;   /* accessed as both */
} S_801733BC_1;   /* arg0 in func_801733BC */

typedef struct S_801733BC_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
} S_801733BC_2;   /* object in func_801733BC */

typedef struct S_801733BC_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801733BC_3;   /* arg1 in func_801733BC */

typedef struct S_801733BC_4 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0xC];
    u32 unk_A4;
} S_801733BC_4;   /* effectPart in func_801733BC */

typedef struct S_801733BC_5 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x8];
    u32 unk_28;
} S_801733BC_5;   /* objectPart in func_801733BC */

typedef struct S_801733BC_6 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_801733BC_6;   /* D_80083460 in func_801733BC */


typedef struct S_801733BC_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u16 unk_18;
} S_801733BC_8;   /* projectilePart in func_801733BC */

typedef struct S_801733BC_9 {
    u8 pad_00[0x10];
    union { void * p; u32 i; } unk_10;   /* accessed as both */
} S_801733BC_9;   /* effectList in func_801733BC */

typedef struct S_801733BC_10 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801733BC_10;   /* ((S_801733BC_2 *)object)->unk_08 in func_801733BC */



typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} __attribute__((packed)) Rect;

typedef struct {
    s16 x;
    s16 y;
} Point;

extern s32 D_80045340;
extern s32 D_800814A0;
extern u8 D_80083460[];
extern u8 D_80083498[];
extern Rect D_80170874;
extern u8 D_801740FC[];
extern u8 D_801741A4[];
extern u8 D_80174228[];

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32, s32);
extern s32 func_80069EF8(void);
extern void func_8009A028(void *);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A2FE0(void *);
extern void func_800A32A4(void *);
extern void func_800A56E0(s32);
extern void func_800ACF88(void *);
extern void func_800B8FC8(void *, Rect *, Point *, s32, s32);

void func_801733BC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    Rect rect;
    Point center;
    s32 count;
    void *object;
    void *callback;
    void *effectPart;
    void *objectPart;
    void *projectilePart;
    void *projectileCallback;
    u8 *effectList;
    s32 random;
    u16 value;
    u16 projectileY;
    u16 projectileZ;

    rect = D_80170874;

    if (!(((S_801733BC_0 *)arg2)->unk_14 & 0x8000) &&
        ((S_801733BC_1 *)arg0)->unk_9B == 1) {
        count = 3;
        callback = D_801740FC;
        ((S_801733BC_1 *)arg0)->unk_A8.u += 0x12;
        do {
            object = func_8003FD64(0x112, D_80083498);
            if (object != 0) {
                func_8004491C(object, &D_80045340);
                ((S_801733BC_2 *)object)->unk_10 = callback;

                random = func_80069EF8();
                ((S_801733BC_10 *)(((S_801733BC_2 *)object)->unk_08))->unk_02 =
                    ((S_801733BC_3 *)arg1)->unk_02 + (random & 0x3F) - 0x20;

                random = func_80069EF8();
                ((S_801733BC_10 *)(((S_801733BC_2 *)object)->unk_08))->unk_06 =
                    ((S_801733BC_3 *)arg1)->unk_06 + (random & 0x3F) - 0x20;

                random = func_80069EF8();
                {
                    u32 owner;
                    u16 sourceZ;
                    register u32 effectColor ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                    register u16 flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    u16 flaggedFlags;
                    register u16 size ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    register s32 command ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    register s32 zeroArg ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    u32 objectColor;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    register u16 objectArg ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

                    random %= ((S_801733BC_1 *)arg0)->unk_A8.s + 0x60;
                    effectColor = 0x00040404;
                    objectColor = 0x00500000;
                    sourceZ = ((S_801733BC_3 *)arg1)->unk_0A;
                    objectColor |= 0x5050;
                    ((S_801733BC_10 *)(((S_801733BC_2 *)object)->unk_08))->unk_0A =
                        sourceZ - random - 0x10;

                    effectPart = (u8 *)object + 0x20;
                    ((S_801733BC_4 *)effectPart)->unk_A4 = effectColor;
                    ((S_801733BC_4 *)effectPart)->unk_96 = 6;

                    objectPart = ((S_801733BC_2 *)object)->unk_0C;
                    owner = ((S_801733BC_0 *)arg2)->unk_28;
                    command = 0x2E;
                    ((S_801733BC_5 *)objectPart)->unk_28 = owner;
                    ((S_801733BC_5 *)objectPart)->unk_1E = 0x1000;
                    ((S_801733BC_5 *)objectPart)->unk_1C = 0x1000;
                    flags = ((S_801733BC_0 *)arg2)->unk_14;
                    zeroArg = 0;
                    ((S_801733BC_5 *)objectPart)->unk_14 = flags;
                    ASM_USE(flags);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    flaggedFlags = flags;
                    size = 0x20;
                    objectArg = ((S_801733BC_0 *)arg2)->unk_12;
                    flaggedFlags |= 0xC;
                    ((S_801733BC_5 *)objectPart)->unk_10 = size;
                    ((S_801733BC_5 *)objectPart)->unk_0C = objectColor;
                    ((S_801733BC_5 *)objectPart)->unk_14 = flaggedFlags;
                    ((S_801733BC_5 *)objectPart)->unk_12 = objectArg;
                    func_80047784(objectPart, command, zeroArg, objectArg);
                }
            }
            count--;
        } while (count >= 0);
    }

    switch (((S_801733BC_1 *)arg0)->unk_9B) {
    case 0:
        if (((S_801733BC_6 *)D_80083460)->unk_0A != 0) {
            break;
        }
        if (((Rec_D_80082E80 *)arg3)->unk_14.at00_u32.v & 0x4000) {
            if (!(((Rec_D_80082E80 *)arg3)->unk_14.at00_u32.v & 0x20000000)) {
                func_800ACF88(arg3);
            }
        }
        ((S_801733BC_1 *)arg0)->unk_9B++;
        /* fallthrough */
    case 1:
        if (!(((S_801733BC_0 *)arg2)->unk_14 & 0xE000)) {
            break;
        }
        ((S_801733BC_1 *)arg0)->unk_A8.u = 0;
        {
            register void *centerCallObject ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            Rect *rectArg;
            Point *centerArg;
            s16 centerY;

            centerCallObject = arg0;
            rectArg = &rect;
            centerArg = &center;
            ASM_USE(centerArg);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            center.x = rect.x + ((s16)rect.w >> 1);
            centerY = rect.y + ((s16)rect.h >> 1);
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            center.y = centerY;
            func_800B8FC8(centerCallObject, rectArg, centerArg, 1, 0);
        }

        ((Rec_D_80082E80 *)arg3)->unk_1C.at00_u32.v |= 0x10000000;
        ((S_801733BC_0 *)arg2)->unk_10 = 0x60;
        ((S_801733BC_0 *)arg2)->unk_0C.u32 = 0x00C0C0C0;
        ((S_801733BC_0 *)arg2)->unk_14 |= 0xC;
        ((S_801733BC_0 *)arg2)->unk_12 -= 0x80;
        ((S_801733BC_1 *)arg0)->unk_9B++;
        func_800A56E0(0x806);

        object = func_8003FD64(0x12, D_80083498);
        if (object == 0) {
            break;
        }
        func_8004491C(object, D_80174228);
        projectileCallback = D_801741A4;
        ASM_KEEP(projectileCallback);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_801733BC_2 *)object)->unk_10 = projectileCallback;
        ((S_801733BC_2 *)object)->unk_20 = ((S_801733BC_3 *)arg1)->unk_02;
        projectileY = ((S_801733BC_3 *)arg1)->unk_06;
        projectilePart = (u8 *)object + 0x20;
        ((S_801733BC_8 *)projectilePart)->unk_02 = projectileY;
        projectileZ = ((S_801733BC_3 *)arg1)->unk_0A;
        ((S_801733BC_8 *)projectilePart)->unk_10 = 0xFFFC0000;
        ((S_801733BC_8 *)projectilePart)->unk_0C = 0;
        ((S_801733BC_8 *)projectilePart)->unk_14 = 0xFFFE8000;
        ((S_801733BC_8 *)projectilePart)->unk_18 = 0x14;
        ((S_801733BC_8 *)projectilePart)->unk_08 = 0;
        ((S_801733BC_8 *)projectilePart)->unk_04 = projectileZ;
        break;

    case 2:
        ((Rec_D_80082E80 *)arg3)->unk_1C.at00_u32.v |= 0x10000000;
        ((S_801733BC_0 *)arg2)->unk_0C.u32 += 0xFFEFEFF0;
        if (((S_801733BC_0 *)arg2)->unk_0C.u8 < 0x11) {
            ((S_801733BC_1 *)arg0)->unk_96 = 10;
            ((S_801733BC_1 *)arg0)->unk_9B++;
        }
        break;

    case 3:
        value = ((S_801733BC_1 *)arg0)->unk_96 - 1;
        ((S_801733BC_1 *)arg0)->unk_96 = value;
        if ((s16)value > 0) {
            break;
        }
        effectList = D_80083460;
        if (((S_801733BC_9 *)effectList)->unk_10.p == (u8 *)arg3 - 0x20) {
            ((S_801733BC_9 *)effectList)->unk_10.i &= 0x7FFFFFFF;
        }
        func_800A2FE0(arg3);
        func_800A32A4(arg3);
        func_8009A3D0(((S_801733BC_0 *)arg2)->unk_24, ((S_801733BC_0 *)arg2)->unk_25,
            (((Rec_D_80082E80 *)arg3)->unk_1C.at00_u32.v & 0x2000) ? 0x300 : 0x3000);
        func_8009A028(arg3);
        (*(u16 *)((u8 *)arg3 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    }
}

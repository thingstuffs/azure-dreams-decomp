#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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

    if (!(FIELD(arg2, u16, 0x14) & 0x8000) &&
        FIELD(arg0, u8, 0x9B) == 1) {
        count = 3;
        callback = D_801740FC;
        FIELD(arg0, u16, 0xA8) += 0x12;
        do {
            object = func_8003FD64(0x112, D_80083498);
            if (object != 0) {
                func_8004491C(object, &D_80045340);
                FIELD(object, void *, 0x10) = callback;

                random = func_80069EF8();
                FIELD(FIELD(object, void *, 8), u16, 2) =
                    FIELD(arg1, u16, 2) + (random & 0x3F) - 0x20;

                random = func_80069EF8();
                FIELD(FIELD(object, void *, 8), u16, 6) =
                    FIELD(arg1, u16, 6) + (random & 0x3F) - 0x20;

                random = func_80069EF8();
                {
                    u32 owner;
                    u16 sourceZ;
                    register u32 effectColor ASM_REG("$4");
                    register u16 flags ASM_REG("$2");
                    register u16 flaggedFlags ASM_REG("$3");
                    register u16 size ASM_REG("$2");
                    register s32 command ASM_REG("$5");
                    register s32 zeroArg ASM_REG("$6");
                    register u32 objectColor ASM_REG("$8");
                    register u16 objectArg ASM_REG("$7");

                    random %= FIELD(arg0, s16, 0xA8) + 0x60;
                    ASM_SCHED_BARRIER();
                    effectColor = 0x00040404;
                    objectColor = 0x00500000;
                    sourceZ = FIELD(arg1, u16, 0xA);
                    ASM_USE(objectColor);
                    objectColor |= 0x5050;
                    ASM_SCHED_BARRIER();
                    FIELD(FIELD(object, void *, 8), u16, 0xA) =
                        sourceZ - random - 0x10;

                    effectPart = (u8 *)object + 0x20;
                    FIELD(effectPart, u32, 0xA4) = effectColor;
                    FIELD(effectPart, u16, 0x96) = 6;

                    objectPart = FIELD(object, void *, 0xC);
                    owner = FIELD(arg2, u32, 0x28);
                    ASM_USE2(objectPart, owner);
                    command = 0x2E;
                    ASM_USE(command);
                    FIELD(objectPart, u32, 0x28) = owner;
                    FIELD(objectPart, u16, 0x1E) = 0x1000;
                    FIELD(objectPart, u16, 0x1C) = 0x1000;
                    flags = FIELD(arg2, u16, 0x14);
                    ASM_USE(flags);
                    zeroArg = 0;
                    ASM_USE(zeroArg);
                    FIELD(objectPart, u16, 0x14) = flags;
                    ASM_USE(flags);
                    flaggedFlags = flags;
                    ASM_USE(flaggedFlags);
                    size = 0x20;
                    objectArg = FIELD(arg2, u16, 0x12);
                    ASM_USE2(size, objectArg);
                    flaggedFlags |= 0xC;
                    ASM_USE(flaggedFlags);
                    FIELD(objectPart, u16, 0x10) = size;
                    FIELD(objectPart, u32, 0xC) = objectColor;
                    FIELD(objectPart, u16, 0x14) = flaggedFlags;
                    ASM_SCHED_BARRIER();
                    FIELD(objectPart, u16, 0x12) = objectArg;
                    func_80047784(objectPart, command, zeroArg, objectArg);
                }
            }
            count--;
        } while (count >= 0);
    }

    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
        if (FIELD(D_80083460, s16, 0xA) != 0) {
            break;
        }
        if (FIELD(arg3, u32, 0x14) & 0x4000) {
            if (!(FIELD(arg3, u32, 0x14) & 0x20000000)) {
                func_800ACF88(arg3);
            }
        }
        FIELD(arg0, u8, 0x9B)++;
        /* fallthrough */
    case 1:
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            break;
        }
        FIELD(arg0, u16, 0xA8) = 0;
        {
            register void *centerCallObject ASM_REG("$4");
            Rect *rectArg;
            Point *centerArg;
            s16 centerY;

            centerCallObject = arg0;
            rectArg = &rect;
            centerArg = &center;
            ASM_USE2(centerCallObject, rectArg);
            ASM_USE(centerArg);
            center.x = rect.x + ((s16)rect.w >> 1);
            centerY = rect.y + ((s16)rect.h >> 1);
            ASM_SCHED_BARRIER();
            center.y = centerY;
            func_800B8FC8(centerCallObject, rectArg, centerArg, 1, 0);
        }

        FIELD(arg3, u32, 0x1C) |= 0x10000000;
        FIELD(arg2, u16, 0x10) = 0x60;
        FIELD(arg2, u32, 0xC) = 0x00C0C0C0;
        FIELD(arg2, u16, 0x14) |= 0xC;
        FIELD(arg2, u16, 0x12) -= 0x80;
        FIELD(arg0, u8, 0x9B)++;
        func_800A56E0(0x806);

        object = func_8003FD64(0x12, D_80083498);
        if (object == 0) {
            break;
        }
        func_8004491C(object, D_80174228);
        projectileCallback = D_801741A4;
        ASM_KEEP(projectileCallback);
        FIELD(object, void *, 0x10) = projectileCallback;
        FIELD(object, u16, 0x20) = FIELD(arg1, u16, 2);
        projectileY = FIELD(arg1, u16, 6);
        projectilePart = (u8 *)object + 0x20;
        FIELD(projectilePart, u16, 2) = projectileY;
        projectileZ = FIELD(arg1, u16, 0xA);
        FIELD(projectilePart, u32, 0x10) = 0xFFFC0000;
        FIELD(projectilePart, u32, 0xC) = 0;
        FIELD(projectilePart, u32, 0x14) = 0xFFFE8000;
        FIELD(projectilePart, u16, 0x18) = 0x14;
        FIELD(projectilePart, u32, 8) = 0;
        FIELD(projectilePart, u16, 4) = projectileZ;
        break;

    case 2:
        FIELD(arg3, u32, 0x1C) |= 0x10000000;
        FIELD(arg2, u32, 0xC) += 0xFFEFEFF0;
        if (FIELD(arg2, u8, 0xC) < 0x11) {
            FIELD(arg0, u16, 0x96) = 10;
            FIELD(arg0, u8, 0x9B)++;
        }
        break;

    case 3:
        value = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = value;
        if ((s16)value > 0) {
            break;
        }
        effectList = D_80083460;
        if (FIELD(effectList, void *, 0x10) == (u8 *)arg3 - 0x20) {
            FIELD(effectList, u32, 0x10) &= 0x7FFFFFFF;
        }
        func_800A2FE0(arg3);
        func_800A32A4(arg3);
        func_8009A3D0(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            (FIELD(arg3, u32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
        func_8009A028(arg3);
        FIELD(arg3, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    }
}

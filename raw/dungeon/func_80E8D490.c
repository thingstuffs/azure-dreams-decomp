#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    u8 pad[0x12];
    u8 type;
    u8 pad13;
} LookupEntry;

extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern s32 func_800A94A0(void *, void *, s32, void *);
extern void func_800A56E0(s32);
extern void func_800DB2DC(void *, void *, void *, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern s32 func_8003F270(void);
extern void func_80047784(void *, u8, s32);
extern void func_80172DDC(void) __attribute__((noreturn));
extern void func_80172DE4(void) __attribute__((noreturn));
extern void func_80172DEC(void) __attribute__((noreturn));
extern void func_80172DF8(void) __attribute__((noreturn));
extern void func_80172E6C(void) __attribute__((noreturn));
extern void func_80172ED0(void) __attribute__((noreturn));
extern void func_801731D8(void) __attribute__((noreturn));
extern void func_8017328C(void) __attribute__((noreturn));
extern void func_801733F0(void) __attribute__((noreturn));

extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern LookupEntry D_8006DE24[];
extern void *D_800814A8[];
extern s16 D_80083228[5];
extern u8 D_80083460[];
extern s32 D_8008346C[3];
extern u8 D_80170838[0x44];
extern u8 D_80170880[0x1C];
extern u8 D_801710F4[];
extern u8 D_80174EF8[];
extern u8 D_80174F00[];

void func_80172C90(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register u32 directionOffset ASM_REG("$4");
    register u16 angle ASM_REG("$2");
    register s16 *directionXBase ASM_REG("$3");
    s32 directionX;
    s32 directionY;
    u16 timer;
    u32 state;
    register u8 *selector ASM_REG("$16");
    register s32 special ASM_REG("$21");
    u16 position[3];
    static void *const keepalive[] = {
        &&L0, &&L1, &&L2, &&L3, &&L4, &&L5, &&L6, &&L16,
        &&I1, &&I2, &&I3, &&I4, &&I5, &&I6, &&I7
    };

    ASM_KEEP4_NV(arg0, arg1, arg2, arg3);
    ASM_KEEP_DEP_NV(special, arg3);
    directionXBase = D_8006CCD8;
    angle = FIELD(arg3, u16, 0x2A);
    directionOffset = angle >> 8;
    ASM_USE2_NV(angle, special);
    directionOffset &= 0xE;
    directionX = *(s16 *)((u8 *)directionXBase + directionOffset);
    directionY = *(s16 *)((u8 *)D_8006CCE8 + directionOffset);
    timer = FIELD(arg0, u16, 0x96);
    state = FIELD(arg0, u8, 0x9B);
    FIELD(arg0, u16, 0x96) = timer - 1;
    special = 0;
    if ((u32)state >= 17U) {
        return;
    }
    goto *(((void **)D_80170838)[state]);

L0:
    FIELD(arg0, u16, 0xAC) = FIELD(arg1, u16, 0xA);
    if (FIELD(arg3, u32, 0x1C) & 0x2000) {
        u16 tableKind;
        u32 tableIndex;

        tableKind = FIELD(arg3, u16, 0x46) & 0x3FFF;
        tableIndex = tableKind - 1;
        if (tableIndex >= 7U) {
            goto I4;
        }
        goto *(((void **)D_80170880)[tableIndex]);
    }
    goto IDirect;

I7:
    special = 1;
    ASM_TAILSLOT_PIN(special);
    func_80172DDC();
I6:
    special = 1;
    ASM_TAILSLOT_PIN(special);
    func_80172DE4();
I5:
    special = 1;
    ASM_TAILSLOT_PIN(special);
    func_80172DEC();

IDirect:
    {
    u16 directKind;

    directKind = FIELD(arg3, u16, 0x46) & 0x3FFF;
    switch (directKind) {
    case 1:
        goto I1;
    case 2:
        goto I2;
    case 3:
        goto I3;
    default:
        selector = 0;
        goto IEnd;
    }
    }

I3:
    selector = (u8 *)arg3 + 0xE;
    ASM_TAILSLOT_PIN(selector);
    func_80172DF8();
I2:
    selector = (u8 *)arg3 + 0xB;
    ASM_TAILSLOT_PIN(selector);
    func_80172DF8();
I1:
    selector = (u8 *)arg3 + 8;
    ASM_TAILSLOT_PIN(selector);
    func_80172DF8();
I4:
    selector = 0;

IEnd:
    if (*selector != 0) {
        void *localOwner;
        register void *localLinked ASM_REG("$3");
        s32 specialCheck;
        s32 moveResult;

        FIELD(arg0, u16, 0x98) &= 0xFF7F;
        specialCheck = special;
        ASM_KEEP_NV(specialCheck);
        if (specialCheck) {
            localOwner = D_800814A8[0];
            FIELD(arg3, void *, 0x60) = localOwner;
            func_80172E6C();
        }
        ASM_SCHED_BARRIER();
        if (D_8006DE24[*selector].type == 2) {
            localOwner = FIELD(arg3, void *, 0x60);
            if (localOwner != 0) {
                localLinked = FIELD(localOwner, void *, -0x14);
                FIELD(arg3, u8, 0x72) = FIELD(localLinked, u8, 0x24);
                FIELD(arg3, u8, 0x73) = FIELD(localLinked, u8, 0x25);
                func_80172ED0();
            }
        } else {
            s32 deltaX;
            s32 deltaY;

            FIELD(arg3, void *, 0x60) = func_800A05A4(arg3,
                FIELD(arg2, u8, 0x24),
                FIELD(arg2, u8, 0x25),
                FIELD(arg3, s16, 0x2A), 16);
            ASM_MEM_BARRIER();
            deltaX = FIELD(arg3, s8, 0x72);
            deltaY = FIELD(arg3, s8, 0x73);
            if (deltaX < 0) {
                deltaX = -deltaX;
            }
            if (deltaY < 0) {
                deltaY = -deltaY;
            }
            FIELD(arg3, s8, 0x72) = deltaX;
            FIELD(arg3, s8, 0x73) = deltaY;
            ASM_MEM_BARRIER();
            {
                register void *edgeActor ASM_REG("$4");

                edgeActor = arg3;
                ASM_USE_NV(edgeActor);
            }
        }

        {
            register void *finalActor ASM_REG("$4");

            finalActor = arg3;
            ASM_UNDEF(finalActor);
            position[0] = FIELD(arg1, u16, 2);
            position[1] = FIELD(arg1, u16, 6);
            position[2] = FIELD(arg1, u16, 0xA);
            moveResult = func_800A94A0(finalActor, selector, special,
                                      (u8 *)arg0 + 0x98);
        }
        ASM_MEM_BARRIER();
        if (!moveResult) {
            return;
        }
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        func_800A56E0(0x703);
        func_800DB2DC(arg1, arg2, arg3, 10);
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, u16, 0x96) = 2;
        FIELD(arg0, u16, 0x98) |= 8;
        {
            s32 negativeX;
            s32 negativeY;

            negativeX = -directionX;
            negativeY = -directionY;
            FIELD(arg1, s32, 0xC) =
                (negativeX << 18) + (negativeX << 19);
            FIELD(arg1, s32, 0x10) =
                (negativeY << 18) + (negativeY << 19);
        }
        FIELD(arg1, s32, 0x14) = (s32)0xFFF30000;
        {
            register s32 tail_state ASM_REG("$2");

            tail_state = FIELD(arg0, u8, 0x9B) + 1;
            ASM_TAILSLOT_PIN(tail_state);
            func_8017328C();
        }
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    {
        void *localOwner;

        localOwner = D_800814A8[0];
        D_8008346C[0] = 0;
        FIELD(localOwner, u16, 0xA6)--;
    }
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, u8 *, 0x8C) = D_801710F4;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_801733F0();

L1:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 16;
        FIELD(arg0, u16, 0x98) |= 0x80;
        func_801733F0();
    }
    if (FIELD(arg0, s16, 0x96) <= 0) {
        FIELD(arg1, volatile s32, 0xC) = 0;
        FIELD(arg1, s32, 0xC) = directionX << 18;
        FIELD(arg1, volatile s32, 0x10) = 0;
        FIELD(arg1, s32, 0x10) = directionY << 18;
        FIELD(arg1, volatile s32, 0x14) = 0;
        FIELD(arg1, s32, 0x14) = (s32)0xFFF30000;
        {
            register s32 tail_state ASM_REG("$2");

            tail_state = FIELD(arg0, u8, 0x9B) + 1;
            ASM_TAILSLOT_PIN(tail_state);
            func_8017328C();
        }
    }
    FIELD(arg1, s32, 0xC) *= 2;
    FIELD(arg1, s32, 0x10) *= 2;
    func_801733F0();

L2:
    if (func_8003F270()) {
        FIELD(arg2, u16, 0x14) |= 0x0800;
        func_801733F0();
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;

L3:
    FIELD(arg1, s32, 0x14) += 0x30000;
    if (FIELD(arg2, s8, 4) == 4) {
        if (FIELD(arg2, u16, 0x14) & 0x1000) {
            goto L3Activate;
        }
    }
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
L3Activate:
    {
        register u16 tail_flags ASM_REG("$2");
        register u8 tail_state ASM_REG("$3");

        FIELD(arg1, s32, 0xC) = directionX << 19;
        FIELD(arg1, s32, 0x10) = directionY << 19;
        tail_flags = FIELD(arg0, u16, 0x98);
        tail_state = FIELD(arg0, u8, 0x9B);
        tail_flags |= 0x80;
        ASM_KEEP(tail_state);
        ASM_TAILSLOT_PIN(tail_flags);
        func_801731D8();
    }

L4:
    FIELD(arg1, s32, 0x14) += 0x20000;
    if (FIELD(arg3, u32, 0x1C) & 0x08000000) {
        if (FIELD(arg1, s16, 0xA) <= FIELD(arg0, s16, 0xAC)) {
            goto L4Activate;
        }
    }
    if (FIELD(arg1, s16, 0xA) <= FIELD(arg0, s16, 0xAC)) {
        return;
    }
L4Activate:
    {
    u8 *effect;

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    FIELD(arg0, u16, 0x96) = 4;
    FIELD(arg2, u16, 0x1C) = 0x1400;
    FIELD(arg2, u16, 0x1E) = 0x0C00;
    effect = D_80174F00;
    FIELD(arg2, u8 *, 0x2C) = effect;
    func_80047784(arg2,
        effect[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg0, u8, 0x9B)++;
    func_801733F0();
    }

L5:
    {
        register s32 squareInput ASM_REG("$2");
        s32 square;

        squareInput = FIELD(arg0, s16, 0x96);
        square = squareInput * squareInput;
        ASM_USE_NV(squareInput);
        FIELD(arg2, u16, 0x1C) = 0x1000 + square * 300;
        ASM_MEM_BARRIER();
        FIELD(arg2, u16, 0x1E) = 0x1000 - square * 200;
    }
    if (FIELD(arg0, s16, 0x96) > 0) {
        return;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80174EF8;
    func_80047784(arg2,
        D_80174EF8[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x96) = 10;
    FIELD(arg0, u8, 0x9B)++;
    func_801733F0();

L6:
    {
        s32 rawCoordinate;
        s32 targetCoordinate;
        s32 currentCoordinate;

        rawCoordinate = FIELD(arg2, u8, 0x24);
        ASM_SCHED_BARRIER();
        currentCoordinate = FIELD(arg1, s16, 2);
        targetCoordinate = rawCoordinate << 6;
        ASM_USE_NV(targetCoordinate);
        currentCoordinate -= 0x20;
        ASM_USE_NV(currentCoordinate);
        FIELD(arg1, s32, 0xC) =
            (targetCoordinate - currentCoordinate) << 14;
    }
    {
        s32 rawCoordinate;
        s32 targetCoordinate;
        s32 currentCoordinate;

        rawCoordinate = FIELD(arg2, u8, 0x25);
        ASM_SCHED_BARRIER();
        currentCoordinate = FIELD(arg1, s16, 6);
        targetCoordinate = rawCoordinate << 6;
        ASM_USE_NV(targetCoordinate);
        currentCoordinate -= 0x20;
        ASM_USE_NV(currentCoordinate);
        FIELD(arg1, s32, 0x10) =
            (targetCoordinate - currentCoordinate) << 14;
    }
    if (FIELD(arg0, s16, 0x96) > 0) {
        return;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    FIELD(arg2, u16, 0x14) |= 0x6000;
    FIELD(arg0, u8, 0x9B) = 16;
    func_801733F0();

L16:
    {
    u8 *counter;

    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    if (FIELD(arg2, u8 *, 0x2C) != D_80174F00) {
        FIELD(arg2, u8 *, 0x2C) = D_80174F00;
        func_80047784(arg2,
            D_80174F00[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
    counter = D_80083460;
    if (FIELD(counter, s32, 0xC) != 0) {
        return;
    }
    FIELD(counter, u16, 0xA)--;
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8 *, 0x8C) = D_801710F4;
    func_800A4ACC(arg3);
    if (FIELD(arg3, s8, 0x6D) > 0) {
        FIELD(arg3, u8, 0x6D)--;
    }
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_800A56E0(0xB4);
    }
}

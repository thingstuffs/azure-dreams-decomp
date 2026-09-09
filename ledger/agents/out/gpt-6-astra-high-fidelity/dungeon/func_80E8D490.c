#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172C90_0 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    union { u8 s; s8 u; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80172C90_0;   /* arg3 in func_80172C90 */

typedef struct S_80172C90_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x10];
    union { u16 s; s16 u; } unk_AC;   /* accessed as both */
} S_80172C90_1;   /* arg0 in func_80172C90 */

typedef struct S_80172C90_2 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    union { s32 s; volatile s32 u; } unk_0C;   /* accessed as both */
    union { s32 s; volatile s32 u; } unk_10;   /* accessed as both */
    union { s32 s; volatile s32 u; } unk_14;   /* accessed as both */
} S_80172C90_2;   /* arg1 in func_80172C90 */

typedef struct S_80172C90_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172C90_3_pre;   /* the 0x14 bytes before localOwner in func_80172C90, addressed as localOwner[-1] */

typedef struct S_80172C90_3 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_80172C90_3;   /* localOwner in func_80172C90 */

typedef struct S_80172C90_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172C90_4;   /* localLinked in func_80172C90 */


typedef struct S_80172C90_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172C90_6;   /* counter in func_80172C90 */



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

void func_80172C90(void *arg0, S_80172C90_2 *arg1, Rec_D_80082E80 *arg2, void *arg3)
{
    u32 directionOffset;
    u16 angle;
    s16 *directionXBase;
    s32 directionX;
    s32 directionY;
    u16 timer;
    u32 state;
    register u8 *selector ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 special;
    register s32 tail_state ASM_REG("$2"); /* MATCH: the shared state store receives its value in v0. */
    u16 position[3];
    static void *const keepalive[] = {
        &&L0, &&L1, &&L2, &&L3, &&L4, &&L5, &&L6, &&L16,
        &&I1, &&I2, &&I3, &&I4, &&I5, &&I6, &&I7
    };

    ASM_KEEP4_NV(arg0, arg1, arg2, arg3);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_DEP_NV(special, arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    directionXBase = D_8006CCD8;
    angle = ((S_80172C90_0 *)arg3)->unk_2A.s;
    directionOffset = angle >> 8;
    ASM_USE2_NV(angle, special);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    directionOffset &= 0xE;
    directionX = *(s16 *)((u8 *)directionXBase + directionOffset);
    directionY = *(s16 *)((u8 *)D_8006CCE8 + directionOffset);
    timer = ((S_80172C90_1 *)arg0)->unk_96.s;
    state = ((S_80172C90_1 *)arg0)->unk_9B;
    ((S_80172C90_1 *)arg0)->unk_96.s = timer - 1;
    special = 0;
    if ((u32)state >= 17U) {
        return;
    }
    goto *(((void **)D_80170838)[state]);

L0:
    ((S_80172C90_1 *)arg0)->unk_AC.s = arg1->unk_0A.s;
    if (((S_80172C90_0 *)arg3)->unk_1C & 0x2000) {
        u16 tableKind;
        u32 tableIndex;

        tableKind = ((S_80172C90_0 *)arg3)->unk_46 & 0x3FFF;
        tableIndex = tableKind - 1;
        if (tableIndex >= 7U) {
            goto I4;
        }
        goto *(((void **)D_80170880)[tableIndex]);
    }
    goto IDirect;

I7:
    special = 1;
    goto I3;
I6:
    special = 1;
    goto I2;
I5:
    special = 1;
    goto I1;

IDirect:
    {
    u16 directKind;

    directKind = ((S_80172C90_0 *)arg3)->unk_46 & 0x3FFF;
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
    goto IEnd;
I2:
    selector = (u8 *)arg3 + 0xB;
    goto IEnd;
I1:
    selector = (u8 *)arg3 + 8;
    goto IEnd;
I4:
    selector = 0;

IEnd:
    if (*selector != 0) {
        void *localOwner;
        register void *localLinked ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 specialCheck;
        s32 moveResult;

        ((S_80172C90_1 *)arg0)->unk_98 &= 0xFF7F;
        specialCheck = special;
        ASM_KEEP_NV(specialCheck);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        if (specialCheck) {
            localOwner = D_800814A8[0];
            ((S_80172C90_0 *)arg3)->unk_60 = localOwner;
            goto OwnerLinked;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        if (D_8006DE24[*selector].type == 2) {
            localOwner = ((S_80172C90_0 *)arg3)->unk_60;
            if (localOwner != 0) {
OwnerLinked:
                localLinked = ((S_80172C90_3_pre *)localOwner)[-1].unk_00;
                ((S_80172C90_0 *)arg3)->unk_72.s = ((S_80172C90_4 *)localLinked)->unk_24;
                ((S_80172C90_0 *)arg3)->unk_73.s = ((S_80172C90_4 *)localLinked)->unk_25;
                goto OwnerDone;
            }
        } else {
            s32 deltaX;
            s32 deltaY;

            ((S_80172C90_0 *)arg3)->unk_60 = func_800A05A4(arg3,
                arg2->unk_24,
                arg2->unk_25,
                ((S_80172C90_0 *)arg3)->unk_2A.u, 16);
            ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            deltaX = ((S_80172C90_0 *)arg3)->unk_72.u;
            deltaY = ((S_80172C90_0 *)arg3)->unk_73.u;
            if (deltaX < 0) {
                deltaX = -deltaX;
            }
            if (deltaY < 0) {
                deltaY = -deltaY;
            }
            ((S_80172C90_0 *)arg3)->unk_72.u = deltaX;
            ((S_80172C90_0 *)arg3)->unk_73.u = deltaY;
            ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
OwnerDone:
            {
                register void *edgeActor ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */

                edgeActor = arg3;
                ASM_USE_NV(edgeActor);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            }
        }

        {
            void *finalActor;

            finalActor = arg3;
            ASM_UNDEF(finalActor);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            position[0] = arg1->unk_02.s;
            position[1] = arg1->unk_06.s;
            position[2] = arg1->unk_0A.s;
            moveResult = func_800A94A0(finalActor, selector, special,
                                      (u8 *)arg0 + 0x98);
        }
        if (!moveResult) {
            return;
        }
        arg2->unk_14.at00_u16.v &= 0xF7FF;
        func_800A56E0(0x703);
        func_800DB2DC(arg1, arg2, arg3, 10);
        ((S_80172C90_1 *)arg0)->unk_90 = 0;
        ((S_80172C90_1 *)arg0)->unk_96.s = 2;
        ((S_80172C90_1 *)arg0)->unk_98 |= 8;
        {
            s32 negativeX;
            s32 negativeY;

            negativeX = -directionX;
            negativeY = -directionY;
            arg1->unk_0C.s =
                (negativeX << 18) + (negativeX << 19);
            arg1->unk_10.s =
                (negativeY << 18) + (negativeY << 19);
        }
        arg1->unk_14.s = (s32)0xFFF30000;
        {
            tail_state = ((S_80172C90_1 *)arg0)->unk_9B;
            ASM_SCHED_BARRIER(); /* MATCH: retain separate state loads for L0 and L1. */
            tail_state++;
            goto StoreState;
        }
    }

    arg1->unk_14.s = 0;
    arg1->unk_10.s = 0;
    arg1->unk_0C.s = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
    {
        void *localOwner;

        localOwner = D_800814A8[0];
        D_8008346C[0] = 0;
        ((S_80172C90_3 *)localOwner)->unk_A6--;
    }
    func_800A4ACC(arg3);
    ((S_80172C90_0 *)arg3)->unk_6D.s--;
    ((S_80172C90_1 *)arg0)->unk_8C = D_801710F4;
    ((S_80172C90_0 *)arg3)->unk_73.s = 0;
    ((S_80172C90_0 *)arg3)->unk_72.s = 0;
    ((S_80172C90_0 *)arg3)->unk_46 &= 0x7FFF;
    return;

L1:
    if (arg2->unk_14.at00_u16.v & 0x8000) {
        ((S_80172C90_1 *)arg0)->unk_9B = 16;
        ((S_80172C90_1 *)arg0)->unk_98 |= 0x80;
        return;
    }
    if (((S_80172C90_1 *)arg0)->unk_96.u <= 0) {
        arg1->unk_0C.u = 0;
        arg1->unk_0C.s = directionX << 18;
        arg1->unk_10.u = 0;
        arg1->unk_10.s = directionY << 18;
        arg1->unk_14.u = 0;
        arg1->unk_14.s = (s32)0xFFF30000;
        {
            tail_state = ((S_80172C90_1 *)arg0)->unk_9B + 1;
            goto StoreState;
        }
    }
    arg1->unk_0C.s *= 2;
    arg1->unk_10.s *= 2;
    return;

L2:
    if (func_8003F270()) {
        arg2->unk_14.at00_u16.v |= 0x0800;
        return;
    }
    arg2->unk_14.at00_u16.v &= 0xF7FF;
    ((S_80172C90_1 *)arg0)->unk_9B++;

L3:
    arg1->unk_14.s += 0x30000;
    if (arg2->unk_04.as_s8 == 4) {
        if (arg2->unk_14.at00_u16.v & 0x1000) {
            goto L3Activate;
        }
    }
    if (!(arg2->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
L3Activate:
    {
        u16 tail_flags;
        register u8 tail_state ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        arg1->unk_0C.s = directionX << 19;
        arg1->unk_10.s = directionY << 19;
        tail_flags = ((S_80172C90_1 *)arg0)->unk_98;
        tail_state = ((S_80172C90_1 *)arg0)->unk_9B;
        tail_flags |= 0x80;
        goto UpdateFlags;

L4:
    arg1->unk_14.s += 0x20000;
    if (((S_80172C90_0 *)arg3)->unk_1C & 0x08000000) {
        if (arg1->unk_0A.u <= ((S_80172C90_1 *)arg0)->unk_AC.u) {
            goto L4Activate;
        }
    }
    if (arg1->unk_0A.u <= ((S_80172C90_1 *)arg0)->unk_AC.u) {
        return;
    }
L4Activate:
    {
    u8 *effect;

    arg1->unk_14.s = 0;
    arg1->unk_10.s = 0;
    arg1->unk_0C.s = 0;
    ((S_80172C90_1 *)arg0)->unk_96.s = 4;
    arg2->unk_1C.at00_u16.v = 0x1400;
    arg2->unk_1C.at02_u16.v = 0x0C00;
    effect = D_80174F00;
    arg2->unk_2C.as_pu8 = effect;
    func_80047784(arg2,
        effect[((D_80083228[0] + ((S_80172C90_0 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    tail_flags = ((S_80172C90_1 *)arg0)->unk_98;
    tail_state = ((S_80172C90_1 *)arg0)->unk_9B;
    tail_flags &= 0xFFF7;
UpdateFlags:
    ASM_SCHED_BARRIER(); /* MATCH: keep the state increment in the shared flags tail. */
    tail_state++;
    ((S_80172C90_1 *)arg0)->unk_98 = tail_flags;
    ((S_80172C90_1 *)arg0)->unk_9B = tail_state;
    return;
    }
    }

L5:
    {
        s32 squareInput;
        s32 square;

        squareInput = ((S_80172C90_1 *)arg0)->unk_96.u;
        square = squareInput * squareInput;
        ASM_USE_NV(squareInput);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        arg2->unk_1C.at00_u16.v = 0x1000 + square * 300;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        arg2->unk_1C.at02_u16.v = 0x1000 - square * 200;
    }
    if (((S_80172C90_1 *)arg0)->unk_96.u > 0) {
        return;
    }
    arg2->unk_2C.as_pu8 = D_80174EF8;
    func_80047784(arg2,
        D_80174EF8[((D_80083228[0] + ((S_80172C90_0 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    ((S_80172C90_1 *)arg0)->unk_96.s = 10;
    tail_state = ((S_80172C90_1 *)arg0)->unk_9B + 1;
StoreState:
    ASM_SCHED_BARRIER(); /* MATCH: keep the state store at the shared L5 tail. */
    ((S_80172C90_1 *)arg0)->unk_9B = tail_state;
    return;

L6:
    {
        s32 rawCoordinate;
        s32 targetCoordinate;
        s32 currentCoordinate;

        rawCoordinate = arg2->unk_24;
        currentCoordinate = arg1->unk_02.u;
        targetCoordinate = rawCoordinate << 6;
        ASM_USE_NV(targetCoordinate);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        currentCoordinate -= 0x20;
        arg1->unk_0C.s =
            (targetCoordinate - currentCoordinate) << 14;
    }
    {
        s32 rawCoordinate;
        s32 targetCoordinate;
        s32 currentCoordinate;

        rawCoordinate = arg2->unk_25;
        currentCoordinate = arg1->unk_06.u;
        targetCoordinate = rawCoordinate << 6;
        ASM_USE_NV(targetCoordinate);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        currentCoordinate -= 0x20;
        arg1->unk_10.s =
            (targetCoordinate - currentCoordinate) << 14;
    }
    if (((S_80172C90_1 *)arg0)->unk_96.u > 0) {
        return;
    }
    arg1->unk_14.s = 0;
    arg1->unk_10.s = 0;
    arg1->unk_0C.s = 0;
    arg2->unk_14.at00_u16.v |= 0x6000;
    ((S_80172C90_1 *)arg0)->unk_9B = 16;
    return;

L16:
    {
    u8 *counter;

    if (!(arg2->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    arg1->unk_14.s = 0;
    arg1->unk_10.s = 0;
    arg1->unk_0C.s = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
    if (arg2->unk_2C.as_pu8 != D_80174F00) {
        arg2->unk_2C.as_pu8 = D_80174F00;
        func_80047784(arg2,
            D_80174F00[((D_80083228[0] + ((S_80172C90_0 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
            0);
    }
    counter = D_80083460;
    if (((S_80172C90_6 *)counter)->unk_0C != 0) {
        return;
    }
    ((S_80172C90_6 *)counter)->unk_0A--;
    arg2->unk_14.at00_u16.v &= 0xF7FF;
    ((S_80172C90_1 *)arg0)->unk_8C = D_801710F4;
    func_800A4ACC(arg3);
    if (((S_80172C90_0 *)arg3)->unk_6D.u > 0) {
        ((S_80172C90_0 *)arg3)->unk_6D.s--;
    }
    ((S_80172C90_0 *)arg3)->unk_73.s = 0;
    ((S_80172C90_0 *)arg3)->unk_72.s = 0;
    ((S_80172C90_0 *)arg3)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);
    }
}

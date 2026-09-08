#include "common.h"

typedef struct S_800DAEF4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800DAEF4_0;   /* object in func_800DAEF4 */

typedef struct S_800DAEF4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800DAEF4_1;   /* part in func_800DAEF4 */

typedef struct S_800DAEF4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800DAEF4_2;   /* params in func_800DAEF4 */

typedef struct S_800DAEF4_3_pre {
    u16 unk_00;
} S_800DAEF4_3_pre;   /* the 0x2 bytes before owner in func_800DAEF4, addressed as owner[-1] */

typedef struct S_800DAEF4_3 {
    u8 pad_00[0x10];
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0x36];
    u16 unk_48;
} S_800DAEF4_3;   /* owner in func_800DAEF4 */

typedef struct S_800DAEF4_4 {
    u8 pad_00[0x10];
    u16 unk_10;
    u8 pad_12[0x36];
    u16 unk_48;
} S_800DAEF4_4;   /* work in func_800DAEF4 */

typedef struct S_800DAEF4_5 {
    void * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_800DAEF4_5;   /* node in func_800DAEF4 */

typedef struct S_800DAEF4_6 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800DAEF4_6;   /* link in func_800DAEF4 */

typedef struct S_800DAEF4_7 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800DAEF4_7;   /* ((S_800DAEF4_0 *)object)->unk_08 in func_800DAEF4 */



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
    void *owner;
    void *params;
    register s32 count ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *link;
    void *object;
    void *node;
    register u8 *work ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 random;
    s32 other2;
    s32 random2;
    s32 divisor;
    s32 x;
    s32 linkValue;
    u16 timer;
    u16 paramValue;
    void *part;

    owner = arg0;
    params = arg1;
    count = 12;
    link = (u8 *)&D_800DEA68;
    do {
        object = func_8003FD64(0x312, D_80083498);
        if (object != 0) {
            ((S_800DAEF4_0 *)object)->unk_10 = &D_800DB164;
            func_8004491C(object, D_80045340);
            node = ((S_800DAEF4_0 *)object)->unk_0C;
            work = (u8 *)object + 0x20;

            random = func_80069EF8();
            do {
                const s32 other = func_80069EF8();
                register s32 firstWork ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                s32 secondWork;
                register s32 randomSum ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                part = ((S_800DAEF4_0 *)object)->unk_08;
                firstWork = random;
                if (random < 0) {
                    firstWork = random + 63;
                }
                secondWork = other;
                randomSum = (firstWork >> 6) << 6;
                firstWork = random - randomSum;
                if (other < 0) {
                    secondWork = other + 63;
                }
                randomSum = (secondWork >> 6) << 6;
                randomSum = firstWork + (other - randomSum) - 64;
                ASM_USE_NV(other);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                ((S_800DAEF4_1 *)part)->unk_02 = ((S_800DAEF4_2 *)params)->unk_02 + randomSum / 2;
            } while (0);

            random2 = func_80069EF8();
            other2 = func_80069EF8();
            ((S_800DAEF4_7 *)(((S_800DAEF4_0 *)object)->unk_08))->unk_06 = ((S_800DAEF4_2 *)params)->unk_06 + (random2 % 64 + other2 % 64 - 64) / 2;

            ((S_800DAEF4_7 *)(((S_800DAEF4_0 *)object)->unk_08))->unk_0A = ((S_800DAEF4_3 *)owner)->unk_10.s;
            ((S_800DAEF4_4 *)work)->unk_10 = ((S_800DAEF4_2 *)params)->unk_08.at02.v;

            divisor = (func_80069EF8() & 3) + 4;
            x = ((S_800DAEF4_2 *)params)->unk_08.at00.v;
            x -= ((S_800DAEF4_3 *)owner)->unk_10.u << 16;
            ((S_800DAEF4_7 *)(((S_800DAEF4_0 *)object)->unk_08))->unk_14 = x / divisor;

            ((S_800DAEF4_5 *)node)->unk_14 |= 0xC;
            ((S_800DAEF4_5 *)node)->unk_1C = 0x1000;
            ((S_800DAEF4_5 *)node)->unk_1E = 0x200;
            if (func_80069EF8() & 1) {
                ((S_800DAEF4_5 *)node)->unk_14 |= 1;
            }
            ((S_800DAEF4_5 *)node)->unk_10 = 0x60;
            ((S_800DAEF4_5 *)node)->unk_0C = 0xC06060;
            ((S_800DAEF4_5 *)node)->unk_00 = link;
            linkValue = ((S_800DAEF4_6 *)link)->unk_04;
            ((S_800DAEF4_5 *)node)->unk_04 = 0;
            ((S_800DAEF4_5 *)node)->unk_05 = 0;
            ((S_800DAEF4_5 *)node)->unk_08 = linkValue;
            paramValue = ((S_800DAEF4_2 *)params)->unk_08.at02.v;
            ((S_800DAEF4_4 *)work)->unk_48 = 4;
            ((S_800DAEF4_4 *)work)->unk_10 = paramValue;
        }
        count--;
    } while (count >= 0);

    timer = ((S_800DAEF4_3 *)owner)->unk_48 - 1;
    ((S_800DAEF4_3 *)owner)->unk_48 = timer;
    if ((timer << 16) <= 0) {
        ((S_800DAEF4_3_pre *)owner)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

}

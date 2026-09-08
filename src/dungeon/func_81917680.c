#include "common.h"
#include "records/Rec_func_80024E80_arg1.h"

typedef struct S_80024E80_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80024E80_0;   /* obj in func_80024E80 */

typedef struct S_80024E80_1 {
    s32 unk_00;
    u8 pad_04[0x1C];
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
} S_80024E80_1;   /* arg0 in func_80024E80 */

typedef struct S_80024E80_2 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x8];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} S_80024E80_2;   /* work in func_80024E80 */

typedef struct S_80024E80_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024E80_3;   /* control in func_80024E80 */

typedef struct S_80024E80_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024E80_4;   /* points in func_80024E80 */


typedef struct S_80024E80_6 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80024E80_6;   /* slot in func_80024E80 */


typedef struct SixWords {
    s32 word[6];
} SixWords;

extern s32 func_80024804();
extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 func_800647A0();
extern s16 func_80065F90();
extern s32 rand();

extern u8 D_80024C0C[];
extern s32 D_80045340;
extern u8 D_800DE39C[];


void *func_80024E80(void *arg0, Rec_func_80024E80_arg1 *arg1) {
    void *obj;
    S_80024E80_2 *work;
    S_80024E80_3 *control;
    S_80024E80_4 *points;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 i;
    u8 *slot;
    s32 random;

    obj = func_8003FD64(0x212, (u8 *)arg0 - 0x20);
    if (obj != 0) {

    ((S_80024E80_0 *)obj)->unk_10 = D_80024C0C;
    work = (u8 *)obj + 0x20;
    ((S_80024E80_0 *)obj)->unk_20 = ((S_80024E80_1 *)arg0)->unk_00;
    work->unk_04 = 0;

    control = ((S_80024E80_0 *)obj)->unk_0C;
    control->unk_0E = 0x80;
    control->unk_0D = 0x80;
    control->unk_0C = 0x80;
    control->unk_12 = 0x7DCF;
    control->unk_08 = D_800DE39C;
    control->unk_14 |= 0x100;

    random = rand();
    control->unk_1A = random % 0x1000;
    control->unk_1E = 0x400;
    control->unk_1C = 0x400;

    func_8004491C(obj, &D_80045340);

    points = ((S_80024E80_0 *)obj)->unk_08;
    *(SixWords *)points = *(SixWords *)arg1;
    points->unk_0C = ((S_80024E80_1 *)arg0)->unk_20;
    points->unk_10 = ((S_80024E80_1 *)arg0)->unk_24;
    points->unk_14 = ((S_80024E80_1 *)arg0)->unk_28;

    dx = ((S_80024E80_1 *)arg0)->unk_20 - arg1->unk_00.at00_s32.v;
    dy = ((S_80024E80_1 *)arg0)->unk_24 - arg1->unk_04.at00_s32.v;
    dz = ((S_80024E80_1 *)arg0)->unk_28 - arg1->unk_08.at00_s32.v;

    work->unk_0E = func_80065F90(
        func_800647A0((((dx >> 12) * (dx >> 12)) +
                       ((dy >> 12) * (dy >> 12))) << 4),
        dz >> 4);
    work->unk_10 = func_80065F90(dx >> 4, dy >> 4);

    if (dx < 0) {
        work->unk_12 = 1;
    }

    i = 0;
    slot = work;
    do {
        ((S_80024E80_6 *)slot)->unk_14 = func_80024804(work, points, (s16)i);
        i++;
        slot += 4;
    } while (i < 3);

        return obj;
    }
    return 0;
}

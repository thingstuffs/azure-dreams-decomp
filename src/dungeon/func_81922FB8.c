#include "common.h"
#include "records/Rec_func_800247B8_arg0.h"
#include "records/Rec_func_800247B8_arg1.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800247B8_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_18;   /* overlapping accesses */
    s32 unk_1C;
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    union { s16 s; u16 u; } unk_22;   /* accessed as both */
    union { s16 s; u16 u; } unk_24;   /* accessed as both */
    s16 unk_26;
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
    u8 pad_38[0x22];
    s16 unk_5A;
    s16 unk_5C;
} S_800247B8_0;   /* work in func_800247B8 */

typedef struct S_800247B8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800247B8_1;   /* obj in func_800247B8 */

typedef struct S_800247B8_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800247B8_2;   /* part in func_800247B8 */


typedef struct S_800247B8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800247B8_4;   /* dest in func_800247B8 */




extern s32 func_8002406C(s32);
extern void *func_8003FC64(s32);
extern M2C_UNK func_8004491C();
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand();
extern M2C_UNK D_80024670[];
extern M2C_UNK D_800246C4[];

void func_800247B8(Rec_func_800247B8_arg0 *arg0, Rec_func_800247B8_arg1 *arg1)
{
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 random;
    void *obj;
    S_800247B8_0 *work;
    S_800247B8_2 *part;
    S_800247B8_4 *dest;

    obj = func_8003FC64(0x212);
    if (obj != NULL) {
        work = obj + 0x20;
        work->unk_5A = 10;
        work->unk_5C = 10;
        random = func_8002406C(8);
        work->unk_18.at00.v = 0x303030;
        if (random & 1) {
            work->unk_18.at00u.v = 0x90;
        }
        if (random & 2) {
            work->unk_18.at01.v = 0x90;
        }
        if (random & 4) {
            work->unk_18.at02.v = 0x90;
        }
        work->unk_10 = 0;
        work->unk_14 = 0;
        work->unk_1C = work->unk_18.at00.v;
        ((S_800247B8_1 *)obj)->unk_20 = work->unk_10;
        work->unk_04 = work->unk_14;
        work->unk_08 = work->unk_18.at00.v;
        work->unk_0C = work->unk_1C;
        ((S_800247B8_1 *)obj)->unk_10 = D_800246C4;
        func_8004491C(obj, D_80024670);

        part = ((S_800247B8_1 *)obj)->unk_0C;
        part->unk_10 = 0x20;
        part->unk_14 |= 0xC;
        temp_s0 = rand(part) & 0xFFF;
        temp_s0_2 = (arg0->unk_56 * func_80064584(temp_s0)) >> 12;
        work->unk_24.s = (arg0->unk_56 * func_800644B8(temp_s0)) >> 12;
        temp_s1 = rand() & 0xFFF;
        work->unk_20.s = ((s16)temp_s0_2 * func_80064584(temp_s1)) >> 12;
        work->unk_22.s = ((s16)temp_s0_2 * func_800644B8(temp_s1)) >> 12;

        work->unk_26 = work->unk_20.u + func_8002406C(0x10) - 8;
        work->unk_28 = work->unk_22.u + func_8002406C(0x10) - 8;
        random = func_8002406C(0x10);
        work->unk_36 = 0;
        work->unk_34 = 0;
        work->unk_32 = 0;
        work->unk_30 = 0;
        work->unk_2E = 0;
        work->unk_2C = 0;
        work->unk_2A = work->unk_24.u + random - 8;

        dest = ((S_800247B8_1 *)obj)->unk_08;
        dest->unk_02 = arg1->unk_02;
        dest->unk_06 = arg1->unk_06;
        dest->unk_0A = arg1->unk_0A;

        part = ((S_800247B8_1 *)obj)->unk_0C;
        part->unk_1E = 0x1000;
        part->unk_1C = 0x1000;
        part->unk_0E = 0x80;
        part->unk_0D = 0x80;
        part->unk_0C = 0x80;
    }
}

#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80174BC8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80174BC8_0;   /* obj in func_80174BC8 */

typedef struct S_80174BC8_1 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80174BC8_1;   /* prim in func_80174BC8 */


typedef struct S_80174BC8_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174BC8_3;   /* dst in func_80174BC8 */



typedef struct {
    s32 w[6];
} Block24;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_8003DE58(s32, void *, u16 *, s32);

extern u8 D_80045340[9];
extern u8 D_80174A00[9];

s32 func_80174BC8(void *arg0, void *arg1, Rec_D_80082E80 *arg2)
{
    u16 query_result[3];
    S_80174BC8_0 *obj;
    S_80174BC8_3 *dst;
    S_80174BC8_1 *prim;

    obj = func_8003FC64(0x312);
    if (obj != 0) {
        obj->unk_10 = D_80174A00;
        func_8004491C(obj, D_80045340);

        prim = obj->unk_0C;
        prim->unk_28 = arg2->unk_28.at00_s32.v;
        prim->unk_0E = 0x80;
        prim->unk_0D = 0x80;
        prim->unk_0C = 0x80;
        prim->unk_1E = 0x1000;
        prim->unk_1C = 0x1000;
        prim->unk_06 = 1;
        prim->unk_14 |= 0xC;
        prim->unk_10 |= 0x20;
        func_80047784(prim, 0x37, 0);

        dst = obj->unk_08;
        *(Block24 *)dst = *(Block24 *)arg1;

        query_result[2] = 0;
        query_result[1] = 0;
        query_result[0] = 0;
        if (func_8003DE58(arg2->unk_08, arg2, query_result, 0) != 0) {
            dst->unk_02 += query_result[0];
            dst->unk_06 += query_result[1];
            dst->unk_0A += query_result[2];
        }
        return (s32)obj;
    }
    return 0;
}

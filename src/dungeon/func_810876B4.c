#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80174EB4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80174EB4_0;   /* obj in func_80174EB4 */

typedef struct S_80174EB4_1 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
} S_80174EB4_1;   /* slot in func_80174EB4 */

typedef struct S_80174EB4_2 {
    u8 pad_00[0xC];
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
} S_80174EB4_2;   /* prim in func_80174EB4 */



typedef struct S_80174EB4_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174EB4_5;   /* dst in func_80174EB4 */

typedef struct S_80174EB4_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80174EB4_6;   /* query_arg in func_80174EB4 */



extern void *func_8003FD64(s32, s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_8003DE58(s32, void *, u16 *, s32);

extern u8 D_80045340[9];
extern u8 D_80174D24[9];

s32 func_80174EB4(s32 arg0, Rec_D_800E3D7C *arg1, Rec_func_800AA258_arg2 *arg2) {
    u16 query_result[3];
    void *obj;
    S_80174EB4_5 *dst;
    S_80174EB4_2 *prim;
    S_80174EB4_1 *slot;

    obj = func_8003FD64(0x312, arg0 - 0x20);
    if (obj != 0) {
        ((S_80174EB4_0 *)obj)->unk_10 = D_80174D24;
        func_8004491C(obj, D_80045340);

        slot = (u8 *)obj + 0x20;
        slot->unk_04 = arg1;
        slot->unk_08 = arg2;

        prim = ((S_80174EB4_0 *)obj)->unk_0C;
        prim->unk_28 = arg2->unk_28;
        prim->unk_0E = 0x80;
        prim->unk_0D = 0x80;
        prim->unk_0C = 0x80;
        prim->unk_1E = 0x1000;
        prim->unk_1C = 0x1000;
        prim->unk_14 |= 0xC;
        prim->unk_10 |= 0x20;
        func_80047784(prim, 0x38, 0);

        {
            S_80174EB4_6 *query_arg = arg2;
            u16 *query_out;
            register s32 w0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register s32 w1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s32 w2;
            s32 w3;

            ASM_KEEP(query_arg);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            dst = ((S_80174EB4_0 *)obj)->unk_08;
            ASM_KEEP(dst);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            query_out = query_result;
            ASM_KEEP(query_out);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            w0 = arg1->unk_00.at00_s32.v;
            w1 = arg1->unk_04.at00_s32.v;
            w2 = arg1->unk_08.at00_s32.v;
            w3 = arg1->unk_0C.as_s32;
            dst->unk_00.at00.v = w0;
            dst->unk_04.at00.v = w1;
            dst->unk_08.at00.v = w2;
            dst->unk_0C = w3;
            w0 = arg1->unk_10.at00_s32.v;
            w1 = arg1->unk_14.as_s32;
            dst->unk_10 = w0;
            dst->unk_14 = w1;

            query_result[2] = 0;
            query_result[1] = 0;
            query_result[0] = 0;
            if (func_8003DE58(query_arg->unk_08, query_arg,
                              query_out, 0) != 0) {
                dst->unk_00.at02.v += query_result[0];
                dst->unk_04.at02.v += query_result[1];
                dst->unk_08.at02.v += query_result[2];
            }
        }
        return (s32)obj;
    }
    return 0;
}

/* MECHANISM: A three-halfword output array preserves the callee-written values.
 * Guarded argument and copy-result pins reproduce the retail live ranges and
 * grouped 24-byte copy; the apparent func_80174FFC tail is the local epilogue. */

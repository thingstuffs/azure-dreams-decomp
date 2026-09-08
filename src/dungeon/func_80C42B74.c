#include "common.h"
#include "records/Rec_func_80173CFC_arg1.h"

typedef struct S_80174374_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x2];
    s16 unk_1E;
    u8 pad_20[0x20];
    s32 unk_40;
    s32 unk_44;
} S_80174374_0;   /* work in func_80174374 */

typedef struct S_80174374_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80174374_1;   /* obj in func_80174374 */

typedef struct S_80174374_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80174374_2;   /* part in func_80174374 */


typedef struct S_80174374_4 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174374_4;   /* pos in func_80174374 */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern s32 rand(void);
extern void func_8003DB94(void *, void *, s32);

extern u8 D_80045340;
extern s32 D_800DEC00;
extern u8 D_801741A0;

void func_80174374(void *arg0, Rec_func_80173CFC_arg1 *arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5) {
    void *obj;
    S_80174374_0 *work;
    register void *part ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register void *pos ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 value;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        value = arg4;
        work = (u8 *)obj + 0x20;
        work->unk_1A = 0x14;
        work->unk_1E = arg4;
        ((S_80174374_1 *)obj)->unk_10 = &D_801741A0;
        func_8004491C(obj, &D_80045340);

        part = ((S_80174374_1 *)obj)->unk_0C;
        ((S_80174374_2 *)part)->unk_10 = 0x20;
        ((S_80174374_2 *)part)->unk_14 |= 0xC;

        pos = ((S_80174374_1 *)obj)->unk_08;
        work->unk_40 = arg1->unk_00.at00_s32.v;
        work->unk_44 = arg1->unk_04.at00_s32.v;

        while (value >= 0x1001) {
            value -= 0x1000;
        }

        ((S_80174374_4 *)pos)->unk_00 = work->unk_40 + func_80064584(value) * 0x280;
        ((S_80174374_4 *)pos)->unk_04 = work->unk_44 + func_800644B8(value) * 0x280;
        ((S_80174374_4 *)pos)->unk_0A = arg1->unk_0A + arg5;

        part = ((S_80174374_1 *)obj)->unk_0C;
        ((S_80174374_2 *)part)->unk_1E = 0x400;
        ((S_80174374_2 *)part)->unk_1C = 0x400;
        ((S_80174374_2 *)part)->unk_0E = 0x60;
        ((S_80174374_2 *)part)->unk_0D = 0xFF;
        ((S_80174374_2 *)part)->unk_0C = 0xFF;
        work->unk_00 = 0xFF;
        work->unk_01 = ((S_80174374_2 *)part)->unk_0D;
        work->unk_02 = ((S_80174374_2 *)part)->unk_0E;

        func_8003DB94(part, &D_800DEC00, rand() & 1);
        ((S_80174374_2 *)part)->unk_12 = 0x7DCF;
        ((S_80174374_2 *)part)->unk_14 |= 0x100;
    }
}

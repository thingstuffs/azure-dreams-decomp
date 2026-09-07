#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800224E0_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    union { struct { void * v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_20;   /* overlapping accesses */
    u8 pad_24[0x4];
    s16 unk_28;
} S_800224E0_0;   /* obj in func_800224E0 */

typedef struct S_800224E0_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800224E0_1;   /* prim in func_800224E0 */

typedef struct S_800224E0_2 {
    u8 pad_00[0x48];
    void * unk_48;
} S_800224E0_2;   /* parent in func_800224E0 */

typedef struct S_800224E0_3 {
    u8 pad_00[0x4C];
    void * unk_4C;
} S_800224E0_3;   /* slot in func_800224E0 */

typedef struct S_800224E0_4 {
    s32 unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800224E0_4;   /* draw in func_800224E0 */



extern u8 D_80020224[];
extern u8 D_80022768[];
extern u8 D_80023404[];
extern u8 D_80023DE0[];
extern u8 D_80023EB0[];
extern u8 D_8002415C[];
extern u8 D_80024470[];
extern u8 D_800244A0[];
extern s32 D_80024628[];
extern u8 D_80024640[];
extern u8 D_80024680[];
extern u8 D_800246E0[];
extern u8 D_80046398[];

extern void func_80022290();
extern void func_80033B9C();
extern void *func_8003FC64();
extern void func_8004491C();
extern void func_8004E9E4();
extern void func_8006733C();
extern void func_8008F104();

void func_800224E0(void)
{
    s16 rect[4];
    s32 i;
    register s32 value ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u8 *obj;
    u8 *parent;
    u8 *slot;
    u8 *callback;
    u8 *prim;
    u8 *draw;
    u8 *callback_slot;
    u8 *tbl;
    u32 color;
    u8 *cbt;

    parent = NULL;
    callback = D_80020224;
    func_8004E9E4();
    D_80024628[0] = 0;
    func_80022290(D_800246E0);
    func_80033B9C(0xA4);

    obj = func_8003FC64(0x32);
    if (obj != NULL) {
        parent = obj + 0x20;
        prim = ((S_800224E0_0 *)obj)->unk_08;
        ((S_800224E0_0 *)obj)->unk_10 = D_80022768;
        ((S_800224E0_1 *)prim)->unk_00 = 0x04600000;
        ((S_800224E0_1 *)prim)->unk_04 = 0x03600000;
        ((S_800224E0_2 *)parent)->unk_48 = callback;
        func_8008F104(parent, prim, D_80024470);
    }

    i = 2;
    tbl = D_80023404;
    slot = parent + 8;
    do {
        obj = func_8003FC64(2);
        ((S_800224E0_3 *)slot)->unk_4C = obj;
        if (obj != NULL) {
            ((S_800224E0_0 *)obj)->unk_10 = tbl;
            ((S_800224E0_0 *)obj)->unk_28 = i;
            ((S_800224E0_0 *)obj)->unk_20.at00.v = parent;
        }
        i--;
        slot -= 4;
    } while (i >= 0);

    obj = func_8003FC64(0x136);
    if (obj != NULL) {
        func_8004491C(obj, D_80046398);
        color = 0x00808080;
        cbt = obj + 0x28;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_800224E0_0 *)obj)->unk_10 = D_80023DE0;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        value = 0x1000;
        ASM_KEEP(value);   /* MATCH pin: retail schedule: same instructions, different order without it */
        prim = ((S_800224E0_0 *)obj)->unk_08;
        draw = ((S_800224E0_0 *)obj)->unk_0C;
        ((S_800224E0_0 *)obj)->unk_20.at00.v = parent;
        ((S_800224E0_4 *)draw)->unk_1C = value;
        ((S_800224E0_4 *)draw)->unk_1E = value;
        ((S_800224E0_4 *)draw)->unk_20 = value;
        ((S_800224E0_4 *)draw)->unk_08 = 0x2C;
        ((S_800224E0_4 *)draw)->unk_12 = 0;
        ((S_800224E0_4 *)draw)->unk_14 = 0;
        ((S_800224E0_4 *)draw)->unk_10 = 0;
        ((S_800224E0_4 *)draw)->unk_16 = 0;
        ((S_800224E0_4 *)draw)->unk_18 = 0;
        ((S_800224E0_4 *)draw)->unk_1A = 0;
        ((S_800224E0_4 *)draw)->unk_00 = 0;
        ((S_800224E0_4 *)draw)->unk_04 = 0;
        ((S_800224E0_4 *)draw)->unk_05 = 0;
        ((S_800224E0_4 *)draw)->unk_0C = color;
        ((S_800224E0_1 *)prim)->unk_00 = 0x04400000;
        ((S_800224E0_1 *)prim)->unk_04 = 0x02C00000;
        callback_slot = obj + 0x20;
        ((S_800224E0_1 *)prim)->unk_08 = 0;
        (*(void * volatile *)((u8 *)callback_slot + 0x50)) = callback;
        func_8008F104(cbt, ((S_800224E0_0 *)obj)->unk_08, D_800244A0);
    }

    i = 4;
    do {
        obj = func_8003FC64(0x100);
        if (obj != NULL) {
            func_8004491C(obj, D_8002415C);
            ((S_800224E0_0 *)obj)->unk_20.at00.v = parent;
            ((S_800224E0_0 *)obj)->unk_10 = D_80023EB0;
            obj += 0x20;
            ((S_800224E0_0 *)obj)->unk_20.at02.v = i;
            switch (i) {
            case 0:
                value = 1;
                ((S_800224E0_0 *)obj)->unk_20.at00u.v = value;
                break;
            case 1:
                value = 2;
                ((S_800224E0_0 *)obj)->unk_20.at00u.v = value;
                break;
            case 2:
                value = 3;
                ((S_800224E0_0 *)obj)->unk_20.at00u.v = value;
                break;
            case 3:
            case 4:
            default:
                break;
            }
        }
        i--;
    } while (i >= 0);

    rect[0] = 0x40;
    rect[1] = 0x1D0;
    rect[2] = 0x20;
    rect[3] = 1;
    func_8006733C(rect, D_80024640);
    rect[0] = 0xC0;
    rect[1] = 0x1F8;
    rect[2] = 0x30;
    rect[3] = 1;
    func_8006733C(rect, D_80024680);
}

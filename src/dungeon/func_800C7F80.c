#include "common.h"


extern s32 func_8003FA44();
extern void *func_8003FC64();
extern void func_8004491C();
extern void func_800A56E0();
extern void func_800A6508();
extern s32 func_800A6D30();
extern void func_800CD6AC();
extern void func_800CD744();
extern void func_800CD8E4();

extern u8 D_80045C34[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern u16 D_80083460[6];
extern u8 D_800CD474[];
extern u8 D_800E03E0[];
extern u8 D_800E3D40;


typedef struct S_800CD6E0_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD6E0_0_pre;   /* the 0x14 bytes before arg0 in func_800CD6E0, addressed as arg0[-1] */

typedef struct S_800CD6E0_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0xF];
    u8 unk_13;
    u8 pad_14[0x74];
    u16 unk_88;
} S_800CD6E0_0;   /* arg0 in func_800CD6E0 */

typedef struct S_800CD6E0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD6E0_1;   /* owner in func_800CD6E0 */

typedef struct S_800CD6E0_2 {
    u8 pad_00[0x10];
    void * unk_10;
} S_800CD6E0_2;   /* (obj = func_8003FC64(2)) in func_800CD6E0 */

typedef struct S_800CD6E0_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x10];
    void * unk_20;
} S_800CD6E0_3;   /* obj in func_800CD6E0 */

typedef struct S_800CD6E0_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CD6E0_4;   /* prim in func_800CD6E0 */

typedef struct S_800CD6E0_5 {
    s16 unk_00;
} S_800CD6E0_5;   /* (void *)table_offset in func_800CD6E0 */

typedef struct S_800CD6E0_6 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
} S_800CD6E0_6;   /* spr in func_800CD6E0 */

typedef struct S_800CD6E0_7 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
    u16 unk_0A;
} S_800CD6E0_7;   /* link in func_800CD6E0 */

s32 func_800CD6E0(void *arg0) {
    void *obj;
    S_800CD6E0_1 *owner;
    S_800CD6E0_4 *prim;
    S_800CD6E0_6 *spr;
    S_800CD6E0_7 *link;
    s16 *xpos;
    u16 *counter;
    s32 i;
    s32 random;
    register s32 call_arg ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 divisor;
    s32 gate;
    register s32 color ASM_REG("$7");   /* MATCH pin: retail immediate-load split depends on it */
    register s32 count ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 owner_coord;
    s32 coord;
    register s32 table_offset ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    void *callback_base;

    if (D_800E3D40 == 0) {
        call_arg = func_800A6D30() & 0xFFFF;
        count = ((S_800CD6E0_0 *)arg0)->unk_03;
        if (count != 0) {
            divisor = count;
            ASM_KEEP(divisor);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            count = call_arg % divisor;
            ASM_KEEP(count);   /* MATCH pin: retail basic-block layout depends on it */
            func_800CD744();
            return count;
        }
    }

    gate = 0;
    ASM_KEEP(gate);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    if (gate < 0x30) {
        owner = ((S_800CD6E0_0_pre *)arg0)[-1].unk_00;
        if (owner->unk_14 & 0x8000) {
            func_800CD6AC(arg0, 0x10);
            func_800CD8E4();
            return 1;
        }
        if (func_8003FA44(4) == 0) {
            func_800CD8E4();
            return 0;
        }

        i = 0;
        coord = 0x800D0000;
        ASM_KEEP_NV(coord);   /* MATCH pin: load-bearing for the whole function shape */
        callback_base = (void *)(coord - 0x2B8C);
        counter = D_80083460;
        xpos = D_8006CCD8;
        do {
            ((S_800CD6E0_2 *)((obj = func_8003FC64(2))))->unk_10 = callback_base;
            func_8004491C(obj, D_80045C34);
            color = 0x808080;
            call_arg = 0x50D;
            ASM_KEEP_NV(call_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
            table_offset = i << 2;

            owner_coord = owner->unk_24;
            coord = *xpos;
            prim = ((S_800CD6E0_3 *)obj)->unk_08;
            owner_coord <<= 6;
            coord = (coord << 5) + 0x20;
            owner_coord += coord;
            coord = (u32)D_8006CCE8;
            table_offset += coord;
            prim->unk_02 = owner_coord;
            owner_coord = owner->unk_25;
            coord = ((S_800CD6E0_5 *)((void *)table_offset))->unk_00;
            owner_coord <<= 6;
            coord = (coord << 5) + 0x20;
            owner_coord += coord;
            prim->unk_06 = owner_coord;
            xpos += 2;
            prim->unk_0A = ((S_800CD6E0_0 *)arg0)->unk_88 - 0x200;

            spr = ((S_800CD6E0_3 *)obj)->unk_0C;
            coord = 0x1000;
            spr->unk_1C = coord;
            coord = 0x2000;
            spr->unk_1E = coord;
            coord = (s32)D_800E03E0;
            spr->unk_08 = (void *)coord;
            spr->unk_10 = 0x20;
            spr->unk_16 = 0x400;
            spr->unk_0C = color;
            spr->unk_18 = (i << 10) + 0x400;
            spr->unk_14 |= 0xC;

            link = (u8 *)obj + 0x20;
            link->unk_0A = ((S_800CD6E0_0 *)arg0)->unk_88;
            ((S_800CD6E0_3 *)obj)->unk_20 = arg0;
            link->unk_06 = 0xC;
            link->unk_08 = i;
            ((S_800CD6E0_3 *)obj)->unk_20 = arg0;
            i++;
            counter[5]++;
            func_800A56E0(call_arg, spr, prim, color);
        } while (i < 4);

        func_800CD8E4();
        return 1;
    }

    if (((S_800CD6E0_0 *)arg0)->unk_13 == 0) {
        func_800A6508(call_arg);
    }
    return 1;
}

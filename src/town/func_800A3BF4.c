#include "common.h"

#define SCALE255(value) ((u32)(value) / 255)

extern u8 D_80083160[];
extern s32 func_80069EF8(void);
extern void func_80066844(void *);
extern void func_80066640(void *, s32);
extern void func_800A130C(void *, void *);
extern void func_800A1330(void *, void *);
extern s32 func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_8006658C(void *, void *);
extern u16 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);


typedef struct S_800A1354_0 {
    u8 pad_00[0x10];
    s16 unk_10;
} S_800A1354_0;   /* arg0 in func_800A1354 */

typedef struct S_800A1354_1 {
    u8 pad_00[0x24];
    u8 * unk_24;
    u8 pad_28[0x9C];
    s32 unk_C4;
    u8 pad_C8[0x20];
    u16 unk_E8;
    u16 unk_EA;
    u16 unk_EC;
    u16 unk_EE;
    u16 unk_F0;
    u16 unk_F2;
    u16 unk_F4;
    u16 unk_F6;
} S_800A1354_1;   /* scratch in func_800A1354 */

typedef struct S_800A1354_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800A1354_2;   /* ctx in func_800A1354 */

typedef struct S_800A1354_3 {
    u8 pad_00[0x4];
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_04;   /* overlapping accesses */
    u16 unk_08;
    u16 unk_0A;
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u16 unk_12;
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_14;   /* overlapping accesses */
    u16 unk_18;
    u16 unk_1A;
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_1C;   /* overlapping accesses */
    u16 unk_20;
    u16 unk_22;
} S_800A1354_3;   /* poly in func_800A1354 */

typedef struct S_800A1354_4 {
    u8 pad_00[0x54];
    u8 * unk_54;
    u8 * unk_58;
    u8 * unk_5C;
} S_800A1354_4;   /* obj in func_800A1354 */

typedef struct S_800A1354_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800A1354_5;   /* ((S_800A1354_4 *)obj)->unk_54 in func_800A1354 */

typedef struct S_800A1354_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800A1354_6;   /* ((S_800A1354_4 *)obj)->unk_58 in func_800A1354 */

typedef struct S_800A1354_7 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800A1354_7;   /* ((S_800A1354_4 *)obj)->unk_5C in func_800A1354 */

void func_800A1354(u8 *arg0)
{
    u8 **ctx_addr = (u8 **)D_80083160;
    s32 i = 0;
    u32 mask = 0xFFFFFF;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *obj;
    s32 scale;
    u8 *poly;
    s32 rand1;
    s32 color3;

    scale = ((S_800A1354_0 *)arg0)->unk_10;
    ((S_800A1354_1 *)scratch)->unk_24 = *ctx_addr + 0xB0;
    do {
        u8 *ctx = *ctx_addr;
        u8 *packet;
        obj = arg0 + (i * 4);

        poly = ((S_800A1354_2 *)ctx)->unk_8D0;
        ((S_800A1354_2 *)ctx)->unk_8D0 = poly + 0x28;
        rand1 = func_80069EF8();
        ((S_800A1354_3 *)poly)->unk_04.at00.v = (rand1 * func_80069EF8()) & mask;
        rand1 = func_80069EF8();
        ((S_800A1354_3 *)poly)->unk_0C.at00.v = (rand1 * func_80069EF8()) & mask;
        rand1 = func_80069EF8();
        ((S_800A1354_3 *)poly)->unk_14.at00.v = (rand1 * func_80069EF8()) & mask;
        rand1 = func_80069EF8();
        color3 = rand1 * func_80069EF8();
        ((S_800A1354_3 *)poly)->unk_1C.at00.v = color3 & mask;

        ((S_800A1354_3 *)poly)->unk_04.at00u.v = SCALE255(((S_800A1354_3 *)poly)->unk_04.at00u.v * scale);
        ((S_800A1354_3 *)poly)->unk_04.at01.v = SCALE255(((S_800A1354_3 *)poly)->unk_04.at01.v * scale);
        ((S_800A1354_3 *)poly)->unk_04.at02.v = SCALE255(((S_800A1354_3 *)poly)->unk_04.at02.v * scale);
        ((S_800A1354_3 *)poly)->unk_0C.at00u.v = SCALE255(((S_800A1354_3 *)poly)->unk_0C.at00u.v * scale);
        ((S_800A1354_3 *)poly)->unk_0C.at01.v = SCALE255(((S_800A1354_3 *)poly)->unk_0C.at01.v * scale);
        ((S_800A1354_3 *)poly)->unk_0C.at02.v = SCALE255(((S_800A1354_3 *)poly)->unk_0C.at02.v * scale);
        ((S_800A1354_3 *)poly)->unk_14.at00u.v = SCALE255(((S_800A1354_3 *)poly)->unk_14.at00u.v * scale);
        ((S_800A1354_3 *)poly)->unk_14.at01.v = SCALE255(((S_800A1354_3 *)poly)->unk_14.at01.v * scale);
        ((S_800A1354_3 *)poly)->unk_14.at02.v = SCALE255(((S_800A1354_3 *)poly)->unk_14.at02.v * scale);
        ((S_800A1354_3 *)poly)->unk_1C.at00u.v = ((S_800A1354_3 *)poly)->unk_04.at00u.v;
        ((S_800A1354_3 *)poly)->unk_1C.at01.v = ((S_800A1354_3 *)poly)->unk_04.at01.v;
        ((S_800A1354_3 *)poly)->unk_1C.at02.v = ((S_800A1354_3 *)poly)->unk_04.at02.v;
        func_80066844(poly);
        func_80066640(poly, 1);

        func_800A130C(scratch + 0x74, ((S_800A1354_5 *)(((S_800A1354_4 *)obj)->unk_54))->unk_08);
        func_800A130C(scratch + 0x7C, ((S_800A1354_6 *)(((S_800A1354_4 *)obj)->unk_58))->unk_08);
        func_800A130C(scratch + 0x84, ((S_800A1354_7 *)(((S_800A1354_4 *)obj)->unk_5C))->unk_08);
        func_800A1330(scratch + 0x8C, scratch + 0x74);
        ((S_800A1354_1 *)scratch)->unk_C4 = func_800654B0(
            scratch + 0x74, scratch + 0x7C, scratch + 0x84, scratch + 0x8C, scratch + 0xE8, scratch + 0xEC,
            scratch + 0xF0, scratch + 0xF4, scratch + 0x94, scratch + 0x98) - 0x30;

        ((S_800A1354_3 *)poly)->unk_08 = ((S_800A1354_1 *)scratch)->unk_E8;
        ((S_800A1354_3 *)poly)->unk_0A = ((S_800A1354_1 *)scratch)->unk_EA;
        ((S_800A1354_3 *)poly)->unk_10 = ((S_800A1354_1 *)scratch)->unk_EC;
        ((S_800A1354_3 *)poly)->unk_12 = ((S_800A1354_1 *)scratch)->unk_EE;
        ((S_800A1354_3 *)poly)->unk_18 = ((S_800A1354_1 *)scratch)->unk_F0;
        ((S_800A1354_3 *)poly)->unk_1A = ((S_800A1354_1 *)scratch)->unk_F2;
        ((S_800A1354_3 *)poly)->unk_20 = ((S_800A1354_1 *)scratch)->unk_F4;
        ((S_800A1354_3 *)poly)->unk_22 = ((S_800A1354_1 *)scratch)->unk_F6;
        if (((S_800A1354_1 *)scratch)->unk_C4 >= 0x1E0)
            ((S_800A1354_1 *)scratch)->unk_C4 = 0x1DF;
        if (((S_800A1354_1 *)scratch)->unk_C4 < 0)
            ((S_800A1354_1 *)scratch)->unk_C4 = 0;
        func_8006658C(((S_800A1354_1 *)scratch)->unk_24 + ((S_800A1354_1 *)scratch)->unk_C4 * 4, poly);
        i += 3;
        ctx = *ctx_addr;
        packet = ((S_800A1354_2 *)ctx)->unk_8D0;
        ((S_800A1354_2 *)ctx)->unk_8D0 = packet + 0xC;
        func_80067F20(packet, 1, 0, func_80066460(0, 1, 0x140, 0), 0);
        func_8006658C(((S_800A1354_1 *)scratch)->unk_24 + ((S_800A1354_1 *)scratch)->unk_C4 * 4, packet);
    } while (i < 6);
}

#include "common.h"

typedef struct S_800C7930_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800C7930_0;   /* camera in func_800C7930 */

typedef struct S_800C7930_1 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C7930_1;   /* source in func_800C7930 */

typedef struct S_800C7930_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800C7930_2;   /* work in func_800C7930 */

typedef struct S_800C7930_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C7930_3;   /* destination in func_800C7930 */



extern u8 D_80083780;
extern u16 D_800DCEAC;
extern u16 D_800DCEBC;
extern u8 D_800E58F8;
extern void func_800C77D0(void *arg0, void *arg1, s16 arg2);

s32 func_800C7930(s32 arg0, void *arg1, s32 arg2)
{
    s32 delta;
    s32 source_coord;
    s32 index1;
    s32 index2;
    s32 result;
    u16 table_value;
    register u16 source_x ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    S_800C7930_2 *work;
    register u8 *camera;
    register u8 *destination ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *table1;
    register u8 *table2;
    register s32 object ASM_REG("$10") = arg0;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    S_800C7930_1 *source = arg1;

    ASM_KEEP_NV(object);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_KEEP_NV(source);   /* MATCH pin: retail schedule: same instructions, different order without it */
    camera = &D_80083780;
    ASM_CLOBBER("$7");   /* MATCH pin: retail register colouring depends on it */
    ASM_KEEP(camera);   /* MATCH pin: load-bearing for the whole function shape */
    delta = ((S_800C7930_0 *)camera)->unk_02;
    source_coord = source->unk_02.s;
    source_x = source->unk_02.u;
    delta -= source_coord;
    if (delta < 0) {
        delta = -delta;
    }
    if (delta < 0xC1) {
        delta = ((S_800C7930_0 *)camera)->unk_06;
        source_coord = source->unk_06.s;
        delta -= source_coord;
        if (delta < 0) {
            delta = -delta;
        }
        work = (u8 *)object + 0x20;
        if (delta < 0xC1) {
            destination = &D_800E58F8;
            table1 = (u8 *)&D_800DCEAC;
            index1 = (work->unk_2A >> 8) & 0xE;
            result = (s16)*(u16 *)(table1 + index1) / 2;
            result = source_x - -result;
            ((S_800C7930_3 *)destination)->unk_02 = result;
            table2 = (u8 *)&D_800DCEBC;
            index2 = (work->unk_2A >> 8) & 0xE;
            table_value = *(u16 *)(table2 + index2);
            ((S_800C7930_3 *)destination)->unk_06 = source->unk_06.u + (s16)table_value / 2;
            ((S_800C7930_3 *)destination)->unk_0A = source->unk_0A;
            func_800C77D0((void *)object, destination, (s16)arg2);
        }
    }
    return 0;
}

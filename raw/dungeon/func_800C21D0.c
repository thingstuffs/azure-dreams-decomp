#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_80083780;
extern u16 D_800DCEAC;
extern u16 D_800DCEBC;
extern u8 D_800E58F8;
extern void func_800C77D0(void *arg0, void *arg1, s16 arg2);

s32 func_800C7930(s32 arg0, void *arg1, s32 arg2)
{
    register s32 delta ASM_REG("$2");
    register s32 source_coord ASM_REG("$3");
    s32 index1;
    s32 index2;
    s32 result;
    u16 table_value;
    register u16 source_x ASM_REG("$8");
    register void *work ASM_REG("$4");
    register u8 *camera;
    register u8 *destination ASM_REG("$5");
    register u8 *table1;
    register u8 *table2;
    register s32 object ASM_REG("$10") = arg0;
    register void *source ASM_REG("$9") = arg1;

    ASM_KEEP_NV(object);
    ASM_KEEP_NV(source);
    camera = &D_80083780;
    ASM_CLOBBER("$7");
    ASM_KEEP(camera);
    delta = FIELD(camera, s16, 2);
    source_coord = FIELD(source, s16, 2);
    source_x = FIELD(source, u16, 2);
    delta -= source_coord;
    if (delta < 0) {
        delta = -delta;
    }
    if (delta < 0xC1) {
        delta = FIELD(camera, s16, 6);
        source_coord = FIELD(source, s16, 6);
        delta -= source_coord;
        if (delta < 0) {
            delta = -delta;
        }
        work = (u8 *)object + 0x20;
        if (delta < 0xC1) {
            destination = &D_800E58F8;
            table1 = (u8 *)&D_800DCEAC;
            index1 = (FIELD(work, u16, 0x2A) >> 8) & 0xE;
            result = (s16)*(u16 *)(table1 + index1) / 2;
            result = source_x - -result;
            FIELD(destination, s16, 2) = result;
            table2 = (u8 *)&D_800DCEBC;
            index2 = (FIELD(work, u16, 0x2A) >> 8) & 0xE;
            table_value = *(u16 *)(table2 + index2);
            FIELD(destination, s16, 6) = FIELD(source, u16, 6) + (s16)table_value / 2;
            FIELD(destination, u16, 0xA) = FIELD(source, u16, 0xA);
            func_800C77D0((void *)object, destination, (s16)arg2);
        }
    }
    return 0;
}

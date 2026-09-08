#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct AcHeader {
    u8 pad00[2];
    s16 field02;
    u8 pad04[2];
    s16 field06;
    u8 pad08[2];
    s16 field0A;
} AcHeader;

typedef struct AcMeta {
    u8 pad00[0x0C];
    u32 field0C;
    u8 pad10[4];
    u16 field14;
    u8 pad16[6];
    s16 field1C;
} AcMeta;

typedef struct AcSub AcSub;

struct AcSub {
    void *field00;
    void *field04;
    u16 field08;
    s16 field0A;
    s16 field0C;
    u8 pad0E[2];
    u32 field10;
    u32 field14;
    u32 field18;
    u32 field1C;
    u8 pad20[2];
    u16 field22;
    s16 field24;
    u16 field26;
    void *field28;
    u8 pad2C[0x0C];
    u32 field38;
    u32 field3C;
    u8 pad40[0x10];
    void *slots[4];
};

typedef struct AcObject {
    u8 pad00[8];
    AcHeader *header;
    AcMeta *meta;
    void *field10;
    u8 pad14[0x0C];
    AcSub sub;
} AcObject;

extern u8 D_80083498[];
extern void *D_80073618[];
extern u8 D_800B06F0[];
extern u8 D_800B14FC[];
extern s32 D_800DF03C[];

extern AcObject *func_8003FD64(s32, void *, s32);
extern void func_8004491C(AcObject *, void *, AcMeta *);
extern s32 func_8004E298(void *, s32, s32);
extern s32 func_80069E98(s32);
extern void *func_800B12F4(void);
extern void func_800B1320(u8 *, s32, s32);
extern void func_800B135C(void *, s32);
extern void func_800B13CC(void *, s32);
extern void func_800B1400(void *, s32);
extern void *func_800B1434(void *, void *);

void func_800B1768(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s16 arg4, u16 arg5) {
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a0;
    register s32 var_a0_2 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s8 var_v0;
    s32 var_v1;
    s16 arg0_reg = arg0;
    s32 arg1_reg = arg1;
    register u8 *arg2_reg ASM_REG("$21") = (u8 *)arg2;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 temp_s6 = arg3;
    s32 count = 0;
    register s32 arg3_ff ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    AcObject *obj;
    AcHeader *header;
    AcMeta *meta;
    AcSub *sub;
    register s32 *table_entry ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *base;
    void *new_buf;
    void *buf;
    register void *call_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *prev_arg;
    register s32 hard_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u32 color1;
    u32 color2;
    u32 tail_flags;
    u32 tail_field1c;

    obj = func_8003FD64(0x12, D_80083498, (s32)arg2_reg);
    if (obj != NULL) {
        meta = obj->meta;
        header = obj->header;
        sub = &obj->sub;
        if ((arg4 << 0x10) != 0) {
            meta->field14 |= 1;
        }
        header->field02 = arg1_reg;
        sub->field0A = arg1_reg;
        header->field06 = (s32)arg2_reg;
        sub->field0C = (s32)arg2_reg;
        header->field0A = 0;
        sub->field08 = 1;
        meta->field1C = 0x1000;
        meta->field0C = 0;
        obj->field10 = D_800B14FC;
        func_8004491C(obj, D_800B06F0, meta);
        arg3_ff = temp_s6 & 0xFF;
        ASM_KEEP_NV(arg3_ff);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        base = (u8 *)&sub->field38;
        ASM_KEEP_NV(base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        arg2_reg = base;
        sub->field24 = (s16)((temp_s6 << 0x10) >> 0x18);
        sub->field00 = (u8 *)&sub->slots[0];
        sub->field04 = arg2_reg;
        buf = func_800B12F4();
        sub->field28 = buf;
        if (buf != NULL) {
            if (arg0_reg != 0) {
                count = 1;
                arg2_reg = (u8 *)obj + 0x5C;
                call_arg = buf;
                arg1_reg = count;
                *(void **)((u8 *)obj + 0x70) = call_arg;
                buf = func_800B1434(call_arg, D_80073618[arg0_reg]);
                *(u32 *)((u8 *)obj + 0x58) = 0x808080;
                goto shared_setup;
            }
            arg1_reg = 0;
shared_setup:
            call_arg = buf;
            base = (u8 *)D_800DF03C;
            table_entry = (s32 *)((arg3_ff * 4) + (s32)base);
            ASM_KEEP_NV(table_entry);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
            hard_zero = 0;
#endif
            *(void **)((u8 *)sub + 0x50 + count * 4) = (void *)func_8004E298(call_arg, *table_entry, hard_zero);
            temp_s6 = func_80069E98(*table_entry) * 8;
            count++;
            temp_v0_2 = arg1_reg << 2;
            temp_v0_2 += arg1_reg;
            temp_v1_2 = temp_v0_2 << 1;
            var_a1 = temp_v1_2 + 0x80;
            if (((u16)arg4 << 0x10) != 0) {
                temp_v0_2 = temp_v1_2 + 0x76;
                temp_v0_2 -= temp_s6;
                var_a1 = (s16)temp_v0_2;
            }
            func_800B1320(buf, var_a1, (s16)((0 - (s8)((u8 *)buf)[3]) - 9));
            var_a1_2 = 8;
            if (arg4 != 0) {
                var_a1_2 = 4;
            }
            func_800B135C(buf, var_a1_2);
            func_800B13CC(buf, 0x20);
            func_800B1400(buf, 2);
            color1 = 0x808080;
            *(volatile u32 *)arg2_reg = color1;
            arg2_reg += 4;
            ASM_KEEP_NV(arg2_reg);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            buf = (u8 *)buf + 0x60;
            *(void **)((u8 *)sub + 0x50 + count++ * 4) = buf;
            call_arg = buf;
            prev_arg = (u8 *)buf - 0x60;
            new_buf = func_800B1434(call_arg, prev_arg);
            call_arg = buf;
            buf = new_buf;
            func_800B1320(call_arg, 1, 1);
            color2 = 0x80808;
            temp_v0_2 = count << 2;
            count++;
            var_a0 = -0xA;
            temp_v0_2 += (s32)sub;
            *(volatile u32 *)arg2_reg = color2;
            *(void **)((u8 *)temp_v0_2 + 0x50) = buf;
            ((u8 *)buf)[1] = 0x38;
            if (arg1_reg == 0) {
                var_a0 = -2;
            }
            var_v1 = var_a0;
            if (arg4 != 0) {
                var_v1 -= 2;
            }
            temp_v0_2 = arg1_reg << 1;
            temp_v0_2 += arg1_reg;
            temp_v0_2 <<= 3;
            var_a0_2 = temp_s6 + temp_v0_2;
            ((s8 *)buf)[2] = var_v1;
            ((s8 *)buf)[3] = -0xE;
            ((s8 *)buf)[9] = 0;
            ((s8 *)buf)[8] = 0;
            if (arg1_reg == 0) {
                var_a0_2 += 4;
            }
            var_v0 = var_a0_2;
            if (arg4 != 0) {
                var_v0 -= 2;
            }
            color2 = 0x80000;
            ASM_KEEP_NV(color2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ((s8 *)buf)[0xA] = var_v0;
            var_v0 = 0x10;
            var_a0_2 = 0xC0;
            ((s8 *)buf)[0xB] = var_v0;
            ((u8 *)buf)[0] = var_a0_2;
            sub->field10 = 0;
            sub->field14 = 0;
            color2 |= 0x4008;
            sub->field18 = color2;
            sub->field1C = color2;
            *(s32 *)((u8 *)buf + 4) = sub->field10;
            *(s32 *)((u8 *)buf + 0xC) = sub->field14;
            *(s32 *)((u8 *)buf + 0x10) = sub->field18;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            tail_flags = ((u8 *)buf)[1];
            tail_field1c = sub->field1C;
            tail_flags |= 2;
            ((u8 *)buf)[1] = tail_flags;
            *(s32 *)((u8 *)buf + 0x14) = tail_field1c;
            buf = (u8 *)buf + 0x18;
            *(void **)((u8 *)sub + 0x50 + count * 4) = buf;
            ((u8 *)buf)[1] = 0x81;
            *(s16 *)((u8 *)buf + 4) = 0x20;
            *(s16 *)((u8 *)buf + 6) = 0;
            ((u8 *)buf)[0] = var_a0_2;
        }
        sub->field22 = 4;
        sub->field26 = arg5;
    }
}

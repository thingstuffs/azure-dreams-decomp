#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad0[8];
    void *field8;
    void *fieldC;
    void *field10;
    u8 pad14[0xC];
    u32 field20;
} TempObj;

typedef struct {
    u8 pad0[2];
    s16 field2;
    u8 pad4[2];
    s16 field6;
    u8 pad8[2];
    s16 fieldA;
} TempBuffer;

typedef struct {
    u8 pad0[8];
    void *field8;
    u8 padC[8];
    s16 field14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} TempChild;

typedef struct {
    u8 pad0[4];
    s16 field4;
    u8 pad6[2];
    s8 field8;
    s8 field9;
    s8 fieldA;
    s8 fieldB;
    u8 padC[4];
    s16 field10;
    s16 field12;
    s16 field14;
    u8 pad16[2];
    s16 field18;
    s16 field1A;
    s16 field1C;
    u8 pad1E[2];
    s16 field20;
    s16 field22;
    s16 field24;
    u8 pad26[2];
    s16 field28;
    s16 field2A;
    s16 field2C;
    u8 pad2E[0x1E];
    s16 field4C;
} TempOutput;

extern s8 D_8002745C[];
M2C_UNK func_80026D84() __attribute__((noreturn));
TempObj *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_800264D4;
extern M2C_UNK D_800269CC;
extern s16 D_800273BC[5];

typedef struct S_819613A8_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_819613A8_0;   /* arg2 in func_819613A8 */

void func_819613A8(s16 arg0, s32 arg1, S_819613A8_0 *arg2) {
    
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    register s32 temp_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 temp_a3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 temp_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 temp_t0;
    s32 temp_t1;
    register s32 temp_t2 ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp_v1;
    register s32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register s32 temp_sum ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 temp_t5 ASM_REG("$13");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 temp_t6 ASM_REG("$14");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 temp_t7 ASM_REG("$15");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 temp_s4;
    register s32 temp_tail ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register TempObj *temp_arg0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register void *temp_init ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s8 *temp_base;
    register void *temp_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 *temp_t3 ASM_REG("$11");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp_t4;
    TempObj *temp_v0;

    temp_v0 = func_8003FC64(0x202);
    if (temp_v0 != NULL) {
        temp_s4 = arg1;
        ASM_KEEP(temp_s4);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        temp_s0 = arg1;
        temp_arg0 = temp_v0;
        temp_init = &D_800264D4;
        temp_v0->field10 = temp_init;
        func_8004491C(temp_arg0, &D_800269CC);
        temp_t1 = (s16) arg0;
        temp_t2 = (temp_t1 - 3) << 6;
        ASM_KEEP(temp_t2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_a1 = (s16) temp_s0;
        temp_base = D_8002745C;
        temp_s0 = temp_a1 * 0x10;
        temp_t3 = (s16 *)(temp_s0 + (s32)temp_base);
        temp_a3 = temp_t1 * 2;
        temp_t3 = (s16 *)(temp_a3 + (s32)temp_t3);
        temp_base += 0x10;
        temp_base = (s8 *)(temp_s0 + (s32)temp_base);
        temp_a3 += (s32)temp_base;
        temp_t0 = (temp_a1 - 3) << 6;
        temp_a2 = temp_v0->field8;
        temp_v1 = ((s16 *)arg2)[1];
        temp_a0 = ((s16 *)arg2)[3];
        temp_sum = temp_t3[0];
        temp_t4 = temp_t3[1];
        temp_t5 = ((s16 *)temp_a3)[0];
        temp_t6 = ((s16 *)temp_a3)[1];
        temp_t7 = ((s16 *)arg2)[5];
        temp_v1 += temp_t2;
        temp_a0 += temp_t0;
        temp_sum += temp_t4;
        temp_sum += temp_t5;
        temp_sum += temp_t6;
        temp_sum >>= 2;
        temp_sum += temp_t7;
        ((TempBuffer *)temp_a2)->fieldA = temp_sum;
        ((TempBuffer *)temp_a2)->field2 = temp_v1;
        ((TempBuffer *)temp_a2)->field6 = temp_a0;
        temp_t4 = (s32)temp_v0->fieldC;
        temp_a2 = (void *)&temp_v0->field20;
        ((TempChild *)temp_t4)->field1E = 0x800;
        ((TempChild *)temp_t4)->field1C = 0x800;
        ((TempChild *)temp_t4)->field14 = 0xC;
        temp_v0_2 = ((u16) arg2->unk_02 + temp_t2) - 0x20;
        ((TempOutput *)temp_a2)->field20 = temp_v0_2;
        ((TempOutput *)temp_a2)->field10 = temp_v0_2;
        temp_v0_3 = ((u16) arg2->unk_02 + ((temp_t1 - 2) << 6)) - 0x20;
        ((TempOutput *)temp_a2)->field28 = temp_v0_3;
        ((TempOutput *)temp_a2)->field18 = temp_v0_3;
        temp_v0_4 = ((u16) arg2->unk_06 + temp_t0) - 0x20;
        ((TempOutput *)temp_a2)->field1A = temp_v0_4;
        ((TempOutput *)temp_a2)->field12 = temp_v0_4;
        temp_a1 = (temp_a1 - 2) << 6;
        temp_v0_5 = ((u16) arg2->unk_06 + temp_a1) - 0x20;
        ((TempOutput *)temp_a2)->field2A = temp_v0_5;
        ((TempOutput *)temp_a2)->field22 = temp_v0_5;
        ((TempOutput *)temp_a2)->field14 = (s16) ((u16) arg2->unk_0A + (u16) temp_t3[0]);
        ((TempOutput *)temp_a2)->field1C = (s16) ((u16) arg2->unk_0A + (u16) temp_t3[1]);
        temp_s0 -= 0x80;
        temp_sum = (u16) arg2->unk_0A;
        temp_v1 = (u16) ((s16 *)temp_a3)[0];
        temp_sum += temp_v1;
        ((TempOutput *)temp_a2)->field24 = temp_sum;
        temp_sum = (u16) arg2->unk_0A;
        temp_v1 = (u16) ((s16 *)temp_a3)[1];
        temp_sum += temp_v1;
        ((TempOutput *)temp_a2)->field2C = temp_sum;
        temp_a0 = 0xF8F82CC0;
        temp_tail = 0x13D;
        temp_v0->field20 = temp_a0;
        ((TempOutput *)temp_a2)->field4 = temp_tail;
        temp_tail = temp_t1 * 0x10;
        ((TempOutput *)temp_a2)->field8 = (s8) temp_tail;
        temp_tail = 6;
        ((TempOutput *)temp_a2)->field9 = (s8) temp_s0;
        if (temp_t1 == temp_tail) {
            temp_tail = 0xF;
            ASM_TAILSLOT_PIN(temp_tail);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_80026D84(temp_a0, temp_a1, temp_a2, temp_a3);
            return;
        }
        ((TempOutput *)temp_a2)->fieldA = 0x10;
        temp_tail = (s16) temp_s4;
        temp_v1 = 6;
        if (temp_tail == temp_v1) {
            temp_tail = 0xF;
        } else {
            temp_tail = 0x10;
        }
        ((TempOutput *)temp_a2)->fieldB = temp_tail;
        ((TempChild *)temp_t4)->field8 = temp_a2;
        ((TempOutput *)temp_a2)->field4C = 8;
        (*(s16 *)D_800273BC) = (s16) ((*(u16 *)D_800273BC) + 1);
    }
}

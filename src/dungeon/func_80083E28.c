#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80083160.h"

typedef struct S_80089588_3 {
    s32 unk_00;
} S_80089588_3;   /* temp_s1 in func_80089588 */

typedef struct S_80089588_4 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80089588_4;   /* ((S_80089588_3 *)temp_s1)->unk_00 in func_80089588 */



typedef struct S_80089588_1 {
    u8 pad_00[0x3];
    volatile s8 unk_03;
    volatile s32 unk_04;
    volatile s16 unk_08;
    volatile u16 unk_0A;
    union { s16 s; volatile s16 u; } unk_0C;   /* accessed as both */
    volatile u16 unk_0E;
    volatile s16 unk_10;
    volatile s16 unk_12;
    volatile s16 unk_14;
    volatile s16 unk_16;
} S_80089588_1;   /* temp_s2 in func_80089588 */

typedef struct S_80089588_2 {
    s32 unk_00;
} S_80089588_2;   /* temp_s1 in func_80089588 */


struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 *D_80083160;
extern u8 D_801C9E40[16];
M2C_UNK func_8006658C(void *, void *);
M2C_UNK func_80067E2C();
M2C_UNK func_80067EF4();
M2C_UNK func_80067F20();
extern void func_80089654(void) __attribute__((noreturn));

void func_80089588(void) {
    s32 sp18[2];
    s32 temp_s0;
    register s32 temp_s3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u16 temp_v0;
    u16 temp_v0_3;
    void *temp_s2;
    register u32 temp_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    temp_s0 = (s32) D_80083160 != (s32) D_801C9E40;
    temp_s2 = ((Rec_D_80083160 *)D_80083160)->unk_8D0;
    func_80067E2C(temp_s2, D_80083160);
    func_8006658C((u8 *)D_80083160 + 0x7B0, temp_s2);
    temp_s2 += 0xC;
    func_80067E2C(temp_s2, D_80083160);
    func_8006658C((u8 *)D_80083160 + 0x830, temp_s2);
    temp_s2 += 0xC;
    func_80067EF4(temp_s2, 0, 0);
    func_8006658C((u8 *)D_80083160 + 0x830, temp_s2);
    temp_s2 += 0xC;
    {
        s32 cmd_value;
        do { cmd_value = 0x2A000000; } while (0);
        ((S_80089588_1 *)temp_s2)->unk_04 = cmd_value;
        cmd_value = 1;
        ((S_80089588_1 *)temp_s2)->unk_10 = cmd_value;
        ((S_80089588_1 *)temp_s2)->unk_08 = cmd_value;
        cmd_value = 0x100;
        ((S_80089588_1 *)temp_s2)->unk_14 = cmd_value;
        ((S_80089588_1 *)temp_s2)->unk_0C.s = cmd_value;
    }
    temp_s1 = (u32) &D_80083160;
    ASM_KEEP_NV(temp_s1);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    temp_s3 = temp_s0;
    if (temp_s0 != 0) {
        s32 tail_value;
        tail_value = 0xE0;
        ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80089654();
        return;
    }
    {
        register s32 first_value;
        first_value = 0x1C0;
        ((S_80089588_1 *)temp_s2)->unk_0E = first_value;
        ASM_KEEP(temp_s2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
    temp_v0 = ((S_80089588_1 *)temp_s2)->unk_0E;
    ((S_80089588_1 *)temp_s2)->unk_03 = 5;
    ((S_80089588_1 *)temp_s2)->unk_0A = temp_v0;
    ((S_80089588_1 *)temp_s2)->unk_16 = temp_v0 + 0xE;
    ((S_80089588_1 *)temp_s2)->unk_12 = temp_v0 + 0xE;
    func_8006658C(((S_80089588_2 *)temp_s1)->unk_00 + 0x830, temp_s2);
    temp_s2 += 0x18;
    {
        register s32 cmd_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        cmd_value = 0x2A000000;
        ((S_80089588_1 *)temp_s2)->unk_04 = cmd_value;
        cmd_value = 1;
        ((S_80089588_1 *)temp_s2)->unk_10 = cmd_value;
        ((S_80089588_1 *)temp_s2)->unk_08 = cmd_value;
        cmd_value = 0x100;
        ((S_80089588_1 *)temp_s2)->unk_14 = cmd_value;
        ((S_80089588_1 *)temp_s2)->unk_0C.u = cmd_value;
    }
    {
        register s32 packet_width ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        packet_width = temp_s3;
        ASM_KEEP_NV(packet_width);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        if (packet_width != 0) {
            packet_width = 0xE0;
        } else {
            packet_width = 0x1C0;
        }
        ((S_80089588_1 *)temp_s2)->unk_0E = packet_width;
        ASM_KEEP(temp_s2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
    temp_v0_3 = ((S_80089588_1 *)temp_s2)->unk_0E;
    ((S_80089588_1 *)temp_s2)->unk_03 = 5;
    ((S_80089588_1 *)temp_s2)->unk_0A = temp_v0_3;
    ((S_80089588_1 *)temp_s2)->unk_16 = temp_v0_3 + 0xE;
    ((S_80089588_1 *)temp_s2)->unk_12 = temp_v0_3 + 0xE;
    func_8006658C(((S_80089588_2 *)temp_s1)->unk_00 + 0x7B0, temp_s2);
    temp_s2 += 0x18;
    func_80067EF4(temp_s2, 0, 1);
    func_8006658C(((S_80089588_2 *)temp_s1)->unk_00 + 0x830, temp_s2);
    temp_s2 += 0xC;
    func_80067F20(temp_s2, 0, 0, 0x20, 0);
    func_8006658C(((S_80089588_2 *)temp_s1)->unk_00 + 0x7B0, temp_s2);
    temp_s2 += 0xC;
    func_80067F20(temp_s2, 0, 0, 0x20, 0);
    func_8006658C(((S_80089588_2 *)temp_s1)->unk_00 + 0x830, temp_s2);
    temp_s2 += 0xC;
    sp18[0] = 0x01C00000;
    sp18[1] = 0x100100;
    func_80067E2C(temp_s2, (s32) sp18);
    func_8006658C(((S_80089588_2 *)temp_s1)->unk_00 + 0x7B0, temp_s2);
    temp_s2 += 0xC;
    func_80067E2C(temp_s2, (s32) sp18);
    func_8006658C(((S_80089588_2 *)temp_s1)->unk_00 + 0x830, temp_s2);
    temp_s2 += 0xC;
    ((S_80089588_4 *)(((S_80089588_3 *)temp_s1)->unk_00))->unk_8D0 = temp_s2;
}

#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C08A4_0 {
    void * unk_00;
    u8 pad_04[0x27];
    u8 unk_2B;
    u8 pad_2C[0x34];
    u8 unk_60;
    u8 unk_61;
    u8 pad_62[0x1];
    u8 unk_63;
    u8 pad_64[0xC4];
    u8 * unk_128;
} S_800C08A4_0;   /* temp_s1 in func_800C08A4; pointer addresses record offset 0x18 */

typedef struct S_800C08A4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800C08A4_1;   /* temp_s0 in func_800C08A4 */

typedef struct S_800C08A4_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C08A4_2;   /* counter_base in func_800C08A4 */


extern u8 *D_800E3D7C;
extern u8 D_80083780[12];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern s32 D_80083460[3];
M2C_UNK func_8008D344();
M2C_UNK func_80098864();
M2C_UNK func_80098B38();
s32 func_8004A658();
s32 func_800998C0();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_80099368();
s32 func_80099734();
s32 func_80099978();
M2C_UNK func_800A5720();
M2C_UNK func_800A5F38();
M2C_UNK func_800A6480();
s32 func_800A6D30();
M2C_UNK func_800A7A7C();
s32 func_800AD6FC();
extern M2C_UNK D_80089378;
extern M2C_UNK D_8008937C;
extern M2C_UNK D_800E13DA;
extern M2C_UNK D_800E13E9;

s32 func_800C08A4(u8 *arg0, u8 *arg1, s16 arg2, M2C_UNK arg3) {
    s32 temp_s1_2;
    s32 temp_s1_3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    u8 *temp_v0_7;
    s32 temp_s2;
    u8 *temp_s1;
    S_800C08A4_1 *temp_s0;
    s32 temp_s0_2;

    temp_s1 = arg0;
    if (arg2 == 0xD) {
        if (((S_800C08A4_0 *)((u8 *)temp_s1 - 0x18))->unk_2B == 0x16) {
            ASM_KEEP_NV(arg2); /* MATCH: retain the existing a2 value across the argument setup. */
            if ((func_800A6D30(arg1, arg1, arg2, arg3) & 1) == 0) {
                goto main_path;
            }
        }
        return func_80098864(arg1, arg3);
    }
main_path:
    temp_v0_7 = D_800E3D7C;
    if (temp_s1 == temp_v0_7) {
        ((S_800C08A4_0 *)((u8 *)temp_s1 - 0x18))->unk_128 = arg1;
        func_8008D344(temp_s1, D_80083780, D_80082E80, temp_s1);
        return 0;
    }
    temp_v0_7 = (u8 *) 0x9FFFFFFF;
    if ((u32) temp_s1 <= (u32) temp_v0_7) {
        if (((S_800C08A4_0 *)((u8 *)temp_s1 - 0x18))->unk_2B != 0x16) {
            func_800A6480(temp_s1, arg1);
            if (func_800AD6FC(temp_s1, (D_800DDE84[((S_800C08A4_0 *)((u8 *)temp_s1 - 0x18))->unk_2B] >> 4) & 3, 0) == 0) {
                func_800A5F38(temp_s1, arg1);
                return 1;
            }
            func_80098B38(arg1);
            goto decrement;
        }
        temp_s0 = ((S_800C08A4_0 *)((u8 *)temp_s1 - 0x18))->unk_00;
        ((S_800C08A4_0 *)((u8 *)temp_s1 - 0x18))->unk_63 = (u8) (((S_800C08A4_0 *)((u8 *)temp_s1 - 0x18))->unk_63 & 0xDF);
        func_800A7A7C((u16) temp_s0->unk_02 >> 6, (u16) temp_s0->unk_06 >> 6, temp_s0->unk_0A, func_8004A658(((S_800C08A4_0 *)((u8 *)temp_s1 - 0x18))->unk_61, ((S_800C08A4_0 *)((u8 *)temp_s1 - 0x18))->unk_60), temp_s1 + 0x48);
        ((S_800C08A4_0 *)((u8 *)temp_s1 - 0x18))->unk_60 = (u8) *arg1;
        ((S_800C08A4_0 *)((u8 *)temp_s1 - 0x18))->unk_63 = (u8) (((S_800C08A4_0 *)((u8 *)temp_s1 - 0x18))->unk_63 | 0x20);
        temp_s2 = func_800990FC();
        temp_v0 = func_80099734(temp_s1, temp_s2);
        temp_v0_2 = func_80099194(&D_800E13DA, temp_v0);
        {
            s32 node;
            s32 offset;
            s32 captured;
            s32 result;

            node = func_80099978(temp_v0_2);
            captured = func_80099194(&D_80089378, node);
            offset = node - 2;
            ASM_KEEP_DEP_NV(offset, node);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(captured);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            node = captured;
            result = func_80099368(arg1, node);
            {
                register s32 pass ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

                pass = node;
                node = result;
                ASM_KEEP(node);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                func_800998C0(offset, pass);
            }
            func_80099290(func_80099194(&D_8008937C, node));
        }
        func_800A5720(temp_s2);
        func_80098B38(arg1);
        goto decrement;
    }
    temp_s2 = func_800990FC();
    temp_v0_4 = func_80099734(temp_s1, temp_s2);
    temp_v0_5 = func_80099194(&D_800E13E9, temp_v0_4);
    {
        s32 node;
        s32 offset;
        s32 captured;
        s32 result;

        node = func_80099978(temp_v0_5);
        captured = func_80099194(&D_80089378, node);
        offset = node - 2;
        ASM_KEEP_DEP_NV(offset, node);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(captured);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        node = captured;
        result = func_80099368(arg1, node);
        {
            register s32 pass ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

            pass = node;
            node = result;
            ASM_KEEP(node);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            func_800998C0(offset, pass);
        }
        func_80099290(func_80099194(&D_8008937C, node));
    }
    func_800A5720(temp_s2);
decrement:
    {
        u8 *counter_base = (u8 *) D_80083460;
        ((S_800C08A4_2 *)counter_base)->unk_0A = (u16) (((S_800C08A4_2 *)counter_base)->unk_0A - 1);
    }
    return 1;
}

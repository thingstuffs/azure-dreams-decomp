#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800A94A0_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x23];
    u8 unk_2B;
    u8 pad_2C[0x4C];
    void * unk_78;
    u8 pad_7C[0x24];
    s16 unk_A0;
} S_800A94A0_0;   /* arg0 in func_800A94A0; pointer addresses record offset 0x18 */


typedef struct S_800A94A0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
    void * unk_20;
} S_800A94A0_2;   /* temp_v0 in func_800A94A0 */

typedef struct S_800A94A0_3 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 unk_08;
    u8 unk_09;
} S_800A94A0_3;   /* temp_v0_3 in func_800A94A0 */

typedef struct S_800A94A0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A94A0_4;   /* temp_s0 in func_800A94A0 */

typedef struct S_800A94A0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A94A0_5;   /* temp_v1 in func_800A94A0 */

typedef struct S_800A94A0_6 {
    s32 unk_00;
} S_800A94A0_6;   /* temp_v0_4 in func_800A94A0; pointer addresses record offset 0x14 */

typedef struct S_800A94A0_7 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800A94A0_7;   /* temp_s5 in func_800A94A0 */

typedef struct S_800A94A0_8 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800A94A0_8;   /* temp_t0 in func_800A94A0 */

typedef struct S_800A94A0_9 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_800A94A0_9;   /* *D_800E3D7C in func_800A94A0 */


extern u8 D_80083498[];
extern s32 D_800814A0[3];
extern volatile s16 D_80013714[8];
extern u8 D_80082E80[];
extern u8 D_800E3CC8[];
extern u8 *D_800E3D7C[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];
struct S_8006DE24_Entry;
typedef struct S_8006DE24_Entry S_8006DE24_Entry;
struct S_8006DE24_Entry {
    s32 unk0;
    u8 pad4[4];
    s32 unk8;
    u8 padC[8];
};
extern S_8006DE24_Entry D_8006DE24[];

void *func_8003FD64();
M2C_UNK func_80069EF8();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_80099734();
M2C_UNK func_8009FD40();
M2C_UNK func_800A5720();
s16 func_800A9400();
void func_800A96D8() __attribute__((noreturn));
void *func_800A971C();
void *func_800A97CC();
void *func_800A97FC();
s32 func_800A982C();
M2C_UNK func_800C77D0();
M2C_UNK func_800C78A0();
M2C_UNK func_800C7A3C();
void func_800AD594();
extern M2C_UNK D_80089080;
extern u8 D_800DD880[];
extern u8 D_800DD8B4[];
extern M2C_UNK D_800E1C58;
extern u8 D_800E3D68;

void *func_800A94A0(void *arg0, Rec_D_800E3D7C *arg1, s16 arg2, void *arg3) {
    s32 temp_s0_2;
    s32 temp_v0_2;
    register s32 temp_v0_5 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 temp_v0_5_result;
    M2C_UNK temp_v1_2;
    s16 temp_v0_6;
    s32 entry_arg2;
    u16 temp_a0;
    s32 temp_a1;
    s32 temp_a1_2;
    register void *temp_a0_3 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u8 temp_a0_2;
    register s16 temp_s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    S_800A94A0_4 *temp_s0;
    S_800A94A0_7 *temp_s5;
    void *temp_v0;
    S_800A94A0_3 *temp_v0_3;
    void *temp_v0_4;
    S_800A94A0_5 *temp_v1;
    u8 *temp_t0;

    temp_s5 = ((S_800A94A0_0 *)((u8 *)arg0 - 0x18))->unk_04;
    temp_v0 = func_8003FD64(0x12, D_80083498);
    if (temp_v0 != NULL) {
        entry_arg2 = ((s32) arg2 << 0x10) >> 0x10;
        {
            register s32 entry_a1 ASM_REG("$5") = entry_arg2;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            u8 entry_v1;
            do { temp_s2 = arg1->unk_00.at00_u8.v; } while (0);
            entry_v1 = arg1->unk_00.at01_u8.v;
            D_800E3D68 = entry_v1;
            temp_v0_2 = func_800A982C((u8) temp_s2, entry_a1, ((S_800A94A0_0 *)((u8 *)arg0 - 0x18))->unk_2B);
        }
        ASM_KEEP_NV(temp_s2);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        if (temp_v0_2 == 0) {
            temp_a0 = ((S_800A94A0_2 *)temp_v0)->unk_1E | 0x8000;
            temp_a1 = D_800814A0[0] | 0x8000;
            ((S_800A94A0_2 *)temp_v0)->unk_1E = temp_a0;
            D_800814A0[0] = temp_a1;
            return NULL;
        }
        ((S_800A94A0_2 *)temp_v0)->unk_10 = temp_v0_2;
        temp_v0_3 = temp_v0 + 0x20;
        ((S_800A94A0_2 *)temp_v0)->unk_20 = arg0;
        temp_v0_3->unk_04 = arg3;
        temp_v0_3->unk_08 = temp_s2;
        D_800E3CC8[0] = temp_s2;
        temp_a0_2 = arg1->unk_00.at01_u8.v;
        temp_v0_3->unk_09 = temp_a0_2;
        D_800E3CC8[1] = temp_a0_2;
        if (arg2 == 0) {
            temp_v1 = ((S_800A94A0_0 *)((u8 *)arg0 - 0x18))->unk_00;
            temp_s0 = ((S_800A94A0_2 *)temp_v0)->unk_08;
            temp_s0->unk_02 = (u16) temp_v1->unk_02;
            temp_s0->unk_06 = (u16) temp_v1->unk_06;
            temp_s0->unk_0A = (u16) temp_v1->unk_0A;
            temp_v0_5 = func_80069EF8();
            if (!((u16) *D_80013714 & 1)) {
                temp_v0_4 = ((S_800A94A0_0 *)((u8 *)arg0 - 0x18))->unk_78;
                if (temp_v0_4 != NULL) {
                    func_8009FD40(((S_800A94A0_0 *)((u8 *)arg0 - 0x18))->unk_04, ((S_800A94A0_6 *)((u8 *)temp_v0_4 - 0x14))->unk_00);
                }
            }
            func_800C77D0(temp_v0, temp_s0, 8, 0x300);
            ASM_KEEP(temp_v0_5);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            goto block_21;
        }
        temp_t0 = D_80082E80;
        if (!(temp_s5->unk_14 & 0x8000)) {
            if (!(((S_800A94A0_8 *)temp_t0)->unk_14 & 0x8000)) {
                func_800C7A3C(temp_t0, temp_s5, ((S_800A94A0_9 *)(*D_800E3D7C))->unk_88, ((S_800A94A0_0 *)((u8 *)arg0 - 0x18))->unk_A0, 8, 0x300);
                goto block_21;
            }
            goto block_16;
        }
block_16:
        temp_v1_2 = ((u16) ((S_800A94A0_9 *)(*D_800E3D7C))->unk_2A >> 8) & 0xE;
        func_800C78A0(arg0 - 0x20, (((S_800A94A0_8 *)temp_t0)->unk_24 << 6) + ((s32) (*(u16 *)((u8 *)D_800DCEAC + temp_v1_2) << 0x10) >> 0x11) + 0x20, (((S_800A94A0_8 *)temp_t0)->unk_25 << 6) + ((s32) (*(u16 *)((u8 *)D_800DCEBC + temp_v1_2) << 0x10) >> 0x11) + 0x20, ((S_800A94A0_9 *)(*D_800E3D7C))->unk_88, 8, 0x300);
block_21:
        if ((arg2 << 0x10) != 0) {
            register s32 lookup_index ASM_REG("$2") = temp_s2;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            temp_a1_2 = D_800DD8B4[lookup_index];
            temp_a0_3 = arg0;
            temp_a1_2 <<= 6;
        } else {
            register s32 lookup_index ASM_REG("$2") = temp_s2;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            temp_a1_2 = D_800DD880[lookup_index];
            temp_a0_3 = arg0;
            temp_a1_2 <<= 8;
        }
        func_800AD594(temp_a0_3, temp_a1_2);
        if ((temp_v0 != NULL) && ((s8) ((S_800A94A0_0 *)((u8 *)arg0 - 0x18))->unk_2B > 0)) {
            temp_v0_5_result = func_800990FC();
            temp_a0_3 = arg0;
            temp_v0_5 = temp_v0_5_result;
            temp_s0_2 = func_80099194(&D_800E1C58, func_80099734(temp_a0_3, temp_v0_5));
            if (((u32)(u16)arg2 << 0x10) != 0) {
                temp_v0_6 = func_800A9400(((s32)temp_s2 << 0x10) >> 0x10);
                return func_800A97CC(D_8006DE24[temp_v0_6].unk8);
            }
            {
                register s32 entry_index ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                S_8006DE24_Entry *entry_base;
                entry_index = (s32)temp_s2 << 0x10;
                entry_base = D_8006DE24;
                entry_index >>= 0x10;
                temp_s0_2 = func_80099194(entry_base[entry_index].unk0, temp_s0_2);
                func_80099290(func_80099194(&D_80089080, temp_s0_2));
                ASM_KEEP(temp_s0_2);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            }
            func_800A5720(temp_v0_5);
            goto block_25;
        }
        return temp_v0;
    }
block_25:
    return temp_v0;
}

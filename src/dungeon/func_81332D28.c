#include "common.h"
#include "m2c_compat.h"

extern u8 D_80083498[];
extern u8 *D_80175D50[3];
extern u8 D_80045340[];
extern u8 D_8016A36C[];
extern u8 *func_8003FD64(s32, u8 *);
extern void func_8004491C(u8 *, u8 *);
extern void func_800A9C18(u8 *, void *, void *, s32);
extern void func_800AA36C(u8 *, void *, void *, u8 *);
extern s32 func_800F6598(s32, s32, s32, s32);
extern M2C_UNK D_80169EC0;
extern M2C_UNK D_80173980;

typedef struct S_80169D28_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80169D28_0;   /* obj in func_80169D28 */

typedef struct S_80169D28_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x6C];
    u8 * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0xD];
    s8 unk_AA;
    u8 pad_AB[0x1];
    s8 unk_AC;
} S_80169D28_1;   /* child in func_80169D28 */

typedef struct S_80169D28_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80169D28_2;   /* first in func_80169D28 */

typedef struct S_80169D28_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80169D28_3;   /* second in func_80169D28 */

u8 *func_80169D28(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *result;
    s32 mode;
    u8 *obj;
    u8 *child;
    u8 *first;
    u8 *second;
    s16 saved_arg0;
    /* MATCH: Preserve retail's register allocation for the saved second argument. */
    register s16 saved_arg1 ASM_REG("$20");
    s16 saved_arg2;
    /* MATCH: Schedule the saved fourth argument after result initialization. */
    register s16 saved_arg3 ASM_REG("$17");

    result = NULL;
    saved_arg3 = arg3;
    saved_arg0 = arg0;
    saved_arg1 = arg1;
    saved_arg2 = arg2;
    if (func_800F6598(arg0, arg1, arg2, arg3) == 0) {
        obj = func_8003FD64(0x112, D_80083498);
        if (obj != NULL) {
            result = obj + 0x20;
            *D_80175D50 = obj;
            ((S_80169D28_0 *)obj)->unk_10 = &D_80169EC0;
            child = obj + 0x20;
            ((S_80169D28_1 *)child)->unk_13 = 0x38;
            func_8004491C(obj, D_80045340);
            first = ((S_80169D28_0 *)obj)->unk_08;
            ((S_80169D28_2 *)first)->unk_0A = saved_arg3;
            second = ((S_80169D28_0 *)obj)->unk_0C;
            mode = saved_arg0 & 3;
            ((S_80169D28_3 *)second)->unk_24 = saved_arg1;
            ((S_80169D28_3 *)second)->unk_2C = &D_80173980;
            ((S_80169D28_3 *)second)->unk_25 = saved_arg2;
            if (mode == 1) {
                ((S_80169D28_1 *)child)->unk_14 = ((S_80169D28_1 *)child)->unk_14 | 0x6000;
                ((S_80169D28_1 *)child)->unk_1C = ((S_80169D28_1 *)child)->unk_1C | 0x6000;
            } else if (mode >= 2) {
                ((S_80169D28_1 *)child)->unk_14 = ((S_80169D28_1 *)child)->unk_14 | 0x2000;
                ((S_80169D28_1 *)child)->unk_1C = ((S_80169D28_1 *)child)->unk_1C | 0x2000;
            }
            ((S_80169D28_1 *)child)->unk_AC = 0;
            ((S_80169D28_3 *)second)->unk_14 = ((S_80169D28_3 *)second)->unk_14 | 0x400;
            func_800A9C18(obj, first, second, saved_arg0);
            ((S_80169D28_1 *)child)->unk_9A = 0xFF;
            ((S_80169D28_1 *)child)->unk_9C = -1;
            ((S_80169D28_1 *)child)->unk_8C = D_8016A36C;
            ((S_80169D28_1 *)child)->unk_AA = 0;
            ((S_80169D28_3 *)second)->unk_14 = ((S_80169D28_3 *)second)->unk_14 | 0x80;
            func_800AA36C(child, first, second, result);
        }
    }
    return result;
}

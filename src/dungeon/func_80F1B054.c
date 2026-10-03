#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"


typedef s32 M2C_UNK;

typedef struct S_8015E854_0 {
    u8 pad_00[0x8];
    void ** unk_08;
    void ** unk_0C;
    void * unk_10;
} S_8015E854_0;   /* objectBase in func_8015E854 */

typedef struct S_8015E854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8015E854_1;   /* result in func_8015E854 */

typedef struct S_8015E854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8015E854_2;   /* data08 in func_8015E854 */

typedef struct S_8015E854_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8015E854_3;   /* data0C in func_8015E854 */

typedef struct S_8015E854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
    s16 unk_A6;
} S_8015E854_4;   /* objectState in func_8015E854 */


extern u8 D_8015EA8C[];
extern u8 D_80161D30[];
extern u8 D_80161D78[];
extern u8 D_8015EF74[];

extern void *func_8003FD64();
extern M2C_UNK func_8004491C();
extern s32 func_800A6D30(void);
extern M2C_UNK func_800A48F0();
extern M2C_UNK func_800A9C18();
extern M2C_UNK func_800AA36C();
extern M2C_UNK func_80044A50();
extern M2C_UNK func_800BC318();

#define BODY_STORAGE
#define BODY_ATTR

BODY_STORAGE void *func_8015E854(s16 mode, s16 value24, s16 value25, s16 value0A) BODY_ATTR;

BODY_STORAGE void *func_8015E854(s16 mode, s16 value24, s16 value25, s16 value0A)
{
    s32 modeBits;
    s32 optionValue;
    void *objectBaseForCallbacks;
    S_8015E854_3 *data0C;
    S_8015E854_2 *data08;
    void *objectState;
    void *objectBase;
    S_8015E854_1 *result;

    result = 0;
    optionValue = 1;
    objectBase = func_8003FD64(274, ((u8 *)(&D_80083498)));
    if (objectBase != 0) {
        result = (u8 *)objectBase + 0x20;
        ((S_8015E854_0 *)objectBase)->unk_10 = D_8015EA8C;
        result->unk_13 = 0x23;
        func_8004491C(objectBase, func_80045340);
        data08 = ((S_8015E854_0 *)objectBase)->unk_08;
        data08->unk_0A = value0A;
        data0C = ((S_8015E854_0 *)objectBase)->unk_0C;
        data0C->unk_25 = value25;
        objectState = result;
        data0C->unk_2C = D_80161D30;
        modeBits = mode & 3;
        data0C->unk_24 = value24;
        if (modeBits == 1) {
            result->unk_14 |= 0x6000;
            result->unk_1C |= 0x6000;
        } else if (modeBits >= 2) {
            result->unk_14 |= 0x2000;
            result->unk_1C |= 0x2000;
        } else if (((mode & ~3) << 16) == 0) {
            if (!(result->unk_14 & 0x200)) {
                if (func_800A6D30() & 1) {
                    result->unk_1C |= 0x200;
                    func_800A48F0(result, 1, (func_800A6D30() & 0x3F) | 0x20);
                    data0C->unk_2C = D_80161D78;
                }
            }
            optionValue = func_800A6D30() & 3;
        }
        func_800A9C18(objectBase, data08, data0C, mode);
        ((S_8015E854_4 *)objectState)->unk_9A = 0xFF;
        ((S_8015E854_4 *)objectState)->unk_9C = -1;
        ((S_8015E854_4 *)objectState)->unk_8C = D_8015EF74;
        ((S_8015E854_4 *)objectState)->unk_A4 = -1;
        if (optionValue != 0) {
            ((S_8015E854_4 *)objectState)->unk_A6 = 0;
        } else {
            objectBaseForCallbacks = (u8 *)objectState - 0x20;
            ((S_8015E854_4 *)objectState)->unk_A6 = 1;
            data0C->unk_10 = 0x60;
            data0C->unk_14 |= 0xC;
            data0C->unk_12 -= 0x80;
            func_80044A50(objectBaseForCallbacks);
            func_800BC318(objectBaseForCallbacks);
        }
        func_800AA36C(objectState, data08, data0C, result);
    }
    return result;
}

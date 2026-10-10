#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "records/Rec_func_800249DC_arg0.h"

typedef struct S_819ACB28_0_pre {
    u16 unk_00;
} S_819ACB28_0_pre;   /* the 0x2 bytes before object in func_80024328, addressed as object[-1] */

typedef struct S_819ACB28_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x18];
    u16 unk_24;
    u16 unk_26;
    union { s16 s; u16 u; } unk_28;   /* accessed as both */
    u8 pad_2A[0x2];
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    s16 unk_2E;
} S_819ACB28_0;   /* object in func_80024328 */

typedef struct S_819ACB28_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_819ACB28_1;   /* data_ptr in func_80024328 */


typedef struct S_819ACB28_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_819ACB28_3;   /* offsets in func_80024328 */

typedef struct S_819ACB28_4 {
    u8 pad_00[0xC];
    union { u8 u8; u32 u32; } unk_0C;   /* accessed as both */
} S_819ACB28_4;   /* packed_value in func_80024328 */

typedef struct S_819ACB28_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_819ACB28_5;   /* ((S_819ACB28_0 *)object)->unk_08 in func_80024328 */



typedef struct CounterView {
    u16 value;
    u16 pad[5];
} CounterView;

typedef struct FlagsView {
    s32 value;
    s32 pad[2];
} FlagsView;


void func_80024328(void *object, Rec_func_800249DC_arg0 *record, S_819ACB28_4 *packed_value)
{
    s16 mode;
    u16 mode_value;
    S_819ACB28_3 *offsets;
    S_819ACB28_1 *data_ptr;

    D_80027452[0] = D_80027452[0] + 1;
    mode = ((S_819ACB28_0 *)object)->unk_2C.s;
    mode_value = ((S_819ACB28_0 *)object)->unk_2C.u;

    if (mode == 0) {
        data_ptr = ((S_819ACB28_5 *)(((S_819ACB28_0 *)object)->unk_08))->unk_0C;
        if (((S_819ACB28_0 *)object)->unk_2E == 0) {
            if (func_8003DE58(data_ptr->unk_08, data_ptr,
                              (u8 *)object + 0x24, 0) == 0) {
                if (data_ptr->unk_14 & 0x8000) {
                    ((S_819ACB28_0 *)object)->unk_28.s = -0x40;
                }
            }
            ((S_819ACB28_0 *)object)->unk_2E = 1;
        }

        offsets = ((S_819ACB28_5 *)(((S_819ACB28_0 *)object)->unk_08))->unk_08;
        record->unk_00.at02_s16.v =
            offsets->unk_02 + ((S_819ACB28_0 *)object)->unk_24;
        record->unk_06 =
            offsets->unk_06 + ((S_819ACB28_0 *)object)->unk_26;
        record->unk_0A =
            offsets->unk_0A + ((S_819ACB28_0 *)object)->unk_28.u;
        if (func_800249DC(record) != 0) {
            func_8004491C((u8 *)object - 0x20, func_80045340);
            ((S_819ACB28_0 *)object)->unk_2C.u = ((S_819ACB28_0 *)object)->unk_2C.u + 1;
            return;
        }
    } else if (mode == 1) {
        if (packed_value->unk_0C.u8 < 0xC0) {
            packed_value->unk_0C.u32 += 0x202020;
            return;
        }
        ((S_819ACB28_0 *)object)->unk_2C.u = mode_value + 1;
        return;
    } else if (mode == 2) {
        packed_value->unk_0C.u32 += 0xFFEFEFF0;
        if (packed_value->unk_0C.u8 == 0) {
            ((S_819ACB28_0_pre *)object)[-1].unk_00 |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
    }
}


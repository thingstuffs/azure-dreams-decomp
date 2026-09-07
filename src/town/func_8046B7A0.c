#include "common.h"

typedef struct S_8001C7A0_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_8001C7A0_0;   /* root in func_8001C7A0 */

typedef struct S_8001C7A0_1 {
    u8 pad_00[0x10];
    union { s32 s; void * u; } unk_10;   /* accessed as both */
} S_8001C7A0_1;   /* owner in func_8001C7A0 */



extern s32 func_8001E670(s32);
extern s8 D_80016000[];
extern s16 D_80018740[];
extern u8 D_80018748[];

typedef struct {
    u8 flags[4];
    volatile s32 next;
} TownRecord;

extern TownRecord D_800186C0[];

void func_8001C7A0(void)
{
    if (D_800186C0[0].next != 0) {
        s16 *value_base = D_80018740;
        TownRecord *record = D_800186C0;
        s16 *value;
        s32 i = 0;

outer:
        value = value_base;

        do {
            if ((record->flags[i] != 0) != (func_8001E670(*value) != 0)) {
                break;
            }
            i++;
            value++;
        } while (i < 4);

        if (i == 4) {
            void *root = *(void **)D_80016000;
            void *owner = ((S_8001C7A0_0 *)root)->unk_1C;

            ((S_8001C7A0_1 *)owner)->unk_10.s = record->next;
            return;
        }
        record++;
        i = 0;
        if (record->next != 0) {
            goto outer;
        }
    }

    {
        void *root = *(void **)D_80016000;
        void *owner = ((S_8001C7A0_0 *)root)->unk_1C;

        ((S_8001C7A0_1 *)owner)->unk_10.u = D_80018748;
    }
}

/* MECHANISM: an 8-byte record type keeps s2 as the record base without holding
   a separate +4 field pointer; the s16 base/cursor occupy s3/s1 and i occupies s0.
   The apparent 0x8001C864 callee is the row-local shared epilogue, so success returns. */

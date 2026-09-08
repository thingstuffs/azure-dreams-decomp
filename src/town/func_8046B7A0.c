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

/* Selects the first record matching all four flag checks, or the default data. */
void func_8001C7A0(void)
{
    if (D_800186C0[0].next != 0) {
        s16 *check_values = D_80018740;
        TownRecord *record = D_800186C0;
        s16 *check_value;
        s32 flag_index = 0;

check_record:
        check_value = check_values;

        do {
            if ((record->flags[flag_index] != 0) != (func_8001E670(*check_value) != 0)) {
                break;
            }
            flag_index++;
            check_value++;
        } while (flag_index < 4);

        if (flag_index == 4) {
            void *root = *(void **)D_80016000;
            void *owner = ((S_8001C7A0_0 *)root)->unk_1C;

            ((S_8001C7A0_1 *)owner)->unk_10.s = record->next;
            return;
        }
        record++;
        flag_index = 0;
        if (record->next != 0) {
            goto check_record;
        }
    }

    {
        void *root = *(void **)D_80016000;
        void *owner = ((S_8001C7A0_0 *)root)->unk_1C;

        ((S_8001C7A0_1 *)owner)->unk_10.u = D_80018748;
    }
}


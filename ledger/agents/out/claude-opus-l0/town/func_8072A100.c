#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct SceneStateVtbl {
    u8 pad_00[0x330];
    s32 (*unk_330)(M2C_UNK);
    s32 (*unk_334)(M2C_UNK);
} SceneStateVtbl;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_80016100 */




M2C_UNK func_80017684();                         /* extern */
M2C_UNK func_800176FC();                         /* extern */
s32 func_8001777C();                         /* extern */
s32 func_80017918();                                /* extern */
extern Rec_D_80016000 *D_80016000;
extern s16 D_80017A6C;
extern s16 D_80017A74;


/* Refresh the four menu labels plus the two fixed rows from the scene's state query. */
void func_80016100(void) {
    s16 *label_cursor;
    s16 *state_cursor;
    s32 state;
    s32 slot;

    state = ((SceneStateVtbl *)(D_80016000->unk_20))->unk_330(0);
    slot = 0;
    label_cursor = &D_80017A6C;
    state_cursor = &D_80017A74;
loop_1:
    if (state == *state_cursor) {
        func_80017684(*label_cursor++);
    } else {
        func_800176FC(*label_cursor++);
    }
    state_cursor += 1;
    slot += 1;
    if (slot >= 4) {
        if (((SceneStateVtbl *)(D_80016000->unk_20))->unk_334(0) != 5) {
            func_80017684(0xBE0);
        } else {
            func_800176FC(0xBE0);
        }
        if ((func_80017918() < 5) || ((func_80017918() >= 5) && (func_8001777C(0x1460) != 0))) {
            func_80017684(0xBE1);
        } else {
            func_800176FC(0xBE1);
        }
        return;
    }
    goto loop_1;
}

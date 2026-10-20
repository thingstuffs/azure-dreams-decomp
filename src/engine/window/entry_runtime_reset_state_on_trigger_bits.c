#include "common.h"

#include "common.h"
#include "records/Rec_func_80036210_arg0.h"

#include "records/Rec_D_80081FDC.h"


typedef struct S_80036210_2 {
    u8 pad_00[0x80];
    s32 unk_80;
} S_80036210_2;   /* ((Rec_func_80036210_arg0 *)arg0)->unk_74.as_pv in func_80036210 */


void create_cursor_object(s32 task_buffer, Rec_D_80081FDC *record, s32 *source, s16 state_value, s32 setup_arg);
extern u8 D_80081FDC[];
extern u8 D_80082414[];
void runtime_reset_state_on_trigger_bits();

/* Initialize the object's runtime state and set its next handler. */
void func_80036210(Rec_func_80036210_arg0 *object) {
    create_cursor_object(&D_80082414, &D_80081FDC, object, 0,
        ((S_80036210_2 *)(((Rec_func_80036210_arg0 *)object)->unk_74.as_pv))->unk_80);
    object->unk_4C = 0;
    object->unk_68 = &runtime_reset_state_on_trigger_bits;
}

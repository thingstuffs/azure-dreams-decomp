#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"


typedef struct S_8008DB0C_1 {
    u8 pad_00[0x8A];
    s16 unk_8A;
} S_8008DB0C_1;   /* call_obj in func_8008DB0C */



extern void func_80048A44(void *, u8, s32, s32);
extern s32 func_80098C80(s32);
extern void func_8009F644(void *, s32, s16, s32);

extern s32 D_80082EB0;
extern s16 D_80083228;
extern u8 D_800DD130[];

/* Initializes object state and its directional display, then dispatches an action. */
void func_8008DB0C(void *obj, s32 unused, void *display, s32 mode, u16 variant) {
    u8 *direction_table = D_800DD130;
    s32 lookup_result;
    u16 saved_mode;

    ((Rec_func_8008ACDC_arg0 *)obj)->unk_9A.as_s8 = 0x26;
    ((Rec_func_8008ACDC_arg0 *)obj)->unk_9B.as_s8 = 0;
    ((Rec_func_8008ACDC_arg0 *)obj)->unk_8C.as_s32 = 0;
    (*(u8 **)((u8 *)display + 0x2C)) = direction_table;
    saved_mode = mode;
    func_80048A44(
        display,
        direction_table[((D_80083228 + ((Rec_func_8008ACDC_arg0 *)obj)->unk_2A + 0x100) >> 9) & 7],
        0,
        1);

    ((Rec_func_8008ACDC_arg0 *)obj)->unk_72 = saved_mode;
    ((Rec_func_8008ACDC_arg0 *)obj)->unk_73 = (s8)variant;

    {
        s32 action_kind;
        register void *action_obj;
        s32 field_value;
        register s32 action_arg;

        if (D_80082EB0 != 0) {
            lookup_result = func_80098C80(D_80082EB0);
            action_obj = obj;
            action_kind = 0x68;
            field_value = ((Rec_func_8008ACDC_arg0 *)obj)->unk_8A;
            action_arg = (s16)lookup_result;
        } else {
            action_kind = 0x88;
            action_obj = obj;
            field_value = ((S_8008DB0C_1 *)action_obj)->unk_8A;
            action_arg = 0;
        }
        func_8009F644(action_obj, action_kind, field_value, action_arg);
    }
}


/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_80033D08();
void func_8003DB94();
void func_800478B8();
M2C_UNK func_8008F134();
M2C_UNK func_8009706C();
s32 func_8009CFE0();
s32 func_800C2E1C();
s32 func_800C2F14();
extern s32 D_800814A0[3];


typedef struct S_800AAB20_0_pre {
    u16 unk_00;
} S_800AAB20_0_pre;   /* the 0x2 bytes before arg0 in func_800AAB20, addressed as arg0[-1] */



/* Updates an object and its display state, or removes it when requested. */
void func_800AAB20(void *object, M2C_UNK update_ctx, Rec_D_80082E80 *display) {
    s32 frame_index;
    s8 *active_flag;

    if (func_8009CFE0(object, update_ctx) != 0) {
        func_8008F134(object);
        active_flag = ((Rec_D_80082D58 *)object)->unk_98.as_ps8;
        if (active_flag != NULL) {
            *active_flag = 0;
        }
        func_80033D08(object);
        ((S_800AAB20_0_pre *)object)[-1].unk_00 = (u16) (((S_800AAB20_0_pre *)object)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        return;
    }
    func_8009706C(update_ctx);
    ((Rec_D_80082D58 *)object)->unk_50.as_xcdccad(object, object, update_ctx, display);
    if (!(((S_800AAB20_0_pre *)object)[-1].unk_00 & 0x8000)) {
        frame_index = func_800C2E1C(((Rec_D_80082D58 *)object)->unk_72, ((Rec_D_80082D58 *)object)->unk_64);
        if (((Rec_D_80082D58 *)object)->unk_74 != frame_index) {
            func_8003DB94(display, ((Rec_D_80082D58 *)object)->unk_78[frame_index], display->unk_04.as_s8);
            ((Rec_D_80082D58 *)object)->unk_74 = frame_index;
        }
        {
            s32 display_flags;

            if ((func_800C2F14(((Rec_D_80082D58 *)object)->unk_72, ((Rec_D_80082D58 *)object)->unk_64) << 0x10) != 0) {
                display_flags = display->unk_14.at00_u16.v | 1;
            } else {
                display_flags = display->unk_14.at00_u16.v & 0xFFFE;
            }
            display->unk_14.at00_u16.v = (u16) display_flags;
        }
        func_800478B8(display);
    }
}

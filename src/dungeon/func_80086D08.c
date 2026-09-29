#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"

extern u8 D_800DD050[];
extern u8 D_800DD0E0[];

extern void func_80048A44(void *, s16, s16, s32);

/* Reset entity state and select its animation page and directional entry. */
void func_8008C468(void *entity, void *unused, void *animation, EntityRec *state) {
    if (!(((Rec_func_8008ACDC_arg0 *)entity)->unk_98 & 0xC)) {
        u8 *page;
        u8 *current_page;

        ((Rec_func_8008ACDC_arg0 *)entity)->unk_9A.as_u8 = 0x16;
        ((Rec_func_8008ACDC_arg0 *)entity)->unk_9B.as_u8 = 0;
        ((Rec_func_8008ACDC_arg0 *)entity)->unk_8C.as_s32 = 0;
        ((Rec_func_8008ACDC_arg0 *)entity)->unk_A2 &= 0xFFFE;
        if (state->flags1C & 0x100000) {
            u8 *alternate_page = D_800DD0E0;
            current_page = (*(u8 **) ((u8 *)animation + 0x2C));
            page = alternate_page;
        } else {
            current_page = (*(u8 * volatile *) ((u8 *)animation + 0x2C));
            page = D_800DD050;
        }
        if (current_page != page) {
            entity = animation;
            (*(u8 * *)((u8 *)entity + 0x2C)) = page;
            func_80048A44(entity, *(u8 *)((((gameWork.view.viewAngle + state->facing + 0x100) >> 9) & 7) + (u32)page), 0, 1);
        }
    }
}

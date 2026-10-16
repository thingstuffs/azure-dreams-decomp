#include "common.h"

extern void cardBootShowNoSavedGameNotice(void *value);
extern void cardBootShowDeleteConfirmation(void *owner, void *data);

extern s32 D_80083E98[][32];
extern s32 D_80025788;
extern s32 D_8002593C;
extern s32 D_80024FAC;


/* Sets up the object from its indexed table entry and assigns its state data. */
void cardBootConfirmSelectedSlotDeletion(void *state) {
    void *object = (u8 *)state - 0x20;
    s32 table_index = *(s32 *)((u8 *)state + 0x28);

    if (D_80083E98[table_index][0] != 0) {
        s32 *state_data = &D_80025788;
        void *update_data = (u8 *)state + 0x38;
        *(s32 **)((u8 *)state + 0x34) = state_data;
        cardBootShowDeleteConfirmation(object, update_data);
        *(s32 **)((u8 *)state - 0x10) = &D_80024FAC;
    } else {
        *(s32 **)((u8 *)state + 0x34) = &D_8002593C;
        cardBootShowNoSavedGameNotice(object);
        *(s32 **)((u8 *)state - 0x10) = &D_80024FAC;
    }

}

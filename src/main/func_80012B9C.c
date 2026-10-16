#include "common.h"
#include "m2c_compat.h"

void cardBootDestroySlotSelectionMenu();                         /* extern */
typedef struct Node8002BB08 Node8002BB08;
Node8002BB08 *initCardBootRequestObject();                /* extern */

typedef struct S_80025B9C_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_80025B9C_0;   /* arg0 in cardBootReturnFromSlotMenu */

/* Processes the object header and passes its stored value to initCardBootRequestObject. */
void cardBootReturnFromSlotMenu(void *object_data) {
    cardBootDestroySlotSelectionMenu(object_data - 0x20);
    initCardBootRequestObject(((S_80025B9C_0 *)object_data)->unk_20, 0);
}

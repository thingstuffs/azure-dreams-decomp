#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"

typedef struct S_80094E34_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80094E34_1;   /* object in func_80094E34 */


extern s32 D_80081484;
extern s32 D_800E3540;

/* Clear the root and linked object flags, saving and resetting D_80081484 when the root flag is set. */
void func_80094E34(void) {
    EntityRec *root;
    S_80094E34_1 *linkedObject;
    s32 savedGlobalValue;
    s32 rootFlags;

    root = D_800E3D7C;
    if (root->flags1C & 0x100000) {
        linkedObject = root->unk_124;
        if (linkedObject != 0) {
            linkedObject->unk_1C = (s32)(linkedObject->unk_1C & 0xFFF7FFFF);
        }
        rootFlags = root->flags1C;
        savedGlobalValue = D_80081484;
        D_80081484 = 0;
        root->flags1C = rootFlags & 0xFFEFFFFF;
        D_800E3540 = savedGlobalValue;
    }
}

#include "common.h"

typedef struct S_80094E34_0 {
    u8 pad_00[0x1C];
    union { s32 s; volatile s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0x104];
    void * unk_124;
} S_80094E34_0;   /* root in func_80094E34 */

typedef struct S_80094E34_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80094E34_1;   /* object in func_80094E34 */



extern volatile s32 D_80081484;
extern s32 D_800E3540;
extern void *D_800E3D7C;

/* Clear the root and linked object flags, saving and resetting D_80081484 when the root flag is set. */
void func_80094E34(void) {
    void *root;
    S_80094E34_1 *linkedObject;
    s32 savedGlobalValue;
    s32 rootFlags;

    root = D_800E3D7C;
    if (((S_80094E34_0 *)root)->unk_1C.s & 0x100000) {
        linkedObject = ((S_80094E34_0 *)root)->unk_124;
        if (linkedObject != 0) {
            linkedObject->unk_1C = (s32)(linkedObject->unk_1C & 0xFFF7FFFF);
        }
        rootFlags = ((S_80094E34_0 *)root)->unk_1C.u;
        savedGlobalValue = D_80081484;
        D_80081484 = 0;
        ((S_80094E34_0 *)root)->unk_1C.u = rootFlags & 0xFFEFFFFF;
        D_800E3540 = savedGlobalValue;
    }
}

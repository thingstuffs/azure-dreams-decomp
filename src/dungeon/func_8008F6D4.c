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

void func_80094E34(void) {
    void *root;
    S_80094E34_1 *object;
    s32 saved;
    s32 flags;

    root = D_800E3D7C;
    if (((S_80094E34_0 *)root)->unk_1C.s & 0x100000) {
        object = ((S_80094E34_0 *)root)->unk_124;
        if (object != 0) {
            object->unk_1C = (s32)(object->unk_1C & 0xFFF7FFFF);
        }
        flags = ((S_80094E34_0 *)root)->unk_1C.u;
        saved = D_80081484;
        D_80081484 = 0;
        ((S_80094E34_0 *)root)->unk_1C.u = flags & 0xFFEFFFFF;
        D_800E3540 = saved;
        
    }
}

/* MECHANISM: Frameless leaf holds the root pointer across both flag regions and pins the saved word in $a1.
   Splitting the final flag read/store gives $v0 its retail lifetime and forces the page base into $v1.
   Volatile ordering preserves root-load, saved-load, clear-store, root-store and closes the last lw swap. */

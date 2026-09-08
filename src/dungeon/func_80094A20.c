#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8009A180_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x3C];
    union { s32 s; void * u; } unk_5C;   /* accessed as both */
} S_8009A180_0;   /* arg1 in func_8009A180 */


typedef struct S_8009A180_2 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8009A180_2;   /* node in func_8009A180 */


extern void func_8009A028(void *arg0);


s32 func_8009A180(void *arg0, S_8009A180_0 *arg1) {
    register u32 carrier ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 flags;
    s32 link;
    S_8009A180_2 *node;
    u32 mask;

    if (arg0 == arg1) {
        result = 0;
        flags = arg1->unk_1C;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        carrier = 0x80000000;
        arg1->unk_1C = flags | carrier;
        return;
    }

    mask = 0x80000000;
    result = ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32;
    if (result >= 0) {
        result |= mask;
        ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 = result;
        carrier = (u32)arg0;
        func_8009A028((void *)carrier);

        link = arg1->unk_5C.s;
        ((Rec_D_800E3D7C *)arg0)->unk_5C = link;
        ASM_KEEP(link);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        node = (void *)(link + 0x20);
        ASM_KEEP(node);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        carrier = (u32)node->unk_58;
        ASM_KEEP(carrier);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        result = 1;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ((Rec_D_800E3D7C *)arg0)->unk_58 = (void *)carrier;
        carrier = (u32)((u8 *)arg0 - 0x20);
        node->unk_58 = (void *)carrier;
        arg1->unk_5C.u = (void *)carrier;
        return;
    }

    return 0;
}

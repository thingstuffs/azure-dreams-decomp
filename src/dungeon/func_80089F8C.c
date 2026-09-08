#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80048A44();
M2C_UNK func_8009A66C();
M2C_UNK func_8009F644();
s32 func_800A44E0();
s32 func_800A7234();
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_80081485;
extern s16 D_80083228;
extern u16 D_80083460[];
extern u8 D_800DD0D0[];

/* Updates actor state and animation when the position checks succeed. */
void func_8008F6EC(void *state, void *target, void *sprite, void *actor) {
    s16 probe_a;
    s16 probe_b;
    s16 probe_c;
    s32 direction_offset;
    register s32 can_animate ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    can_animate = 0;
    if (D_80081485 == 0x13) {
        can_animate = (func_8009A66C(((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, sprite, actor, 0x20) << 0x10) > 0;
    } else if ((func_800A44E0(((Rec_D_800E3D7C *)target)->unk_00.at02_u16.v, ((Rec_D_800E3D7C *)target)->unk_04.at02_u16.v, ((Rec_D_800E3D7C *)actor)->unk_88.as_s16, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16) << 0x10) == 0) {
        direction_offset = ((u16) ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 8) & 0xE;
        if ((func_800A7234((s16) (((Rec_D_80082E80 *)sprite)->unk_24 + *(u16 *)(D_8006CCD8 + direction_offset)), (s16) (((Rec_D_80082E80 *)sprite)->unk_25 + *(u16 *)(D_8006CCE8 + direction_offset)), ((Rec_D_800E3D7C *)actor)->unk_88.as_s16, &probe_a, &probe_b, &probe_c) << 0x10) != 0) {
            can_animate = 1;
        }
    }
    if (can_animate != 0) {
        ((Rec_func_8008ACDC_arg0 *)state)->unk_9A.as_s8 = 0x1F;
        ((Rec_func_8008ACDC_arg0 *)state)->unk_9B.as_s8 = 0;
        ((Rec_func_8008ACDC_arg0 *)state)->unk_8C.as_s32 = 0;
        (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DD0D0;
        func_80048A44(sprite, D_800DD0D0[(((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100)) >> 9) & 7], 0, 1);
        D_80083460[5] = D_80083460[5] + 1;
        func_8009F644(actor, 0x28, 0, 0);
    }
}

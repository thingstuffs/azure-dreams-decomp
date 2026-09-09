#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800CFCB4.h"

typedef void (*Callback)(void *, void *, void *, s32);



typedef struct S_8009B6B4_2_pre {
    u16 unk_00;
} S_8009B6B4_2_pre;   /* the 0x2 bytes before arg0 in func_8009B6B4, addressed as arg0[-1] */

typedef struct S_8009B6B4_2 {
    u8 pad_00[0x50];
    void * unk_50;
} S_8009B6B4_2;   /* arg0 in func_8009B6B4 */



extern void func_80095388(void *);
extern void func_8009539C(void *);
extern s16 func_8008F170(void *, void *);
extern void func_8008F27C(void *, void *, s16);
extern s32 func_8008F294(void *, void *);
extern void func_8008F664(void *, void *);
extern s32 func_8008C180(s16, s16);
extern s32 func_800C1D44(u16);
extern void SD_Call(u32);

extern u8 D_8009B454[];
extern s16 D_800D45AA[];
extern u8 D_800FE488[];

/* Update object motion, handle contact, and play the tile height sound. */
void func_8009B6B4(void *object, Rec_D_800CFCB4 *collision, Rec_D_800E3D7C *motion, s32 callback_arg) {
    s16 contact_height;
    s32 contact_height_ext;

    func_80095388(motion);
    if (motion->unk_14.as_s32 > 0x200000) {
        motion->unk_14.as_s32 = 0x200000;
    }
    func_8009539C(motion);
    contact_height = func_8008F170(motion, D_800FE488);
    func_8008F294(collision, motion);
    func_8008F664(collision, motion);
    contact_height_ext = contact_height;
    if (motion->unk_08.at02_s16.v >= contact_height_ext) {
        func_8008F27C(collision, motion, contact_height_ext);
        ((Callback *)(*(void **)((u8 *)object + 0x58)))[1](object, collision, motion, callback_arg);
    } else if (collision->unk_3B != 0) {
        motion->unk_14.as_s32 = 0;
        ((Callback *)(*(void **)((u8 *)object + 0x58)))[1](object, collision, motion, callback_arg);
    }
    if ((((S_8009B6B4_2_pre *)object)[-1].unk_00 & 0x8000) == 0 &&
        D_8009B454 == ((S_8009B6B4_2 *)object)->unk_50) {
        s32 tile_type;

        tile_type = func_800C1D44((u16)func_8008C180(
            motion->unk_00.at02_s16.v, motion->unk_04.at02_s16.v));
        if (tile_type != 0) {
            s16 *thresholds = D_800D45AA;
            s16 height = motion->unk_08.at02_s16.v;
            s16 threshold = thresholds[tile_type];

            if (height > threshold) {
                SD_Call(0x517);
            }
        }
    }
}

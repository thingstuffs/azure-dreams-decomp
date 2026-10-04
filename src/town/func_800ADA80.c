#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"


typedef void (*Callback)(void *, s32, void *);

extern void func_80033D08(void *, s32);
/* garbage-passthru: a2/a3 survive func_800AAFE0; explicit arguments add saves/reloads absent from retail. */
extern s32 func_800352FC(void);
extern void func_800AAF5C(void);
extern void func_800AAFE0(void *, s32);
extern void func_800C2C80(void *, void *, s32, s32);
extern void func_800C2CB0(void *, void *, void *, s8);
extern s32 func_800C2E1C(s16, s16);
extern s32 func_800C2F14(s16, s16);

extern s32 D_800834A8;


typedef struct S_800AB1E0_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800AB1E0_0;   /* ref in func_800AB1E0 */

typedef struct S_800AB1E0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800AB1E0_1;   /* base in func_800AB1E0 */


void func_800AB1E0(void *ptr, s32 value, Rec_D_80082E80 *record) {
    GameWork *work = &gameWork;
    s16 buf[12];
    s32 index;
    u16 flag_value;

    if (D_800834A8 == 0) {
        func_80033D08(ptr, value);
        (*(u16 *)((u8 *)ptr + (-2))) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }

    func_800AAFE0(buf, 0);
    if (buf[1] != D_80083780.x.w.i || buf[3] != D_80083780.y.w.i ||
        buf[5] != D_80083780.z.w.i || func_800352FC() != 0 ||
        (work->buttons & 0xF000) != 0) {
        func_800AAF5C();
        (*(s16 *)((u8 *)ptr + (0x90))) = 0;
    } else {
        (*(s16 *)((u8 *)ptr + (0x90))) = (*(s16 *)((u8 *)ptr + (0x90))) + 1;
        if ((*(s16 *)((u8 *)ptr + (0x90))) > 100) {
            (*(s16 *)((u8 *)ptr + (0x90))) = 100;
        }
    }
    (*(Callback *)((u8 *)ptr + (0x50)))(ptr, value, record);
    if (((*(u16 *)((u8 *)ptr + (-2))) & 0x8000) != 0) {
        return;
    }

    index = func_800C2E1C((*(s16 *)((u8 *)ptr + (0x72))), (*(s16 *)((u8 *)ptr + (0x64))));
    if ((*(s16 *)((u8 *)ptr + (0x74))) != index) {
        func_800C2CB0(ptr, record, ((void **)(*(void * *)((u8 *)ptr + (0x78))))[index],
                      record->unk_04.as_s8);
        (*(s16 *)((u8 *)ptr + (0x74))) = index;
    }

    if (((*(u8 *)((u8 *)ptr + (0x71))) & 1) == 0) {
        if ((s16)func_800C2F14((*(s16 *)((u8 *)ptr + (0x72))),
                               (*(s16 *)((u8 *)ptr + (0x64)))) == 0) {
            flag_value = record->unk_14.at00_u16.v;
                         /* MATCH: keep each clear load in its own arm. */
            flag_value = (u16)(flag_value - (flag_value & 1));
        } else {
            flag_value = record->unk_14.at00_u16.v | 1;
        }
    } else {
        if ((s16)func_800C2F14((*(s16 *)((u8 *)ptr + (0x72))),
                               (*(s16 *)((u8 *)ptr + (0x64)))) != 0) {
            flag_value = record->unk_14.at00_u16.v;

            flag_value &= 0xFFFE;
        } else {
            flag_value = record->unk_14.at00_u16.v | 1;
        }
    }

         /* MATCH: keep the flag store in the common tail. */
    record->unk_14.at00_u16.v = flag_value;
    func_800C2C80(ptr, record, 0, 0);
}

#include "common.h"


extern s32 func_800AB1C0(void);
extern void func_800A4ACC(void *);
extern void func_800CAA94(void *, s32, s32);

extern u16 D_80013714;
extern u16 D_80083462;
extern u8 D_800C9F34;


typedef struct S_800CAAC8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x22];
    u16 unk_B6;
} S_800CAAC8_0;   /* entity in func_800CAAC8 */

typedef struct S_800CAAC8_1 {
    u8 pad_00[0x71];
    u8 unk_71;
    u8 pad_72[0x18];
    s16 unk_8A;
} S_800CAAC8_1;   /* actor in func_800CAAC8 */

/* Updates the actor and entity counter, then advances the entity or sets its callback. */
void func_800CAAC8(void *entity_ptr, s32 input_arg_1, s32 input_arg_2, void *actor_ptr)
{
    s32 update_arg_1 = input_arg_1;
    s32 update_arg_2 = input_arg_2;
    void *actor = actor_ptr;
    u16 remaining_count;

    if (func_800AB1C0() == 0) {
        goto check_flag;
    }

    func_800A4ACC(actor);
    remaining_count = ((S_800CAAC8_0 *)entity_ptr)->unk_B6 - 1;
    ((S_800CAAC8_0 *)entity_ptr)->unk_B6 = remaining_count;

    if ((remaining_count << 16) > 0) {
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        if (!(D_80013714 & 8)) {
            goto set_callback;
        }
    }

    if (((S_800CAAC8_1 *)actor)->unk_71 != ((S_800CAAC8_1 *)actor)->unk_8A) {
        goto set_callback;
    }

    func_800CAA94(entity_ptr, update_arg_1, update_arg_2);
    return;

set_callback:
    ((S_800CAAC8_0 *)entity_ptr)->unk_8C = &D_800C9F34;

check_flag:
    if (D_80083462 & 0x80) {
        ((S_800CAAC8_0 *)entity_ptr)->unk_92 = -0x20;
    }
}


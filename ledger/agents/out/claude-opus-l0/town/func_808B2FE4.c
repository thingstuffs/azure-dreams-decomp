#include "common.h"

typedef struct S_808B2FE4_0 {
    u8 pad_00[0x8];
    s32 * unk_08;
} S_808B2FE4_0;   /* *(void **)0xA0700F5C in func_808B2FE4 */

typedef struct S_808B2FE4_1 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_808B2FE4_1;   /* status in func_808B2FE4 */



extern s32 func_8070021C();
extern s32 func_807002A4();
extern s32 func_807002D4();
extern s32 func_8070090C();

/* When the gate and the counter both pass, refresh the status byte and return the stage handler's result. */
s32 func_808B2FE4(s32 entry)
{
    S_808B2FE4_1 *status;

    if ((func_8070021C(1) != 0) &&
        (*((S_808B2FE4_0 *)(*(void **)0xA0700F5C))->unk_08 >= 2)) {
        func_807002A4(1);
        status = *(void **)0xA0700F40;
        status->unk_0E = status->unk_0E;
        return func_8070090C();
    }
    func_807002D4(1);
    return entry;
}

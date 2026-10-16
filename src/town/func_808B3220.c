#include "common.h"

typedef struct S_80700A20_0 {
    u8 pad_00[0x8];
    s32 *unk_08;
} S_80700A20_0;

typedef struct S_80700A20_1 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_80700A20_1;

extern s32 func_8070021C();
extern s32 func_807002A4();
extern s32 func_807002D4();
extern s32 func_80700B7C();

/* When gate 2 and the counter both pass, refresh the status byte and return the stage handler's result. */
s32 func_80700A20(s32 entry)
{
    S_80700A20_1 *status;

    if ((func_8070021C(2) != 0) &&
        (*((S_80700A20_0 *)(*(void **)0xA0700F5C))->unk_08 > 0)) {
        func_807002A4(2);
        status = *(void **)0xA0700F40;
        status->unk_0E = status->unk_0E;
        return func_80700B7C();
    }
    func_807002D4(2);
    return entry;
}

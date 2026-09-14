#include "common.h"

typedef struct S_808B32AC_0 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_808B32AC_0;   /* temp_v1 in func_808B32AC */



extern s32 func_8070021C();
extern s32 func_807002A4();
extern s32 func_807002D4();
extern s32 func_80700B7C();

s32 func_808B32AC(s32 arg0)
{
    S_808B32AC_0 *temp_v1;

    if (func_8070021C(2) == 0) {
        func_807002D4(2);
        return arg0;
    }
    else {
        func_807002A4(2);
        temp_v1 = *(void **)0xA0700F40;
        temp_v1->unk_0E = temp_v1->unk_0E;
        func_80700B7C();
    }
}

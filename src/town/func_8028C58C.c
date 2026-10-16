/* Relink of matched town/func_8032C1F0; every changed retail word is a paired relocation. */
#include "common.h"

extern void func_80019B54(s32 record, s32 entry_index);
extern void func_80019BC0(void);
extern s32 func_8001B0C8(void);

/* Process the request after checking the threshold of 25. */
void func_80016D8C(s32 request, s32 context) {
    if (func_8001B0C8() >= 0x19) {
        func_80019BC0();
    }
    func_80019B54(request, context);
}

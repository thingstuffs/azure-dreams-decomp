#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B648C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800B648C_0;   /* arg0 in func_800B648C */

typedef struct S_800B648C_1 {
    u8 pad_00[0xC];
    union { s32 s; void * u; } unk_0C;   /* accessed as both */
} S_800B648C_1;   /* var_s1 in func_800B648C */


void *func_800B6464();                       /* extern */
s32 func_800B677C();                         /* extern */

/* Stores the fetched chain and initializes its terminal link. */
void func_800B648C(S_800B648C_0 *owner, M2C_UNK source) {
    S_800B648C_1 *tail;

    tail = func_800B6464(source);
    owner->unk_0C = tail;
    if (tail->unk_0C.s != 0) {
        do {
            tail = tail->unk_0C.u;
        } while (tail->unk_0C.s != 0);
    }
    tail->unk_0C.s = func_800B677C(source);
}

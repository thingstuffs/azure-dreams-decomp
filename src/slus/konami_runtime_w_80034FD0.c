#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_D_80082A38.h"



/* Tests whether the stored address differs from the record's offset-8 address. */
s32 func_80034FD0(void *record) {
    return ((Rec_D_80082A38 *)record)->unk_10 != (s32) (record + 8);
}

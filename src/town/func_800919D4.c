#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_8008F134_1 {
    u8 pad_00[0x4];
    void ** unk_04;
} S_8008F134_1;   /* temp_v1 in func_8008F134 */

void func_8008F134(Rec_func_80094268_arg0 *arg0) {
    S_8008F134_1 *temp_v1;

    temp_v1 = arg0->unk_00.as_pv;
    if (temp_v1 != NULL) {
        temp_v1->unk_04 = (void **) arg0->unk_04.as_ppv;
        *arg0->unk_04.as_ppv = arg0->unk_00.as_pv;
        arg0->unk_00.as_pv = NULL;
        arg0->unk_04.as_ppv = NULL;
    }
}

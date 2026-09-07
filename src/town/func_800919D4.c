#include "common.h"
#include "m2c_compat.h"

typedef struct S_8008F134_0 {
    void * unk_00;
    void ** unk_04;
} S_8008F134_0;   /* arg0 in func_8008F134 */

typedef struct S_8008F134_1 {
    u8 pad_00[0x4];
    void ** unk_04;
} S_8008F134_1;   /* temp_v1 in func_8008F134 */

void func_8008F134(S_8008F134_0 *arg0) {
    S_8008F134_1 *temp_v1;

    temp_v1 = arg0->unk_00;
    if (temp_v1 != NULL) {
        temp_v1->unk_04 = (void **) arg0->unk_04;
        *arg0->unk_04 = arg0->unk_00;
        arg0->unk_00 = NULL;
        arg0->unk_04 = NULL;
    }
}

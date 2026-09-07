#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001BBB8_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001BBB8_2;   /* temp_v1 in func_8001BBB8 */

typedef struct S_8001BBB8_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_8001BBB8_3;   /* ((S_8001BBB8_2 *)temp_v1)->unk_04 in func_8001BBB8 */




/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_8001BBB8_0 {
    u8 pad_00[0x69C];
    void * unk_69C;
} S_8001BBB8_0;   /* arg0 in func_8001BBB8 */

typedef struct S_8001BBB8_1 {
    void * unk_00;
} S_8001BBB8_1;   /* temp_v1 in func_8001BBB8 */

void func_8001BBB8(void *arg0) {
    S_8001BBB8_1 *temp_v1;

    temp_v1 = ((S_8001BBB8_0 *)arg0)->unk_69C;
    ((S_8001BBB8_3 *)(((S_8001BBB8_2 *)temp_v1)->unk_04))->unk_08 = 0xA0;
    ((S_8001BBB8_3 *)(((S_8001BBB8_2 *)temp_v1)->unk_04))->unk_0A = 0x78;
    temp_v1->unk_00 = (void *) (arg0 + 0x24);
}

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

/* Set the linked coordinates to (160, 120) and reference the object's embedded data. */
void func_8001BBB8(void *object) {
    S_8001BBB8_1 *linked_state;

    linked_state = ((S_8001BBB8_0 *)object)->unk_69C;
    ((S_8001BBB8_3 *)(((S_8001BBB8_2 *)linked_state)->unk_04))->unk_08 = 0xA0;
    ((S_8001BBB8_3 *)(((S_8001BBB8_2 *)linked_state)->unk_04))->unk_0A = 0x78;
    linked_state->unk_00 = (void *) (object + 0x24);
}

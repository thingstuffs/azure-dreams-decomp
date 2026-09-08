/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80170A54_0 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_80170A54_0;   /* base in func_80170A54 */

typedef struct S_80170A54_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80170A54_1;   /* object in func_80170A54 */

typedef struct S_80170A54_2 {
    u16 unk_00;
} S_80170A54_2;   /* arg0 in func_80170A54; pointer addresses record offset 0x2 */


__asm__(".set D_80080000, 0x80080000");

void func_800489F4(); /* extern */
extern s32 D_800814A0[3];
extern void *D_800814A8[3];
extern u8 D_80082E80[];
extern s16 D_80083228[5];
extern u8 D_80080000[];

/* Applies a direction-indexed table entry in state 2 and sets record and global flags. */
void func_80170A54(void *record_data) {
    s32 required_state = 2;
    register u8 *memory_base ASM_REG("$4") = (u8 *)0x80080000;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register u8 *state_data = D_80082E80;
    S_80170A54_1 *active_object;

    ASM_KEEP(state_data);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    {
        register u8 direction_entry;
        active_object = *(void **)(memory_base + 0x14A8);
        if (((S_80170A54_0 *)state_data)->unk_04 != required_state)
            goto done;
        direction_entry = ((u8 **)state_data)[0xB][
                 (((s32) (D_80083228[0] +
                          active_object->unk_2A +
                          0x100) >> 9) & 7)];
        func_800489F4(state_data, direction_entry,
            4, 1);
        ((S_80170A54_2 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_80170A54_2 *)((u8 *)record_data - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
done:
    ;
}

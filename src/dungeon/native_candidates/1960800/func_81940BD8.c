#include "modules/dungeon_ovl_1960800.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"




/* cfail-repair: tf7-phase1-cache-v3 */


   /* temp_v1 in func_800243D8 */

   /* the 0x18 bytes before arg0 in func_800243D8, addressed as arg0[-1] */

   /* temp_a0 in func_800243D8 */

   /* temp_v1_2 in func_800243D8 */

/* Creates an object linked to the source with its position and default part data. */
void func_800243D8(void *source, void *unused_position, void *unused_sprite) {
    S_800243D8_2 *position;
    Part *part;
    void *object;
    S_800243D8_0 *state;
    S_800243D8_3 *source_position;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        state = object + 0x20;
        state->unk_2A = 0xB;
        state->unk_60 = source;
        (*(M2C_UNK **)((u8 *)object + 0x10)) = &func_80024104;
        func_8004491C(object, (s32)func_80045340);
        part = (*(Part **)((u8 *)object + 0xC));
        part->field10 = 0x20;
        part->field6 = 0;
        part->flags14 = (u16) (part->flags14 | 0xC);
        source_position = ((S_800243D8_1_pre *)source)[-1].unk_00;
        position = (*(void **)((u8 *)object + 8));
        position->unk_00 = (s32) source_position->unk_00;
        position->unk_04 = (s32) source_position->unk_04;
        position->unk_08 = (s32) source_position->unk_08;
        part = (*(Part **)((u8 *)object + 0xC));
        part->field1E = 0;
        part->field1C = 0;
        part->byteE = 0;
        part->byteD = 0;
        part->byteC = 0;
        (*(Copy12 *)((u8 *)object + 0x92)) = *(Copy12 *)&D_800256E0;
        part->ptr8 = (void *) (object + 0x92);
    }
}

#include "common.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80175D50.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct S_80170700_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0x24];
    s16 unk_38;
} S_80170700_1;   /* temp_v0 in func_80170700 */

typedef struct S_80170700_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80170700_2;   /* temp_s0_2 in func_80170700 */

typedef struct S_80170700_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170700_3;   /* temp_a0 in func_80170700 */


extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 func_80047784();
typedef struct {
    s32 w[12];
} Copy48;
extern s32 D_80170534;
extern u8 D_80170000[0x3A81];
extern void *D_80175D50;
extern void *D_80175D64;

/* Creates an object from the current object's data and initializes its position and appearance. */
void func_80170700(void) {
    s32 data_index;
    S_80170700_3 *position;
    void *source_data;
    S_80170700_2 *render_data;
    S_80170700_1 *object;

    source_data = ((Rec_D_80175D50 *)D_80175D50)->unk_0C;
    object = func_8003FC64(0x112);
    if (object != NULL) {
        render_data = object->unk_0C;
        object->unk_38 = 0;
        object->unk_10 = &D_80170534;
        *(Copy48 *)render_data = *(Copy48 *)source_data;
        render_data->unk_14 =
            (render_data->unk_14 & 0xFF7F) | 0x400;
        func_8004491C(object, func_80045340);
        data_index = *(&D_80170000[0x3A80]);
        render_data->unk_2C = &D_80170000[0x3A80];
        func_80047784(render_data, data_index, 0);
        render_data->unk_06 = 6;
        render_data->unk_14 &= 0xFFF3;
        position = object->unk_08;
        position->unk_02 = ((u16)D_80083780.x.w.i);
        position->unk_06 = ((u16)D_80083780.y.w.i) - 0x400;
        position->unk_0A = ((u16)D_80083780.z.w.i);
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        render_data->unk_0E = 0x80;
        render_data->unk_0D = 0x80;
        render_data->unk_0C = 0x80;
        D_80175D64 = object;
    }
}

/* MECHANISM: the 48-byte render-data copy is a struct assignment (mips block-move
   loop: lw/sw x4 through $2-$5, src $7, dst $6, end $8), and func_8004491C takes
   two arguments, so $6 is set once in the function: sched1's birthing boost
   places `move $6,$0` right before the second jal. */

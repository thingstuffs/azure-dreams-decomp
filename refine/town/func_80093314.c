#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s32 func_80033B2C();                         /* extern */
M2C_UNK func_8008B158();                         /* extern */
M2C_UNK func_80093ED8();     /* extern */
M2C_UNK func_80094088();     /* extern */
M2C_UNK func_800942B0();     /* extern */
M2C_UNK func_80094378();     /* extern */
M2C_UNK func_800943B8();     /* extern */
M2C_UNK func_800944BC();     /* extern */
M2C_UNK func_8009451C();     /* extern */
M2C_UNK func_80094C1C();                      /* extern */
M2C_UNK func_80095094();                      /* extern */
s32 func_8009567C();            /* extern */
s32 func_80095840();               /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
M2C_UNK func_80098868();     /* extern */
extern u8 D_80083160[];
extern s32 D_800CFCB4;
extern M2C_UNK D_800CFCEF;
extern u8 D_800FE488[];



typedef struct S_80090A74_1 {
    u8 unk_00;
} S_80090A74_1;   /* &D_800CFCEF in func_80090A74 */

typedef struct S_80090A74_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80090A74_2;   /* temp_s4 in func_80090A74 */

typedef struct S_80090A74_3 {
    u8 pad_00[0x2C];
    s32 unk_2C;
} S_80090A74_3;   /* arg0 in func_80090A74 */

typedef struct S_80090A74_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80090A74_4;   /* temp_s3 in func_80090A74 */

/* Update the actor and dispatch town actions from input and interaction state. */
void func_80090A74(S_80090A74_3 *actor, Rec_D_800E3D7C *record, M2C_UNK context) {
    s16 height;
    s32 action_result;
    s32 interaction_result;
    register u8 *page_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *shared_data ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *input_state = D_80083160;

    func_80095C80(record);
    func_80095094(record);
    {
        void *height_record = record;

        ASM_KEEP(height_record);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        page_base = (u8 *)0x80100000;
        ASM_KEEP(page_base);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        shared_data = page_base - 0x1B78;
        height = func_80095978(height_record, shared_data);
    }
    if ((height - record->unk_08.at02_s16.v) >= 4) {
        if (((S_80090A74_1 *)(&D_800CFCEF))->unk_00 == 0) {
            func_80094378(actor, record, context);
            return;
        }
    } else if (((S_80090A74_1 *)(&D_800CFCEF))->unk_00 == 0) {
        func_80095A94(record, height, shared_data);
    }
    if (((S_80090A74_2 *)input_state)->unk_10 & 0x10) {
        func_800942B0(actor, record, context);
        return;
    }
    if (((S_80090A74_2 *)input_state)->unk_10 & 0x40) {
        action_result = func_80095840(actor, &D_800CFCB4);
        if (action_result != 0) {
            if (action_result == 2) {
                func_8009451C(actor, record, context);
                return;
            }
            func_800944BC(actor, record, context);
            return;
        }
        if (func_80033B2C(0xA4) != 0) {
            func_80094088(actor, record, context);
            return;
        }
    } else {
        page_base = (u8 *)0x800D0000;
        ASM_KEEP(page_base);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        shared_data = page_base - 0x34C;
        interaction_result = func_8009567C(shared_data);
        if (interaction_result != 0) {
            if (interaction_result == -1) {
                func_80094C1C(actor);
                func_80098868(actor, record, context);
                actor->unk_2C = 0;
                func_8008B158(((S_80090A74_4 *)shared_data)->unk_10);
                return;
            }
            func_800943B8(actor, record, context);
            return;
        }
        if (((S_80090A74_2 *)input_state)->unk_08 & 0xF000) {
            func_80093ED8(actor, record, context);
        }
    }
}

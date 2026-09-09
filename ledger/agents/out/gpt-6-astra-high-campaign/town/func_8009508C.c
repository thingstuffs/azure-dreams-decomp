#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800CFCC4.h"

M2C_UNK func_80035208();                         /* extern */
M2C_UNK func_8008B158();                         /* extern */
M2C_UNK func_80093D38();     /* extern */
M2C_UNK func_8009455C();     /* extern */
M2C_UNK func_800945B8();     /* extern */
M2C_UNK func_80094660();     /* extern */
M2C_UNK func_800946A0();     /* extern */
M2C_UNK func_80094774();     /* extern */
s32 func_80094B0C();                          /* extern */
M2C_UNK func_80094C1C();                      /* extern */
M2C_UNK func_80095094();                      /* extern */
M2C_UNK func_8009550C();                      /* extern */
M2C_UNK func_8009567C();                   /* extern */
s32 func_80095760();                       /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
M2C_UNK func_800988C8();     /* extern */
M2C_UNK func_80099754();                      /* extern */
s32 func_8009FF50();                                /* extern */
s32 func_800A9D74();                     /* extern */
extern u8 D_80083160[];
extern M2C_UNK D_80093B00;
extern M2C_UNK D_8009B828;
extern M2C_UNK D_8009B8E8;
extern M2C_UNK D_8009B9BC;
extern M2C_UNK D_800CFCB4;
extern void *D_800CFCC4;
extern u8 D_800CFCEF[];
extern M2C_UNK D_800FE488;
extern s32 D_800FE518[];
extern s32 *D_800FE5D8;



typedef struct S_800927EC_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800927EC_1;   /* state in func_800927EC */



typedef struct S_800927EC_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800927EC_4;   /* var_v0 in func_800927EC */

typedef struct S_800927EC_5 {
    u8 pad_00[0x50];
    s32 unk_50;
} S_800927EC_5;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_2C in func_800927EC */

/* Update the actor and dispatch town movement and interaction input. */
void func_800927EC(void *actor, Rec_D_800E3D7C *position, M2C_UNK context) {
    u8 *input = D_80083160;
    M2C_UNK *interaction;
    s16 ground_height;
    s32 interaction_result;
    s32 target_handler;

    func_80095C80(position);
    func_80094C1C(actor);
    func_80095094(position);
    ground_height = func_80095978(position, &D_800FE488);
    if ((ground_height - position->unk_08.at02_s16.v) >= 4) {
        if (D_800CFCEF[0] == 0) {
            func_80094660(actor, position, context);
            return;
        }
        goto handle_input;
    }
    if (D_800CFCEF[0] == 0) {
        func_80095A94(position, ground_height, &D_800FE488);
    }
handle_input:
    if (((S_800927EC_1 *)input)->unk_10 & 0x10) {
        func_800945B8(actor, position, context);
        return;
    }
    if (((S_800927EC_1 *)input)->unk_10 & 0x80) {
        if ((D_800CFCC4 != NULL) && (((Rec_D_800CFCC4 *)D_800CFCC4)->unk_14 == 4)) {
            func_8009550C(position);
            func_80094774(actor, position, context);
            D_800FE518[0] = 1;
            return;
        }
        func_80099754(position);
        func_8009550C(position);
        if (func_80094B0C(actor - 0x20) != 0) {
            func_80093D38(actor, position, context);
            D_800FE5D8 = &D_80093B00;
            return;
        }
    } else {
        if (((S_800927EC_1 *)input)->unk_10 & 0x40) {
            func_800946A0(actor, position, context);
            return;
        }
        if ((func_80095760(&D_800CFCB4) == -1) && (func_8009FF50() == 0)) {
            func_8009567C(&D_800CFCB4);
            func_80094C1C(actor);
            func_800988C8(actor, position, context);
            target_handler = ((S_800927EC_5 *)(((Rec_func_80094268_arg0 *)actor)->unk_2C))->unk_50;
            if ((target_handler != &D_8009B828) && (target_handler != &D_8009B8E8)) {
                if (target_handler != &D_8009B9BC) {
                    ((Rec_func_80094268_arg0 *)actor)->unk_2C = NULL;
                }
            }
            interaction = &D_800CFCB4;
            interaction_result = func_800A9D74(((S_800927EC_4 *)interaction)->unk_10, ((Rec_func_80094268_arg0 *)actor)->unk_2C);
            if (interaction_result != 0) {
                func_80035208(interaction_result);
            } else {
                func_8008B158(((S_800927EC_4 *)interaction)->unk_10);
            }
            D_800FE5D8 = &D_80093B00;
            return;
        }
        if (((S_800927EC_1 *)input)->unk_08 & 0xF000) {
            func_8009455C(actor, position, context);
        }
    }
}

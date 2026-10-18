/* Relink of matched dungeon/func_8002DBE8; every changed retail word is a paired relocation. */
#define D_800CB2DC D_800C6680
#define D_800D6910 D_800D591C
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#define M2C_BREAK() 0

/* cfail-repair: tf7-phase1-cache-v3 */
extern void initialize_object_entries(void *, M2C_UNK, void *);
extern u8 D_80082660[][8];
extern M2C_UNK D_800C6680;
extern M2C_UNK D_800D591C;


/* Initialize the object's state, clear its slot flag, and set its counter to six. */
void func_800C66E0(void *object, M2C_UNK unused, M2C_UNK context) {
    initialize_object_entries(object, context, &D_800D591C);
    D_80082660[((Rec_func_80094268_arg0 *)object)->unk_60][0] = 0;
    ((Rec_func_80094268_arg0 *)object)->unk_54 = &D_800C6680;
    ((Rec_func_80094268_arg0 *)object)->unk_6C.as_s16 = 6;
}

#include "common.h"

extern s32 func_800214FC(void);
extern void func_80021538(void);
extern void func_80021B18(void *arg0, s32 arg1);
extern void func_800220DC(void);
extern void func_8005FE18(s32 arg0);
extern void _card_wait(s32 arg0);
extern void erase(void *arg0);

typedef struct {
    s32 unk0[32];
} Unk80083E98Elem;

typedef struct {
    s32 unk0[8];
} Sp10Buf;

extern Unk80083E98Elem D_80083E98[];

/* Erase a memory card file, wait for completion, and clear its cached entry. */
s32 func_8002219C(s32 file_index) {
    Sp10Buf file_path;
    s32 erase_status;

    func_80021B18(&file_path, file_index);
    _card_wait(0);
    _card_wait(1);
    func_80021538();
    erase(&file_path);
    do {
        erase_status = func_800214FC();
        if (erase_status == 0) {
            func_8005FE18(0);
        }
    } while (erase_status == 0);
    if (file_index < 5) {
        D_80083E98[file_index].unk0[0] = 0;
        func_800220DC();
    }
    return erase_status == 1;
}

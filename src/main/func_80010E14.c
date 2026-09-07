#include "common.h"

extern void func_80023B18(s32 *arg0);
extern void func_80023BE4(void *arg0, s32 arg1, s32 arg2);
extern void func_80023C44(s32 *arg0);
extern void func_80023D64(s32 *arg0);
extern void func_80023EAC(void) __attribute__((noreturn));

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u8 pad10[0x80 - 0x0A];
} EntryS80083E98; // size 0x80

extern EntryS80083E98 D_80083E98[];

void func_80023E14(s32 *arg0) {
    func_80023BE4((u8 *)arg0 + 0x134, 0x80, 0x18);
    func_80023BE4((u8 *)arg0 + 0x1AC, 0x2A, 0x14);
    if (D_80083E98[*arg0].unk0 != 0) {
        func_80023C44(arg0);
        if (D_80083E98[*arg0].unk8 != 0) {
            func_80023D64(arg0);
            func_80023EAC();
        }
    } else {
        func_80023B18(arg0);
    }
}

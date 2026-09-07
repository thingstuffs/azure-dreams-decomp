#include "common.h"
#include "records/Rec_D_800E3D7C.h"



extern s32 func_8008D344();
extern s32 func_80098864();
extern void func_80098B38();
extern s32 func_800990FC();
extern s32 func_80099194();
extern void func_80099290();
extern void func_800A5720();
extern void func_800A5F38();
extern void func_800A6480();
extern s32 func_800AD6FC();
extern void func_800C4D78();

extern s32 D_80082E80;
extern s8 D_80082EA6;
extern s32 D_80083460;
extern s32 D_80083780;
extern u8 D_800DDE84[];
extern u8 D_800E1567[];
extern u8 D_800E3648[];
extern u8 *D_800E3D7C;


s32 func_800C2130(Rec_D_800E3D7C *arg0, s32 arg1, s16 arg2, s32 arg3) {
    s32 call_arg;
    volatile u8 *entry;
    u8 *state;
    u16 *counter;
    s32 object;
    s32 result;
    s32 i;
    u8 flags;

    if (arg2 == 0xD) {
        return func_80098864(arg1, arg3);
    }
    if (arg0 == D_800E3D7C) {
        arg0->unk_110 = arg1;
        func_8008D344(arg0, &D_80083780, &D_80082E80, arg0);
        return 0;
    }
    if ((u32)arg0 <= 0x9FFFFFFF) {
        func_800A6480(arg0, arg1);
        if (func_800AD6FC(
                arg0,
                ((u16 *)D_800DDE84)[arg0->unk_10.at03_u8.v] & 3,
                arg1) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
        goto final;
    }

    func_800C4D78(0xC02020, 1);
    object = func_800990FC();
    
    call_arg = object;
    if (D_80082EA6 >= 0) {
        i = 0;
        entry = D_800E3648;
        do {
            if (entry[1] != 0 && entry[0] != 0) {
                flags = entry[3];
                if (!(flags & 0x40)) {
                    entry[3] = flags | 0x80;
                }
            }
            i++;
            entry += 4;
        } while (i < 0x20);
        
        func_80099290(call_arg);
    } else {
        result = func_80099194(D_800E1567, object);
        func_80099290(result);
    }
    func_800A5720(object);

final:
    state = (u8 *)&D_80083460;
    counter = (u16 *)(state + 0xA);
    *counter = *counter - 1;
    func_80098B38(arg1);
    return 1;
}

/* MECHANISM: TRUE-space CFG uses ordinary return/join edges, exact callee arity, and a u16 table.
   ASM_KEEP holds the allocation result while the guarded a0 call argument survives the byte loop.
   A volatile single-base cursor and named D_80083460 base preserve retail addressing and schedule. */

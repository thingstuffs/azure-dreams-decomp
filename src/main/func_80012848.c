#include "common.h"

extern void func_800230A4(void *arg0);
extern void func_80023144(void *arg0, void *arg1);

extern s32 D_80083E98[][32];
extern s32 D_80025788;
extern s32 D_8002593C;
extern s32 D_80024FAC;

#ifndef NON_MATCHING
register u8 *data_ptr ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif

/* Sets up the object from its indexed table entry and assigns its state data. */
void func_80025848(void *state) {
#ifndef NON_MATCHING
    void *object;
    s32 table_entry;

    data_ptr = (u8 *)0x80080000;
    __asm__ __volatile__("" : "=r"(data_ptr) : "0"(data_ptr));
    table_entry = *(s32 *)((u8 *)state + 0x28);
    data_ptr += 0x3E98;
    table_entry <<= 7;
    table_entry += (u32)data_ptr;
    data_ptr = (u8 *)*(u32 *)table_entry;
    object = (u8 *)state - 0x20;

    if (data_ptr != 0) {
        void *update_data;

        data_ptr = (u8 *)0x80020000;
        __asm__ __volatile__("" : "=r"(data_ptr) : "0"(data_ptr));
        data_ptr += 0x5788;
        update_data = (u8 *)state + 0x38;
        __asm__ __volatile__("" ::: "memory");
        *(u8 **)((u8 *)state + 0x34) = data_ptr;
        func_80023144(object, update_data);
        data_ptr = (u8 *)0x80020000;
    } else {
        data_ptr = (u8 *)0x80020000;
        __asm__ __volatile__("" : "=r"(data_ptr) : "0"(data_ptr));
        data_ptr += 0x593C;
        *(u8 **)((u8 *)state + 0x34) = data_ptr;
        func_800230A4(object);
        data_ptr = (u8 *)0x80020000;
    }
    data_ptr += 0x4FAC;
    *(u8 **)((u8 *)state - 0x10) = data_ptr;
#else
    void *object = (u8 *)state - 0x20;
    s32 table_index = *(s32 *)((u8 *)state + 0x28);

    if (D_80083E98[table_index][0] != 0) {
        s32 *state_data = &D_80025788;
        void *update_data = (u8 *)state + 0x38;
        __asm__ __volatile__("" ::: "memory");
        *(s32 **)((u8 *)state + 0x34) = state_data;
        func_80023144(object, update_data);
    } else {
        *(s32 **)((u8 *)state + 0x34) = &D_8002593C;
        func_800230A4(object);
    }
    *(s32 **)((u8 *)state - 0x10) = &D_80024FAC;
#endif
}

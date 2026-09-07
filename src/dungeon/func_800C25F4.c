typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef void (*Callback)(s16, s16, s16, s16);

typedef struct CallbackEntry {
    Callback callback;
    s16 arg0;
    s16 arg1;
    s16 arg2;
    s16 arg3;
} CallbackEntry;

extern CallbackEntry *D_800DF640[4];
extern u8 D_800DF64C[9];
extern void func_800BD184(u32);

void func_800C7D54(s16 index) {
    CallbackEntry *entry;

    func_800BD184(D_800DF64C[index]);
    entry = D_800DF640[index];
    while (entry->callback != 0) {
        entry->callback(entry->arg0, entry->arg1, entry->arg2, entry->arg3);
        entry++;
    }
}

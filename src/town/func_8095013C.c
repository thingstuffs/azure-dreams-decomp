typedef int s32;
typedef short s16;

typedef struct Entry {
    s16 key;
    char pad2[2];
    void *value;
} Entry;

typedef struct RuntimeMethods {
    char pad0[0x168];
    void (*assert_fail)(char *, char *, s32);
    char pad16C[8];
    void (*terminate)(s32);
} RuntimeMethods;

typedef struct RuntimeRoot {
    char pad0[0x20];
    RuntimeMethods *methods;
} RuntimeRoot;

extern RuntimeRoot *D_80016000;
extern char D_80016080[];
extern char D_800160A8[];

s32 func_8095013C(Entry *arg0, s32 arg1)
{
    Entry *entry;
    s32 index;

    index = 0;
    if (arg0[0].value != 0) {
        entry = arg0;
        while (entry->value != 0) {
            if (entry->key == arg1) {
                break;
            }
            entry++;
            index++;
        }

        if (arg0[index].value != 0) {
            return index;
        }
    }

    D_80016000->methods->assert_fail(D_80016080, D_800160A8, 39);
    D_80016000->methods->terminate(1);
    return index;
}

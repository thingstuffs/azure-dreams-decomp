/* func_99999999: goto temp_comment; (u8 *)p + 0x90; */
#define FAKE(x) \
    void macro_fake(void) { goto bad; }
extern void func_80001000(void *);
const char *message = "D_12345678 M2C_FAKE goto var_fake 0xFFFF";
int func_80002000(void *arg0) {
    int var_v0;
    var_v0 = *(int *)((u8 *)arg0 + 0x24);
    if (var_v0 == 42) {
        if (arg0 != 0) {
            while (var_v0 > 1) {
                M2C_ERROR("literal");
                goto done;
            }
        }
    }
done:
    func_80001000(arg0);
    return var_v0;
}

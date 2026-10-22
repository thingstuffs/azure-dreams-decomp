struct Data { int value; } table[] = {{3}, {4}};
void (*callback)(int) = 0;
extern int helper(void);
static int helper(void) { return 0; }
int first(void) {
    extern void declared_only(void);
    helper();
    helper();
    return helper();
}
#include "another_fragment.h"
int second(void) __attribute__((noinline)) { return first(); }
#if OPTION
int variant(void) { return second(); }
#else
int variant(void) { return 0; }
#endif

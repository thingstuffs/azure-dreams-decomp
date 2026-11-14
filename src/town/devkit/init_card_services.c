#include "common.h"
#include "town/devkit.h"
#include "frontend/card/server_imports.h"


/* Run the setup sequence using the supplied context. */
void init_card_services(void *context) {
    func_8007CB08(0);
    func_8007CA38();
    InitCARD2_80408798(context);
    func_804088A0();
    func_80408958();
    func_8007CA48();
}

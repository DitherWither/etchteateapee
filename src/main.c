#include <etch/etch.h>

ETCH_PROGRAM(8080)
{
        EtchResponse res = {0};
        res.status_code = ETCH_STATUS_CODE_OK;
        casprintf(&res.body, "Hello, World\n");
        casprintf(&res.body, "Hello, World\n");
        casprintf(&res.body, "Hello, World\n");
        casprintf(&res.body, "Hello, World\n");

        return res;
}

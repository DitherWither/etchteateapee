#include <etch/etch.h>

ETCH_SERVER_ON(8080)

ETCH_INIT
{
        printf("Hello, World\n");
}

ETCH_HANDLER
{
        EtchResponse res = {0};
        res.status_code = ETCH_STATUS_CODE_OK;
        casprintf(&res.body, "Hello, World\n");
        casprintf(&res.body, "Hello, World\n");
        casprintf(&res.body, "Hello, World\n");
        casprintf(&res.body, "Hello, World\n");

        return res;
}


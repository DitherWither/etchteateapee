#include "connection.h"
#include <etch/response.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EtchResponse handler(char *buffer, size_t len)
{
        EtchResponse res = {0};
        res.status_code = ETCH_STATUS_CODE_OK;

        res.body = malloc(256 * sizeof(char));
        sprintf(res.body, "Hello, World\n");

        return res;
}

int32_t main()
{
        etch_serve(8080, handler);
        return 0;
}

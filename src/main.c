#include "etch/response.h"
#include "etch/utils.h"
#include <etch/etch.h>

ETCH_SERVER_ON(8080)

// TODO: deallocate memory

ETCH_INIT
{
        printf("Hello, World\n");
}

ETCH_HANDLER
{
        EtchResponse res = { 0 };
        res.status_code = ETCH_STATUS_CODE_OK;

        casprintf(&res.body, "<h1>Hello from '%s'</h1><ul>", req.path);
        for (int i = 0; i < req.headers_count - 1; i++) {
                casprintf(&res.body, "<li>%s is %s</li>", req.headers[i].name, req.headers[i].value);
        }
        casprintf(&res.body, "</ul>");
        casprintf(&res.body, "<p>Body is</p><pre>%s</pre>", req.body);

        return res;
}


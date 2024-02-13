#include "etch/response.h"
#include "etch/utils.h"
#include <etch/etch.h>

ETCH_SERVER_ON(8080)


ETCH_INIT
{
        printf("Hello, World\n");
}

ETCH_HANDLER
{
        EtchResponse res = etch_response_default();

        etch_response_add_header(&res, "X-Test-Header", "Hello, World");
        etch_response_add_header(&res, "X-Test-Header-B", "Hello, World");
        etch_response_add_header(&res, "X-Test-Header-C", "Hello, World");
        etch_response_add_header(&res, "X-Test-Header-D", "Hello, World");
        etch_response_add_header(&res, "X-Test-Header-E", "Hello, World");
        etch_response_add_header(&res, "X-Test-Header-F", "Hello, World");

        casprintf(&res.body, "<h1>Hello from '%s'</h1><ul>", req.path);
        for (int i = 0; i < req.headers_count - 1; i++) {
                casprintf(&res.body, "<li>%s is %s</li>", req.headers[i].name, req.headers[i].value);
        }
        casprintf(&res.body, "</ul>");
        casprintf(&res.body, "<p>Body is</p><pre>%s</pre>", req.body);

        return res;
}


#include <etch/http/response.h>
#include <etch/core/utils.h>
#include <etch/etch.h>

ETCH_SERVER_ON(8080)

ETCH_INIT
{
        printf("Hello, World\n");
}

ETCH_HANDLER
{
        EtchResponse res = etch_response_default();

        if (etch_response_serve_file(&res, req.path) < 0) {
                casprintf(&res.body, "<h1>404: Not Found</h1>");
        }

        return res;
}

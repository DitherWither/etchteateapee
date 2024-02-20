#include <etch.h>

ETCH_SERVER

ETCH_INIT
{
        etch_set_port(8081);
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

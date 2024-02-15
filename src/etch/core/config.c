#include <etch/core/config.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct EtchConfig {
        char *resource_dir;
        uint16_t port;
        int32_t max_pending_connections;
} EtchConfig;

EtchConfig config = { 0 };

void etch_config_init(void)
{
        etch_set_res_dir(ETCH_DEFAULT_RES_DIR);
        etch_set_port(8080);
}

const char *etch_get_res_dir(void)
{
        return config.resource_dir;
}
void etch_set_res_dir(const char *dir)
{
        if (config.resource_dir != NULL)
                free(config.resource_dir);
        config.resource_dir = malloc((strlen(dir) + 1) * sizeof(char));
        strcpy(config.resource_dir, dir);
}

uint16_t etch_get_port(void)
{
        return config.port;
}

void etch_set_port(uint16_t port)
{
        config.port = port;
}

int32_t etch_get_max_pending_connections(void)
{
        return config.max_pending_connections;
}

void etch_set_max_pending_connections(int32_t max_pending_connections)
{
        config.max_pending_connections = max_pending_connections;
}
#include <etch/config.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct EtchConfig {
        char *resource_dir;
} EtchConfig;

EtchConfig config = { 0 };

void etch_config_init(void)
{
        etch_set_res_dir(ETCH_DEFAULT_RES_DIR);
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
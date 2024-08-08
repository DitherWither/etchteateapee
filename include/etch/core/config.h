#ifndef __ETCH_CORE_CONFIG_H__
#define __ETCH_CORE_CONFIG_H__

#include <stdint.h>
#define ETCH_DEFAULT_RES_DIR "res"

void etch_config_init(void);

const char *etch_get_res_dir(void);
void etch_set_res_dir(const char *res_dir);

uint16_t etch_get_port(void);
void etch_set_port(uint16_t port);

int32_t etch_get_max_pending_connections(void);
void etch_set_max_pending_connections(int32_t max_pending_connections);

#endif /* __ETCH_CORE_CONFIG_H__ */

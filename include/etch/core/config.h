#ifndef __ETCH_CONFIG_H__
#define __ETCH_CONFIG_H__

#define ETCH_DEFAULT_RES_DIR "res"

void etch_config_init(void);

const char *etch_get_res_dir(void);
void etch_set_res_dir(const char*);

#endif /* __ETCH_CONFIG_H__ */

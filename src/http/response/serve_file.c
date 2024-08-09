#include <etch/core/config.h>
#include <etch/http/response.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

static int read_file(const char *path, char **file);
static int is_regular_file(const char *path);

int etch_response_serve_file(EtchResponse *res, const char *path)
{
        const char *resource_dir = etch_get_res_dir();
        // allocate size of index.html just in case
        int length =
                strlen(resource_dir) + strlen(path) + sizeof("/index.html") + 1;

        char *full_path = malloc(length * sizeof(char));
        strcpy(full_path, resource_dir);
        strcat(full_path, path);

        if (!is_regular_file(full_path)) {
                strcat(full_path, "/index.html");
        }

        if (res->body != NULL) {
                free(res->body);
        }

        if (read_file(full_path, &res->body) < 0) {
                return -1;
        }

        free(full_path);
        return 0;
}

static int read_file(const char *path, char **file)
{
        int fd = open(path, O_RDONLY);
        if (fd == -1) {
                return -1;
        }

        // lseek returns the offset it moved to
        // seeking to end gives the length
        size_t length = lseek(fd, 0, SEEK_END);
        lseek(fd, 0, SEEK_SET); // move back to start

        char *mmap_file = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);

        *file = malloc(length + 1);
        memset(*file, 0,
               length +
                       1); // For some reason, using array indexes gives segfault
        memcpy(*file, mmap_file, length);

        munmap(mmap_file, length);
        close(fd);

        return 0;
}

static int is_regular_file(const char *path)
{
        struct stat path_stat;
        stat(path, &path_stat);
        return S_ISREG(path_stat.st_mode);
}
#include <cstdlib>
#include "utils.hpp"

long GetTimeMilliseconds()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

void Log(const char *message, ...)
{
    char buffer[1024];

    va_list args;
    va_start(args, message);
    vsnprintf(buffer, sizeof(buffer), message, args );
    va_end(args);
}

bool LoadFile(const char *filePath, char **buffer, int &size)
{
    size = 0;
    *buffer = nullptr;

    FILE *fp = fopen(filePath, "rb");

    if (fp)
    {
        fseek(fp, 0L, SEEK_END);
        size = (int) ftell(fp);
        fseek(fp, 0L, SEEK_SET);

        *buffer = (char *) malloc (size);
        fread(*buffer, size, 1, fp);
        fclose(fp);

        return true;
    }

    return false;
}

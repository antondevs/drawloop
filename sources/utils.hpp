#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/time.h>

/* Log with native methods */
void Log(const char *message, ...);

/* Load file with native methods */
bool LoadFile(const char *filePath, char **buffer, int &size);

/* Get time in milliseconds */
long GetTimeMilliseconds();

#endif

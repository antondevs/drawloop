//
//  Utils.m
//  Example
//
//  Created by Anton on 18.12.2019.
//  Copyright © 2019 Anton. All rights reserved.
//

#import "utils.hpp"
#import <Foundation/Foundation.h>

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

    NSLog(@"DrawLoop: %@", [NSString stringWithUTF8String:buffer]);
}

bool LoadFile(const char *filePath, char **buffer, int &size)
{
    size = 0;
    *buffer = nullptr;

    char fullPath[512];
    NSString *dataPath = [[[NSBundle mainBundle] resourcePath]
                         stringByAppendingPathComponent:@"data"];
    strncpy(fullPath, [dataPath UTF8String], 512);
    strcat(fullPath, "/");
    strcat(fullPath, filePath);

    FILE *fp = fopen(fullPath, "rb");

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

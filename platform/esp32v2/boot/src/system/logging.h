#pragma once

#include <stdio.h>
#include <stdarg.h>

#ifndef __FILE_NAME__
#define __FILE_NAME__ __FILE__
#endif

#ifndef STRINGIFY
  #define STRINGIFY_NX(a) #a
  #define STRINGIFY(a) STRINGIFY_NX(a)
#endif

// Log levels
#define LOG_LEVEL_ALWAYS 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_INFO 100
#define LOG_LEVEL_DEBUG 200

#ifdef PBL_LOG_ENABLED
  #define PBL_LOG(level, fmt, args...) \
    printf(__FILE_NAME__ ":" STRINGIFY(__LINE__) "> " fmt, ## args)
    
  #define PBL_LOG_VERBOSE(fmt, args...) \
    PBL_LOG(LOG_LEVEL_DEBUG, fmt, ## args)
    
#else
  #define PBL_LOG(level, fmt, args...)
  #define PBL_LOG_VERBOSE(fmt, args...)
#endif

// Convenience macros that directly use printf when PBL_LOG_ENABLED
#ifdef PBL_LOG_ENABLED
  #define LOG_ERROR(fmt, args...)   printf("[ERROR] " __FILE_NAME__ ":" STRINGIFY(__LINE__) "> " fmt, ## args)
  #define LOG_INFO(fmt, args...)    printf("[INFO] " __FILE_NAME__ ":" STRINGIFY(__LINE__) "> " fmt, ## args)  
  #define LOG_DEBUG(fmt, args...)   printf("[DEBUG] " __FILE_NAME__ ":" STRINGIFY(__LINE__) "> " fmt, ## args)
#else
  #define LOG_ERROR(fmt, args...) printf("[ERROR] " fmt, ## args)
  #define LOG_INFO(fmt, args...) printf("[INFO] " fmt, ## args)
  #define LOG_DEBUG(fmt, args...) printf("[DEBUG] " fmt, ## args)
#endif
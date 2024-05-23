#pragma once
#define lRED "\x1B[31m"
#define lGRN "\x1B[32m"
#define lYEL "\x1B[33m"
#define lBLU "\x1B[34m"
#define lMAG "\x1B[35m"
#define lCYN "\x1B[36m"
#define lWHT "\x1B[37m"
#define lRESET "\x1B[0m"

#ifdef SF_DEBUG
#define SF_LOGE(...)                                    \
    do { printf(lRED "[Error] | " lRESET __VA_ARGS__);  \
    printf("\n"); } while(0)
#define SF_LOGW(...)                                    \
    do { printf(lYEL "[Warn] | " lRESET __VA_ARGS__);   \
    printf("\n"); } while(0)
#define SF_LOGI(...)                                    \
    do { printf(lGRN "[Info] | " lRESET __VA_ARGS__);   \
    printf("\n"); } while(0)
#else
#define SF_LOGE(...)
#define SF_LOGW(...)
#define SF_LOGI(...)
#endif
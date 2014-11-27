#ifndef COMMON_H_
#define COMMON_H_

#define COLA  "/mensajes"
#define MAX_SIZE    1024
#define BUFFER_SIZE    70960
#define MSG_STOP    "exit"

#define CHECK(x) \
    do { \
        if (!(x)) { \
            fprintf(stderr, "%s:%d: ", __func__, __LINE__); \
            perror(#x); \
            exit(-1); \
        } \
    } while (0) \

#endif /* #ifndef COMMON_H_ */

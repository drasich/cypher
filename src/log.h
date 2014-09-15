#ifndef __log__
#define __log__

#define LOG(str,...) do {printf("LOG : "); printf(str, ## __VA_ARGS__); printf("\n");} while (0)
#define ERR(str,...) do {printf("ERROR : "); printf(str, ## __VA_ARGS__); printf("\n");} while (0)


#endif

#ifndef KLIB_H
#define KLIB_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

size_t kstrlen(const char *str);
int kstrcmp(const char *s1, const char *s2);
size_t kstrspn(const char *s, const char *accept);
char *kstrcpy(char *dst, const char *src);
uint32_t kstrtou32(char *nptr);
void *kmemset(void *s, uint8_t c, size_t n);
void *kmemmove(void *dst, const void *src, size_t n);
int ku32tostr(char *str, size_t len, uint32_t value, int base);
int ks32tostr(char *str, size_t len, int32_t value, unsigned base);
char *kreverse(char *s, size_t len);

int kputc(char c);
int kputs(char *s);
int kprintf(char *fmt, ...);

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
void io_wait(void);

void enable(void);		/*enable interrupts */
void disable(void);		/*disable interrupts */
void halt(void);		/*halt system */
uint64_t time(void);		/*timer ticks since reset */

void _panic(const char *msg, const char *file, const char *func, unsigned line);
void _assert(int test, const char *expr, const char *file, const char *func, unsigned line);

#define panic(MSG) _panic((MSG), __FILE__, __func__, __LINE__)
#define assert(EXPR) _assert((EXPR), # EXPR, __FILE__, __func__, __LINE__)

#endif

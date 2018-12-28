#ifndef __SHELL_H__
#define __SHELL_H__

#include "stm32f10x.h"

/******************** LOG & UART START *******************************************/
#define readl(addr)         (*( ( volatile uint32_t * )(addr)) )
#define writel(addr, data)  (*( ( volatile uint32_t * )(addr)) = data)

#define UART_IO_SIZE       (256)

enum  UART_WORK_MODE {
	TSHELL_MODE = 0,	/* thread shell */
	ISHELL_MODE,			/* int    shell */
};

enum LOG_LEVEL_E {
    LOG_EMG = 1,
    LOG_ERR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG,
    LOG_MAX,
};

extern uint32_t default_log_level;

uint32_t set_log_level(uint32_t log_level);

#define PRINT_EMG(fmt, ...)     do { if ( default_log_level >= LOG_EMG   ) { printf(fmt, ##__VA_ARGS__); } } while (0)
#define PRINT_ERR(fmt, ...)     do { if ( default_log_level >= LOG_ERR   ) { printf(fmt, ##__VA_ARGS__); } } while (0)
#define PRINT_WARN(fmt, ...)    do { if ( default_log_level >= LOG_WARN  ) { printf(fmt, ##__VA_ARGS__); } } while (0)
#define PRINT_INFO(fmt, ...)    do { if ( default_log_level >= LOG_INFO  ) { printf(fmt, ##__VA_ARGS__); } } while (0)
#define PRINT_DEBUG(fmt, ...)   do { if ( default_log_level >= LOG_DEBUG ) { printf(fmt, ##__VA_ARGS__); } } while (0)

/******************** LOG & UART END *******************************************/

typedef int32_t (*func_0)();
typedef int32_t (*func_4)(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);

#define SHELL_ARGS_MAX  (32)
struct shell_cmd_info {
    char *name;
    func_0 func;
    char *desc;
};

extern volatile char * volatile shell_cmd;

extern uint32_t argc;
extern char *argv[SHELL_ARGS_MAX];

int32_t shell(char *cmd);
void shell_init(void);

#endif /* __SHELL_H__ */

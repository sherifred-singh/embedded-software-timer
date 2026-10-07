/**
 * @file soft_timer.h
 * @brief Lightweight, non-blocking Software Timer Module in C99.
 * @author Sherifred Singh
 */

#ifndef SOFT_TIMER_H
#define SOFT_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
    TIMER_MODE_ONE_SHOT = 0,
    TIMER_MODE_PERIODIC
} timer_mode_t;

typedef enum {
    TIMER_STATE_STOPPED = 0,
    TIMER_STATE_RUNNING,
    TIMER_STATE_EXPIRED
} timer_state_t;

typedef void (*timer_callback_t)(void *user_arg);

typedef struct soft_timer_s {
    uint32_t period_ticks;
    uint32_t expiry_tick;
    timer_mode_t mode;
    timer_state_t state;
    timer_callback_t callback;
    void *user_arg;
    struct soft_timer_s *next;
} soft_timer_t;

void soft_timer_init(void);
void soft_timer_tick(uint32_t elapsed_ticks);
uint32_t soft_timer_get_ticks(void);

bool soft_timer_create(soft_timer_t *timer,
                       uint32_t period_ticks,
                       timer_mode_t mode,
                       timer_callback_t callback,
                       void *user_arg);

bool soft_timer_start(soft_timer_t *timer);
bool soft_timer_stop(soft_timer_t *timer);
bool soft_timer_restart(soft_timer_t *timer);
bool soft_timer_is_running(const soft_timer_t *timer);

#ifdef __cplusplus
}
#endif

#endif /* SOFT_TIMER_H */

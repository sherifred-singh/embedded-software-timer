/**
 * @file soft_timer.c
 * @brief Implementation of tick-based non-blocking software timer.
 * @author Sherifred Singh
 */

#include "soft_timer.h"

static volatile uint32_t g_system_ticks = 0;
static soft_timer_t *g_timer_list_head = NULL;

void soft_timer_init(void) {
    g_system_ticks = 0;
    g_timer_list_head = NULL;
}

uint32_t soft_timer_get_ticks(void) {
    return g_system_ticks;
}

bool soft_timer_create(soft_timer_t *timer,
                       uint32_t period_ticks,
                       timer_mode_t mode,
                       timer_callback_t callback,
                       void *user_arg) {
    if (timer == NULL || period_ticks == 0) return false;

    timer->period_ticks = period_ticks;
    timer->expiry_tick = 0;
    timer->mode = mode;
    timer->state = TIMER_STATE_STOPPED;
    timer->callback = callback;
    timer->user_arg = user_arg;
    timer->next = NULL;

    return true;
}

bool soft_timer_start(soft_timer_t *timer) {
    if (timer == NULL) return false;

    timer->expiry_tick = g_system_ticks + timer->period_ticks;
    timer->state = TIMER_STATE_RUNNING;

    /* Check if already in list */
    soft_timer_t *curr = g_timer_list_head;
    while (curr != NULL) {
        if (curr == timer) return true;
        curr = curr->next;
    }

    /* Insert at head */
    timer->next = g_timer_list_head;
    g_timer_list_head = timer;
    return true;
}

bool soft_timer_stop(soft_timer_t *timer) {
    if (timer == NULL) return false;
    timer->state = TIMER_STATE_STOPPED;
    return true;
}

bool soft_timer_restart(soft_timer_t *timer) {
    if (timer == NULL) return false;
    return soft_timer_start(timer);
}

bool soft_timer_is_running(const soft_timer_t *timer) {
    if (timer == NULL) return false;
    return (timer->state == TIMER_STATE_RUNNING);
}

void soft_timer_tick(uint32_t elapsed_ticks) {
    g_system_ticks += elapsed_ticks;

    soft_timer_t *curr = g_timer_list_head;
    while (curr != NULL) {
        if (curr->state == TIMER_STATE_RUNNING) {
            /* Check if expired (handles 32-bit tick roll-over) */
            if ((int32_t)(g_system_ticks - curr->expiry_tick) >= 0) {
                if (curr->callback != NULL) {
                    curr->callback(curr->user_arg);
                }

                if (curr->mode == TIMER_MODE_PERIODIC) {
                    curr->expiry_tick += curr->period_ticks;
                } else {
                    curr->state = TIMER_STATE_EXPIRED;
                }
            }
        }
        curr = curr->next;
    }
}

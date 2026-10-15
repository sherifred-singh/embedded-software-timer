/**
 * @file test_timer.c
 * @brief Unit tests for Software Timer Module.
 * @author Sherifred Singh
 */

#include <stdio.h>
#include <assert.h>
#include "soft_timer.h"

static int g_one_shot_fired = 0;
static int g_periodic_count = 0;

static void one_shot_handler(void *arg) {
    (void)arg;
    g_one_shot_fired++;
}

static void periodic_handler(void *arg) {
    (void)arg;
    g_periodic_count++;
}

int main(void) {
    printf("\n=======================================================\n");
    printf(" 🚀 C Embedded Software Timer -- Unit Test Suite\n");
    printf("=======================================================\n\n");

    soft_timer_init();

    soft_timer_t t_oneshot;
    soft_timer_t t_periodic;

    assert(soft_timer_create(&t_oneshot, 5, TIMER_MODE_ONE_SHOT, one_shot_handler, NULL));
    assert(soft_timer_create(&t_periodic, 2, TIMER_MODE_PERIODIC, periodic_handler, NULL));

    printf("[TEST 1] Timer Creation & Start... ");
    assert(soft_timer_start(&t_oneshot));
    assert(soft_timer_start(&t_periodic));
    assert(soft_timer_is_running(&t_oneshot));
    assert(soft_timer_is_running(&t_periodic));
    printf("PASSED [OK]\n");

    printf("[TEST 2] Simulating 4 Ticks... ");
    soft_timer_tick(4);
    assert(g_one_shot_fired == 0); /* 4 < 5 -> not fired */
    assert(g_periodic_count == 2); /* 4 / 2 -> fired twice */
    printf("PASSED [OK]\n");

    printf("[TEST 3] Simulating 5th Tick (One-shot expiry)... ");
    soft_timer_tick(1); /* Now 5 ticks total */
    assert(g_one_shot_fired == 1);
    assert(!soft_timer_is_running(&t_oneshot));
    printf("PASSED [OK]\n");

    printf("[TEST 4] Stopping Periodic Timer... ");
    soft_timer_stop(&t_periodic);
    assert(!soft_timer_is_running(&t_periodic));
    soft_timer_tick(10);
    assert(g_periodic_count == 2); /* Should not increment while stopped */
    printf("PASSED [OK]\n");

    printf("[TEST 5] Rapid Cancel & Re-arm Stress Test (1000 iterations)... ");
    for (int i = 0; i < 1000; i++) {
        assert(soft_timer_start(&t_periodic));
        soft_timer_tick(1);
        soft_timer_stop(&t_periodic);
    }
    /* Period is 2, and timer was stopped after 1 tick each time, so zero extra expirations should occur */
    assert(g_periodic_count == 2);
    printf("PASSED [OK]\n");

    printf("\n=======================================================\n");
    printf(" 🎉 ALL SOFTWARE TIMER TESTS PASSED! (5/5)\n");
    printf("=======================================================\n\n");

    return 0;
}

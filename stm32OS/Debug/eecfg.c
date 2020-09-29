#include "ee.h"





/***************************************************************************
 *
 * Kernel ( CPU 0 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(TaskOS_2ms);
    DeclareTask(TaskOS_5ms);
    DeclareTask(TaskOS_10ms);
    DeclareTask(TaskOS_20ms);
    DeclareTask(TaskOS_50ms);
    DeclareTask(TaskOS_100ms);
    DeclareTask(TaskOS_500ms);

    const EE_THREAD_PTR EE_hal_thread_body[EE_MAX_TASK] = {
        &FuncTaskOS_2ms,		/* thread TaskOS_2ms */
        &FuncTaskOS_5ms,		/* thread TaskOS_5ms */
        &FuncTaskOS_10ms,		/* thread TaskOS_10ms */
        &FuncTaskOS_20ms,		/* thread TaskOS_20ms */
        &FuncTaskOS_50ms,		/* thread TaskOS_50ms */
        &FuncTaskOS_100ms,		/* thread TaskOS_100ms */
        &FuncTaskOS_500ms 		/* thread TaskOS_500ms */

    };

    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1U,		/* thread TaskOS_2ms */
        0x40U,		/* thread TaskOS_5ms */
        0x20U,		/* thread TaskOS_10ms */
        0x10U,		/* thread TaskOS_20ms */
        0x8U,		/* thread TaskOS_50ms */
        0x4U,		/* thread TaskOS_100ms */
        0x2U 		/* thread TaskOS_500ms */
    };

    /* dispatch priority */
    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1U,		/* thread TaskOS_2ms */
        0x40U,		/* thread TaskOS_5ms */
        0x20U,		/* thread TaskOS_10ms */
        0x10U,		/* thread TaskOS_20ms */
        0x8U,		/* thread TaskOS_50ms */
        0x4U,		/* thread TaskOS_100ms */
        0x2U 		/* thread TaskOS_500ms */
    };

    /* thread status */
    #if defined(__MULTI__) || defined(__WITH_STATUS__)
        EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
            EE_READY,
            EE_READY,
            EE_READY,
            EE_READY,
            EE_READY,
            EE_READY,
            EE_READY
        };
    #endif

    /* next thread */
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL,
        EE_NIL,
        EE_NIL,
        EE_NIL,
        EE_NIL,
        EE_NIL,
        EE_NIL
    };

    EE_TYPEPRIO EE_th_nact[EE_MAX_TASK];
    /* The first stacked task */
    EE_TID EE_stkfirst = EE_NIL;

    /* The first task into the ready queue */
    EE_TID EE_rqfirst  = EE_NIL;

    /* system ceiling */
    EE_TYPEPRIO EE_sys_ceiling= 0x0000U;



/***************************************************************************
 *
 * Counters
 *
 **************************************************************************/
    EE_counter_RAM_type       EE_counter_RAM[EE_MAX_COUNTER] = {
        {0, -1}         /* OSMainCounter */
    };



/***************************************************************************
 *
 * Alarms
 *
 **************************************************************************/
    const EE_alarm_ROM_type   EE_alarm_ROM[EE_ALARM_ROM_SIZE] = {
        {0, EE_ALARM_ACTION_TASK    , TaskOS_2ms, NULL},
        {0, EE_ALARM_ACTION_TASK    , TaskOS_5ms, NULL},
        {0, EE_ALARM_ACTION_TASK    , TaskOS_10ms, NULL},
        {0, EE_ALARM_ACTION_TASK    , TaskOS_20ms, NULL},
        {0, EE_ALARM_ACTION_TASK    , TaskOS_50ms, NULL},
        {0, EE_ALARM_ACTION_TASK    , TaskOS_100ms, NULL},
        {0, EE_ALARM_ACTION_TASK    , TaskOS_500ms, NULL}
    };

    EE_alarm_RAM_type         EE_alarm_RAM[EE_MAX_ALARM];


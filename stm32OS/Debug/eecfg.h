#ifndef EECFG_H
#define EECFG_H


#define RTDRUID_CONFIGURATOR_NUMBER 1278



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 7
    #define TaskOS_2ms 0
    #define TaskOS_5ms 1
    #define TaskOS_10ms 2
    #define TaskOS_20ms 3
    #define TaskOS_50ms 4
    #define TaskOS_100ms 5
    #define TaskOS_500ms 6

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 0U

    /* ALARM definition */
    #define EE_MAX_ALARM 7U
    #define AlarmOS_2ms 0U
    #define AlarmOS_5ms 1U
    #define AlarmOS_10ms 2U
    #define AlarmOS_20ms 3U
    #define AlarmOS_50ms 4U
    #define AlarmOS_100ms 5U
    #define AlarmOS_500ms 6U

    /* SCHEDULING TABLE definition */
    #define EE_MAX_SCHEDULETABLE 0U

    /* COUNTER OBJECTS definition */
    #define EE_MAX_COUNTER_OBJECTS (EE_MAX_ALARM + EE_MAX_SCHEDULETABLE)

    /* COUNTER definition */
    #define EE_MAX_COUNTER 1U
    #define OSMainCounter 0U

    /* APPMODE definition */
    #define EE_MAX_APPMODE 0U

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

    /* Number of isr 2 */
    #define EE_MAX_ISR2   1
    #define EE_MAX_ISR_ID 1

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define __NO_APP__
#define __USE_SYSTICK__
#define __ADD_LIBS__


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
#define __RTD_CYGWIN__
#define __STM32__
#define __STM32F4xx__
#define __CORTEX_MX__
#define __CORTEX_M4__
#define __GNU__
#define __FP__
#define __MONO__
#define __ALARMS__
#define __FP_NO_RESOURCE__

#endif



/***************************************************************************
 *
 * ISR definition
 *
 **************************************************************************/
#define EE_CORTEX_MX_SYSTICK_ISR systick_handler
#define EE_CORTEX_MX_SYSTICK_ISR_PRI EE_ISR_PRI_1


/***************************************************************************
 *
 * Vector size defines
 *
 **************************************************************************/
    #define EE_ALARM_ROM_SIZE 7


#endif


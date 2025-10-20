#ifndef CMSIS_STUBS_H
#define CMSIS_STUBS_H

#if defined(MICRO_FAMILY_ESP32_C3)

#include <stdint.h>
#include <stddef.h>

// Forward declare FreeRTOS function to avoid include issues
extern int xPortInIsrContext(void);

// Define IRQn_Type for compatibility 
typedef enum {
    ESP32_IRQ_0 = 0,
    ESP32_IRQ_1 = 1,
    ESP32_IRQ_MAX = 32
} IRQn_Type;

// ESP32 CMSIS compatibility function declarations

/**
 * \brief   Get IPSR Register (ESP32 stub)
 * \details ESP32 doesn't have IPSR. Return 0 for thread mode, non-zero for interrupt context.
 * \return  0 if in thread mode, non-zero if in interrupt context
 */
__attribute__((always_inline)) static inline uint32_t __get_IPSR(void) {
    // On ESP32, use FreeRTOS API to determine interrupt context
    return (uint32_t)xPortInIsrContext();
}

/**
 * \brief   Get Control Register (ESP32 stub) 
 * \details ESP32 doesn't have ARM Control register. Always return 0 (privileged mode).
 * \return  Always 0 (privileged mode)
 */
__attribute__((always_inline)) static inline uint32_t __get_CONTROL(void) {
    return 0; // ESP32 FreeRTOS runs in privileged mode
}

/**
 * \brief   Get Main Stack Pointer (ESP32 stub)
 * \details Return current stack pointer
 * \return  Current stack pointer value
 */
__attribute__((always_inline)) static inline uint32_t __get_MSP(void) {
    void *sp;
    __asm volatile ("mov %0, sp" : "=r" (sp));
    return (uint32_t)(uintptr_t)sp;
}

/**
 * \brief   Get Process Stack Pointer (ESP32 stub)
 * \details ESP32 doesn't use separate process stack. Return MSP.
 * \return  Current stack pointer (same as MSP)
 */
__attribute__((always_inline)) static inline uint32_t __get_PSP(void) {
    return __get_MSP(); // ESP32 uses single stack model
}

/**
 * \brief   Get Interrupt Priority (ESP32 stub)
 * \details ESP32 doesn't have NVIC. Return default priority.
 * \param   IRQn  Interrupt number
 * \return  Default interrupt priority (configMAX_SYSCALL_INTERRUPT_PRIORITY)
 */
__attribute__((always_inline)) static inline uint32_t NVIC_GetPriority(IRQn_Type IRQn) {
    (void)IRQn;
    // Return default FreeRTOS interrupt priority for ESP32
    return 5; // Mid-range priority
}

/**
 * \brief   Set Interrupt Priority (ESP32 stub)
 * \details ESP32 priority setting is managed by ESP-IDF. This is a no-op stub.
 * \param   IRQn      Interrupt number  
 * \param   priority  Priority to set
 */
__attribute__((always_inline)) static inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority) {
    (void)IRQn;
    (void)priority;
    // ESP32 interrupt priorities are handled by ESP-IDF
    // This is a no-op stub for compatibility
}

/**
 * \brief   Enable Interrupt (ESP32 stub)
 * \details ESP32 interrupt enabling is managed by ESP-IDF. This is a no-op stub.
 * \param   IRQn  Interrupt number
 */
__attribute__((always_inline)) static inline void NVIC_EnableIRQ(IRQn_Type IRQn) {
    (void)IRQn;
    // ESP32 interrupt management is handled by ESP-IDF
}

/**
 * \brief   Disable Interrupt (ESP32 stub)
 * \details ESP32 interrupt disabling is managed by ESP-IDF. This is a no-op stub.
 * \param   IRQn  Interrupt number
 */
__attribute__((always_inline)) static inline void NVIC_DisableIRQ(IRQn_Type IRQn) {
    (void)IRQn;
    // ESP32 interrupt management is handled by ESP-IDF
}

/**
 * \brief   Set Priority Grouping (ESP32 stub)
 * \details ESP32 doesn't use ARM priority grouping. This is a no-op stub.
 * \param   PriorityGroup  Priority grouping value
 */
__attribute__((always_inline)) static inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup) {
    (void)PriorityGroup;
    // ESP32 doesn't use ARM-style priority grouping
}

/**
 * \brief   Clear Pending Interrupt (ESP32 stub)
 * \details ESP32 interrupt management is handled by ESP-IDF. This is a no-op stub.
 * \param   IRQn  Interrupt number
 */
__attribute__((always_inline)) static inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn) {
    (void)IRQn;
    // ESP32 interrupt management is handled by ESP-IDF
}

/**
 * \brief   Get Priority Mask (ESP32 stub)
 * \details ESP32 doesn't have PRIMASK. Return 0 (interrupts enabled).
 * \return  Always 0 (interrupts enabled)
 */
__attribute__((always_inline)) static inline uint32_t __get_PRIMASK(void) {
    // ESP32 uses FreeRTOS critical sections instead of PRIMASK
    // Return 0 to indicate interrupts are enabled
    return 0;
}

/**
 * \brief   Set Priority Mask (ESP32 stub)
 * \details ESP32 doesn't have PRIMASK. This is a no-op stub.
 * \param   priMask  Priority mask value
 */
__attribute__((always_inline)) static inline void __set_PRIMASK(uint32_t priMask) {
    (void)priMask;
    // ESP32 uses FreeRTOS critical sections instead of PRIMASK
}

/**
 * \brief   Set Control Register (ESP32 stub)
 * \details ESP32 doesn't have ARM Control register. This is a no-op stub.
 * \param   control  Control register value
 */
__attribute__((always_inline)) static inline void __set_CONTROL(uint32_t control) {
    (void)control;
    // ESP32 doesn't have ARM Control register
}

#endif // MICRO_FAMILY_ESP32_C3

#endif // CMSIS_STUBS_H

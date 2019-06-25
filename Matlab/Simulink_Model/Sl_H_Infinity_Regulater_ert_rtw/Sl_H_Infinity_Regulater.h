/*
 * File: Sl_H_Infinity_Regulater.h
 *
 * Code generated for Simulink model 'Sl_H_Infinity_Regulater'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Mon Jun 24 13:46:44 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Sl_H_Infinity_Regulater_h_
#define RTW_HEADER_Sl_H_Infinity_Regulater_h_
#include <string.h>
#include <stddef.h>
#ifndef Sl_H_Infinity_Regulater_COMMON_INCLUDES_
# define Sl_H_Infinity_Regulater_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Sl_H_Infinity_Regulater_COMMON_INCLUDES_ */

#include "Sl_H_Infinity_Regulater_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T DiscreteStateSpace_DSTATE[7]; /* '<Root>/Discrete State-Space' */
} DW_Sl_H_Infinity_Regulater_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Ref;                          /* '<Root>/Ref ' */
  real_T Osvetenost;                   /* '<Root>/Osvetenost ' */
} ExtU_Sl_H_Infinity_Regulater_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T motor;                        /* '<Root>/motor' */
  real_T lampa;                        /* '<Root>/lampa' */
} ExtY_Sl_H_Infinity_Regulater_T;

/* Parameters (auto storage) */
struct P_Sl_H_Infinity_Regulater_T_ {
  real_T DiscreteStateSpace_A[49];     /* Computed Parameter: DiscreteStateSpace_A
                                        * Referenced by: '<Root>/Discrete State-Space'
                                        */
  real_T DiscreteStateSpace_B[7];      /* Computed Parameter: DiscreteStateSpace_B
                                        * Referenced by: '<Root>/Discrete State-Space'
                                        */
  real_T DiscreteStateSpace_C[14];     /* Computed Parameter: DiscreteStateSpace_C
                                        * Referenced by: '<Root>/Discrete State-Space'
                                        */
  real_T DiscreteStateSpace_X0;        /* Expression: 0
                                        * Referenced by: '<Root>/Discrete State-Space'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Sl_H_Infinity_Regulat_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (auto storage) */
extern P_Sl_H_Infinity_Regulater_T Sl_H_Infinity_Regulater_P;

/* Block states (auto storage) */
extern DW_Sl_H_Infinity_Regulater_T Sl_H_Infinity_Regulater_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_Sl_H_Infinity_Regulater_T Sl_H_Infinity_Regulater_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_Sl_H_Infinity_Regulater_T Sl_H_Infinity_Regulater_Y;

/* Model entry point functions */
extern void Sl_H_Infinity_Regulater_initialize(void);
extern void Sl_H_Infinity_Regulater_step(void);
extern void Sl_H_Infinity_Regulater_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Sl_H_Infinity_Regula_T *const Sl_H_Infinity_Regulater_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Sl_H_Infinity_Regulater'
 */
#endif                                 /* RTW_HEADER_Sl_H_Infinity_Regulater_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

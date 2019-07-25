/*
 * File: Sl_H_Infinity_Regulater.c
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

#include "Sl_H_Infinity_Regulater.h"
#include "Sl_H_Infinity_Regulater_private.h"

/* Block states (auto storage) */
DW_Sl_H_Infinity_Regulater_T Sl_H_Infinity_Regulater_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_Sl_H_Infinity_Regulater_T Sl_H_Infinity_Regulater_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_Sl_H_Infinity_Regulater_T Sl_H_Infinity_Regulater_Y;

/* Real-time model */
RT_MODEL_Sl_H_Infinity_Regula_T Sl_H_Infinity_Regulater_M_;
RT_MODEL_Sl_H_Infinity_Regula_T *const Sl_H_Infinity_Regulater_M =
  &Sl_H_Infinity_Regulater_M_;

/* Model step function */
void Sl_H_Infinity_Regulater_step(void)
{
  /* local block i/o variables */
  real_T rtb_Sum;
  real_T rtb_DiscreteStateSpace[2];

  /* DiscreteStateSpace: '<Root>/Discrete State-Space' */
  {
    {
      static const int_T colCidxRow0[7] = { 0, 1, 2, 3, 4, 5, 6 };

      const int_T *pCidx = &colCidxRow0[0];
      const real_T *pC0 = Sl_H_Infinity_Regulater_P.DiscreteStateSpace_C;
      const real_T *xd = &Sl_H_Infinity_Regulater_DW.DiscreteStateSpace_DSTATE[0];
      real_T *y0 = &rtb_DiscreteStateSpace[0];
      int_T numNonZero = 6;
      *y0 = (*pC0++) * xd[*pCidx++];
      while (numNonZero--) {
        *y0 += (*pC0++) * xd[*pCidx++];
      }
    }

    {
      static const int_T colCidxRow1[7] = { 0, 1, 2, 3, 4, 5, 6 };

      const int_T *pCidx = &colCidxRow1[0];
      const real_T *pC7 = &Sl_H_Infinity_Regulater_P.DiscreteStateSpace_C[7];
      const real_T *xd = &Sl_H_Infinity_Regulater_DW.DiscreteStateSpace_DSTATE[0];
      real_T *y1 = &rtb_DiscreteStateSpace[1];
      int_T numNonZero = 6;
      *y1 = (*pC7++) * xd[*pCidx++];
      while (numNonZero--) {
        *y1 += (*pC7++) * xd[*pCidx++];
      }
    }
  }

  /* Outport: '<Root>/motor' */
  Sl_H_Infinity_Regulater_Y.motor = rtb_DiscreteStateSpace[0];

  /* Outport: '<Root>/lampa' */
  Sl_H_Infinity_Regulater_Y.lampa = rtb_DiscreteStateSpace[1];

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/Osvetenost '
   *  Inport: '<Root>/Ref '
   */
  rtb_Sum = Sl_H_Infinity_Regulater_U.Ref - Sl_H_Infinity_Regulater_U.Osvetenost;

  /* Update for DiscreteStateSpace: '<Root>/Discrete State-Space' */
  {
    real_T xnew[7];

    {
      static const int_T colAidxRow0[7] = { 0, 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow0[0];
      const real_T *pA0 = Sl_H_Infinity_Regulater_P.DiscreteStateSpace_A;
      const real_T *xd = &Sl_H_Infinity_Regulater_DW.DiscreteStateSpace_DSTATE[0];
      real_T *pxnew0 = &xnew[0];
      int_T numNonZero = 6;
      *pxnew0 = (*pA0++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew0 += (*pA0++) * xd[*pAidx++];
      }
    }

    xnew[0] += (Sl_H_Infinity_Regulater_P.DiscreteStateSpace_B[0])*rtb_Sum;

    {
      static const int_T colAidxRow1[7] = { 0, 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow1[0];
      const real_T *pA7 = &Sl_H_Infinity_Regulater_P.DiscreteStateSpace_A[7];
      const real_T *xd = &Sl_H_Infinity_Regulater_DW.DiscreteStateSpace_DSTATE[0];
      real_T *pxnew1 = &xnew[1];
      int_T numNonZero = 6;
      *pxnew1 = (*pA7++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew1 += (*pA7++) * xd[*pAidx++];
      }
    }

    xnew[1] += (Sl_H_Infinity_Regulater_P.DiscreteStateSpace_B[1])*rtb_Sum;

    {
      static const int_T colAidxRow2[7] = { 0, 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow2[0];
      const real_T *pA14 = &Sl_H_Infinity_Regulater_P.DiscreteStateSpace_A[14];
      const real_T *xd = &Sl_H_Infinity_Regulater_DW.DiscreteStateSpace_DSTATE[0];
      real_T *pxnew2 = &xnew[2];
      int_T numNonZero = 6;
      *pxnew2 = (*pA14++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew2 += (*pA14++) * xd[*pAidx++];
      }
    }

    xnew[2] += (Sl_H_Infinity_Regulater_P.DiscreteStateSpace_B[2])*rtb_Sum;

    {
      static const int_T colAidxRow3[7] = { 0, 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow3[0];
      const real_T *pA21 = &Sl_H_Infinity_Regulater_P.DiscreteStateSpace_A[21];
      const real_T *xd = &Sl_H_Infinity_Regulater_DW.DiscreteStateSpace_DSTATE[0];
      real_T *pxnew3 = &xnew[3];
      int_T numNonZero = 6;
      *pxnew3 = (*pA21++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew3 += (*pA21++) * xd[*pAidx++];
      }
    }

    xnew[3] += (Sl_H_Infinity_Regulater_P.DiscreteStateSpace_B[3])*rtb_Sum;

    {
      static const int_T colAidxRow4[7] = { 0, 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow4[0];
      const real_T *pA28 = &Sl_H_Infinity_Regulater_P.DiscreteStateSpace_A[28];
      const real_T *xd = &Sl_H_Infinity_Regulater_DW.DiscreteStateSpace_DSTATE[0];
      real_T *pxnew4 = &xnew[4];
      int_T numNonZero = 6;
      *pxnew4 = (*pA28++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew4 += (*pA28++) * xd[*pAidx++];
      }
    }

    xnew[4] += (Sl_H_Infinity_Regulater_P.DiscreteStateSpace_B[4])*rtb_Sum;

    {
      static const int_T colAidxRow5[7] = { 0, 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow5[0];
      const real_T *pA35 = &Sl_H_Infinity_Regulater_P.DiscreteStateSpace_A[35];
      const real_T *xd = &Sl_H_Infinity_Regulater_DW.DiscreteStateSpace_DSTATE[0];
      real_T *pxnew5 = &xnew[5];
      int_T numNonZero = 6;
      *pxnew5 = (*pA35++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew5 += (*pA35++) * xd[*pAidx++];
      }
    }

    xnew[5] += (Sl_H_Infinity_Regulater_P.DiscreteStateSpace_B[5])*rtb_Sum;

    {
      static const int_T colAidxRow6[7] = { 0, 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow6[0];
      const real_T *pA42 = &Sl_H_Infinity_Regulater_P.DiscreteStateSpace_A[42];
      const real_T *xd = &Sl_H_Infinity_Regulater_DW.DiscreteStateSpace_DSTATE[0];
      real_T *pxnew6 = &xnew[6];
      int_T numNonZero = 6;
      *pxnew6 = (*pA42++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew6 += (*pA42++) * xd[*pAidx++];
      }
    }

    xnew[6] += (Sl_H_Infinity_Regulater_P.DiscreteStateSpace_B[6])*rtb_Sum;
    (void) memcpy(&Sl_H_Infinity_Regulater_DW.DiscreteStateSpace_DSTATE[0], xnew,
                  sizeof(real_T)*7);
  }
}

/* Model initialize function */
void Sl_H_Infinity_Regulater_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Sl_H_Infinity_Regulater_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&Sl_H_Infinity_Regulater_DW, 0,
                sizeof(DW_Sl_H_Infinity_Regulater_T));

  /* external inputs */
  (void) memset((void *)&Sl_H_Infinity_Regulater_U, 0,
                sizeof(ExtU_Sl_H_Infinity_Regulater_T));

  /* external outputs */
  (void) memset((void *)&Sl_H_Infinity_Regulater_Y, 0,
                sizeof(ExtY_Sl_H_Infinity_Regulater_T));

  /* InitializeConditions for DiscreteStateSpace: '<Root>/Discrete State-Space' */
  {
    int_T i1;
    real_T *dw_DSTATE = &Sl_H_Infinity_Regulater_DW.DiscreteStateSpace_DSTATE[0];
    for (i1=0; i1 < 7; i1++) {
      dw_DSTATE[i1] = Sl_H_Infinity_Regulater_P.DiscreteStateSpace_X0;
    }
  }
}

/* Model terminate function */
void Sl_H_Infinity_Regulater_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

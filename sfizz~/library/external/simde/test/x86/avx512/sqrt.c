/* SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Copyright:
 *   2020      Evan Nemerson <evan@nemerson.com>
 *   2020      Himanshi Mathur <himanshi18037@iiitd.ac.in>
 */

#define SIMDE_TEST_X86_AVX512_INSN sqrt

#include <test/x86/avx512/test-avx512.h>
#include <simde/x86/avx512/set.h>
#include <simde/x86/avx512/sqrt.h>

static int
test_simde_mm512_sqrt_ps (SIMDE_MUNIT_TEST_ARGS) {
  static const struct {
    const simde_float32 a[16];
    const simde_float32 r[16];
  } test_vec[] = {
     { { SIMDE_FLOAT32_C(   217.83), SIMDE_FLOAT32_C(   108.94), SIMDE_FLOAT32_C(    38.33), SIMDE_FLOAT32_C(   277.15),
        SIMDE_FLOAT32_C(    59.82), SIMDE_FLOAT32_C(   344.99), SIMDE_FLOAT32_C(   240.56), SIMDE_FLOAT32_C(   162.50),
        SIMDE_FLOAT32_C(    91.12), SIMDE_FLOAT32_C(   517.25), SIMDE_FLOAT32_C(   419.27), SIMDE_FLOAT32_C(   630.58),
        SIMDE_FLOAT32_C(   139.48), SIMDE_FLOAT32_C(   227.23), SIMDE_FLOAT32_C(   130.66), SIMDE_FLOAT32_C(   968.78) },
      { SIMDE_FLOAT32_C(    14.76), SIMDE_FLOAT32_C(    10.44), SIMDE_FLOAT32_C(     6.19), SIMDE_FLOAT32_C(    16.65),
        SIMDE_FLOAT32_C(     7.73), SIMDE_FLOAT32_C(    18.57), SIMDE_FLOAT32_C(    15.51), SIMDE_FLOAT32_C(    12.75),
        SIMDE_FLOAT32_C(     9.55), SIMDE_FLOAT32_C(    22.74), SIMDE_FLOAT32_C(    20.48), SIMDE_FLOAT32_C(    25.11),
        SIMDE_FLOAT32_C(    11.81), SIMDE_FLOAT32_C(    15.07), SIMDE_FLOAT32_C(    11.43), SIMDE_FLOAT32_C(    31.13) } },
    { { SIMDE_FLOAT32_C(   223.24), SIMDE_FLOAT32_C(    61.22), SIMDE_FLOAT32_C(     5.71), SIMDE_FLOAT32_C(   939.37),
        SIMDE_FLOAT32_C(   950.58), SIMDE_FLOAT32_C(   463.21), SIMDE_FLOAT32_C(    93.23), SIMDE_FLOAT32_C(   926.17),
        SIMDE_FLOAT32_C(   149.54), SIMDE_FLOAT32_C(   345.84), SIMDE_FLOAT32_C(   517.84), SIMDE_FLOAT32_C(   367.13),
        SIMDE_FLOAT32_C(   366.95), SIMDE_FLOAT32_C(   396.36), SIMDE_FLOAT32_C(   650.42), SIMDE_FLOAT32_C(   583.12) },
      { SIMDE_FLOAT32_C(    14.94), SIMDE_FLOAT32_C(     7.82), SIMDE_FLOAT32_C(     2.39), SIMDE_FLOAT32_C(    30.65),
        SIMDE_FLOAT32_C(    30.83), SIMDE_FLOAT32_C(    21.52), SIMDE_FLOAT32_C(     9.66), SIMDE_FLOAT32_C(    30.43),
        SIMDE_FLOAT32_C(    12.23), SIMDE_FLOAT32_C(    18.60), SIMDE_FLOAT32_C(    22.76), SIMDE_FLOAT32_C(    19.16),
        SIMDE_FLOAT32_C(    19.16), SIMDE_FLOAT32_C(    19.91), SIMDE_FLOAT32_C(    25.50), SIMDE_FLOAT32_C(    24.15) } },
    #if !defined(SIMDE_FAST_MATH)
    { { SIMDE_FLOAT32_C(   710.05), SIMDE_FLOAT32_C(   748.28), SIMDE_FLOAT32_C(   893.06), SIMDE_FLOAT32_C(   -62.84),
        SIMDE_FLOAT32_C(   792.96), SIMDE_FLOAT32_C(   635.10), SIMDE_FLOAT32_C(   563.04), SIMDE_FLOAT32_C(   594.48),
        SIMDE_FLOAT32_C(   976.52), SIMDE_FLOAT32_C(   154.93), SIMDE_FLOAT32_C(    90.22), SIMDE_FLOAT32_C(   370.25),
        SIMDE_FLOAT32_C(   935.93), SIMDE_FLOAT32_C(   -51.25), SIMDE_FLOAT32_C(   771.97), SIMDE_FLOAT32_C(   851.63) },
      { SIMDE_FLOAT32_C(    26.65), SIMDE_FLOAT32_C(    27.35), SIMDE_FLOAT32_C(    29.88),            SIMDE_MATH_NANF,
        SIMDE_FLOAT32_C(    28.16), SIMDE_FLOAT32_C(    25.20), SIMDE_FLOAT32_C(    23.73), SIMDE_FLOAT32_C(    24.38),
        SIMDE_FLOAT32_C(    31.25), SIMDE_FLOAT32_C(    12.45), SIMDE_FLOAT32_C(     9.50), SIMDE_FLOAT32_C(    19.24),
        SIMDE_FLOAT32_C(    30.59),            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(    27.78), SIMDE_FLOAT32_C(    29.18) } },
    { { SIMDE_FLOAT32_C(   -30.75), SIMDE_FLOAT32_C(   -68.78), SIMDE_FLOAT32_C(   -79.81), SIMDE_FLOAT32_C(   475.72),
        SIMDE_FLOAT32_C(   407.95), SIMDE_FLOAT32_C(   958.53), SIMDE_FLOAT32_C(   380.76), SIMDE_FLOAT32_C(   553.07),
        SIMDE_FLOAT32_C(   201.21), SIMDE_FLOAT32_C(   214.86), SIMDE_FLOAT32_C(   771.54), SIMDE_FLOAT32_C(   348.19),
        SIMDE_FLOAT32_C(   997.59), SIMDE_FLOAT32_C(   154.92), SIMDE_FLOAT32_C(   997.20), SIMDE_FLOAT32_C(   140.62) },
      {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(    21.81),
        SIMDE_FLOAT32_C(    20.20), SIMDE_FLOAT32_C(    30.96), SIMDE_FLOAT32_C(    19.51), SIMDE_FLOAT32_C(    23.52),
        SIMDE_FLOAT32_C(    14.19), SIMDE_FLOAT32_C(    14.66), SIMDE_FLOAT32_C(    27.78), SIMDE_FLOAT32_C(    18.66),
        SIMDE_FLOAT32_C(    31.58), SIMDE_FLOAT32_C(    12.45), SIMDE_FLOAT32_C(    31.58), SIMDE_FLOAT32_C(    11.86) } },
    #endif
    { { SIMDE_FLOAT32_C(   466.31), SIMDE_FLOAT32_C(   614.68), SIMDE_FLOAT32_C(   580.31), SIMDE_FLOAT32_C(   539.32),
        SIMDE_FLOAT32_C(   203.17), SIMDE_FLOAT32_C(   122.82), SIMDE_FLOAT32_C(   465.01), SIMDE_FLOAT32_C(   751.36),
        SIMDE_FLOAT32_C(   957.86), SIMDE_FLOAT32_C(    40.61), SIMDE_FLOAT32_C(   299.33), SIMDE_FLOAT32_C(   397.65),
        SIMDE_FLOAT32_C(   571.56), SIMDE_FLOAT32_C(   866.02), SIMDE_FLOAT32_C(   947.17), SIMDE_FLOAT32_C(   787.06) },
      { SIMDE_FLOAT32_C(    21.59), SIMDE_FLOAT32_C(    24.79), SIMDE_FLOAT32_C(    24.09), SIMDE_FLOAT32_C(    23.22),
        SIMDE_FLOAT32_C(    14.25), SIMDE_FLOAT32_C(    11.08), SIMDE_FLOAT32_C(    21.56), SIMDE_FLOAT32_C(    27.41),
        SIMDE_FLOAT32_C(    30.95), SIMDE_FLOAT32_C(     6.37), SIMDE_FLOAT32_C(    17.30), SIMDE_FLOAT32_C(    19.94),
        SIMDE_FLOAT32_C(    23.91), SIMDE_FLOAT32_C(    29.43), SIMDE_FLOAT32_C(    30.78), SIMDE_FLOAT32_C(    28.05) } },
    #if !defined(SIMDE_FAST_MATH)
    { { SIMDE_FLOAT32_C(   379.06), SIMDE_FLOAT32_C(   518.14), SIMDE_FLOAT32_C(   498.86), SIMDE_FLOAT32_C(    -3.46),
        SIMDE_FLOAT32_C(   -23.53), SIMDE_FLOAT32_C(   266.36), SIMDE_FLOAT32_C(   681.68), SIMDE_FLOAT32_C(   242.19),
        SIMDE_FLOAT32_C(   263.88), SIMDE_FLOAT32_C(   654.06), SIMDE_FLOAT32_C(   331.27), SIMDE_FLOAT32_C(   317.61),
        SIMDE_FLOAT32_C(   624.18), SIMDE_FLOAT32_C(   874.14), SIMDE_FLOAT32_C(   894.91), SIMDE_FLOAT32_C(   175.60) },
      { SIMDE_FLOAT32_C(    19.47), SIMDE_FLOAT32_C(    22.76), SIMDE_FLOAT32_C(    22.34),            SIMDE_MATH_NANF,
                   SIMDE_MATH_NANF, SIMDE_FLOAT32_C(    16.32), SIMDE_FLOAT32_C(    26.11), SIMDE_FLOAT32_C(    15.56),
        SIMDE_FLOAT32_C(    16.24), SIMDE_FLOAT32_C(    25.57), SIMDE_FLOAT32_C(    18.20), SIMDE_FLOAT32_C(    17.82),
        SIMDE_FLOAT32_C(    24.98), SIMDE_FLOAT32_C(    29.57), SIMDE_FLOAT32_C(    29.91), SIMDE_FLOAT32_C(    13.25) } },
    { { SIMDE_FLOAT32_C(   910.44), SIMDE_FLOAT32_C(   492.48), SIMDE_FLOAT32_C(   518.91), SIMDE_FLOAT32_C(   259.60),
        SIMDE_FLOAT32_C(   324.91), SIMDE_FLOAT32_C(   233.97), SIMDE_FLOAT32_C(   654.12), SIMDE_FLOAT32_C(   260.58),
        SIMDE_FLOAT32_C(   230.74), SIMDE_FLOAT32_C(   276.07), SIMDE_FLOAT32_C(   -86.08), SIMDE_FLOAT32_C(   582.99),
        SIMDE_FLOAT32_C(   393.66), SIMDE_FLOAT32_C(   633.68), SIMDE_FLOAT32_C(   958.09), SIMDE_FLOAT32_C(   559.47) },
      { SIMDE_FLOAT32_C(    30.17), SIMDE_FLOAT32_C(    22.19), SIMDE_FLOAT32_C(    22.78), SIMDE_FLOAT32_C(    16.11),
        SIMDE_FLOAT32_C(    18.03), SIMDE_FLOAT32_C(    15.30), SIMDE_FLOAT32_C(    25.58), SIMDE_FLOAT32_C(    16.14),
        SIMDE_FLOAT32_C(    15.19), SIMDE_FLOAT32_C(    16.62),            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(    24.15),
        SIMDE_FLOAT32_C(    19.84), SIMDE_FLOAT32_C(    25.17), SIMDE_FLOAT32_C(    30.95), SIMDE_FLOAT32_C(    23.65) } },
    #endif
    { { SIMDE_FLOAT32_C(   421.74), SIMDE_FLOAT32_C(   223.58), SIMDE_FLOAT32_C(   636.89), SIMDE_FLOAT32_C(   288.28),
        SIMDE_FLOAT32_C(    38.61), SIMDE_FLOAT32_C(   936.22), SIMDE_FLOAT32_C(    31.25), SIMDE_FLOAT32_C(   215.71),
        SIMDE_FLOAT32_C(   498.70), SIMDE_FLOAT32_C(   630.00), SIMDE_FLOAT32_C(   370.58), SIMDE_FLOAT32_C(   365.46),
        SIMDE_FLOAT32_C(   300.68), SIMDE_FLOAT32_C(   498.16), SIMDE_FLOAT32_C(   559.20), SIMDE_FLOAT32_C(   547.97) },
      { SIMDE_FLOAT32_C(    20.54), SIMDE_FLOAT32_C(    14.95), SIMDE_FLOAT32_C(    25.24), SIMDE_FLOAT32_C(    16.98),
        SIMDE_FLOAT32_C(     6.21), SIMDE_FLOAT32_C(    30.60), SIMDE_FLOAT32_C(     5.59), SIMDE_FLOAT32_C(    14.69),
        SIMDE_FLOAT32_C(    22.33), SIMDE_FLOAT32_C(    25.10), SIMDE_FLOAT32_C(    19.25), SIMDE_FLOAT32_C(    19.12),
        SIMDE_FLOAT32_C(    17.34), SIMDE_FLOAT32_C(    22.32), SIMDE_FLOAT32_C(    23.65), SIMDE_FLOAT32_C(    23.41) } },
    { { SIMDE_FLOAT32_C(   482.41), SIMDE_FLOAT32_C(   904.16), SIMDE_FLOAT32_C(   301.69), SIMDE_FLOAT32_C(   497.46),
        SIMDE_FLOAT32_C(   869.63), SIMDE_FLOAT32_C(   866.07), SIMDE_FLOAT32_C(    86.91), SIMDE_FLOAT32_C(   705.04),
        SIMDE_FLOAT32_C(   534.39), SIMDE_FLOAT32_C(   480.29), SIMDE_FLOAT32_C(   152.20), SIMDE_FLOAT32_C(     7.09),
        SIMDE_FLOAT32_C(    89.72), SIMDE_FLOAT32_C(   938.68), SIMDE_FLOAT32_C(   472.63), SIMDE_FLOAT32_C(   431.56) },
      { SIMDE_FLOAT32_C(    21.96), SIMDE_FLOAT32_C(    30.07), SIMDE_FLOAT32_C(    17.37), SIMDE_FLOAT32_C(    22.30),
        SIMDE_FLOAT32_C(    29.49), SIMDE_FLOAT32_C(    29.43), SIMDE_FLOAT32_C(     9.32), SIMDE_FLOAT32_C(    26.55),
        SIMDE_FLOAT32_C(    23.12), SIMDE_FLOAT32_C(    21.92), SIMDE_FLOAT32_C(    12.34), SIMDE_FLOAT32_C(     2.66),
        SIMDE_FLOAT32_C(     9.47), SIMDE_FLOAT32_C(    30.64), SIMDE_FLOAT32_C(    21.74), SIMDE_FLOAT32_C(    20.77) } }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m512 a = simde_mm512_loadu_ps(test_vec[i].a);
    simde__m512 r = simde_mm512_sqrt_ps(a);
    simde_test_x86_assert_equal_f32x16(r, simde_mm512_loadu_ps(test_vec[i].r), 1);
  }

  return 0;
}

static int
test_simde_mm512_mask_sqrt_ps (SIMDE_MUNIT_TEST_ARGS) {
  static const struct {
    const simde_float32 src[16];
    const simde__mmask8 k;
    const simde_float32 a[16];
    const simde_float32 r[16];
  } test_vec[] = {
    #if !defined(SIMDE_FAST_MATH)
    { { SIMDE_FLOAT32_C(   437.33), SIMDE_FLOAT32_C(   830.55), SIMDE_FLOAT32_C(   885.40), SIMDE_FLOAT32_C(   946.45),
        SIMDE_FLOAT32_C(   740.66), SIMDE_FLOAT32_C(   515.39), SIMDE_FLOAT32_C(   501.14), SIMDE_FLOAT32_C(   807.71),
        SIMDE_FLOAT32_C(   988.01), SIMDE_FLOAT32_C(   854.01), SIMDE_FLOAT32_C(   302.94), SIMDE_FLOAT32_C(   510.25),
        SIMDE_FLOAT32_C(    -3.35), SIMDE_FLOAT32_C(   705.28), SIMDE_FLOAT32_C(   895.93), SIMDE_FLOAT32_C(   944.13) },
      UINT8_C( 44),
      { SIMDE_FLOAT32_C(   -17.46), SIMDE_FLOAT32_C(   104.01), SIMDE_FLOAT32_C(   -12.13), SIMDE_FLOAT32_C(   572.59),
        SIMDE_FLOAT32_C(   553.23), SIMDE_FLOAT32_C(   667.21), SIMDE_FLOAT32_C(   175.86), SIMDE_FLOAT32_C(   857.51),
        SIMDE_FLOAT32_C(   875.76), SIMDE_FLOAT32_C(   661.26), SIMDE_FLOAT32_C(   359.55), SIMDE_FLOAT32_C(   492.88),
        SIMDE_FLOAT32_C(   614.94), SIMDE_FLOAT32_C(   592.23), SIMDE_FLOAT32_C(   639.48), SIMDE_FLOAT32_C(   586.75) },
      { SIMDE_FLOAT32_C(   437.33), SIMDE_FLOAT32_C(   830.55),            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(    23.93),
        SIMDE_FLOAT32_C(   740.66), SIMDE_FLOAT32_C(    25.83), SIMDE_FLOAT32_C(   501.14), SIMDE_FLOAT32_C(   807.71),
        SIMDE_FLOAT32_C(   988.01), SIMDE_FLOAT32_C(   854.01), SIMDE_FLOAT32_C(   302.94), SIMDE_FLOAT32_C(   510.25),
        SIMDE_FLOAT32_C(    -3.35), SIMDE_FLOAT32_C(   705.28), SIMDE_FLOAT32_C(   895.93), SIMDE_FLOAT32_C(   944.13) } },
    #endif
    { { SIMDE_FLOAT32_C(   830.85), SIMDE_FLOAT32_C(   416.09), SIMDE_FLOAT32_C(   252.98), SIMDE_FLOAT32_C(   170.02),
        SIMDE_FLOAT32_C(   649.47), SIMDE_FLOAT32_C(    61.92), SIMDE_FLOAT32_C(   -30.00), SIMDE_FLOAT32_C(   565.15),
        SIMDE_FLOAT32_C(   804.54), SIMDE_FLOAT32_C(   537.62), SIMDE_FLOAT32_C(   139.69), SIMDE_FLOAT32_C(   223.23),
        SIMDE_FLOAT32_C(   700.71), SIMDE_FLOAT32_C(    84.06), SIMDE_FLOAT32_C(   154.25), SIMDE_FLOAT32_C(   749.16) },
      UINT8_C(186),
      { SIMDE_FLOAT32_C(   637.38), SIMDE_FLOAT32_C(   483.43), SIMDE_FLOAT32_C(   245.18), SIMDE_FLOAT32_C(   987.92),
        SIMDE_FLOAT32_C(   407.77), SIMDE_FLOAT32_C(   184.67), SIMDE_FLOAT32_C(   504.64), SIMDE_FLOAT32_C(   244.98),
        SIMDE_FLOAT32_C(   -92.45), SIMDE_FLOAT32_C(   233.10), SIMDE_FLOAT32_C(   347.51), SIMDE_FLOAT32_C(   453.74),
        SIMDE_FLOAT32_C(   654.02), SIMDE_FLOAT32_C(   778.35), SIMDE_FLOAT32_C(   364.48), SIMDE_FLOAT32_C(   774.62) },
      { SIMDE_FLOAT32_C(   830.85), SIMDE_FLOAT32_C(    21.99), SIMDE_FLOAT32_C(   252.98), SIMDE_FLOAT32_C(    31.43),
        SIMDE_FLOAT32_C(    20.19), SIMDE_FLOAT32_C(    13.59), SIMDE_FLOAT32_C(   -30.00), SIMDE_FLOAT32_C(    15.65),
        SIMDE_FLOAT32_C(   804.54), SIMDE_FLOAT32_C(   537.62), SIMDE_FLOAT32_C(   139.69), SIMDE_FLOAT32_C(   223.23),
        SIMDE_FLOAT32_C(   700.71), SIMDE_FLOAT32_C(    84.06), SIMDE_FLOAT32_C(   154.25), SIMDE_FLOAT32_C(   749.16) } },
    { { SIMDE_FLOAT32_C(   341.01), SIMDE_FLOAT32_C(   234.85), SIMDE_FLOAT32_C(    83.58), SIMDE_FLOAT32_C(   -91.38),
        SIMDE_FLOAT32_C(   735.59), SIMDE_FLOAT32_C(   -51.68), SIMDE_FLOAT32_C(   211.29), SIMDE_FLOAT32_C(   125.75),
        SIMDE_FLOAT32_C(   171.18), SIMDE_FLOAT32_C(   387.03), SIMDE_FLOAT32_C(   278.80), SIMDE_FLOAT32_C(   688.49),
        SIMDE_FLOAT32_C(   284.47), SIMDE_FLOAT32_C(   309.43), SIMDE_FLOAT32_C(   761.03), SIMDE_FLOAT32_C(   804.65) },
      UINT8_C( 32),
      { SIMDE_FLOAT32_C(   348.92), SIMDE_FLOAT32_C(   -22.74), SIMDE_FLOAT32_C(   451.50), SIMDE_FLOAT32_C(   370.23),
        SIMDE_FLOAT32_C(   582.81), SIMDE_FLOAT32_C(   734.74), SIMDE_FLOAT32_C(    42.12), SIMDE_FLOAT32_C(   353.92),
        SIMDE_FLOAT32_C(   504.09), SIMDE_FLOAT32_C(   977.38), SIMDE_FLOAT32_C(   328.27), SIMDE_FLOAT32_C(   482.22),
        SIMDE_FLOAT32_C(   737.20), SIMDE_FLOAT32_C(   630.17), SIMDE_FLOAT32_C(   265.58), SIMDE_FLOAT32_C(   661.60) },
      { SIMDE_FLOAT32_C(   341.01), SIMDE_FLOAT32_C(   234.85), SIMDE_FLOAT32_C(    83.58), SIMDE_FLOAT32_C(   -91.38),
        SIMDE_FLOAT32_C(   735.59), SIMDE_FLOAT32_C(    27.11), SIMDE_FLOAT32_C(   211.29), SIMDE_FLOAT32_C(   125.75),
        SIMDE_FLOAT32_C(   171.18), SIMDE_FLOAT32_C(   387.03), SIMDE_FLOAT32_C(   278.80), SIMDE_FLOAT32_C(   688.49),
        SIMDE_FLOAT32_C(   284.47), SIMDE_FLOAT32_C(   309.43), SIMDE_FLOAT32_C(   761.03), SIMDE_FLOAT32_C(   804.65) } },
    #if !defined(SIMDE_FAST_MATH)
    { { SIMDE_FLOAT32_C(   525.05), SIMDE_FLOAT32_C(   166.18), SIMDE_FLOAT32_C(   952.07), SIMDE_FLOAT32_C(   664.08),
        SIMDE_FLOAT32_C(   409.88), SIMDE_FLOAT32_C(   422.77), SIMDE_FLOAT32_C(   381.48), SIMDE_FLOAT32_C(   505.76),
        SIMDE_FLOAT32_C(   441.87), SIMDE_FLOAT32_C(   222.70), SIMDE_FLOAT32_C(   519.86), SIMDE_FLOAT32_C(   854.25),
        SIMDE_FLOAT32_C(   -46.91), SIMDE_FLOAT32_C(    81.38), SIMDE_FLOAT32_C(   328.69), SIMDE_FLOAT32_C(   977.87) },
      UINT8_C(124),
      { SIMDE_FLOAT32_C(   332.53), SIMDE_FLOAT32_C(   706.88), SIMDE_FLOAT32_C(   312.95), SIMDE_FLOAT32_C(   533.68),
        SIMDE_FLOAT32_C(   -71.13), SIMDE_FLOAT32_C(   -10.56), SIMDE_FLOAT32_C(   585.48), SIMDE_FLOAT32_C(   449.30),
        SIMDE_FLOAT32_C(   860.34), SIMDE_FLOAT32_C(    80.38), SIMDE_FLOAT32_C(   990.66), SIMDE_FLOAT32_C(   203.10),
        SIMDE_FLOAT32_C(   -25.23), SIMDE_FLOAT32_C(   283.85), SIMDE_FLOAT32_C(   906.28), SIMDE_FLOAT32_C(   992.76) },
      { SIMDE_FLOAT32_C(   525.05), SIMDE_FLOAT32_C(   166.18), SIMDE_FLOAT32_C(    17.69), SIMDE_FLOAT32_C(    23.10),
                   SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(    24.20), SIMDE_FLOAT32_C(   505.76),
        SIMDE_FLOAT32_C(   441.87), SIMDE_FLOAT32_C(   222.70), SIMDE_FLOAT32_C(   519.86), SIMDE_FLOAT32_C(   854.25),
        SIMDE_FLOAT32_C(   -46.91), SIMDE_FLOAT32_C(    81.38), SIMDE_FLOAT32_C(   328.69), SIMDE_FLOAT32_C(   977.87) } },
    { { SIMDE_FLOAT32_C(   261.52), SIMDE_FLOAT32_C(   593.91), SIMDE_FLOAT32_C(   282.09), SIMDE_FLOAT32_C(   905.01),
        SIMDE_FLOAT32_C(   558.85), SIMDE_FLOAT32_C(   546.97), SIMDE_FLOAT32_C(    39.41), SIMDE_FLOAT32_C(    37.09),
        SIMDE_FLOAT32_C(   653.22), SIMDE_FLOAT32_C(   550.08), SIMDE_FLOAT32_C(   671.18), SIMDE_FLOAT32_C(   893.07),
        SIMDE_FLOAT32_C(    49.27), SIMDE_FLOAT32_C(   666.55), SIMDE_FLOAT32_C(    76.85), SIMDE_FLOAT32_C(    59.26) },
      UINT8_C( 52),
      { SIMDE_FLOAT32_C(   191.70), SIMDE_FLOAT32_C(   831.43), SIMDE_FLOAT32_C(   284.20), SIMDE_FLOAT32_C(   147.82),
        SIMDE_FLOAT32_C(   463.91), SIMDE_FLOAT32_C(   -90.80), SIMDE_FLOAT32_C(   595.96), SIMDE_FLOAT32_C(   665.44),
        SIMDE_FLOAT32_C(   187.07), SIMDE_FLOAT32_C(   126.37), SIMDE_FLOAT32_C(   751.70), SIMDE_FLOAT32_C(   153.73),
        SIMDE_FLOAT32_C(   678.31), SIMDE_FLOAT32_C(   781.00), SIMDE_FLOAT32_C(   842.34), SIMDE_FLOAT32_C(     5.66) },
      { SIMDE_FLOAT32_C(   261.52), SIMDE_FLOAT32_C(   593.91), SIMDE_FLOAT32_C(    16.86), SIMDE_FLOAT32_C(   905.01),
        SIMDE_FLOAT32_C(    21.54),            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(    39.41), SIMDE_FLOAT32_C(    37.09),
        SIMDE_FLOAT32_C(   653.22), SIMDE_FLOAT32_C(   550.08), SIMDE_FLOAT32_C(   671.18), SIMDE_FLOAT32_C(   893.07),
        SIMDE_FLOAT32_C(    49.27), SIMDE_FLOAT32_C(   666.55), SIMDE_FLOAT32_C(    76.85), SIMDE_FLOAT32_C(    59.26) } },
    #endif
    { { SIMDE_FLOAT32_C(   370.90), SIMDE_FLOAT32_C(   934.09), SIMDE_FLOAT32_C(   929.98), SIMDE_FLOAT32_C(   111.97),
        SIMDE_FLOAT32_C(   630.79), SIMDE_FLOAT32_C(   778.41), SIMDE_FLOAT32_C(   263.20), SIMDE_FLOAT32_C(   298.61),
        SIMDE_FLOAT32_C(   360.62), SIMDE_FLOAT32_C(   832.32), SIMDE_FLOAT32_C(   957.47), SIMDE_FLOAT32_C(   168.49),
        SIMDE_FLOAT32_C(   294.36), SIMDE_FLOAT32_C(   406.95), SIMDE_FLOAT32_C(   757.71), SIMDE_FLOAT32_C(   992.73) },
      UINT8_C( 43),
      { SIMDE_FLOAT32_C(   358.33), SIMDE_FLOAT32_C(   783.52), SIMDE_FLOAT32_C(   332.05), SIMDE_FLOAT32_C(   318.37),
        SIMDE_FLOAT32_C(   298.14), SIMDE_FLOAT32_C(    66.82), SIMDE_FLOAT32_C(   869.43), SIMDE_FLOAT32_C(   946.18),
        SIMDE_FLOAT32_C(   680.16), SIMDE_FLOAT32_C(   120.71), SIMDE_FLOAT32_C(   248.65), SIMDE_FLOAT32_C(   -79.28),
        SIMDE_FLOAT32_C(   590.86), SIMDE_FLOAT32_C(   707.03), SIMDE_FLOAT32_C(   570.73), SIMDE_FLOAT32_C(    84.44) },
      { SIMDE_FLOAT32_C(    18.93), SIMDE_FLOAT32_C(    27.99), SIMDE_FLOAT32_C(   929.98), SIMDE_FLOAT32_C(    17.84),
        SIMDE_FLOAT32_C(   630.79), SIMDE_FLOAT32_C(     8.17), SIMDE_FLOAT32_C(   263.20), SIMDE_FLOAT32_C(   298.61),
        SIMDE_FLOAT32_C(   360.62), SIMDE_FLOAT32_C(   832.32), SIMDE_FLOAT32_C(   957.47), SIMDE_FLOAT32_C(   168.49),
        SIMDE_FLOAT32_C(   294.36), SIMDE_FLOAT32_C(   406.95), SIMDE_FLOAT32_C(   757.71), SIMDE_FLOAT32_C(   992.73) } },
    #if !defined(SIMDE_FAST_MATH)
    { { SIMDE_FLOAT32_C(   -62.52), SIMDE_FLOAT32_C(   613.71), SIMDE_FLOAT32_C(   789.90), SIMDE_FLOAT32_C(   932.36),
        SIMDE_FLOAT32_C(   552.83), SIMDE_FLOAT32_C(   530.45), SIMDE_FLOAT32_C(   607.43), SIMDE_FLOAT32_C(   797.28),
        SIMDE_FLOAT32_C(   661.83), SIMDE_FLOAT32_C(   -89.44), SIMDE_FLOAT32_C(   318.54), SIMDE_FLOAT32_C(   945.75),
        SIMDE_FLOAT32_C(   -58.88), SIMDE_FLOAT32_C(   130.26), SIMDE_FLOAT32_C(    25.25), SIMDE_FLOAT32_C(   627.24) },
      UINT8_C( 40),
      { SIMDE_FLOAT32_C(   242.87), SIMDE_FLOAT32_C(   758.11), SIMDE_FLOAT32_C(    97.46), SIMDE_FLOAT32_C(   -58.70),
        SIMDE_FLOAT32_C(   972.97), SIMDE_FLOAT32_C(   -55.48), SIMDE_FLOAT32_C(   199.83), SIMDE_FLOAT32_C(    10.44),
        SIMDE_FLOAT32_C(   304.24), SIMDE_FLOAT32_C(   341.28), SIMDE_FLOAT32_C(   281.04), SIMDE_FLOAT32_C(   900.87),
        SIMDE_FLOAT32_C(   363.46), SIMDE_FLOAT32_C(   218.41), SIMDE_FLOAT32_C(   940.41), SIMDE_FLOAT32_C(   457.09) },
      { SIMDE_FLOAT32_C(   -62.52), SIMDE_FLOAT32_C(   613.71), SIMDE_FLOAT32_C(   789.90),            SIMDE_MATH_NANF,
        SIMDE_FLOAT32_C(   552.83),            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   607.43), SIMDE_FLOAT32_C(   797.28),
        SIMDE_FLOAT32_C(   661.83), SIMDE_FLOAT32_C(   -89.44), SIMDE_FLOAT32_C(   318.54), SIMDE_FLOAT32_C(   945.75),
        SIMDE_FLOAT32_C(   -58.88), SIMDE_FLOAT32_C(   130.26), SIMDE_FLOAT32_C(    25.25), SIMDE_FLOAT32_C(   627.24) } },
    #endif
    { { SIMDE_FLOAT32_C(   750.99), SIMDE_FLOAT32_C(   296.52), SIMDE_FLOAT32_C(   456.51), SIMDE_FLOAT32_C(   964.82),
        SIMDE_FLOAT32_C(   376.02), SIMDE_FLOAT32_C(    -0.77), SIMDE_FLOAT32_C(   -19.77), SIMDE_FLOAT32_C(   808.40),
        SIMDE_FLOAT32_C(   462.68), SIMDE_FLOAT32_C(   106.03), SIMDE_FLOAT32_C(   864.38), SIMDE_FLOAT32_C(   846.10),
        SIMDE_FLOAT32_C(   539.67), SIMDE_FLOAT32_C(   599.36), SIMDE_FLOAT32_C(   551.35), SIMDE_FLOAT32_C(   -77.63) },
      UINT8_C( 43),
      { SIMDE_FLOAT32_C(   762.24), SIMDE_FLOAT32_C(   130.02), SIMDE_FLOAT32_C(   518.26), SIMDE_FLOAT32_C(   332.17),
        SIMDE_FLOAT32_C(   129.59), SIMDE_FLOAT32_C(   952.63), SIMDE_FLOAT32_C(    71.40), SIMDE_FLOAT32_C(   788.60),
        SIMDE_FLOAT32_C(   964.30), SIMDE_FLOAT32_C(   468.08), SIMDE_FLOAT32_C(   636.78), SIMDE_FLOAT32_C(   267.82),
        SIMDE_FLOAT32_C(   875.24), SIMDE_FLOAT32_C(   684.32), SIMDE_FLOAT32_C(   694.20), SIMDE_FLOAT32_C(   586.14) },
      { SIMDE_FLOAT32_C(    27.61), SIMDE_FLOAT32_C(    11.40), SIMDE_FLOAT32_C(   456.51), SIMDE_FLOAT32_C(    18.23),
        SIMDE_FLOAT32_C(   376.02), SIMDE_FLOAT32_C(    30.86), SIMDE_FLOAT32_C(   -19.77), SIMDE_FLOAT32_C(   808.40),
        SIMDE_FLOAT32_C(   462.68), SIMDE_FLOAT32_C(   106.03), SIMDE_FLOAT32_C(   864.38), SIMDE_FLOAT32_C(   846.10),
        SIMDE_FLOAT32_C(   539.67), SIMDE_FLOAT32_C(   599.36), SIMDE_FLOAT32_C(   551.35), SIMDE_FLOAT32_C(   -77.63) } }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m512 src = simde_mm512_loadu_ps(test_vec[i].src);
    simde__m512 a = simde_mm512_loadu_ps(test_vec[i].a);
    simde__m512 r = simde_mm512_mask_sqrt_ps(src, test_vec[i].k, a);
    simde_test_x86_assert_equal_f32x16(r, simde_mm512_loadu_ps(test_vec[i].r), 1);
  }

  return 0;
}

static int
test_simde_mm512_sqrt_pd (SIMDE_MUNIT_TEST_ARGS) {
  static const struct {
    const simde_float64 a[8];
    const simde_float64 r[8];
  } test_vec[] = {
    { { SIMDE_FLOAT64_C(   475.48), SIMDE_FLOAT64_C(   699.80), SIMDE_FLOAT64_C(   552.88), SIMDE_FLOAT64_C(   673.91),
        SIMDE_FLOAT64_C(   591.26), SIMDE_FLOAT64_C(   249.70), SIMDE_FLOAT64_C(   639.44), SIMDE_FLOAT64_C(   997.04) },
      { SIMDE_FLOAT64_C(    21.81), SIMDE_FLOAT64_C(    26.45), SIMDE_FLOAT64_C(    23.51), SIMDE_FLOAT64_C(    25.96),
        SIMDE_FLOAT64_C(    24.32), SIMDE_FLOAT64_C(    15.80), SIMDE_FLOAT64_C(    25.29), SIMDE_FLOAT64_C(    31.58) } },
    { { SIMDE_FLOAT64_C(   727.89), SIMDE_FLOAT64_C(   978.25), SIMDE_FLOAT64_C(     4.89), SIMDE_FLOAT64_C(   693.62),
        SIMDE_FLOAT64_C(   611.57), SIMDE_FLOAT64_C(   256.31), SIMDE_FLOAT64_C(   600.18), SIMDE_FLOAT64_C(   836.50) },
      { SIMDE_FLOAT64_C(    26.98), SIMDE_FLOAT64_C(    31.28), SIMDE_FLOAT64_C(     2.21), SIMDE_FLOAT64_C(    26.34),
        SIMDE_FLOAT64_C(    24.73), SIMDE_FLOAT64_C(    16.01), SIMDE_FLOAT64_C(    24.50), SIMDE_FLOAT64_C(    28.92) } },
    { { SIMDE_FLOAT64_C(   214.90), SIMDE_FLOAT64_C(   393.95), SIMDE_FLOAT64_C(   919.26), SIMDE_FLOAT64_C(   432.55),
        SIMDE_FLOAT64_C(   371.71), SIMDE_FLOAT64_C(   880.26), SIMDE_FLOAT64_C(   482.63), SIMDE_FLOAT64_C(   601.65) },
      { SIMDE_FLOAT64_C(    14.66), SIMDE_FLOAT64_C(    19.85), SIMDE_FLOAT64_C(    30.32), SIMDE_FLOAT64_C(    20.80),
        SIMDE_FLOAT64_C(    19.28), SIMDE_FLOAT64_C(    29.67), SIMDE_FLOAT64_C(    21.97), SIMDE_FLOAT64_C(    24.53) } },
    #if !defined(SIMDE_FAST_MATH)
    { { SIMDE_FLOAT64_C(   234.49), SIMDE_FLOAT64_C(   534.45), SIMDE_FLOAT64_C(    -6.91), SIMDE_FLOAT64_C(   455.17),
        SIMDE_FLOAT64_C(   785.50), SIMDE_FLOAT64_C(   558.55), SIMDE_FLOAT64_C(    29.83), SIMDE_FLOAT64_C(   758.42) },
      { SIMDE_FLOAT64_C(    15.31), SIMDE_FLOAT64_C(    23.12),             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(    21.33),
        SIMDE_FLOAT64_C(    28.03), SIMDE_FLOAT64_C(    23.63), SIMDE_FLOAT64_C(     5.46), SIMDE_FLOAT64_C(    27.54) } },
    #endif
    { { SIMDE_FLOAT64_C(   958.27), SIMDE_FLOAT64_C(   519.34), SIMDE_FLOAT64_C(   591.49), SIMDE_FLOAT64_C(    62.08),
        SIMDE_FLOAT64_C(   499.87), SIMDE_FLOAT64_C(   535.48), SIMDE_FLOAT64_C(    73.76), SIMDE_FLOAT64_C(   819.20) },
      { SIMDE_FLOAT64_C(    30.96), SIMDE_FLOAT64_C(    22.79), SIMDE_FLOAT64_C(    24.32), SIMDE_FLOAT64_C(     7.88),
        SIMDE_FLOAT64_C(    22.36), SIMDE_FLOAT64_C(    23.14), SIMDE_FLOAT64_C(     8.59), SIMDE_FLOAT64_C(    28.62) } },
    { { SIMDE_FLOAT64_C(   299.98), SIMDE_FLOAT64_C(   211.87), SIMDE_FLOAT64_C(    78.11), SIMDE_FLOAT64_C(   113.36),
        SIMDE_FLOAT64_C(   727.13), SIMDE_FLOAT64_C(   252.70), SIMDE_FLOAT64_C(   421.79), SIMDE_FLOAT64_C(   169.91) },
      { SIMDE_FLOAT64_C(    17.32), SIMDE_FLOAT64_C(    14.56), SIMDE_FLOAT64_C(     8.84), SIMDE_FLOAT64_C(    10.65),
        SIMDE_FLOAT64_C(    26.97), SIMDE_FLOAT64_C(    15.90), SIMDE_FLOAT64_C(    20.54), SIMDE_FLOAT64_C(    13.04) } },
    { { SIMDE_FLOAT64_C(   878.93), SIMDE_FLOAT64_C(   333.65), SIMDE_FLOAT64_C(   469.80), SIMDE_FLOAT64_C(   224.14),
        SIMDE_FLOAT64_C(   245.21), SIMDE_FLOAT64_C(   905.97), SIMDE_FLOAT64_C(   267.17), SIMDE_FLOAT64_C(   243.63) },
      { SIMDE_FLOAT64_C(    29.65), SIMDE_FLOAT64_C(    18.27), SIMDE_FLOAT64_C(    21.67), SIMDE_FLOAT64_C(    14.97),
        SIMDE_FLOAT64_C(    15.66), SIMDE_FLOAT64_C(    30.10), SIMDE_FLOAT64_C(    16.35), SIMDE_FLOAT64_C(    15.61) } },
    { { SIMDE_FLOAT64_C(   486.76), SIMDE_FLOAT64_C(   343.81), SIMDE_FLOAT64_C(   521.65), SIMDE_FLOAT64_C(   919.38),
        SIMDE_FLOAT64_C(   462.37), SIMDE_FLOAT64_C(   489.02), SIMDE_FLOAT64_C(   941.81), SIMDE_FLOAT64_C(   719.89) },
      { SIMDE_FLOAT64_C(    22.06), SIMDE_FLOAT64_C(    18.54), SIMDE_FLOAT64_C(    22.84), SIMDE_FLOAT64_C(    30.32),
        SIMDE_FLOAT64_C(    21.50), SIMDE_FLOAT64_C(    22.11), SIMDE_FLOAT64_C(    30.69), SIMDE_FLOAT64_C(    26.83) } },
    { { SIMDE_FLOAT64_C(   260.10), SIMDE_FLOAT64_C(  2158.90), SIMDE_FLOAT64_C(  9449.89), SIMDE_FLOAT64_C(  5861.96),
        SIMDE_FLOAT64_C(   394.19), SIMDE_FLOAT64_C(  3597.89), SIMDE_FLOAT64_C(  5033.33), SIMDE_FLOAT64_C(  1539.23) },
      { SIMDE_FLOAT64_C(    16.13), SIMDE_FLOAT64_C(    46.46), SIMDE_FLOAT64_C(    97.21), SIMDE_FLOAT64_C(    76.56),
        SIMDE_FLOAT64_C(    19.85), SIMDE_FLOAT64_C(    59.98), SIMDE_FLOAT64_C(    70.95), SIMDE_FLOAT64_C(    39.23) } }

    };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m512d a = simde_mm512_loadu_pd(test_vec[i].a);
    simde__m512d r = simde_mm512_sqrt_pd(a);
    simde_test_x86_assert_equal_f64x8(r, simde_mm512_loadu_pd(test_vec[i].r), 1);
  }

  return 0;
}

static int
test_simde_mm512_mask_sqrt_pd (SIMDE_MUNIT_TEST_ARGS) {
  static const struct {
    const simde_float64 src[8];
    const simde__mmask8 k;
    const simde_float64 a[8];
    const simde_float64 r[8];
  } test_vec[] = {
    { { SIMDE_FLOAT64_C(   436.97), SIMDE_FLOAT64_C(   398.19), SIMDE_FLOAT64_C(   907.60), SIMDE_FLOAT64_C(    61.33),
        SIMDE_FLOAT64_C(   912.86), SIMDE_FLOAT64_C(   540.33), SIMDE_FLOAT64_C(   579.42), SIMDE_FLOAT64_C(   990.91) },
      UINT8_C( 17),
      { SIMDE_FLOAT64_C(   499.36), SIMDE_FLOAT64_C(   607.00), SIMDE_FLOAT64_C(   184.57), SIMDE_FLOAT64_C(   -79.89),
        SIMDE_FLOAT64_C(   246.08), SIMDE_FLOAT64_C(   684.81), SIMDE_FLOAT64_C(   154.65), SIMDE_FLOAT64_C(   825.63) },
      { SIMDE_FLOAT64_C(    22.35), SIMDE_FLOAT64_C(   398.19), SIMDE_FLOAT64_C(   907.60), SIMDE_FLOAT64_C(    61.33),
        SIMDE_FLOAT64_C(    15.69), SIMDE_FLOAT64_C(   540.33), SIMDE_FLOAT64_C(   579.42), SIMDE_FLOAT64_C(   990.91) } },
    { { SIMDE_FLOAT64_C(   735.36), SIMDE_FLOAT64_C(   411.96), SIMDE_FLOAT64_C(   273.29), SIMDE_FLOAT64_C(   443.97),
        SIMDE_FLOAT64_C(   379.78), SIMDE_FLOAT64_C(   504.36), SIMDE_FLOAT64_C(    13.17), SIMDE_FLOAT64_C(    95.38) },
      UINT8_C(184),
      { SIMDE_FLOAT64_C(   913.65), SIMDE_FLOAT64_C(   567.81), SIMDE_FLOAT64_C(   431.31), SIMDE_FLOAT64_C(   891.24),
        SIMDE_FLOAT64_C(   236.76), SIMDE_FLOAT64_C(   364.35), SIMDE_FLOAT64_C(   850.12), SIMDE_FLOAT64_C(   890.20) },
      { SIMDE_FLOAT64_C(   735.36), SIMDE_FLOAT64_C(   411.96), SIMDE_FLOAT64_C(   273.29), SIMDE_FLOAT64_C(    29.85),
        SIMDE_FLOAT64_C(    15.39), SIMDE_FLOAT64_C(    19.09), SIMDE_FLOAT64_C(    13.17), SIMDE_FLOAT64_C(    29.84) } },
    { { SIMDE_FLOAT64_C(   218.79), SIMDE_FLOAT64_C(   849.62), SIMDE_FLOAT64_C(   238.02), SIMDE_FLOAT64_C(   635.35),
        SIMDE_FLOAT64_C(   466.14), SIMDE_FLOAT64_C(    -6.77), SIMDE_FLOAT64_C(   423.69), SIMDE_FLOAT64_C(   491.52) },
      UINT8_C( 45),
      { SIMDE_FLOAT64_C(   263.35), SIMDE_FLOAT64_C(   539.75), SIMDE_FLOAT64_C(   722.58), SIMDE_FLOAT64_C(   197.33),
        SIMDE_FLOAT64_C(   953.96), SIMDE_FLOAT64_C(   549.94), SIMDE_FLOAT64_C(   504.50), SIMDE_FLOAT64_C(   168.47) },
      { SIMDE_FLOAT64_C(    16.23), SIMDE_FLOAT64_C(   849.62), SIMDE_FLOAT64_C(    26.88), SIMDE_FLOAT64_C(    14.05),
        SIMDE_FLOAT64_C(   466.14), SIMDE_FLOAT64_C(    23.45), SIMDE_FLOAT64_C(   423.69), SIMDE_FLOAT64_C(   491.52) } },
    { { SIMDE_FLOAT64_C(   937.73), SIMDE_FLOAT64_C(   521.55), SIMDE_FLOAT64_C(   689.62), SIMDE_FLOAT64_C(   704.92),
        SIMDE_FLOAT64_C(   375.20), SIMDE_FLOAT64_C(   562.70), SIMDE_FLOAT64_C(   460.68), SIMDE_FLOAT64_C(   702.26) },
      UINT8_C( 99),
      { SIMDE_FLOAT64_C(   247.65), SIMDE_FLOAT64_C(   799.76), SIMDE_FLOAT64_C(   469.26), SIMDE_FLOAT64_C(   689.97),
        SIMDE_FLOAT64_C(   966.92), SIMDE_FLOAT64_C(   496.27), SIMDE_FLOAT64_C(   437.90), SIMDE_FLOAT64_C(   542.79) },
      { SIMDE_FLOAT64_C(    15.74), SIMDE_FLOAT64_C(    28.28), SIMDE_FLOAT64_C(   689.62), SIMDE_FLOAT64_C(   704.92),
        SIMDE_FLOAT64_C(   375.20), SIMDE_FLOAT64_C(    22.28), SIMDE_FLOAT64_C(    20.93), SIMDE_FLOAT64_C(   702.26) } },
    { { SIMDE_FLOAT64_C(   239.42), SIMDE_FLOAT64_C(   982.54), SIMDE_FLOAT64_C(   153.70), SIMDE_FLOAT64_C(   223.51),
        SIMDE_FLOAT64_C(   914.90), SIMDE_FLOAT64_C(   712.58), SIMDE_FLOAT64_C(   479.58), SIMDE_FLOAT64_C(   340.52) },
      UINT8_C(110),
      { SIMDE_FLOAT64_C(   629.70), SIMDE_FLOAT64_C(    40.18), SIMDE_FLOAT64_C(   773.21), SIMDE_FLOAT64_C(   826.47),
        SIMDE_FLOAT64_C(   650.68), SIMDE_FLOAT64_C(   597.70), SIMDE_FLOAT64_C(    99.58), SIMDE_FLOAT64_C(   419.32) },
      { SIMDE_FLOAT64_C(   239.42), SIMDE_FLOAT64_C(     6.34), SIMDE_FLOAT64_C(    27.81), SIMDE_FLOAT64_C(    28.75),
        SIMDE_FLOAT64_C(   914.90), SIMDE_FLOAT64_C(    24.45), SIMDE_FLOAT64_C(     9.98), SIMDE_FLOAT64_C(   340.52) } },
    { { SIMDE_FLOAT64_C(   659.09), SIMDE_FLOAT64_C(   166.50), SIMDE_FLOAT64_C(   866.73), SIMDE_FLOAT64_C(   759.19),
        SIMDE_FLOAT64_C(   667.51), SIMDE_FLOAT64_C(   836.84), SIMDE_FLOAT64_C(   988.98), SIMDE_FLOAT64_C(   546.59) },
      UINT8_C(105),
      { SIMDE_FLOAT64_C(   223.00), SIMDE_FLOAT64_C(   -16.57), SIMDE_FLOAT64_C(   745.33), SIMDE_FLOAT64_C(   813.45),
        SIMDE_FLOAT64_C(   615.39), SIMDE_FLOAT64_C(   490.76), SIMDE_FLOAT64_C(   133.77), SIMDE_FLOAT64_C(   749.00) },
      { SIMDE_FLOAT64_C(    14.93), SIMDE_FLOAT64_C(   166.50), SIMDE_FLOAT64_C(   866.73), SIMDE_FLOAT64_C(    28.52),
        SIMDE_FLOAT64_C(   667.51), SIMDE_FLOAT64_C(    22.15), SIMDE_FLOAT64_C(    11.57), SIMDE_FLOAT64_C(   546.59) } },
    #if !defined(SIMDE_FAST_MATH)
    { { SIMDE_FLOAT64_C(   910.80), SIMDE_FLOAT64_C(    67.30), SIMDE_FLOAT64_C(    90.00), SIMDE_FLOAT64_C(   999.85),
        SIMDE_FLOAT64_C(   617.26), SIMDE_FLOAT64_C(    51.15), SIMDE_FLOAT64_C(   319.01), SIMDE_FLOAT64_C(    38.40) },
      UINT8_C(223),
      { SIMDE_FLOAT64_C(   305.09), SIMDE_FLOAT64_C(   369.65), SIMDE_FLOAT64_C(   856.43), SIMDE_FLOAT64_C(   297.17),
        SIMDE_FLOAT64_C(   331.69), SIMDE_FLOAT64_C(   827.02), SIMDE_FLOAT64_C(   -88.21), SIMDE_FLOAT64_C(   -20.46) },
      { SIMDE_FLOAT64_C(    17.47), SIMDE_FLOAT64_C(    19.23), SIMDE_FLOAT64_C(    29.26), SIMDE_FLOAT64_C(    17.24),
        SIMDE_FLOAT64_C(    18.21), SIMDE_FLOAT64_C(    51.15),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN } },
    #endif
    { { SIMDE_FLOAT64_C(   151.41), SIMDE_FLOAT64_C(   225.20), SIMDE_FLOAT64_C(   805.52), SIMDE_FLOAT64_C(   450.20),
        SIMDE_FLOAT64_C(   464.68), SIMDE_FLOAT64_C(   748.22), SIMDE_FLOAT64_C(   -32.49), SIMDE_FLOAT64_C(   491.49) },
      UINT8_C(  9),
      { SIMDE_FLOAT64_C(   616.36), SIMDE_FLOAT64_C(   262.82), SIMDE_FLOAT64_C(   503.00), SIMDE_FLOAT64_C(   184.91),
        SIMDE_FLOAT64_C(    81.40), SIMDE_FLOAT64_C(   665.20), SIMDE_FLOAT64_C(   481.84), SIMDE_FLOAT64_C(   -81.41) },
      { SIMDE_FLOAT64_C(    24.83), SIMDE_FLOAT64_C(   225.20), SIMDE_FLOAT64_C(   805.52), SIMDE_FLOAT64_C(    13.60),
        SIMDE_FLOAT64_C(   464.68), SIMDE_FLOAT64_C(   748.22), SIMDE_FLOAT64_C(   -32.49), SIMDE_FLOAT64_C(   491.49) } }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m512d src = simde_mm512_loadu_pd(test_vec[i].src);
    simde__m512d a = simde_mm512_loadu_pd(test_vec[i].a);
    simde__m512d r = simde_mm512_mask_sqrt_pd(src, test_vec[i].k, a);
    simde_test_x86_assert_equal_f64x8(r, simde_mm512_loadu_pd(test_vec[i].r), 1);
  }

  return 0;
}

SIMDE_TEST_FUNC_LIST_BEGIN
  SIMDE_TEST_FUNC_LIST_ENTRY(mm512_sqrt_ps)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm512_mask_sqrt_ps)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm512_sqrt_pd)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm512_mask_sqrt_pd)
SIMDE_TEST_FUNC_LIST_END

#include <test/x86/avx512/test-avx512-footer.h>

/*!
  \file math_tests.h

  \brief Simple code for testing some terralib math features.

  \author Etore Marcari Jr. <etore@dpi.inpe.br>
*/

#include "Common.h"

void matrix_test() {
  // Run tests for some terralib features

  std::cout << "Running terralib matrix tests... ";
  
  std::complex<double> c1( 1., 2.);
  std::complex<double> c2( 2., 2.);
  std::complex<double> c3( 3., 3.);
  std::complex<double> c4( 4., 4.);
  std::complex<double> c5( 5., 5.);
  std::complex<double> c6( 6., 6.);
  std::complex<double> c7( 7., 7.);
  std::complex<double> c8( 8., 8.);
  std::complex<double> c9( 9., 9.);

  boost::numeric::ublas::matrix<std::complex<double>> m1(3, 3);

  m1(0,0) = c1;
  m1(0,1) = c2;
  m1(0,2) = c3;
  m1(1,0) = c4;
  m1(1,1) = c5;
  m1(1,2) = c6;
  m1(2,0) = c7;
  m1(2,1) = c8;
  m1(2,2) = c9;

  boost::numeric::ublas::matrix<std::complex<double>> m2(3, 3);

  int result = te::common::GetInverseMatrix(m1, m2);
  assert(result == 1);

  double eps = 1e-5;
  
  assert((m2(0,0).real() - 0.) < eps);
  assert((m2(0,0).imag() + 1.) < eps);
  assert((m2(0,1).real() - 0.) < eps);
  assert((m2(0,1).imag() - 2.) < eps);
  assert((m2(0,2).real() - 0.) < eps);
  assert((m2(0,2).imag() + 1.) < eps);


  assert((m2(1,0).real() - 0.) < eps);
  assert((m2(1,0).imag() - 2.) < eps);
  assert((m2(1,1).real() + 1.5) < eps);
  assert((m2(1,1).imag() + 2.5) < eps);
  assert((m2(1,2).real() - 1.) < eps);
  assert((m2(1,2).imag() - 1.) < eps);

  assert((m2(2,0).real() - 0.) < eps);
  assert((m2(2,0).imag() + 1.) < eps);
  assert((m2(2,1).real() - 1.333333) < eps);
  assert((m2(2,1).imag() - 0.666667) < eps);
  assert((m2(2,2).real() + 0.833333) < eps);
  assert((m2(2,2).imag() + 0.166667) < eps);

  result = te::common::GetPseudoInverseMatrix(m1, m2);
  assert(result == 1);

  assert((m2(0,0).real() - 0.) < eps);
  assert((m2(0,0).imag() + 1.) < eps);
  assert((m2(0,1).real() - 0.) < eps);
  assert((m2(0,1).imag() - 2.) < eps);
  assert((m2(0,2).real() - 0.) < eps);
  assert((m2(0,2).imag() + 1.) < eps);


  assert((m2(1,0).real() - 0.) < eps);
  assert((m2(1,0).imag() - 2.) < eps);
  assert((m2(1,1).real() + 1.5) < eps);
  assert((m2(1,1).imag() + 2.5) < eps);
  assert((m2(1,2).real() - 1.) < eps);
  assert((m2(1,2).imag() - 1.) < eps);

  assert((m2(2,0).real() - 0.) < eps);
  assert((m2(2,0).imag() + 1.) < eps);
  assert((m2(2,1).real() - 1.333333) < eps);
  assert((m2(2,1).imag() - 0.666667) < eps);
  assert((m2(2,2).real() + 0.833333) < eps);
  assert((m2(2,2).imag() + 0.166667) < eps);

  std::cout << "done." << std::endl;
}

void run_terralib_math_tests() {
  matrix_test();
}

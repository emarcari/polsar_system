/*!
  \file numberical_tests.h

  \brief Simple code for numerical tests using boost and std libraries.

  \author Etore Marcari Jr. <etore@dpi.inpe.br>
*/

#include "common.h"

void complex_number_test() {
  // Run simple tests using std::complex<double>

  std::cout << "Running simple complex number operations... ";
  
  std::complex<double> c1( 1., 1.);
  std::complex<double> c2( 2., 2.);

  std::complex<double> x1;

  x1 = c2 + c1;
  assert(x1 == std::complex<double>(3., 3.));

  x1 = c2 - c1;
  assert(x1 == std::complex<double>(1., 1.));

  x1 = c2 * c1;
  assert(x1 == std::complex<double>(0., 4.));

  x1 = c2 / c1;
  assert(x1 == std::complex<double>(2., 0.));

  x1 = std::conj(c1);
  assert(x1 == std::complex<double>(1., -1.));

  std::cout << "done." << std::endl;
}

void boost_ublas_test() {
  // Run tests using boost::ublas

  std::cout << "Running operations using boost::ublas... ";

  std::complex<double> c1( 1., 1.);
  std::complex<double> c2( 2., 2.);
  std::complex<double> c3( 3., 3.);
  std::complex<double> c4( 4., 4.);
  std::complex<double> c5( 5., 5.);
  std::complex<double> c6( 6., 6.);
  std::complex<double> c7( 7., 7.);
  std::complex<double> c8( 8., 8.);

  boost::numeric::ublas::matrix<std::complex<double>> m1(2, 2);
  boost::numeric::ublas::matrix<std::complex<double>> m2(2, 2);

  m1(0,0) = c1;
  m1(0,1) = c2;
  m1(1,0) = c3;
  m1(1,1) = c4;
  m2(0,0) = c5;
  m2(0,1) = c6;
  m2(1,0) = c7;
  m2(1,1) = c8;

  boost::numeric::ublas::matrix<std::complex<double>> x1 = prod(m1, m2);

  assert(x1(0,0).real() == 0.);
  assert(x1(0,0).imag() == 38.);

  assert(x1(0,1).real() == 0.);
  assert(x1(0,1).imag() == 44.);

  assert(x1(1,0).real() == 0.);
  assert(x1(1,0).imag() == 86.);

  assert(x1(1,1).real() == 0.);
  assert(x1(1,1).imag() == 100.);


  std::cout << "done." << std::endl;
}

void run_numerical_tests() {
  complex_number_test();
  boost_ublas_test();
}

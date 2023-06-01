#include "timer.hh"
#include "Matrices.hh"
#include "SpMM.hh"

#include <cassert>

int main(int argc, char *argv[]) {
  assert(argc > 1);
// read from file
  int rows, cols;
  string filename(argv[1]);
  SparseMatrix B(filename);
  std::tie(rows, cols) = B.size();
  Matrix A(rows, cols);
  Matrix C, C_opt;
  {
    ScopeTimer timer("baseline");
    C = SpMM_base(A, B);
  }
  {
    ScopeTimer timer("optimized");
    C_opt = SpMM_opt(A, B);
  }
  if (C != C_opt) {
    std::cout << endl << "result not match" << endl;
    return -1;
  }
  return 0;
}
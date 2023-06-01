#include "SpMM.hh"

Matrix SpMM_base(const Matrix &A, const SparseMatrix &B) {
  if (A.size() != B.size()) return Matrix();
  int A_rows, A_cols, B_rows, B_cols;
  vector<float> data;
  std::tie(A_rows, A_cols) = A.size();
  std::tie(B_rows, B_cols) = B.size();
  for (int i = 0; i < A_rows; ++i) {
    for (int j = 0; j < B_rows; ++j) {
      float sum = 0;
      for (int k = 0; k < B_cols; ++k) {
        sum += A.at(i, k) * B.at(j, k);
      }
      data.push_back(sum);
    }
  }
  return Matrix(data, A_rows, B_rows);
}

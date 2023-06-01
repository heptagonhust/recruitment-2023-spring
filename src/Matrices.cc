#include "Matrices.hh"
#include "SpMM.hh"

#include <random>
#include <fstream>
#include <cassert>
#include <tuple>


SparseMatrix::SparseMatrix(string &filename) {
  ifstream in(filename, ios::in | ios::binary);
  assert(in);
  int m, n;
  in.read(reinterpret_cast<char *>(&m), sizeof(int));
  in.read(reinterpret_cast<char *>(&n), sizeof(int));
  m_ = m;
  n_ = n;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      float num;
      in.read(reinterpret_cast<char *>(&num), sizeof(float));
      data_.push_back(num);
    }
  }
  in.close();
}

void SparseMatrix::fill_random() {
  static default_random_engine e;
  bernoulli_distribution b(.01);
  uniform_real_distribution<float> u(0, 1);
  data_.clear();
  for (int i = 0; i < m_; ++i) {
    for (int j = 0; j < n_; ++j) {
      data_.push_back(b(e) ? u(e) : 0);
    }
  }
}

tuple<int, int> SparseMatrix::size() const {
  return make_tuple(m_, n_);
}

const float& SparseMatrix::at(int i, int j) const {
  return data_[i * n_ + j];
}

float& SparseMatrix::at(int i, int j) {
  return data_[i * n_ + j];
}


Matrix::Matrix(int m, int n) : m_(m), n_(n) {
  static default_random_engine e;
  uniform_real_distribution<float> u(0, 1);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      data_.push_back(u(e));
    }
  }
}

tuple<int, int> Matrix::size() const {
  return make_tuple(m_, n_);
}

const float& Matrix::at(int i, int j) const {
  return data_[i * n_ + j];
}

float& Matrix::at(int i, int j) {
  return data_[i * n_ + j];
}


bool operator==(const Matrix &A, const Matrix &B) {
  if (A.size() != B.size()) return 0;
  int rows, cols;
  std::tie(rows, cols) = A.size();
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (abs(A.at(i, j) - B.at(i, j)) > Matrix::eps)  return 0;
    }
  }
  return 1;
}

bool operator!=(const Matrix &A, const Matrix &B) { 
  return (A == B) ? 0 : 1;
}

Matrix operator*(const Matrix &A, const SparseMatrix &B) {
  return SpMM_base(A, B);
}
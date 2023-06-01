#pragma once
#include <vector>
#include <string>
#include <tuple>
using namespace std;

class SparseMatrix {
  vector<float> data_;
  int m_, n_;

public:
  SparseMatrix() = default;
  SparseMatrix(int m, int n) : m_(m), n_(n) {};
  // import data from file
  SparseMatrix(string &filename);
  
  void fill_random();
  tuple<int, int> size() const;
  const float& at(int i, int j) const;
  float& at(int i, int j);
};

class Matrix {
  vector<float> data_;
  int m_, n_;

public:
  static constexpr float eps = 1e-5;

  Matrix() = default;
  // generate ramdon data
  Matrix(int m, int n);
  Matrix(vector<float> &data, int m, int n) : data_(data), m_(m), n_(n) {}

  tuple<int, int> size() const;
  const float& at(int i, int j) const;
  float& at(int i, int j);
};

bool operator==(const Matrix &A, const Matrix &B);
bool operator!=(const Matrix &A, const Matrix &B);

Matrix operator*(const Matrix &A, const SparseMatrix &B);
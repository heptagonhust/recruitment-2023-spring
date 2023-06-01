#pragma once

#include "Matrices.hh"
#include "timer.hh"

Matrix SpMM_base(const Matrix &A, const SparseMatrix &B);

Matrix SpMM_opt(const Matrix &A, const SparseMatrix &B);

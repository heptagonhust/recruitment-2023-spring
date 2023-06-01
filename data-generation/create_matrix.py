"""
Usage:
  > import create_matrix
  > import random
  > mat_size = random.choice(create_matrix.SPM_SIZES)
  > mat_type = random.choice(create_matrix.SPARSE_MATRIX_TYPES)
  > mat = create_matrix.create_sparse_matrix(mat_type, *mat_size) # 生成稀疏矩阵
  > create_matrix.dump_to_file(mat, "matrix.bin") # 写入二进制文件
  > mat = create_matrix.read_from_file("matrix.bin") # 读入二进制文件
"""

import random
import struct

DENSITY = .1
UPPER, LOWER = 1, -1
SPM_SIZES = [(256, 256), (512, 512), (1024, 1024)]

def _generate_random_float():
  return random.uniform(LOWER, UPPER)

# 对称稀疏矩阵
def _symmetric_matrix(m, n):
  chance = DENSITY / 2
  mat = [[_generate_random_float() if j >= i and random.random() < chance
          else .0 for j in range(n)]
          for i in range(m)]
  for i in range(m):
    for j in range(n):
      if mat[i][j] != .0:
        mat[j][i] = mat[i][j]
  return mat

# （上）三角稀疏矩阵
def _triangular_matrix(m, n):
  chance = DENSITY * 2
  return [[_generate_random_float() if j >= i and random.random() < chance
          else .0 for j in range(n)]
          for i in range(m)]

# 对角稀疏矩阵
def _diagonal_matrix(m, n):
  return [[_generate_random_float() if i == j else .0 for j in range(n)]
          for i in range(m)]

# 条带系数矩阵
def _banded_matrix(m, n):
  half_width = random.randint(1, 5)
  return [[_generate_random_float() if abs(i - j) <= half_width else .0 for j in range(n)]
          for i in range(m)]

# 一般稀疏矩阵
def _general_matrix(m, n):
  return [[_generate_random_float() if random.random() < DENSITY
          else .0 for _ in range(n)]
          for _ in range(m)]

SPARSE_MATRIX_TYPES = ["symmetric", "triangular", "diagonal", "banded", "general"]
_SPARSE_MATRIX_TYPES_MAPPER = {
      "symmetric": _symmetric_matrix,
      "triangular": _triangular_matrix,
      "diagonal": _diagonal_matrix,
      "banded": _banded_matrix,
      "general": _general_matrix
    }

def _check_sparsity(mat):
  total = len(mat) * len(mat[0])
  zeros = sum(row.count(.0) for row in mat)
  return zeros / total > .01

def create_sparse_matrix(type_, m, n):
  while True:
    assert type_ in SPARSE_MATRIX_TYPES
    mat = _SPARSE_MATRIX_TYPES_MAPPER[type_](m, n)
    if _check_sparsity(mat):
      return mat

def dump_to_file(mat, filename):
  m, n = len(mat), len(mat[0])
  with open(filename, "wb") as f:
    f.write(struct.pack("i", m))
    f.write(struct.pack("i", n))
    for row in mat:
      for num in row:
        f.write(struct.pack("f", num))

def read_from_file(filename):
  with open(filename, "rb") as f:
    m, n = struct.unpack("ii", f.read(8))
    return [[struct.unpack('f', f.read(4))[0] for _ in range(n)] for _ in range(m)]

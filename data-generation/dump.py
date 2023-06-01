import create_matrix
import random
import sys
mat_size = random.choice(create_matrix.SPM_SIZES)
mat_type = random.choice(create_matrix.SPARSE_MATRIX_TYPES)
mat = create_matrix.create_sparse_matrix(mat_type, *mat_size) # 生成稀疏矩阵
assert sys.argv[1] is not None
create_matrix.dump_to_file(mat, sys.argv[1]) # 写入二进制文件

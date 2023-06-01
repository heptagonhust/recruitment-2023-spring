import create_matrix
import sys
assert sys.argv[1] is not None
mat = create_matrix.read_from_file(sys.argv[1]) # 读入二进制文件
print(len(mat), len(mat[0]))
print(mat)

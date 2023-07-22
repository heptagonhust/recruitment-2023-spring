#include "SpMM.hh"

Matrix SpMM_opt(const Matrix &A, const SparseMatrix &B) { 
  if(A.size()!=B.size())
  return Matrix();
  int A_rows, A_cols, B_rows, B_cols;
  std::tie(A_rows,A_cols)=A.size();
  std::tie(B_rows,B_cols)=B.size();
  vector<int>col_indices,row_pointers;
  vector<float>values;
  int nnz_count = 0;
  row_pointers.push_back(nnz_count);

  for(int i=0;i<B_rows;i++)
  {
      for(int j=0;j<B_cols;j++)
      {
          if(B.at(i,j)!=0)
          {
              values.push_back(B.at(i,j));
              col_indices.push_back(j);
              nnz_count+=1;
          }
      }
      row_pointers.push_back(nnz_count);
  }
  vector<float>data;
  #pragma omp parallel for
    for (int i = 0; i < A_rows; ++i) {

        for (int j = 0; j < B_rows; ++j) {
            float sum = 0;
            int startPos = row_pointers[j];
            int endPos = row_pointers[j+1];
            for (int pos = startPos; pos < endPos; ++pos) {
                int colIndex = col_indices[pos];
                float value = values[pos];
                sum += A.at(i,colIndex)* value;
            }
             data.push_back(sum);
        }
    }
  return Matrix(data,A_rows,B_rows);
}

# 23-spring-recruiment

# 题目背景

## 总述

稀疏矩阵是一种元素大部分为零的矩阵。这种矩阵在存储和计算时，由于其稀疏性，可以使用一些特殊的数据结构和算法进行优化，以减少内存使用和计算时间。稀疏矩阵-矩阵乘法（SpMM, Sparse Matrix Multiplication）是稀疏矩阵运算的一种，是线性代数中的基本操作。在 SpMM 中，我们需要将一个密集矩阵和一个稀疏矩阵相乘，产生一个新的矩阵。

一般的 SpMM 公式跟普通矩阵乘法一样：

$$
C = A \times B
$$

其中 $A$ 和 $C$ 均为稠密矩阵，大小分别为 $M \times K$ 和 $M \times N$ ； $B$ 是稀疏矩阵，大小为 $K \times N$ ，有 $nnz$ 个非零元（ $nnz \ll K \times N$ ）。SpMM 相较于普通矩阵乘法，区别在于稀疏矩阵 $B$ 有大量的零元。
我们可以用稀疏度来描述矩阵中零元素所占的比例。如果一个矩阵中的大部分元素都是零，我们通常说这个矩阵是稀疏的，反之则是稠密的。

计算稀疏度的公式为：

$$sparsity = \frac{total - nnz}{total}$$

这个比例值在 0 和 1 之间，值越接近 1，矩阵越稀疏；值越接近 0，矩阵越稠密。

例如，如果一个 10x10 的矩阵中有 95 个元素是零，那么稀疏度就是 95 / (10 \* 10) = 0.95，这是一个非常稀疏的矩阵。

稀疏度是一个非常重要的概念，它不仅影响着矩阵的存储和计算效率，而且在很多应用中，比如机器学习、数据挖掘、网络科学等，矩阵的稀疏性也是一个重要的特性。对于稀疏矩阵，我们通常使用特殊的数据结构和算法进行处理，以提高存储和计算的效率。

## 历史

对稀疏矩阵的研究可以追溯到上个世纪的 60 年代。当时，随着计算机科学的发展，人们开始认识到在许多应用中，矩阵往往是稀疏的，也就是说，矩阵中的大部分元素都是零。而对于这类稀疏矩阵，传统的矩阵运算方法会浪费大量的计算资源，因此，人们开始研究适用于稀疏矩阵的算法。

SpMM 作为稀疏矩阵运算的一种，其历史并不长，但发展迅速。随着近年来大数据和机器学习应用的飞速发展，SpMM 的研究和应用也获得了更多的关注。

## 应用

计算机科学中的应用：

在计算机科学领域，稀疏矩阵和 SpMM 的应用十分广泛。在处理图形和网络问题时，稀疏矩阵是一种常见的数据表示方式。例如，互联网的链接结构、社交网络的关系结构、电路模拟等问题都可以使用稀疏矩阵来表示。在这些问题中，SpMM 是一个基本的运算，可以用来计算节点的属性、网络的结构特性等。

机器学习和数据科学中的应用：

在机器学习和数据科学领域，稀疏矩阵和 SpMM 也有很多应用。在处理大规模数据时，数据往往会被表示为稀疏矩阵，例如，用户的点击行为、文本数据的词袋模型等。在这些问题中，SpMM 可以用来计算特征的重要性、用户的相似度等。

高性能计算中的应用：

在高性能计算领域，稀疏矩阵和 SpMM 的优化是一个重要的研究方向。对于大规模的稀疏矩阵，传统的计算方法可能无法满足性能需求，因此，需要设计和实现高效的算法和数据结构。此外，随着并行计算和分布式计算的发展，如何在多核和多节点环境下实现高效的 SpMM 也是一个重要的问题。

因此，研究和掌握稀疏矩阵-矩阵乘法（SpMM）对于理解和解决实际问题具有重要的意义。

# 项目结构

我们为您提供基础代码文件，文件结构如下图：

```
.
├── CMakeLists.txt
├── data  // 本地生成的数据
├── data-generation  // 数据生成python脚本
│   ├── create_matrix.py
│   ├── dump.py
│   ├── generate.py
│   └── read.py
├── etc  // 测试用cmake文件
│   ├── tests-local.cmake
│   └── tests.cmake
├── include
│   ├── Matrices.hh // 矩阵定义
│   └── SpMM.hh
├── src
│   ├── Matrices.cc  // 矩阵定义
│   ├── SpMM_base.cc  // SpMM的baseline
│   └── SpMM_opt.cc  // 您应编写的优化代码
├── tests
│   ├── CMakeLists.txt
│   └── SpMM_test.cc  // 测试用代码
└── utils
    └── timer.hh  // 计时器
```

# 要求

您需要实现`SpMM_opt.cc`中的以下函数：

```
Matrix SpMM_opt(const Matrix &A, const SparseMatrix &B);
```

其中，A 是密集矩阵，B 是以密集矩阵形式存储的稀疏矩阵。 **注意：** 为使 B 是行主序，B 默认已经转置过，所以您需要优化的矩阵乘公式稍有不同：

$$C[i][j] = \sum_{k = 0}^{K - 1} A[i][k] \cdot B[j][k]$$

baseline 在`SpMM_base.cc`的`SpMM_base()`函数中。您可以在 baseline 的基础上，从以下几个方面进行优化，**包括但不限于**：

- 稀疏矩阵的存储格式
- 并行和分布式计算，如 OpenMP、std::thread
- 硬件特性（CPU、Cache）
- 负载均衡

您可以上网查找相关资料。由于稀疏矩阵-向量乘（SpMV）同 SpMM 有相似之处，我们在此提供一篇 SpMV 的入门文章：https://mp.weixin.qq.com/s/AF3uJ7sutM6W1b4OoNRMwA

以下是我们提供的另外一些参考资料：

- 存储格式：https://doi.org/10.1016/B978-0-12-803738-6.00014-8 、 https://medium.com/analytics-vidhya/sparse-matrix-vector-multiplication-with-cuda-42d191878e8f
- OpenMP：https://www.openmp.org/resources/refguides/
- SIMD： 入门：https://zhuanlan.zhihu.com/p/583326378 ， 内建函数参考手册：https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#
- Cache 相关优化：https://zhuanlan.zhihu.com/p/608663298 ，有兴趣也可以看看原论文
- Cache Blocking（Loop Tiling）：https://zhuanlan.zhihu.com/p/292539074 ， https://www.intel.com/content/www/us/en/developer/articles/technical/cache-blocking-techniques.html
- 稀疏矩阵-向量乘（SpMV）的并行化和向量化：https://doi.org/10.1016/B978-0-12-802118-7.00027-3

您可以使用人工智能（如 GPT、New Bing）辅助进行代码编写，但是应该注明哪些部分使用了人工智能工具。另外，GPT 所能做的优化有限，若想进一步提升加速比，建议自己动手。

**除了`SpMM_opt.cc`和顶层目录的`CMakeLists.txt`外，不得更改其他文件。**

# 测试与提交说明

## 测试：

本项目使用 cmake 构建。您可以输入以下命令构建代码：

```
cmake -B build
cmake --build build
```

对于每个通过面试的选手，我们会提供超算队 CPU 集群的访问权限，选手可以在集群上对自己编写的 SpMM 进行测试。如果您在集群上测试，您只需在`build/`目录下运行如下命令：

```
make test
```

如果您期望在本地测试，您在运行以上命令之前，还需要将顶层目录的`CMakeLists.txt`最后一行（即`include("etc/tests.cmake")`）修改成`include("etc/tests-local.cmake")`。构建时，数据生成脚本会在`data/`目录下生成所需数据文件。

**建议在集群上进行测试。截止日期之后，我们会在集群上对您的代码进行验证，加速比以集群运行结果为准。**

**最终测试时，将会使用另外生成的测试数据进行性能评分，请勿针对数据集优化**

**评分方法为对不同类型稀疏矩阵分别评分后，取各个矩阵评分之和作为总分。单一类型矩阵评分标准为此类型不同大小矩阵加速比的加权平均值**

## 提交：

您需要 fork 此 repo，并在代码提交截止日期（2023.6.16 23:59）前将自己的 repo link 以 issue 的方式发表在本 repo 下。您的 repo 应维持原 repo 的目录结构，并包含 SpMM 的实现代码。

与此同时，您需要制作一份 ppt，内容如下：

1. 你使用的设备信息，如 CPU 型号和核数，内存容量和频率等等（集群的也行）。
2. **每一步**优化的思路、过程和效果（举例：使用了 xxx 优化，相对于原代码，速度提升了 114.514 倍）
   - 最好对程序进行 profile，以了解性能瓶颈
3. 你在解题过程中所参考的资料（如有使用人工智能工具，请注明）
4. 在解题过程中，遇到的有意思的事情，或者是让你印象深刻的 bug（可选）

代码审查会用到这份 ppt，因此请您把它发送到超算队邮箱。另外，代码提交截止后，您需要进行一个 presentation，向我们展示您的优化成果。

对题目和提交方式有任何疑问，可在群里提问。

## 怎么入手

1. RTFM，包含此文档和链接给出的题目原文，想明白需要做什么
2. RTFSC，在开始写代码之前，应当清楚每一份文件中的代码的作用，包括 CMake 配置文件
3. STFW，使用英文查询没有想明白的问题
4. 如果打算系统性地了解和学习 HPC，可参考 https://heptagonhust.github.io/HPC-roadmap/

#include "opencv2/highgui.hpp"
//#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
using namespace cv;
int main(){
const int dimsa = 5;
int size[5] = {10, 10, 10, 10, 10};
SparseMat sparse_mat(dimsa, size, CV_32F);
for(int i = 0; i < 10; i++)
{
            int idx[dimsa];
                for(int k = 0; k < dimsa; k++)
                                idx[k] = rand() % size[k];
                                    sparse_mat.ref<float>(idx) += 1.f;
}
cout << "nnz = " << sparse_mat.nzcount() << endl;
// prints elements of a sparse floating-point matrix
// and the sum of elements.
SparseMatConstIterator_<float>
    it = sparse_mat.begin<float>(),
        it_end = sparse_mat.end<float>();
        double s = 0;
        int  dims = sparse_mat.dims();
        for(; it != it_end; ++it)
        {
                    // print element indices and the element value
                        const SparseMat::Node* n = it.node();
                            printf("(");
                                for(int i = 0; i < dims; i++)
                                                printf("%d%s", n->idx[i], i < dims-1 ? ", " : ")");
                                                    printf(": %g\n", it.value<float>());
                                                        s += *it;
        }
        printf("Element sum is %g\n", s);
return 0;
}

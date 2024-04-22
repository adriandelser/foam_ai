import numpy

def print_matrix(M):
    print (M)

def transform_matrix(M, L):
    for x in L:
        M = M*x
    return M

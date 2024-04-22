#include <abstract.h>
#include <numpy/ndarrayobject.h>
#include <vector>

// initialize python
Py_InitializeEx(1);

// import our test module
PyObject* numpy_test_module = PyImport_ImportModule("numpy_test");

// retrieve 'print_matrix(); from our module
PyObject* print_matrix = PyObject_GetAttrString(numpy_test_module, "print_matrix");

// retrieve 'some_function' from our module
PyObject* transform_matrix = PyObject_GetAttrString(numpy_test_module, "transform_matrix");

// no longer need to reference the module directly
Py_XDECREF(numpy_test_module);

// initialize numpy array library
import_array1(-1); // returns -1 on failure

// create a new numpy array

// array dimensions
npy_intp dim[] = {5, 5};

// array data
std::vector<double> buffer(25, 1.0);

// create a new array using 'buffer'
PyObject* array_2d = PyArray_SimpleNewFromData(2, dim, NPY_DOUBLE, &buffer[0]);

// print the array by calling 'print_matrix'
PyObject* return_value1 = PyObject_CallFunction(print_matrix, "O", array_2d);
// we don't need the return value, release the reference
Py_XDECREF(return_value1);

// create list
PyObject* list = PyList_New(3);
PyList_SetItem(list, 0, PyLong_FromLong(2));
PyList_SetItem(list, 1, PyLong_FromLong(3));
PyList_SetItem(list, 2, PyLong_FromLong(4));

// call the function with the array as its parameter
PyObject* transformed_matrix = PyObject_CallFunction(transform_matrix, "OO", array_2d, list);
// no longer need the list, free the reference
Py_XDECREF(list);

// print the returned array by calling 'print_matrix'
PyObject* return_value2 = PyObject_CallFunction(print_matrix, "O", transformed_matrix);
// no longer need the 'return_value2', release the reference
Py_XDECREF(return_value2);

// no longer need 'transformed_matrix'
Py_XDECREF(transformed_matrix);

// no longer need the array
Py_XDECREF(array_2d);

// no longer need the reference to transform_matrix
Py_XDECREF(transform_matrix);

// no longer need the reference to 'print_matrix'
Py_XDECREF(print_matrix);

// clean up python
Py_Finalize();

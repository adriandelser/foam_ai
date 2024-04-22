/* Initialize Python and add current directory to path*/
Py_Initialize ();
PyRun_SimpleString("import sys");
PyRun_SimpleString("sys.path.append (\".\")");

/* Python API datastructures */
PyObject *array_2d , *rank_val;

/* initialize numpy array library */
import_array1 (-1);

/* Import the "python_module.py" module from the current
directory */
PyObject *pName = PyUnicode_DecodeFSDefault("python_module");
// Python filename
PyObject *pModule = PyImport_Import(pName);

/* Import the function "python_func"*/
PyObject *python_func = PyObject_GetAttrString(pModule , "python_func");

/*The tuple contains the items that need to be passed to the
"python_func" function */
PyObject *python_func_args = PyTuple_New (2);

/*Numpy datastructure to obtain return value from python
method */
PyArrayObject *pValue;

/* Release memory */
Py_DECREF(pName);
Py_DECREF(pModule);

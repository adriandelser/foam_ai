/* Initialize Python and add current directory to path*/
Py_Initialize ();
PyRun_SimpleString("import sys");

//This line tells us what directory python is operating in 
PyRun_SimpleString("import os; cwd = os.getcwd(); print(cwd)");
PyRun_SimpleString("sys.path.append(\".\")");
PyRun_SimpleString("sys.path.append('.')");


//The line below points to the global location of the solver because for some reason sys cannot find the python file using just the line above This needs to be fixed otherwise this solver will be very local. Appending "." to sys makes python search in the directory that the solver is run from (ie the specific case directory). This is a minor, but annoying, complication.
PyRun_SimpleString("sys.path.append('/home/daep/a.del-ser/OpenFOAM/a.del-ser-9/applications/solvers/incompressible/myPisoFoam')");
//PyRun_SimpleString("import numpy");

//Print the current path python has access to when searching for files
PyRun_SimpleString("print(sys.path)");

/* Python API datastructures */
PyObject *array_2d , *rank_val;

/* initialize numpy array library */
Info << "BEFORE erroneous function" << nl << endl;

//PyObject *numpy = PyImport_ImportModule("numpy.core._multiarray_umath");

import_array1(-1);
//Py_Finalize();


/* Import the "python_module.py" module from the current
directory */
PyObject *pName = PyUnicode_DecodeFSDefault("python_module");
// Python filename
PyObject *pModule = PyImport_ImportModule("python_module");
//PyObject *pModule = PyImport_Import(pName);

//This is required to ensure the module is actually found, otherwise c++ will return a segmentation error 
if (pModule == NULL)
	{
	PyErr_Print();
	//if inside this if statement, the below statement will necessarily fail so c++ exits
	assert(pModule != NULL);
	}

//Info << "AFTER erroneous function" << nl << endl;
/* Import the function "python_func"*/
PyObject *python_func = PyObject_GetAttrString(pModule , "python_func");

if (python_func == NULL)
	{
	PyErr_Print();
	//if inside this if statement, the below statement will necessarily fail so c++ exits
	assert(python_func != NULL);
	}
Info << "AFTER erroneous function" << nl << endl;
/* Release memory */
Py_DECREF(pName);
Py_DECREF(pModule);

//Py_Finalize();

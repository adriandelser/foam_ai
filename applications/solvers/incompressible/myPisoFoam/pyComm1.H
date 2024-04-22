/* Initialize Python and add current directory to path*/
Py_Initialize ();

PyRun_SimpleString("import sys");
PyRun_SimpleString("sys.path.append (\".\")");

//The line below points to the global location of the solver because for some reason sys cannot find the python file using just the line above This needs to be fixed otherwise this solver will be very local. Appending "." to sys makes python search in the directory that the solver is run from (ie the specific case directory). This is a minor, but annoying, complication.
PyRun_SimpleString("sys.path.append('/home/daep/a.del-ser/OpenFOAM/a.del-ser-9/applications/solvers/incompressible/myPisoFoam')");

/* Python API datastructures */
PyObject *array_2d /*, *rank_val*/;
PyObject *meshCoords2d;

/* initialize numpy array library */
import_array1 (-1);

/* Import the "python_module.py" module from the current
directory */
PyObject *pName = PyUnicode_DecodeFSDefault("python_module");
//PyObject *mynum = 1;
// Python filename
PyObject *pModule = PyImport_Import(pName);

//This is required to ensure the module is actually found, otherwise c++ will return a segmentation error 
/*if (pModule == NULL)
	{
	PyErr_Print();
	//if inside this if statement, the below statement will necessarily fail so c++ exits
	assert(pModule != NULL);
	}
*/
	
//This is required to ensure the module is actually found, otherwise c++ will return a segmentation error 
if (!pModule)
{
    PyErr_Print();
    FatalErrorInFunction
        << "Errors loading python_module (missing imports?)" << nl
        << exit(FatalError);
}

/* Import the function "python_func"*/
PyObject *python_func = PyObject_GetAttrString(pModule , "python_func");
PyObject *test_func = PyObject_GetAttrString(pModule , "test_func");

if (python_func == NULL)
	{
	PyErr_Print();
	//if inside this if statement, the below statement will necessarily fail so c++ exits
	assert(python_func != NULL);
	}

/*The tuple contains the items that need to be passed to the
"python_func" function */
PyObject *python_func_args = PyTuple_New (2);

/*Numpy datastructure to obtain return value from python
method */
PyArrayObject *pValue(nullptr);
PyObject *testValue;

/*test definition of input_vals aka urec from PythonFOAM repository, found in PythonCreate.H
volScalarField urec_(U.component(vector::X)); */

// Placeholder to grab data before sending to Python
//int num_cells = mesh.cells().size();
//double input_vals[num_cells][1];

/* Release memory */
Py_DECREF(pName);
Py_DECREF(pModule);



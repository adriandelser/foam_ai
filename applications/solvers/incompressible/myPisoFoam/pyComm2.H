// Placeholder to grab data before sending to Python
int num_cells = mesh.cells().size();
/*making a multidimensional array of size num_cells (vertically) by 1 (horizontally), so basically a column vector. */
double input_vals[num_cells][1];
double meshCoords_input_vals[num_cells][3];

//Info << input_vals << endl;
//PyObject *python_func_args = PyTuple_New (2);
/* Extract double precision data from OpenFOAM datastructure
*/
volScalarField ux_ = U.component(vector ::X);

volVectorField meshCoords = mesh.C();
//Info << meshCoords.internalField() << endl;
/* Storing data in double precision array for sending to
Python */
forAll(ux_.internalField (), id)
	{ /* Storing velocities */
	input_vals[id][0] = ux_[id];
	}
forAll(meshCoords.internalField (), id)
	{ /* Storing velocities */
	//Info<<id<<" " <<meshCoords[id]/*<< " " << typeid(meshCoords[id][0]).name()<<" " << ux_[id]<< " "<< typeid(ux_[id]).name()*/<<endl;
	meshCoords_input_vals[id][0] = meshCoords[id][0];
	meshCoords_input_vals[id][1] = meshCoords[id][1];
	meshCoords_input_vals[id][2] = meshCoords[id][2];
	}
//Info << input_vals << endl;
/* The dimensions of the numpy array to be created */

npy_intp dim[] = {num_cells , 1};
/* Pass data to numpy array */
array_2d = PyArray_SimpleNewFromData (2, dim , NPY_DOUBLE , &
	input_vals [0]);
npy_intp dim1[] = {num_cells , 3};
meshCoords2d = PyArray_SimpleNewFromData (2, dim1 , NPY_DOUBLE , &
	meshCoords_input_vals[0]);
//Info << array_2d << endl;
/* Pass the array to the python function */

/* PyTuple_SetItem(PyObject *p, Py_ssize_t pos, PyObject *o): 
 ^ Insert a reference to object o at position pos of the tuple pointed to by p. Return 0 on success. If pos is out of bounds, return -1 and set an IndexError exception.
 */
PyTuple_SetItem(python_func_args , 0, array_2d);
PyTuple_SetItem(python_func_args , 1, meshCoords2d);

/* Call the function - pValue stores the return value of the
function */
//Info << "before python call" << endl;
Info << "test1" << endl;
//PyEval_InitThreads();


//Py_BEGIN_ALLOW_THREADS
Info << "test2" << endl;
pValue = (PyArrayObject *) PyObject_CallObject(python_func , python_func_args);
testValue = (PyObject *) PyObject_CallObject(test_func , NULL);

Info << pValue << endl;
PyObject* objectsRepresentation = PyObject_Repr(testValue);
const char* s = PyUnicode_AsUTF8(objectsRepresentation);
//PyObject result = *testValue;
Info << s << endl;
Info << testValue << endl;
Info << "test3" << endl;
//Py_END_ALLOW_THREADS
Info << "test4" << endl;


if (!pValue)
{
    PyErr_Print();
    FatalErrorInFunction
        << "Errors loading python_module (missing imports?)" << nl
        << exit(FatalError);
}

//Info << "After python call" << endl;
/* Return data from Python into OpenFOAM datastructure -
allocate memory */
volScalarField out_ = U.component(vector ::X);

/* Load return value from Python into OpenFOAM data structure
*/
// I have no idea what truncation is doing, getting rid of it for now
/*for (int mode = 0; mode < truncation; ++mode)
{*/
/* Overwriting data */
//Info << "before function call" << endl;
forAll(out_.internalField (), id)
{
// Here we assume that pValue has a numpy array of dimension 2 with 1 column only
out_[id] = *(( double *) PyArray_GETPTR2(pValue , id , 0));
}
Info << out_ << endl;
//Info<< "Print mesh centre coords" << endl;
Info << mesh.C().internalField()[0] << endl;
//Info << "after function call" << endl;
/*}*/

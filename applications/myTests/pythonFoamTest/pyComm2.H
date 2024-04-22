/* Extract double precision data from OpenFOAM datastructure
*/
volScalarField ux_ = U.component(vector ::X);

/* Storing data in double precision array for sending to
Python */
forAll(ux_.internalField (), id)
	{ /* Storing velocities */
	input_vals[id][0] = ux_[id];
	}

/* The dimensions of the numpy array to be created */
d
npy_intp dim[] = {num_cells , 1};
/* Pass data to numpy array */
array_2d = PyArray_SimpleNewFromData (2, dim , NPY_DOUBLE , &
	input_vals [0]);

/* Pass the array to the python function */
PyTuple_SetItem(python_func_args , 0, array_2d);

/* Pass the rank to the function */
rank_val = PyLong_FromLong(rank);
PyTuple_SetItem(python_func_args , 1, rank_val);

/* Call the function - pValue stores the return value of the
function */
pValue = (PyArrayObject *) PyObject_CallObject(python_func ,
python_func_args);

/* Return data from Python into OpenFOAM datastructure -
allocate memory */
volScalarField out_ = U.component(vector ::X);

/* Load return value from Python into OpenFOAM data structure
*/
// I have no idea what truncation is doing, getting rid of it for now
/*for (int mode = 0; mode < truncation; ++mode)
{
*/
/* Overwriting data */
forAll(out_.internalField (), id)
{
// Here we assume that pValue has a numpy array of dimension 2 with 1 column only
out_[id] = *(( double *) PyArray_GETPTR2(pValue , id , 0))
;
}
/*}*/

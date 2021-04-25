#define PY_SSIZE_T_CLEAN
#include "C:\Users\Yaniv\AppData\Local\Programs\Python\Python39\include\Python.h"
//#include <Python.h>
#include "Qr.h"
#include "SchmidtAux.h"
#include <stdio.h>
#include <stdlib.h>

/* convert an input 2d Python of PyFloats from the c-api array into a regular 2d double array */
static PyObject* convert_float_double(double**data, PyObject *data_python) {
    Py_ssize_t n, d, counter_n,counter_d;
    PyObject *sublist;
    n = PyList_Size(data_python);
    d = PyList_Size(PyList_GetItem(data_python, 0));
    for (counter_n = 0; counter_n < n; counter_n++) {
        sublist = PyList_GetItem(data_python, counter_n);
        //reprint(sublist);
        for (counter_d = 0; counter_d < d; counter_d++) {
            //reprint(element);
            data[counter_n][counter_d] = PyFloat_AsDouble(PyList_GetItem(sublist, counter_d));
        }
    }
    if (PyErr_Occurred()) {
        PyErr_Print();
        return NULL;
    }
    return data_python;
}

/* convert a regular 2d double array into a c-api output Python array of PyFloats */
static PyObject* convert_double_float(double**data, int n) {
    int i, j;
    PyObject *sublist;
    PyObject *my_list;
    PyObject *curr;
    my_list = PyList_New(0);
    if(my_list == NULL) {
        printf("Error: allocation failed\n");
        return NULL;
    }
    for(i = 0; i < n; i++){
        sublist = PyList_New(0);
        if(sublist == NULL) {
            printf("Error: allocation failed\n");
        }

        for(j = 0; j < n; j++){
            curr = PyFloat_FromDouble(data[i][j]);
            PyList_Append(sublist, curr);
        }
        PyList_Append(my_list, sublist);
    }
    if (PyErr_Occurred()) {
        PyErr_Print();
        return NULL;
    }

    return my_list;
}

/* main function of the module - gets a matrix through c-api, returns its orthonormal eigen vectors+values */
static PyObject* calc_eigen_values_vectors(PyObject *self, PyObject *args){
    PyObject *laplacian, *res;
    double ***ret;
    double **data;
    int n;
    if(!PyArg_ParseTuple(args, "Oi", &laplacian, &n) || self == NULL){
        printf("Error: failed parse tuple\n");
        return NULL;
    }

    if (!PyList_Check(laplacian)) {
        printf("Error: not a list as expected\n");
        return NULL;
    }
    data = allocate_matrix(n, n);
    if(!data){
        printf("Error: allocation failed\n");
        return NULL;
    }
    if(!convert_float_double(data, laplacian))
    {
        return NULL;
    }
    ret = qr_iter(data, n);
    if(!ret){
        return NULL;
    }
    res = PyList_New(0);
    if(!res){
        printf("Error: allocation failed\n");
        return NULL;
    }

    PyList_Append(res, convert_double_float(ret[0], n));
    PyList_Append(res, convert_double_float(ret[1], n));
    free_matrix(data, n);
    return PySequence_List(res);
}

static PyMethodDef _eigenMethods[]={
        {"calc_eigen_values_vectors",(PyCFunction) calc_eigen_values_vectors,
                     METH_VARARGS,PyDoc_STR("calculate eigen values and vectors")},
        {NULL, NULL, 0, NULL}
};

static struct PyModuleDef _moduledef={
        PyModuleDef_HEAD_INIT,"section_four",NULL,-1,_eigenMethods
};

PyMODINIT_FUNC
PyInit_section_four(void){
    PyObject *m;
    m = PyModule_Create(&_moduledef);
    if (!m) {
        return NULL;
    }
    return m;
}
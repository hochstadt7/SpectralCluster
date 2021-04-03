#define PY_SSIZE_T_CLEAN
#include "C:\Users\Yaniv\AppData\Local\Programs\Python\Python39\include\Python.h"
//#include <Python.h>
#include "Qr.h"
#include "ShmidtAux.h"
#include "EigengapHeuristic.h"

static void err_message(char *err){
    printf("%s",err);
    exit(1);
}

static void convert_float_double(double**data, PyObject *data_python) {
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
        err_message("Failed to convert float to double\n");
    }
}

static PyObject* convert_double_float(double**data, int n) {
    int i, j;
    PyObject *sublist;
    PyObject *my_list;
    PyObject *curr;
    my_list = PyList_New(0);
    if(my_list == NULL) {
        printf("error");
    }
    for(i = 0; i < n; i++){
        sublist = PyList_New(0);
        for(j = 0; j < n; j++){
            curr = PyFloat_FromDouble(data[i][j]);
            PyList_Append(sublist, curr);
        }
        PyList_Append(my_list, sublist);
    }
    return my_list;
}

static PyObject* calc_eigen_values_vectors(PyObject *self, PyObject *args){
    PyObject *laplacian, *res;
    double ***ret;
    double **data;
    int n;
    if(!PyArg_ParseTuple(args, "Oi", &laplacian, &n) || self == NULL)
        return NULL;
    if (!PyList_Check(laplacian)) {
        err_message("not a list\n");
        return NULL;
    }
    data = my_alloc(n, n);
    convert_float_double(data, laplacian);
    ret = qr_iter(data, n);
    res = PyList_New(0);
    PyList_Append(res, convert_double_float(ret[0], n));
    PyList_Append(res, convert_double_float(ret[1], n));
    free_arrays(data,n);
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
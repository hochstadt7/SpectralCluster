#define PY_SSIZE_T_CLEAN
#include "C:\Users\LENOVO\AppData\Local\Programs\Python\Python38\include\Python.h"
#include "Qr.h"
#include "ShmidtAux.h"

static void err_message(char *err){
    printf("%s",err);
    exit(1);
}

static void convert_float_double(double**data, PyObject *data_python) {

    Py_ssize_t n,d,counter_n,counter_d;
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

static PyObject* calc_eigen_values_vectors(PyObject *self, PyObject *args){//args: 2 dimension array, dimension

    PyObject *data_python;
    double ***ret;
    double **data;
    int n;
    if(!PyArg_ParseTuple(args, "Oi", &data_python, &n) || self == NULL)
        return NULL;
    data=my_alloc(n,n);
    convert_float_double(data,data_python);
    ret=qr_iter(data,n);
    free_arrays(data,n);
    return Py_BuildValue("O", ret);
}

    static PyMethodDef eigenMethods[]={
            {"calc_eigen_values_vectors",(PyCFunction) calc_eigen_values_vectors,
             METH_VARARGS,PyDoc_STR("calculate eigen values and vectors")},
            {NULL, NULL, 0, NULL}
};

static struct PyModuleDef moduledef={
        PyModuleDef_HEAD_INIT,"section4",NULL,-1,eigenMethods
};

PyMODINIT_FUNC
PyInit_section4(void){
    PyObject *m;
    m = PyModule_Create(&moduledef);
    if (!m) {
        return NULL;
    }
    return m;
}
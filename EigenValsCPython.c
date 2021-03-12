#define PY_SSIZE_T_CLEAN
#include "C:\Users\LENOVO\AppData\Local\Programs\Python\Python38\include\Python.h"
#include "Qr.h"
#include "ShmidtAux.h"
#include "EigengapHeuristic.h"

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

static PyObject* calc_eigen_values_vectors(PyObject *self, PyObject *args){

    PyObject *data_python;
    double ***ret;
    double **data;
    int n,i,j;
    if(!PyArg_ParseTuple(args, "Oi", &data_python, &n) || self == NULL)
        return NULL;
    if (!PyList_Check(data_python)) {
        err_message("not a list\n");
        return NULL;
    }
    data=my_alloc(n,n);


    convert_float_double(data,data_python);


    ret=qr_iter(data,n);
    free_arrays(data,n);
    //num_of_vectors=get_eigen_gap(ret[1],n);


    return Py_BuildValue("O",ret);
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
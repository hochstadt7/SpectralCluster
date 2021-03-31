#define PY_SSIZE_T_CLEAN
#include <Python.h>
#define MAX_ITER 200
/*
 * Helper function that will not be exposed (meaning, should be static)
 */

static double **my_alloc(int first_layer, int second_layer){
    int counter;
    double **ret=(double **)malloc(first_layer*sizeof(double *));
    assert(ret!=NULL);
    for(counter=0; counter<first_layer; counter++){
        ret[counter]=(double *)malloc(second_layer*sizeof(double ));
        assert(ret[counter]!=NULL);
    }
    return ret;
}

/* terminal condition- clusters weren't change */
static int my_compare(double **first, double **second, int k, int d){
    int counter_k,counter_d;
    for(counter_k=0; counter_k<k; counter_k++){
        for(counter_d=0; counter_d<d; counter_d++){
            if (first[counter_k][counter_d]!=second[counter_k][counter_d])
                return 0;
        }
    }
    return 1;
}

static void err_message(char *err){
    printf("%s",err);
    exit(1);
}

static void free_clusters(double ****clusters, int *length, int k){
    int counter_k, counter_len;
    for(counter_k=0; counter_k<k; counter_k++){
        for(counter_len=0; counter_len<length[counter_k]; counter_len++){
            free((*clusters)[counter_k][counter_len]);
        }
        free((*clusters)[counter_k]);
    }
    free(*clusters);
}

/* conversion from python type to c type */
static void convert_float_double(double**data, double**centroids, PyObject *data_python, PyObject *centroids_python) {
    Py_ssize_t k, n, d, counter_k, counter_n, counter_d;
    PyObject *sublist;

    /* convert data */
    k = PyList_Size(centroids_python);
    n = PyList_Size(data_python);
    d = PyList_Size(PyList_GetItem(data_python, 0));
    //reprint(data_python);
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

    /*convert centroids*/
    for(counter_k=0; counter_k<k; counter_k++){
        sublist=PyList_GetItem(data_python, (Py_ssize_t)(PyLong_AsLong(PyList_GetItem(centroids_python,counter_k))));
        for(counter_d=0; counter_d<d; counter_d++){
            centroids[counter_k][counter_d] = PyFloat_AsDouble(PyList_GetItem(sublist, counter_d));
        }
    }
    if(PyErr_Occurred())
        err_message("Failed to convert float to double\n");
}

static PyObject* convert_int_float(int *data, int n) {
    int j;
    PyObject *my_list;
    PyObject *curr;
    my_list = PyList_New(0);
    if(my_list == NULL) {
        err_message("allocation failed\n");
    }
    for(j = 0; j < n; j++){
        curr = Py_BuildValue("i",data[j]);
        if(PyErr_Occurred()){
            err_message("Failed to convert int to float\n");
        }
        PyList_Append(my_list, curr);
    }
    return my_list;
}



static int* k_means(PyObject *data_python ,PyObject *centroids_python , int k, int n, int d){
    int converge,t;
    int counter_k, counter_n, counter_d, closest, *length, *labels;
    double closest_dist,dist,**prev_centroids,***clusters,*new_centroid,**data,**centroids;

    data = my_alloc(n,d);
    centroids = my_alloc(k,d);
    convert_float_double(data, centroids, data_python, centroids_python);
    /* similar to hw1*/
    prev_centroids = my_alloc(k,d);
    labels=(int*)malloc(n*sizeof(int));
    assert(prev_centroids!=NULL&&labels!=NULL);
    converge=0;

    for (t=0; t<MAX_ITER; t++){
        for(counter_k=0; counter_k<k; counter_k++){
            for(counter_d=0; counter_d<d; counter_d++){
                prev_centroids[counter_k][counter_d]=centroids[counter_k][counter_d];
            }
        }
        length=calloc(k,sizeof(Py_ssize_t));
        assert(length!=NULL);

        clusters=(double ***)malloc(k*sizeof(double **));
        assert(clusters!=NULL);

        /* adjust each data point to his cluster */
        for (counter_n = 0; counter_n < n; counter_n++) {
            closest=0; closest_dist=9999999;

            for(counter_k=0; counter_k<k; counter_k++){
                dist=0;
                for(counter_d=0; counter_d<d; counter_d++){
                    dist+=(data[counter_n][counter_d]-centroids[counter_k][counter_d])*(data[counter_n][counter_d]-centroids[counter_k][counter_d]);
                }
                if(dist<closest_dist) {
                    closest_dist = dist;
                    closest = counter_k;
                }
            }
            if(length[closest]==0)
                clusters[closest]=(double**) malloc(sizeof(double *));
            else
                clusters[closest]=(double**) realloc(clusters[closest],(length[closest]+1)*sizeof(double *));
            assert(clusters[closest]!=NULL);

            clusters[closest][length[closest]] = (double *) malloc(d * sizeof(double));
            assert(clusters[closest][length[closest]]!=NULL);

            for(counter_d=0; counter_d<d; counter_d++) {
                clusters[closest][length[closest]][counter_d]=data[counter_n][counter_d];
            }
            labels[counter_n]=closest; // keep the the cluster index of each point
            length[closest]++;
        }

        /* compute new centroid */
        for(counter_k=0; counter_k<k; counter_k++){
            new_centroid=(double *)calloc(d,sizeof(double));
            assert(new_centroid!=NULL);
            for(counter_n=0; counter_n<length[counter_k]; counter_n++){

                for(counter_d=0; counter_d<d; counter_d++){

                    new_centroid[counter_d]+=(clusters[counter_k][counter_n][counter_d]);
                }
            }
            for(counter_d=0; counter_d<d; counter_d++){
                centroids[counter_k][counter_d]=new_centroid[counter_d]/length[counter_k];
            }
            free(new_centroid);
        }
        free_clusters(&clusters,length,k);
        if(my_compare(centroids,prev_centroids,k,d)) {
            converge=1;
            break;
        }
        free(length);
    }

    if(converge&&length!=NULL){
        free(length);
    }
    for(counter_n=0; counter_n<n; counter_n++){
        free(data[counter_n]);
    }
    free(data);
    for(counter_k=0; counter_k<k; counter_k++){
        free(prev_centroids[counter_k]);
        free(centroids[counter_k]);
    }
    free(prev_centroids);
    free(centroids);

    return labels;
}

static PyObject* k_means_api(PyObject *self, PyObject *args){
    PyObject *data;
    PyObject *centroids;
    PyObject *res;
    int* ret;
    int k, n, d;

    if(!PyArg_ParseTuple(args, "OOiii", &data, &centroids, &k, &n, &d) || self == NULL)
        return NULL;
    ret=k_means(data, centroids, k, n, d);
    res = PyList_New(0);
    PyList_Append(res, convert_int_float(ret,n));
    return PySequence_List(res);
}

/*
 * This array tells Python what methods this module has.
 * We will use it in the next structure
 */
static PyMethodDef capiMethods[] = {
        {"k_means_api",                   /* the Python method name that will be used */
                (PyCFunction) k_means_api, /* the C-function that implements the Python function and returns static PyObject*  */
                     METH_VARARGS,           /* flags indicating parameters
accepted for this function */
                        PyDoc_STR("random k-means algorithm")}, /*  The docstring for the function */
        {NULL, NULL, 0, NULL}     /* The last entry must be all NULL as shown to act as a
                                 sentinel. Python looks for this entry to know that all
                                 of the functions for the module have been defined. */
};


/* This initiates the module using the above definitions. */
static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "my_kmeans",
        NULL,
        -1,
        capiMethods
};


/*
 * The PyModuleDef structure, in turn, must be passed to the interpreter in the module’s initialization function.
 * The initialization function must be named PyInit_name(), where name is the name of the module and should match
 * what we wrote in struct PyModuleDef.
 * This should be the only non-static item defined in the module file
 */
PyMODINIT_FUNC
PyInit_my_kmeans(void)
{
    PyObject *m;
    m = PyModule_Create(&moduledef);
    if (!m) {
        return NULL;
    }
    return m;
}//
// Created by LENOVO on 31/03/2021.
//


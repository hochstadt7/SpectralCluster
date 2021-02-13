from invoke import task, call

@task(aliases=['del'])
def clean(c):
    c.run("rm my_kmeans.cpython-38-x86_64-linux-gnu.so")

@task
def run(c):
    c.run("python3.8.5 setup.py build_ext --inplace")
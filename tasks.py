from invoke import task, call

@task(aliases=['del'])
def clean(c):
    c.run("rm section_four.cpython-38-x86_64-linux-gnu.so")

@task
def run(c,k,n,Random=True):
    c.run("python3.8.5 setup.py build_ext --inplace")
    c.run("python3.8.5 SetupKmeans.py build_ext --inplace")
    c.run(f"python3.8.5 main.py {k} {n} {Random}")
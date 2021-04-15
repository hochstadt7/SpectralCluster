from invoke import task, call

@task
def run(c, k=0, n=0, Random=True):
    temp=0
    c.run("python3.8.5 setupmatrix.py build_ext --inplace")
    c.run("python3.8.5 SetupKmeans.py build_ext --inplace")

    if Random:
        temp=1
    c.run(f"python3.8.5 main.py {k} {n} {temp}")
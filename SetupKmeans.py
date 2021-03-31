from setuptools import setup, find_packages, Extension

setup(
    name='my_kmeans',
    version='0.1.0',
    install_requires=['invoke'],
    packages=find_packages(),  # find_packages(where='.', exclude=())
    #    Return a list of all Python packages found within directory 'where'
    license='GPL-2',
    # See https://pypi.python.org/pypi?%3Aaction=list_classifiers
    classifiers=[
        # How mature is this project? Common values are
        #   3 - Alpha
        #   4 - Beta
        #   5 - Production/Stable
        'Development Status :: 3 - Alpha',
        # Pick your license as you wish (should match "license" above)
        'License :: OSI Approved :: GNU General Public License v2 (GPLv2)',
        'Natural Language :: English',
        'Programming Language :: Python :: 3 :: Only',
        # We need to tell the world this is a CPython extension
        'Programming Language :: Python :: Implementation :: CPython',
    ],
    ext_modules=[
        Extension(
            # the qualified name of the extension module to build
            'my_kmeans',
            # the files to compile into our module relative to ``setup.py``
            # see how we handle the include - it is important that the geo.h
            # is in the root, otherwise we would have to use: include_dirs=['...']
            ['kmeans.c'],
            # for example, geo.h is in a folder named myheaders:
            # include_dirs=['myheaders']
        ),
    ]
)

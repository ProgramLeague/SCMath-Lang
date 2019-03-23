TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    scmath/ast.cpp \
    main.cpp \
    scmath/nodetype.cpp \
    scmath/funinterface.cpp \
    scmath/scope.cpp \
    scmath/output.cpp \
    scmath/copynode.cpp \
    scmath.cpp

HEADERS += \
    scmath/ast.h \
    scmath/nodetype.h \
    scmath/scope.h \
    scmath/funinterface.h \
    scmath/output.h \
    scmath/excep.h \
    scmath/marco.h \
    scmath.h \
    scmath/matrix.hpp \
    numcalu.hpp \
    help.h \
    lab.h

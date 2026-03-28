# FormulaDump.pro
TARGET = FormulaDump
TEMPLATE = app

QT += core gui
CONFIG += console
CONFIG -= app_bundle

# QXlsx source include
include(../QXlsx/QXlsx.pri)

SOURCES += \
    main.cpp \
    formula_dump_fullcells.cpp \
    formula_single_cell_evaluator.cpp \
    mini_formula_evaluator.cpp

HEADERS += \
    dump_options.hpp \
    formula_dump_fullcells.hpp \
    formula_single_cell_evaluator.hpp \
    mini_formula_evaluator.hpp

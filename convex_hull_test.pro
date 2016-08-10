TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += '/usr/local/Cellar/boost/1.59.0/include/'

SOURCES += src/main.cpp

HEADERS += \
    src/primitives.hpp \
    src/convex_hull_algorithms.hpp \
    src/art_gallery.hpp \
    src/intersection_algorithms.hpp

QT      +=  webenginewidgets

include($$QTWEBENGINE_ROOT/common.pri)

HEADERS =   mainwindow.h
SOURCES =   main.cpp \
            mainwindow.cpp
RESOURCES = jquery.qrc

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/webkitwidgets/fancybrowser
#INSTALLS += target

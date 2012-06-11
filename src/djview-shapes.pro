# #####################################################################
# Automatically generated by qmake (2.01a) czw. sie 27 19:06:01 2009
# #####################################################################
TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .
QT += network

RESOURCES = resources.qrc

TRANSLATIONS = i18n/pl.ts

win32:LIBS = /home/michal/programming/build/djvulibre-windows/libdjvulibre.dll.a
unix:LIBS = -ldjvulibre

!win32 {
HGID = $$system(hg id -n)
DEFINES += HGID=\\\"$$HGID\\\"

versiontarget.target = version.o
versiontarget.depends = FORCE
PRE_TARGETDEPS += version.o
QMAKE_EXTRA_TARGETS += versiontarget
}

# Input
HEADERS += recentfiles.h \
	 mainwindow.h \
	 qdjvuwidget.h \
	 qdjvuhttp.h \
	 qdjvu.h \
	 messagedialog.h \
	 version.h \ 
    shapetablewidgetitem.h \
    shapenode.h
SOURCES += recentfiles.cpp \
	 mainwindow.cpp \
	 qdjvuwidget.cpp \
	 qdjvuhttp.cpp \
	 qdjvu.cpp \
	 messagedialog.cpp \
	 version.cpp \ 
    main.cpp \
    shapetablewidgetitem.cpp \
    shapenode.cpp
FORMS = mainwindow.ui 

RESOURCES += \
	 resources.qrc

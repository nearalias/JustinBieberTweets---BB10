# Auto-generated by IDE. All changes by user will be lost!
# Created at 25/01/13 12:31 AM

BASEDIR = $$_PRO_FILE_PWD_

INCLUDEPATH +=  \
    $$BASEDIR/src

SOURCES +=  \
    $$BASEDIR/src/JustinBieberTweets.cpp \
    $$BASEDIR/src/MyItemClass.cpp \
    $$BASEDIR/src/MyListItemProvider.cpp \
    $$BASEDIR/src/main.cpp

HEADERS +=  \
    $$BASEDIR/src/JustinBieberTweets.hpp \
    $$BASEDIR/src/MyItemClass.hpp \
    $$BASEDIR/src/MyListItemProvider.hpp

CONFIG += precompile_header
PRECOMPILED_HEADER = $$BASEDIR/precompiled.h

lupdate_inclusion {
    SOURCES += \
        $$BASEDIR/../assets/*.qml
}

TRANSLATIONS = \
    $${TARGET}.ts


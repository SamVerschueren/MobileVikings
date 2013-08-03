APP_NAME = bbVikings

CONFIG += qt warn_on cascades10
QT += network
LIBS += -lbbdata -lbbpim -lbbsystem

include(config.pri)

lupdate_inclusion {
    SOURCES += \
        $$BASEDIR/../src/*.cpp $$BASEDIR/../assets/*.qml $$BASEDIR/../src/Services/*.qml
}

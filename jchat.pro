QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    common/j_ling.cpp \
    common/j_module_t.cpp \
    common/j_msg_property.cpp \
    common/j_msgs_general_stats.cpp \
    common/j_msgs_property_stats.cpp \
    common/j_settings.cpp \
    gui/display/j_abstract_display.cpp \
    gui/display/j_action_toolbar.cpp \
    gui/display/j_input_display.cpp \
    gui/display/j_output_display.cpp \
    gui/display/output/j_profile_dialog.cpp \
    gui/jchat_gui.cpp \
    gui/jchat_log.cpp \
    load/j_profile_loader.cpp \
    main.cpp \
    jchat.cpp \
    proc/handlers/j_general_word_handler.cpp \
    proc/handlers/j_ling_abstract_handler.cpp \
    proc/j_comparator.cpp \
    proc/j_linguist.cpp \
    proc/j_processor.cpp

HEADERS += \
    common/j_abstract_stats.h \
    common/j_ling.h \
    common/j_module_t.h \
    common/j_msg_property.h \
    common/j_msgs_general_stats.h \
    common/j_msgs_property_stats.h \
    common/j_settings.h \
    gui/display/j_abstract_display.h \
    gui/display/j_action_toolbar.h \
    gui/display/j_input_display.h \
    gui/display/j_output_display.h \
    gui/display/output/j_profile_dialog.h \
    gui/jchat_gui.h \
    gui/jchat_log.h \
    jchat.h \
    load/j_profile_loader.h \
    proc/handlers/j_general_word_handler.h \
    proc/handlers/j_ling_abstract_handler.h \
    proc/j_comparator.h \
    proc/j_linguist.h \
    proc/j_processor.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    jchat.qrc

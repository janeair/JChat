QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    common/j_module_t.cpp \
    common/ling/j_ling.cpp \
    common/profile/j_profile.cpp \
    common/property/j_msg_property.cpp \
    common/stats/j_msgs_general_stats.cpp \
    common/stats/j_msgs_property_stats.cpp \
    gui/common/j_action_toolbar.cpp \
    gui/display/j_abstract_display.cpp \
    gui/display/j_input_display.cpp \
    gui/display/j_output_display.cpp \
    gui/display/settings/j_settings.cpp \
    gui/jchat_gui.cpp \
    gui/log/j_log_action.cpp \
    gui/log/jchat_log.cpp \
    gui/subwindow/j_profile_editor.cpp \
    gui/subwindow/text_file_io_dialog.cpp \
    import/color_dialog_button.cpp \
    load/j_profile_loader.cpp \
    main.cpp \
    jchat.cpp \
    proc/handlers/j_general_word_handler.cpp \
    proc/handlers/j_ling_abstract_handler.cpp \
    proc/j_comparator.cpp \
    proc/j_linguist.cpp \
    proc/j_processor.cpp

HEADERS += \
    common/j_module_t.h \
    common/ling/j_ling.h \
    common/profile/j_profile.h \
    common/property/j_msg_property.h \
    common/stats/j_abstract_stats.h \
    common/stats/j_msgs_general_stats.h \
    common/stats/j_msgs_property_stats.h \
    gui/common/j_action_toolbar.h \
    gui/display/j_abstract_display.h \
    gui/display/j_input_display.h \
    gui/display/j_output_display.h \
    gui/display/settings/j_settings.h \
    gui/jchat_gui.h \
    gui/log/j_log_action.h \
    gui/log/jchat_log.h \
    gui/subwindow/j_profile_editor.h \
    gui/subwindow/text_file_io_dialog.h \
    import/action_toolbar.h \
    import/color_dialog_button.h \
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

#include "jchat.h"

jchat::jchat() : QObject()
{
    /// main modules
    loader = std::make_unique<j_profile_loader>();
    linguist = std::make_unique<j_linguist>();
    processor = std::make_unique<j_processor>();
    comparator = std::make_unique<j_comparator>();
    gui = std::make_unique<jchat_gui>();

    /// connect profile base
    connect(loader.get(), &j_profile_loader::send_base, gui.get()->get_editor(), &j_profile_editor::set_profile_base);
    connect(loader.get(), &j_profile_loader::send_base, gui.get()->get_analyzer_widget(), &j_compare_analyzer_widget::set_profile_base);
    connect(loader.get(), &j_profile_loader::send_base, comparator.get(), &j_comparator::set_profile_base);

    /// connect proc stages
    connect(gui.get()->get_input(), &j_input_display::to_analyse, linguist.get(), &j_linguist::process_msg);
    connect(linguist.get(), &j_linguist::lings_to_gui, gui.get()->get_input(), &j_input_display::rewrite_input_message);
    connect(linguist.get(), &j_linguist::stats_to_gui, gui.get()->get_output(), &j_output_display::display_general_stats);
    connect(linguist.get(), &j_linguist::to_process, processor.get(), &j_processor::put_to_buffer);
    connect(processor.get(), &j_processor::to_compare, comparator.get(), &j_comparator::compare_stats_with_base);

    connect(processor.get(), &j_processor::stats_to_gui, gui.get()->get_output(), &j_output_display::display_property_stats);
    connect(comparator.get(), &j_comparator::results_to_gui, gui.get()->get_output(), &j_output_display::display_compare_results);

    /// connect profile editor
    connect(processor.get(), &j_processor::stats_to_gui, gui.get()->get_editor(), &j_profile_editor::set_current_stats);

    /// configure proc with gui settings
    connect(gui.get(), &jchat_gui::to_configure_ling, linguist.get(), &j_linguist::configure_settings);
    connect(gui.get(), &jchat_gui::to_configure_proc, processor.get(), &j_processor::configure_settings);
    connect(gui.get(), &jchat_gui::to_configure_comp, comparator.get(), &j_comparator::configure_settings);

    gui->get_analyzer_widget()->set_comparator(comparator.get());

    loader->load_profiles();

    gui->show();
}

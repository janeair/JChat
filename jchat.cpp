#include "jchat.h"

jchat::jchat() : QObject()
{
    gui = std::make_unique<jchat_gui>();
    linguist = std::make_unique<j_linguist>();
    processor = std::make_unique<j_processor>();
    comparator = std::make_unique<j_comparator>();
    loader = std::make_unique<j_profile_loader>();

    comparator->set_loader(loader.get());

    /// connect proc stages
    connect(gui.get()->get_input(), &j_input_display::to_analyse, linguist.get(), &j_linguist::process_msg);
    connect(linguist.get(), &j_linguist::lings_to_gui, gui.get()->get_output(), &j_output_display::display_lings);
    connect(linguist.get(), &j_linguist::stats_to_gui, gui.get()->get_output(), &j_output_display::display_general_stats);
    connect(linguist.get(), &j_linguist::to_process, processor.get(), &j_processor::put_to_buffer);
    connect(processor.get(), &j_processor::to_compare, comparator.get(), &j_comparator::compare_stats_with_base);

    connect(processor.get(), &j_processor::stats_to_gui, gui.get()->get_output(), &j_output_display::save_property_stats);
    connect(comparator.get(), &j_comparator::results_to_gui, gui.get()->get_output(), &j_output_display::display_compare_results);

    /// connect profile loader with gui
    connect(loader.get(), &j_profile_loader::profiles_to_gui, gui.get()->get_output(), &j_output_display::on_change_profiles);
    connect(gui.get()->get_output(), &j_output_display::new_profile, loader.get(), &j_profile_loader::add);

    connect(loader.get(), &j_profile_loader::profile_data_to_gui, gui.get()->get_output(), &j_output_display::display_profile);
    connect(gui.get()->get_output(), &j_output_display::get_profile_data, loader.get(), &j_profile_loader::get_profile_from_gui);

    /// configure proc with gui settings
    connect(gui.get(), &jchat_gui::to_configure_ling, linguist.get(), &j_linguist::configure_settings);
    connect(gui.get(), &jchat_gui::to_configure_proc, processor.get(), &j_processor::configure_settings);
    connect(gui.get(), &jchat_gui::to_configure_comp, comparator.get(), &j_comparator::configure_settings);

    gui->show();
}

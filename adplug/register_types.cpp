#include "register_types.h"

#include "audio_stream_adlib.h"
#include "audio_stream_playback_adlib.h"

#ifdef TOOLS_ENABLED
#include "resource_importer_adplug.h"
#endif

void initialize_adplug_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	GDREGISTER_CLASS(AudioStreamAdlib);
	GDREGISTER_CLASS(AudioStreamPlaybackAdlib);

#ifdef TOOLS_ENABLED
	if (Engine::get_singleton()->is_editor_hint()) {
		Ref<ResourceImporterAdplug> adplug_importer;
		adplug_importer.instantiate();
		ResourceFormatImporter::get_singleton()->add_importer(adplug_importer);
	}

	ClassDB::APIType prev_api = ClassDB::get_current_api();
	ClassDB::set_current_api(ClassDB::API_EDITOR);

	// Required to document import options in the class reference.
	GDREGISTER_CLASS(ResourceImporterAdplug);

	ClassDB::set_current_api(prev_api);
#endif

}

void uninitialize_adplug_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

#include "audio_stream_adlib.h"
#include "audio_stream_playback_adlib.h"
#include "core/string/print_string.h"

AudioStreamAdlib::AudioStreamAdlib() : mix_rate(44100), hz(639) {
}

Ref<AudioStreamPlayback> AudioStreamAdlib::instantiate_playback() {
	Ref<AudioStreamPlaybackAdlib> playback;
	playback.instantiate();
	playback->base = Ref<AudioStreamAdlib>(this);
	return playback;
}

String AudioStreamAdlib::get_stream_name() const {
	return "";
}

void AudioStreamAdlib::set_loop(bool p_enable) {
	loop = p_enable;
}

bool AudioStreamAdlib::has_loop() const {
	return loop;
}

void AudioStreamAdlib::set_chipset(ChipType p_type) {
	chipset = p_type;
}

AudioStreamAdlib::ChipType AudioStreamAdlib::get_chipset() {
	return chipset;
}

void AudioStreamAdlib::set_emulator(Emulator p_emulator) {
	emulator = p_emulator;
}

AudioStreamAdlib::Emulator AudioStreamAdlib::get_emulator() {
	return emulator;
}

void AudioStreamAdlib::set_file_path(const String p_path) {
	file_path = p_path;
}

String AudioStreamAdlib::get_file_path() {
	return file_path;
}

void AudioStreamAdlib::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_stream_name"), &AudioStreamAdlib::get_stream_name);
	
	ClassDB::bind_method(D_METHOD("set_loop", "enable"), &AudioStreamAdlib::set_loop);
	ClassDB::bind_method(D_METHOD("has_loop"), &AudioStreamAdlib::has_loop);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "loop"), "set_loop", "has_loop");

	ClassDB::bind_method(D_METHOD("set_chipset", "chip_type"), &AudioStreamAdlib::set_chipset);
	ClassDB::bind_method(D_METHOD("get_chipset"), &AudioStreamAdlib::get_chipset);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "chipset", PROPERTY_HINT_ENUM, "OPL2,OPL3,DUAL OPL2,AUTO"), "set_chipset", "get_chipset");

	ClassDB::bind_method(D_METHOD("set_emulator", "emulator"), &AudioStreamAdlib::set_emulator);
	ClassDB::bind_method(D_METHOD("get_emulator"), &AudioStreamAdlib::get_emulator);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "emulator", PROPERTY_HINT_ENUM, "NUKED,ADPLUG"), "set_emulator", "get_emulator");

	ClassDB::bind_method(D_METHOD("set_file_path", "path"), &AudioStreamAdlib::set_file_path);
	ClassDB::bind_method(D_METHOD("get_file_path"), &AudioStreamAdlib::get_file_path);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "file_path"), "set_file_path", "get_file_path");
	BIND_ENUM_CONSTANT(TYPE_OPL2);
	BIND_ENUM_CONSTANT(TYPE_DUAL_OPL2);
	BIND_ENUM_CONSTANT(TYPE_OPL3);
	BIND_ENUM_CONSTANT(TYPE_AUTO);

	BIND_ENUM_CONSTANT(NUKED);
	BIND_ENUM_CONSTANT(ADPLUG);
}
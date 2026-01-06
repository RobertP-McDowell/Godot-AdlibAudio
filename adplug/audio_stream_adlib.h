#ifndef AUDIOSTREAM_ADLIB_H
#define AUDIOSTREAM_ADLIB_H

#include "mutuals.h"
// #include "core/reference.h"
// #include "core/resource.h"
#include "servers/audio/audio_stream.h"

// For extensions
#include "core/io/resource.h"
#include "core/io/resource_loader.h"

class AudioStreamAdlib : public AudioStream {
	GDCLASS(AudioStreamAdlib, AudioStream);
	OBJ_SAVE_TYPE(AudioStream); // Saves derived classes with common type so they can be interchanged.
	RES_BASE_EXTENSION("adplugstr");
	friend class AudioStreamPlaybackAdlib;
public:
	enum ChipType {
		TYPE_OPL2 = 0,
		TYPE_OPL3 = 1,
		TYPE_DUAL_OPL2 = 2,
		TYPE_AUTO = 3 // Even though it's defualt make it 4, so the other enum's correspond to Copl's ChipType.
	};
	enum Emulator {
		NUKED = 0, // nemuopl.h; The recommended emulator.
		ADPLUG = 1 // emuopl.h; The adplug standard emulator.
	};
	void set_loop(bool p_enable);
	virtual bool has_loop() const;
	void set_chipset(ChipType p_type);
	ChipType get_chipset();
	void set_emulator(Emulator p_emulator);
	Emulator get_emulator();
	void set_file_path(const String p_path);
	String get_file_path();
	
	virtual Ref<AudioStreamPlayback> instantiate_playback();
	virtual String get_stream_name() const;

	virtual double get_length() const { return 0; } // if supported, otherwise return 0
	virtual bool can_be_sampled() const override { return false; }
	AudioStreamAdlib();
private:
	int mix_rate;
	int hz;
	bool loop = false;
	ChipType chipset = TYPE_AUTO;
	Emulator emulator = NUKED;
	String file_path = "DEFUALT";
protected:
	static void _bind_methods();
};
VARIANT_ENUM_CAST(AudioStreamAdlib::ChipType);
VARIANT_ENUM_CAST(AudioStreamAdlib::Emulator);

#endif
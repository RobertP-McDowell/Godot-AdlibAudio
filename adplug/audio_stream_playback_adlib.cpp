#include "audio_stream_playback_adlib.h"
#include "audio_stream_adlib.h"

#include "core/math/math_funcs.h"
#include "core/string/print_string.h"

#include "core/config/project_settings.h"
#include "servers/audio_server.h"

// Adplug definitions:
#include <adplug/adplug.h>
#include <adplug/emuopl.h>
#include <adplug/nemuopl.h>

using namespace std;

AudioStreamPlaybackAdlib::AudioStreamPlaybackAdlib() {
}

AudioStreamPlaybackAdlib::~AudioStreamPlaybackAdlib() {
	cout << "Playback Adlib deinit, active = " << "\n";
	if (active) {
		stop();
	}
}

void AudioStreamPlaybackAdlib::stop() {
	if (adplug_buffer) {
		memdelete_arr(adplug_buffer);
	}
	adplug_buffer = nullptr;
	if (opl) {
		opl = nullptr;
	}
	if (playback) {
		playback = nullptr;
	}
	towrite = 0;
	active = false;
}

void AudioStreamPlaybackAdlib::start(double p_from_pos) {
	active = true;
	Copl::ChipType copl_chip_type = static_cast<Copl::ChipType>(base->get_chipset());
	if (adplug_buffer) {
		print_error("Error, already Allocated buffer!");
	}
	if (opl) {
		print_error("Error, already Allocated opl!");
	}
	if (playback) {
		print_error("Error, already Allocated playback!");
	}
	if (base->emulator == AudioStreamAdlib::NUKED) { // Opl3, Recommended.
		opl = make_unique<CNemuopl>(RATE);
		stereo = true;
		adplug_buffer = memnew_arr(short, STEREO_BUFSIZE);
	}
	else { // elif (base->emulator == AudioStreamAdlib::ADPLUG) { // Opl2, Dual Opl2, Opl3.
		unique_ptr<CEmuopl> new_opl = make_unique<CEmuopl>(RATE, BIT16, false);
		new_opl->settype(copl_chip_type);
		opl = move(new_opl);
		if (copl_chip_type == Copl::TYPE_DUAL_OPL2 || copl_chip_type == Copl::TYPE_OPL3) {
			stereo = true;
			adplug_buffer = memnew_arr(short, STEREO_BUFSIZE);
		}
		else {
			stereo = false;
			adplug_buffer = memnew_arr(short, BUFSIZE);
		}
	}
	if (!adplug_buffer) {
		cout << "Buffer failed to be allocated!" << adplug_buffer << "\n";
	}
	if (!opl) {
		cout << "Opl failed to be allocated!" << "\n";
	}
	
	String GlobalFilePath = ProjectSettings::get_singleton()->globalize_path(base->file_path);
	const char *char_path = GlobalFilePath.utf8();
	playback.reset(CAdPlug::factory(char_path, opl.get()));
	if (!playback) {
		print_error("Can't load Adplug file! " + base->file_path);
		stop();
		return;
	}
	playback->seek((unsigned long)(p_from_pos*1000));
	towrite = RATE / playback->getrefresh();
}

void AudioStreamPlaybackAdlib::seek(double p_time) {
	if (p_time < 0) {
		p_time = 0;
	}
	if (playback) {
		playback->seek((unsigned long)(p_time*1000));
		if (!playback->update()) {
			stop();
			return;
		}
		towrite = RATE / playback->getrefresh();
	}
}

int AudioStreamPlaybackAdlib::_process(AudioFrame *p_buffer, unsigned int p_frames, unsigned int p_buffer_offset) {
	unsigned int write = (towrite > p_frames ? p_frames : towrite);
	if (stereo == true) {
		opl->update(adplug_buffer, write);
		for (unsigned int buf_index = 0; buf_index < write; buf_index++) {
			float sample1 = float(adplug_buffer[(buf_index*2)]) / INT16_TO_FLOAT;
			float sample2 = float(adplug_buffer[(buf_index*2)+1]) / INT16_TO_FLOAT;
			p_buffer[p_buffer_offset + buf_index] = AudioFrame(sample1, sample2);
		}
	}
	else {
		opl->update(adplug_buffer, write);
		for (unsigned int buf_index = 0; buf_index < write; buf_index++) {
			float sample = float(adplug_buffer[buf_index]) / INT16_TO_FLOAT;
			p_buffer[p_buffer_offset + buf_index] = AudioFrame(sample, sample);
		}
	}
	towrite -= write;
	if (towrite <= 0) { // When true we had to make the last buffer smaller, therefore we need to update.
		if (!playback->update()) {
			if (base->loop) {
				seek(0.0);
			}
			else {
				stop();
			}
			return write;
		}
		towrite = RATE / playback->getrefresh(); // Important to refresh towrite after update.
		if (write < p_frames) { // If true, there are more p_frames left to process.
			write += _process(p_buffer, p_frames - write, p_buffer_offset + write); // Finish the buffer since towrite ran out.
		}
	}
	return write;
}

int AudioStreamPlaybackAdlib::mix(AudioFrame *p_buffer, float p_rate_scale, int p_frames) {
	if (!active) {
		return 0;
	}
	// On first import, p_frames is a much bigger number than the usual 512.
	// We must make sure to acommodate a large number of p_frames.
	unsigned long total_frames_processed = 0, frames_left = p_frames;
	int used_bufsize = (stereo == true ? BUFSIZE : BUFSIZE);
	int write = min((int)frames_left, used_bufsize);
	while (active && frames_left != 0) {
		long new_frames_processed = _process(p_buffer, write, total_frames_processed);
		total_frames_processed += new_frames_processed;
		
		if (new_frames_processed == 0) {
			return total_frames_processed;
		}
		frames_left = p_frames - total_frames_processed;
		
		write = min((int)frames_left, used_bufsize);
	}
	return total_frames_processed;
}

int AudioStreamPlaybackAdlib::get_loop_count() const {
	return 0;
}
double AudioStreamPlaybackAdlib::get_playback_position() const {
	return 0.0;
}
// double AudioStreamPlaybackAdlib::get_length() const {
	// return 0.0;
// }
bool AudioStreamPlaybackAdlib::is_playing() const {
	return active;
}

void AudioStreamPlaybackAdlib::_bind_methods() {
	return;
}



#include "BeepPlayer.h"

#ifdef WIN32   
#include <windows.h>
#endif

#ifdef __linux__
#include <unistd.h>
#endif

#include <sstream>

#include "SDL2/SDL.h"

namespace BeepPlayer {

	NoteValue::NoteValue(const float& value) : value{value} {}

	inline
	float NoteValue::getValue() const {
		return this->value;
	}


	float NoteValue::getDotValue() const {
		return this->getValue() + (this->getValue() / 2);
	}

	inline
	int NoteValue::getDurationBy(int tact) {
		return tact * this->getValue();
	}

	const NoteValue NoteValue::V1 = {1.0f};
	const NoteValue NoteValue::V2 = {1/2.f};
	const NoteValue NoteValue::V4 = {1/4.f};
	const NoteValue NoteValue::V8 = {1/8.f};
	const NoteValue NoteValue::V16 = {1/16.f};
	const NoteValue NoteValue::V32 = {1/32.f};

	void playSong(const std::string& song) {
		std::stringstream songStream(song);

	}

	void sleep(int sleepTimeInMs) {
#ifdef WIN32
	Sleep(sleepTimeInMs);
	return;
#endif 	
		usleep(sleepTimeInMs * 1000);
	}

	const int AMPLITUDE = 28000;
	const int FREQUENCY = 44100;

	struct Beep {
		int frequency; 
		int samplesLeft;
	};

	void audio_callback(void *_beep, Uint8 *_stream, int _length)
	{
		Sint16 *stream = (Sint16*) _stream;
		Beep *beep = (Beep*) _beep;
		int length = _length / 2;

		int i = 0;
		double v = 0;
		while (i < length) {
			int samplesToDo = std::min(i + beep->samplesLeft, length);
			beep->samplesLeft -= samplesToDo - i;

			while (i < samplesToDo) {
				stream[i] = AMPLITUDE * std::sin(v * 2 * M_PI / FREQUENCY);
				i++;
				v += beep->frequency;
			}
		}
	}	

	void beep(int frequency, int duration) {
#ifdef WIN32
	Beep(frequency,duration);
	return;
#endif
		Beep beep;
		beep.frequency = frequency;
		beep.samplesLeft = duration * FREQUENCY / 1000;

		SDL_AudioSpec desiredSpec;
		desiredSpec.freq = FREQUENCY;
		desiredSpec.format = AUDIO_S16SYS;
		desiredSpec.channels = 1;
		desiredSpec.samples = 2048;
		desiredSpec.callback = audio_callback;
		desiredSpec.userdata = &beep;


		SDL_AudioSpec obtainedSpec;

		// you might want to look for errors here
		SDL_OpenAudio(&desiredSpec, &obtainedSpec);

		// start play audio
		SDL_PauseAudio(0);

	}
	
	void playSong(const BeepPlayer::Song& song) {
		for (auto note : song.notes) {
			if (note.frequence == BeepPlayer::NoteFrequencie::PAUSE) {
				sleep(note.noteValue.getDurationBy(song.tact));
			} else {
				beep(static_cast<int> (note.frequence), note.noteValue.getDurationBy(song.tact));
			}
		}
	}
};

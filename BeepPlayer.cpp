
#include "BeepPlayer.h"

#if defined _WIN32 || defined _WIN64 || defined __MINGW32__
#include <windows.h>
#endif

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <queue>

#include "SDL2/SDL.h"

using namespace std;

namespace BeepPlayer
{

	NoteValue::NoteValue(const float &value) : value{value} {}

	inline float NoteValue::getValue() const
	{
		return this->value;
	}

	float NoteValue::getDotValue() const
	{
		return this->getValue() + (this->getValue() / 2);
	}

	inline int NoteValue::getDurationBy(int tact)
	{
		return tact * this->getValue();
	}

	const NoteValue NoteValue::V1 = {1.0f};
	const NoteValue NoteValue::V2 = {1 / 2.f};
	const NoteValue NoteValue::V4 = {1 / 4.f};
	const NoteValue NoteValue::V8 = {1 / 8.f};
	const NoteValue NoteValue::V16 = {1 / 16.f};
	const NoteValue NoteValue::V32 = {1 / 32.f};

	struct BeepTone
	{
		int frequency;
		int samplesLeft;
	};

	void playSong(const string &song)
	{
		stringstream songStream(song);
	}

	SDL_AudioDeviceID audioDevice = 0;
	const int AMPLITUDE = 28000;
	const int FREQUENCY = 44000;
	double v;
	bool initialized = false;
	bool initializing = false;
	queue<BeepTone> beepTones;
	BeepPlayer::Song *currentSong = NULL;

	void
	audio_callback(void *none, Uint8 *_stream, int _length)
	{

		Sint16 *stream = (Sint16 *)_stream;
		int length = _length / 2;

		int i = 0;
		if (beepTones.empty())
		{
			while (i < length)
			{
				stream[i] = 0;
				i++;
			}
			return;
		}

		while (i < length)
		{
			BeepTone &tone = beepTones.front();

			int samplesToDo = min(i + tone.samplesLeft, length);
			tone.samplesLeft -= samplesToDo - i;

			while (i < samplesToDo)
			{
				stream[i] = AMPLITUDE * sin(v * 2 * M_PI / FREQUENCY);
				i++;
				v += tone.frequency;
			}

			if (tone.samplesLeft == 0)
			{
				beepTones.pop();
			}
		}
	}

	void sleep(int sleepTimeInMs)
	{
#if defined USE_NATIVE && (defined _WIN32 || defined _WIN64 || defined __MINGW32__)
		Sleep(sleepTimeInMs);
#else
		SDL_Delay(sleepTimeInMs);
#endif
	}

	void beep(int frequency, int duration)
	{
#if defined USE_NATIVE && (defined _WIN32 || defined _WIN64 || defined __MINGW32__)
		Beep(frequency, duration);
#else
		BeepTone beepTone;
		beepTone.frequency = frequency;
		beepTone.samplesLeft = duration * FREQUENCY / 1000.0;

		SDL_LockAudioDevice(audioDevice);
		beepTones.push(beepTone);
		SDL_UnlockAudioDevice(audioDevice);

#endif
	}

	void start()
	{
		return;
		if (initialized)
		{
			SDL_Log("BeepPlayer already initialized");
			return;
		}

		if (initializing)
		{
			SDL_Log("BeepPlayer initialization is already in progress");
			return;
		}

		initializing = true;

		SDL_AudioSpec desiredSpec;
		SDL_memset(&desiredSpec, 0, sizeof(desiredSpec));
		desiredSpec.freq = FREQUENCY;
		desiredSpec.format = AUDIO_S16SYS;
		desiredSpec.channels = 1;
		desiredSpec.samples = 1024 * 4;
		desiredSpec.callback = audio_callback;

		SDL_AudioSpec obtainedSpec;

		audioDevice = SDL_OpenAudioDevice(NULL, 0, &desiredSpec, &obtainedSpec, 0);
		if (audioDevice < 2)
		{
			SDL_Log("Failed to open audio device: %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		else
		{
			if (obtainedSpec.format != desiredSpec.format)
			{
				SDL_Log("Desired format differs from expected format");
			}
			SDL_PauseAudioDevice(audioDevice, 0);
		}

		initialized = true;
		initializing = false;
	}

	void stop()
	{
		if (initializing)
		{
			SDL_Log("BeepPlayer stop is not possible as initializing is in progress");
			return;
		}

		if (initialized)
		{
			if (audioDevice >= 2)
			{
				SDL_CloseAudioDevice(audioDevice);
			}
			initialized = false;
		}
	}

	void playSong(const BeepPlayer::Song &song)
	{
		currentSong = (BeepPlayer::Song *)&song;
		for (auto note : song.notes)
		{
			if (note.frequence == BeepPlayer::NoteFrequencie::PAUSE)
			{
				beep(0, note.noteValue.getDurationBy(song.tact));
			}
			else
			{
				beep(static_cast<int>(note.frequence), note.noteValue.getDurationBy(song.tact));
			}
		}
	}

	bool isSongFinished()
	{
		int size = 0;
		SDL_LockAudioDevice(audioDevice);
		size = beepTones.size();
		SDL_UnlockAudioDevice(audioDevice);
		return size == 0;
	}

	void repeatCurrentFinishedSong()
	{
		if (currentSong != NULL)
		{
			if (isSongFinished())
			{
				BeepPlayer::playSong(*currentSong);
			}
		}
	}

	void waitForSongCompletion()
	{
		int size;
		do
		{
			SDL_Delay(10);
			SDL_LockAudioDevice(audioDevice);
			size = beepTones.size();
			SDL_UnlockAudioDevice(audioDevice);

		} while (size > 0);
	}
};
